/**CFile****************************************************************

  FileName    [mlCmd.c]

  PackageName [SYNAPSE: neural optimization co-processor for ABC.]

  Synopsis    [Command suite, registrar, and decision hooks.]

  Commands    [ml_config, ml_features, ml_potential, ml_resub, ml_stats]

***********************************************************************/

#include "base/main/main.h"
#include "base/main/mainInt.h"
#include "base/cmd/cmd.h"
#include "base/abc/abc.h"
#include "aig/gia/gia.h"
#include "misc/extra/extra.h"
#include "ml_abc.h"

ABC_NAMESPACE_IMPL_START

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                                ///
////////////////////////////////////////////////////////////////////////

// globalUtilOptarg / Extra_UtilGetopt come from misc/extra/extra.h.

static int Ml_CommandConfig   ( Abc_Frame_t * pAbc, int argc, char ** argv );
static int Ml_CommandFeatures ( Abc_Frame_t * pAbc, int argc, char ** argv );
static int Ml_CommandPotential( Abc_Frame_t * pAbc, int argc, char ** argv );
static int Ml_CommandResub    ( Abc_Frame_t * pAbc, int argc, char ** argv );
static int Ml_CommandStats    ( Abc_Frame_t * pAbc, int argc, char ** argv );

////////////////////////////////////////////////////////////////////////
///                         REGISTRAR                                  ///
////////////////////////////////////////////////////////////////////////

void Ml_Register( Abc_Frame_t * pAbc )
{
    Cmd_CommandAdd( pAbc, "SYNAPSE", "ml_config",    Ml_CommandConfig,    0 );
    Cmd_CommandAdd( pAbc, "SYNAPSE", "ml_features",  Ml_CommandFeatures,  0 );
    Cmd_CommandAdd( pAbc, "SYNAPSE", "ml_potential", Ml_CommandPotential, 0 );
    Cmd_CommandAdd( pAbc, "SYNAPSE", "ml_resub",     Ml_CommandResub,     1 );
    Cmd_CommandAdd( pAbc, "SYNAPSE", "ml_stats",     Ml_CommandStats,     0 );
}

////////////////////////////////////////////////////////////////////////
///                        ml_config                                   ///
////////////////////////////////////////////////////////////////////////

static int Ml_CommandConfig( Abc_Frame_t * pAbc, int argc, char ** argv )
{
    Ml_Man_t * p = Ml_ManGet();
    int c;
    Extra_UtilGetoptReset();
    while ( ( c = Extra_UtilGetopt( argc, argv, "edvm:c:xh" ) ) != EOF )
    {
        switch ( c )
        {
        case 'e': p->fEnabled = 1; break;
        case 'd': p->fEnabled = 0; break;
        case 'v': p->fVerbose ^= 1; break;
        case 'm':
            ABC_FREE( p->pModelPath );
            p->pModelPath = Abc_UtilStrsav( (char *)globalUtilOptarg );
            p->Backend = ML_BACKEND_ONNX;
            Ml_InferQuit( p );
            Ml_InferInit( p );          // try to (re)load the ONNX model
            break;
        case 'c':
            Ml_CollectOpen( p, globalUtilOptarg );
            break;
        case 'x':
            Ml_CollectClose( p );
            break;
        case 'h': goto usage;
        default:  goto usage;
        }
    }
    Abc_Print( 1, "SYNAPSE config: enabled=%d verbose=%d backend=%s%s%s collect=%d\n",
        p->fEnabled, p->fVerbose,
        p->Backend == ML_BACKEND_ONNX ? "onnx" : "fallback",
        p->pModelPath ? " model=" : "", p->pModelPath ? p->pModelPath : "",
        p->fCollect );
    if ( p->Backend == ML_BACKEND_ONNX && p->pOnnx == NULL )
        Abc_Print( 0, "  (ONNX model not loaded; using analytic fallback)\n" );
    return 0;
usage:
    Abc_Print( -2, "usage: ml_config [-edvxh] [-m <model.onnx>] [-c <data.csv>]\n" );
    Abc_Print( -2, "\t          configure the SYNAPSE neural co-processor\n" );
    Abc_Print( -2, "\t-e      : enable ML-guided hooks\n" );
    Abc_Print( -2, "\t-d      : disable (revert to stock ABC behaviour)\n" );
    Abc_Print( -2, "\t-v      : toggle verbose logging\n" );
    Abc_Print( -2, "\t-m file : load a trained ONNX model (needs ABC_USE_ONNX build)\n" );
    Abc_Print( -2, "\t-c file : start dumping training data to file\n" );
    Abc_Print( -2, "\t-x      : stop dumping training data\n" );
    Abc_Print( -2, "\t-h      : print the command usage\n" );
    return 1;
}

////////////////////////////////////////////////////////////////////////
///                        ml_features                                 ///
////////////////////////////////////////////////////////////////////////

static int Ml_CommandFeatures( Abc_Frame_t * pAbc, int argc, char ** argv )
{
    Gia_Man_t * pGia = (Gia_Man_t *)Abc_FrameReadGia( pAbc );
    char * pOut = (char *)"synapse_features.txt";
    int c;
    Extra_UtilGetoptReset();
    while ( ( c = Extra_UtilGetopt( argc, argv, "o:h" ) ) != EOF )
    {
        switch ( c )
        {
        case 'o': pOut = (char *)globalUtilOptarg; break;
        case 'h': goto usage;
        default:  goto usage;
        }
    }
    if ( pGia == NULL )
    {
        Abc_Print( -1, "ml_features: no GIA. Run \"&get\" (or \"&r file.aig\") first.\n" );
        return 1;
    }
    if ( !Ml_GiaDumpFeatures( pGia, pOut ) )
    {
        Abc_Print( -1, "ml_features: could not write \"%s\".\n", pOut );
        return 1;
    }
    Abc_Print( 1, "SYNAPSE: wrote node features + edges to \"%s\".\n", pOut );
    return 0;
usage:
    Abc_Print( -2, "usage: ml_features [-o <file>] [-h]\n" );
    Abc_Print( -2, "\t         dump the current GIA node-feature matrix and edges\n" );
    Abc_Print( -2, "\t-o file: output file (default synapse_features.txt)\n" );
    return 1;
}

////////////////////////////////////////////////////////////////////////
///                        ml_potential                                ///
////////////////////////////////////////////////////////////////////////

static int Ml_CommandPotential( Abc_Frame_t * pAbc, int argc, char ** argv )
{
    Ml_Man_t * p = Ml_ManGet();
    Gia_Man_t * pGia = (Gia_Man_t *)Abc_FrameReadGia( pAbc );
    Gia_Obj_t * pObj;
    float * pFeat; int i, nObjs = 0, nTop = 10, c;
    int * pBestId; float * pBestVal; int nHave = 0;

    Extra_UtilGetoptReset();
    while ( ( c = Extra_UtilGetopt( argc, argv, "N:h" ) ) != EOF )
    {
        switch ( c )
        {
        case 'N': nTop = atoi( globalUtilOptarg ); break;
        case 'h': goto usage;
        default:  goto usage;
        }
    }
    if ( pGia == NULL )
    {
        Abc_Print( -1, "ml_potential: no GIA. Run \"&get\" first.\n" );
        return 1;
    }
    if ( nTop < 1 ) nTop = 1;
    pFeat = Ml_GiaExtractNodeFeatures( pGia, &nObjs );
    pBestId  = ABC_CALLOC( int, nTop );
    pBestVal = ABC_CALLOC( float, nTop );

    Gia_ManForEachAnd( pGia, pObj, i )
    {
        float v = Ml_InferPotential( p, pFeat + (size_t)i * ML_NODE_FEAT_DIM );
        // insert into the small top-N buffer
        if ( nHave < nTop || v > pBestVal[nTop-1] )
        {
            int j = (nHave < nTop) ? nHave++ : nTop-1;
            for ( ; j > 0 && pBestVal[j-1] < v; j-- )
            {
                pBestVal[j] = pBestVal[j-1];
                pBestId[j]  = pBestId[j-1];
            }
            pBestVal[j] = v;
            pBestId[j]  = i;
        }
    }

    Abc_Print( 1, "SYNAPSE non-myopic node potential (backend=%s), top %d of %d ANDs:\n",
        p->Backend == ML_BACKEND_ONNX ? "onnx" : "fallback", nHave, Gia_ManAndNum(pGia) );
    for ( i = 0; i < nHave; i++ )
        Abc_Print( 1, "  #%-8d  potential=%.4f\n", pBestId[i], pBestVal[i] );

    ABC_FREE( pFeat );
    ABC_FREE( pBestId );
    ABC_FREE( pBestVal );
    return 0;
usage:
    Abc_Print( -2, "usage: ml_potential [-N <num>] [-h]\n" );
    Abc_Print( -2, "\t         score GIA nodes by predicted (non-myopic) value\n" );
    Abc_Print( -2, "\t-N num : how many top nodes to print (default 10)\n" );
    return 1;
}

////////////////////////////////////////////////////////////////////////
///                        ml_resub                                    ///
////////////////////////////////////////////////////////////////////////

// Turn on ML guidance, run the (classic) resub pass with the divisor-rerank
// hook live, then restore the previous enable state.
static int Ml_CommandResub( Abc_Frame_t * pAbc, int argc, char ** argv )
{
    Ml_Man_t * p = Ml_ManGet();
    int fWas = p->fEnabled, c;
    char Cmd[64] = "resub";
    Extra_UtilGetoptReset();
    while ( ( c = Extra_UtilGetopt( argc, argv, "h" ) ) != EOF )
    {
        switch ( c ) { case 'h': default: goto usage; }
    }
    if ( Abc_FrameReadNtk( pAbc ) == NULL )
    {
        Abc_Print( -1, "ml_resub: no current network.\n" );
        return 1;
    }
    p->fEnabled = 1;                     // arm the resub hook
    Cmd_CommandExecute( pAbc, Cmd );     // run stock resub; hook reranks divisors
    p->fEnabled = fWas;
    Abc_Print( 1, "SYNAPSE: ML-guided resub complete (%d divisor sets reranked).\n",
        p->nCandsReranked );
    return 0;
usage:
    Abc_Print( -2, "usage: ml_resub [-h]\n" );
    Abc_Print( -2, "\t     run resubstitution with SYNAPSE divisor reranking\n" );
    return 1;
}

////////////////////////////////////////////////////////////////////////
///                        ml_stats                                    ///
////////////////////////////////////////////////////////////////////////

static int Ml_CommandStats( Abc_Frame_t * pAbc, int argc, char ** argv )
{
    Ml_Man_t * p = Ml_ManGet();
    Abc_Print( 1, "SYNAPSE runtime counters:\n" );
    Abc_Print( 1, "  nodes scored      : %d\n", p->nNodesScored );
    Abc_Print( 1, "  candidates reranked: %d\n", p->nCandsReranked );
    Abc_Print( 1, "  windows gated      : %d (skipped %d)\n", p->nWindowsGated, p->nWindowsSkipped );
    return 0;
}

////////////////////////////////////////////////////////////////////////
///                     DECISION HOOKS                                 ///
////////////////////////////////////////////////////////////////////////

int Ml_HookResubActive()
{
    Ml_Man_t * p = Ml_ManGet();
    return p->fEnabled;
}

// Build a small pair-feature vector for a classic-network divisor.
static void Ml_ClassicPair( Abc_Ntk_t * pNtk, Abc_Obj_t * pRoot, Abc_Obj_t * pDiv, float * pair )
{
    int i, maxId = Abc_NtkObjNumMax( pNtk );
    int levR = Abc_ObjLevel( pRoot ), levD = Abc_ObjLevel( pDiv );
    int maxL = Abc_AigLevel( pNtk ); if ( maxL <= 0 ) maxL = 1;
    for ( i = 0; i < ML_DIV_FEAT_DIM; i++ ) pair[i] = 0.0f;
    pair[0]  = (float)(levR - levD) / (float)maxL;
    pair[1]  = (float)levD / (float)maxL;
    pair[2]  = ( Abc_ObjId(pDiv) < Abc_ObjId(pRoot) ) ? 1.0f : 0.0f;  // TFI proxy
    pair[3]  = ( levD < levR ) ? 1.0f : 0.0f;
    pair[6]  = (float)abs( levR - levD ) / (float)maxL;
    pair[8]  = Abc_ObjIsNode(pDiv) ? 1.0f : 0.0f;
    pair[9]  = maxId ? (float)abs( (int)Abc_ObjId(pRoot) - (int)Abc_ObjId(pDiv) ) / (float)maxId : 0.0f;
    pair[11] = 1.0f;
}

void Ml_HookResubRerank( void * pNtkVoid, void * pRootVoid, void * vDivsVoid )
{
    Ml_Man_t * p = Ml_ManGet();
    Abc_Ntk_t * pNtk  = (Abc_Ntk_t *)pNtkVoid;
    Abc_Obj_t * pRoot = (Abc_Obj_t *)pRootVoid;
    Vec_Ptr_t * vDivs = (Vec_Ptr_t *)vDivsVoid;
    int i, j, n;
    float * pScore;

    if ( !p->fEnabled || vDivs == NULL || pRoot == NULL )
        return;
    n = Vec_PtrSize( vDivs );
    if ( n < 3 )
        return;                          // nothing meaningful to reorder

    pScore = ABC_ALLOC( float, n );
    for ( i = 0; i < n; i++ )
    {
        float pair[ML_DIV_FEAT_DIM];
        Abc_Obj_t * pDiv = (Abc_Obj_t *)Vec_PtrEntry( vDivs, i );
        Ml_ClassicPair( pNtk, pRoot, pDiv, pair );
        pScore[i] = Ml_InferRankScore( p, NULL, NULL, pair );
        if ( p->fCollect )
            Ml_CollectRow( p, ML_TASK_RESUB_DIV, pair, ML_DIV_FEAT_DIM, 0.0 );
    }
    // stable insertion sort by descending score (n is small: <=150)
    for ( i = 1; i < n; i++ )
    {
        float sv = pScore[i];
        void * dv = Vec_PtrEntry( vDivs, i );
        for ( j = i; j > 0 && pScore[j-1] < sv; j-- )
        {
            pScore[j] = pScore[j-1];
            Vec_PtrWriteEntry( vDivs, j, Vec_PtrEntry( vDivs, j-1 ) );
        }
        pScore[j] = sv;
        Vec_PtrWriteEntry( vDivs, j, dv );
    }
    ABC_FREE( pScore );
    p->nCandsReranked++;
    if ( p->fVerbose )
        Abc_Print( 1, "  [synapse] reranked %d divisors for node %d\n", n, Abc_ObjId(pRoot) );
}

ABC_NAMESPACE_IMPL_END

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                  ///
////////////////////////////////////////////////////////////////////////
