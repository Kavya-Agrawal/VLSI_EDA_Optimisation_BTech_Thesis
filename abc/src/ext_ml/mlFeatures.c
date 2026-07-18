/**CFile****************************************************************

  FileName    [mlFeatures.c]

  PackageName [SYNAPSE: neural optimization co-processor for ABC.]

  Synopsis    [Feature extraction from a GIA (Gia_Man_t) AIG.]

  Notes       [Produces the ML_NODE_FEAT_DIM node feature matrix and the
               ML_DIV_FEAT_DIM candidate pair features consumed by the
               inference layer and by offline training data generation.
               All numeric features are normalized to roughly [0,1].
               The feature order MUST match python/config.py.]

***********************************************************************/

#include <math.h>

#include "aig/gia/gia.h"
#include "ml_abc.h"

ABC_NAMESPACE_IMPL_START

////////////////////////////////////////////////////////////////////////
///                     HELPER COMPUTATIONS                            ///
////////////////////////////////////////////////////////////////////////

// safe division
static inline float Ml_SafeDiv( float a, float b ) { return b > 0 ? a / b : 0.0f; }
static inline float Ml_Log1p( float x )            { return (float)log(1.0 + (x < 0 ? 0 : x)); }
// local 32-bit popcount (avoid depending on external Extra_* symbols)
static inline int   Ml_PopCount32( unsigned w )
{
    w = w - ((w >> 1) & 0x55555555);
    w = (w & 0x33333333) + ((w >> 2) & 0x33333333);
    w = (w + (w >> 4)) & 0x0F0F0F0F;
    return (int)((w * 0x01010101) >> 24);
}

/**Function*************************************************************

  Synopsis    [Compute per-object auxiliary arrays used by the features.]

  Description [Fanout counts, PO-driving fanout counts, reverse levels
               (depth to outputs). Levels are taken from GIA (vLevels).
               Everything is O(nObjs) or O(edges).]

***********************************************************************/
static void Ml_GiaComputeAux( Gia_Man_t * p, int * pFanout, int * pFanoutPo,
                              int * pFanoutCompl, int * pRevLevel )
{
    Gia_Obj_t * pObj;
    int i, nObjs = Gia_ManObjNum(p);
    for ( i = 0; i < nObjs; i++ )
    {
        pFanout[i] = pFanoutPo[i] = pFanoutCompl[i] = pRevLevel[i] = 0;
    }
    // fanout counts from AND nodes
    Gia_ManForEachAnd( p, pObj, i )
    {
        int id0 = Gia_ObjFaninId0( pObj, i );
        int id1 = Gia_ObjFaninId1( pObj, i );
        pFanout[id0]++; pFanout[id1]++;
        pFanoutCompl[id0] += Gia_ObjFaninC0(pObj);
        pFanoutCompl[id1] += Gia_ObjFaninC1(pObj);
    }
    // CO drivers add fanout and mark PO-driving
    {
        int c;
        for ( c = 0; c < Gia_ManCoNum(p); c++ )
        {
            int drv = Gia_ObjFaninId0p( p, Gia_ManCo(p, c) );
            pFanout[drv]++;
            pFanoutPo[drv]++;
        }
    }
    // reverse levels: iterate ANDs in reverse topological order
    Gia_ManForEachAndReverse( p, pObj, i )
    {
        int id0 = Gia_ObjFaninId0( pObj, i );
        int id1 = Gia_ObjFaninId1( pObj, i );
        int rl  = pRevLevel[i] + 1;
        if ( pRevLevel[id0] < rl ) pRevLevel[id0] = rl;
        if ( pRevLevel[id1] < rl ) pRevLevel[id1] = rl;
    }
}

// cheap MFFC-size proxy: 1 + fanins that are ANDs with fanout==1
static int Ml_MffcProxy( Gia_Man_t * p, Gia_Obj_t * pObj, int i, int * pFanout )
{
    int n = 1;
    int id0 = Gia_ObjFaninId0( pObj, i );
    int id1 = Gia_ObjFaninId1( pObj, i );
    if ( Gia_ObjIsAnd( Gia_ManObj(p, id0) ) && pFanout[id0] == 1 ) n++;
    if ( Gia_ObjIsAnd( Gia_ManObj(p, id1) ) && pFanout[id1] == 1 ) n++;
    return n;
}

// local reconvergence proxy: the two fanins share a common fanin id
static int Ml_ReconvProxy( Gia_Man_t * p, Gia_Obj_t * pObj, int i )
{
    Gia_Obj_t * pF0, * pF1;
    int id0 = Gia_ObjFaninId0( pObj, i );
    int id1 = Gia_ObjFaninId1( pObj, i );
    pF0 = Gia_ManObj( p, id0 );
    pF1 = Gia_ManObj( p, id1 );
    if ( !Gia_ObjIsAnd(pF0) || !Gia_ObjIsAnd(pF1) )
        return 0;
    {
        int a0 = Gia_ObjFaninId0( pF0, id0 ), a1 = Gia_ObjFaninId1( pF0, id0 );
        int b0 = Gia_ObjFaninId0( pF1, id1 ), b1 = Gia_ObjFaninId1( pF1, id1 );
        return ( a0 == b0 || a0 == b1 || a1 == b0 || a1 == b1 ) ? 1 : 0;
    }
}

// radius-2 AND-fanin count proxy (local density)
static int Ml_R2Count( Gia_Man_t * p, Gia_Obj_t * pObj, int i )
{
    int cnt = 0, k;
    int ids[2];
    ids[0] = Gia_ObjFaninId0( pObj, i );
    ids[1] = Gia_ObjFaninId1( pObj, i );
    for ( k = 0; k < 2; k++ )
    {
        Gia_Obj_t * pF = Gia_ManObj( p, ids[k] );
        if ( !Gia_ObjIsAnd(pF) ) continue;
        cnt++;
        if ( Gia_ObjIsAnd( Gia_ManObj(p, Gia_ObjFaninId0(pF, ids[k])) ) ) cnt++;
        if ( Gia_ObjIsAnd( Gia_ManObj(p, Gia_ObjFaninId1(pF, ids[k])) ) ) cnt++;
    }
    return cnt;
}

////////////////////////////////////////////////////////////////////////
///                     PUBLIC: NODE FEATURES                          ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Extract the node feature matrix for the whole GIA.]

  Description [Returns nObjs*ML_NODE_FEAT_DIM row-major floats; non-AND rows
               are zeroed. Caller frees with ABC_FREE. See docs/DESIGN.md 4.]

***********************************************************************/
float * Ml_GiaExtractNodeFeatures( void * pGiaVoid, int * pnObjs )
{
    Gia_Man_t * p = (Gia_Man_t *)pGiaVoid;
    Gia_Obj_t * pObj;
    float * pFeat;
    int * pFanout, * pFanoutPo, * pFanoutCompl, * pRevLevel;
    int i, nObjs, maxLevel, maxFanout = 1;

    nObjs = Gia_ManObjNum( p );
    if ( pnObjs ) *pnObjs = nObjs;

    maxLevel = Gia_ManLevelNum( p );          // ensures p->vLevels is populated
    if ( maxLevel <= 0 ) maxLevel = 1;

    pFeat        = ABC_CALLOC( float, (size_t)nObjs * ML_NODE_FEAT_DIM );
    pFanout      = ABC_ALLOC( int, nObjs );
    pFanoutPo    = ABC_ALLOC( int, nObjs );
    pFanoutCompl = ABC_ALLOC( int, nObjs );
    pRevLevel    = ABC_ALLOC( int, nObjs );

    Ml_GiaComputeAux( p, pFanout, pFanoutPo, pFanoutCompl, pRevLevel );
    for ( i = 0; i < nObjs; i++ )
        if ( pFanout[i] > maxFanout ) maxFanout = pFanout[i];

    Gia_ManForEachAnd( p, pObj, i )
    {
        float * f = pFeat + (size_t)i * ML_NODE_FEAT_DIM;
        int id0 = Gia_ObjFaninId0( pObj, i );
        int id1 = Gia_ObjFaninId1( pObj, i );
        int lev = Gia_ObjLevelId( p, i );
        int rev = pRevLevel[i];
        int mffc = Ml_MffcProxy( p, pObj, i, pFanout );
        int r2   = Ml_R2Count( p, pObj, i );

        f[0]  = Ml_SafeDiv( (float)lev, (float)maxLevel );
        f[1]  = Ml_SafeDiv( (float)rev, (float)maxLevel );
        f[2]  = Ml_SafeDiv( Ml_Log1p((float)pFanout[i]), Ml_Log1p((float)maxFanout) );
        f[3]  = (float)Gia_ObjFaninC0( pObj );
        f[4]  = (float)Gia_ObjFaninC1( pObj );
        f[5]  = (float)Gia_ObjIsCi( Gia_ManObj(p, id0) );
        f[6]  = (float)Gia_ObjIsCi( Gia_ManObj(p, id1) );
        f[7]  = Ml_SafeDiv( Ml_Log1p((float)mffc), Ml_Log1p(3.0f) );
        f[8]  = Ml_SafeDiv( (float)pFanoutPo[i], (float)pFanout[i] );
        f[9]  = Ml_SafeDiv( (float)(maxLevel - lev), (float)maxLevel );
        f[10] = Ml_SafeDiv( (float)lev, (float)maxLevel );   // dist-to-PI proxy
        f[11] = Ml_SafeDiv( Ml_Log1p((float)r2), Ml_Log1p(6.0f) );
        f[12] = Ml_SafeDiv( (float)pFanoutCompl[i], (float)pFanout[i] );
        f[13] = ( lev + rev >= maxLevel ) ? 1.0f : 0.0f;     // on a longest path
        f[14] = (float)Ml_ReconvProxy( p, pObj, i );
        f[15] = 1.0f;                                        // bias
    }

    ABC_FREE( pFanout );
    ABC_FREE( pFanoutPo );
    ABC_FREE( pFanoutCompl );
    ABC_FREE( pRevLevel );
    return pFeat;
}

////////////////////////////////////////////////////////////////////////
///                  PUBLIC: CANDIDATE PAIR FEATURES                   ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Fill one divisor/candidate pair-feature row.]

  Description [Relational features between a root node and a candidate
               divisor: level gap, structural signals, and simulation
               signature agreement (Hamming similarity over sim words).
               pRootSim/pCandSim may be NULL (then sim features are 0).]

***********************************************************************/
void Ml_FillPairFeatures( void * pGiaVoid, int RootId, int CandId,
                          unsigned * pRootSim, unsigned * pCandSim,
                          int nSimWords, float * pOut )
{
    Gia_Man_t * p = (Gia_Man_t *)pGiaVoid;
    int i, agree = 0, nBits = 32 * (nSimWords > 0 ? nSimWords : 0);
    int levR = Gia_ObjLevelId( p, RootId );
    int levC = Gia_ObjLevelId( p, CandId );
    int maxLevel = Gia_ManLevelNum( p );
    if ( maxLevel <= 0 ) maxLevel = 1;

    for ( i = 0; i < ML_DIV_FEAT_DIM; i++ ) pOut[i] = 0.0f;

    // simulation-signature agreement (functional similarity)
    if ( pRootSim && pCandSim && nSimWords > 0 )
    {
        int w, same = 0;
        for ( w = 0; w < nSimWords; w++ )
            same += 32 - Ml_PopCount32( pRootSim[w] ^ pCandSim[w] );
        agree = same;
    }

    pOut[0]  = Ml_SafeDiv( (float)(levR - levC), (float)maxLevel ); // level gap
    pOut[1]  = Ml_SafeDiv( (float)levC, (float)maxLevel );          // cand depth
    pOut[2]  = ( CandId < RootId ) ? 1.0f : 0.0f;                   // is in TFI (topo)
    pOut[3]  = ( levC < levR ) ? 1.0f : 0.0f;                       // shallower than root
    pOut[4]  = nBits ? Ml_SafeDiv( (float)agree, (float)nBits ) : 0.0f; // sim agree
    pOut[5]  = nBits ? Ml_SafeDiv( (float)(nBits - agree), (float)nBits ) : 0.0f; // disagree
    pOut[6]  = (float)abs( levR - levC ) / (float)maxLevel;         // |level gap|
    pOut[7]  = ( Gia_ObjIsCi( Gia_ManObj(p, CandId) ) ) ? 1.0f : 0.0f; // cand is CI
    pOut[8]  = ( Gia_ObjIsAnd( Gia_ManObj(p, CandId) ) ) ? 1.0f : 0.0f; // cand is AND
    pOut[9]  = Ml_SafeDiv( (float)(RootId - CandId), (float)Gia_ManObjNum(p) ); // id distance
    pOut[10] = ( agree * 2 > nBits ) ? 1.0f : 0.0f;                 // positive-unate hint
    pOut[11] = 1.0f;                                                // bias
}

////////////////////////////////////////////////////////////////////////
///                  PUBLIC: DUMP FEATURES TO FILE                     ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Dump the node-feature matrix + edge list of the current GIA.]

  Description [Simple text format consumed by python/data/dataset.py:
                 line 1: "NODES <n> <feat_dim>"
                 n lines: "<id> f0 f1 ... f15"
                 line   : "EDGES <m>"
                 m lines: "<src> <dst> <compl>"
               Only AND nodes are emitted as feature rows; edges are the
               two fanin edges of each AND node.]

***********************************************************************/
int Ml_GiaDumpFeatures( void * pGiaVoid, const char * pFileName )
{
    Gia_Man_t * p = (Gia_Man_t *)pGiaVoid;
    Gia_Obj_t * pObj;
    FILE * pFile;
    float * pFeat;
    int i, k, nObjs = 0, nEdges = 0;

    pFile = fopen( pFileName, "wb" );
    if ( pFile == NULL )
        return 0;

    pFeat = Ml_GiaExtractNodeFeatures( p, &nObjs );

    // count edges (2 per AND)
    Gia_ManForEachAnd( p, pObj, i ) nEdges += 2;

    fprintf( pFile, "NODES %d %d\n", Gia_ManAndNum(p), ML_NODE_FEAT_DIM );
    Gia_ManForEachAnd( p, pObj, i )
    {
        float * f = pFeat + (size_t)i * ML_NODE_FEAT_DIM;
        fprintf( pFile, "%d", i );
        for ( k = 0; k < ML_NODE_FEAT_DIM; k++ )
            fprintf( pFile, " %.6f", f[k] );
        fprintf( pFile, "\n" );
    }

    fprintf( pFile, "EDGES %d\n", nEdges );
    Gia_ManForEachAnd( p, pObj, i )
    {
        fprintf( pFile, "%d %d %d\n", Gia_ObjFaninId0(pObj, i), i, Gia_ObjFaninC0(pObj) );
        fprintf( pFile, "%d %d %d\n", Gia_ObjFaninId1(pObj, i), i, Gia_ObjFaninC1(pObj) );
    }

    ABC_FREE( pFeat );
    fclose( pFile );
    return 1;
}

ABC_NAMESPACE_IMPL_END

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                  ///
////////////////////////////////////////////////////////////////////////
