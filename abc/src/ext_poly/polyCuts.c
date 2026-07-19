/**CFile****************************************************************

  FileName    [polyCuts.c]

  PackageName [POLYPHONY]

  Synopsis    [Extract small k-input cuts + truth tables from a GIA.]

***********************************************************************/

#include <string.h>
#include "aig/gia/gia.h"
#include "poly_abc.h"

ABC_NAMESPACE_IMPL_START

static word Poly_VarTT( int v )
{
    static word s_Truths6[6] = {
        ABC_CONST(0xAAAAAAAAAAAAAAAA),
        ABC_CONST(0xCCCCCCCCCCCCCCCC),
        ABC_CONST(0xF0F0F0F0F0F0F0F0),
        ABC_CONST(0xFF00FF00FF00FF00),
        ABC_CONST(0xFFFF0000FFFF0000),
        ABC_CONST(0xFFFFFFFF00000000)
    };
    return s_Truths6[v];
}

static word Poly_MaskN( int n )
{
    if ( n >= 6 ) return ~(word)0;
    return ((word)1 << (1 << n)) - 1;
}

// Recursively collect up to k leaves in the TFI; fail if support grows past k.
static int Poly_CollectSupport( Gia_Man_t * p, int iObj, int * pLeaves, int * pnLeaves, int nMax )
{
    Gia_Obj_t * pObj = Gia_ManObj( p, iObj );
    int i, id0, id1;
    if ( Gia_ObjIsCi(pObj) || iObj == 0 )
    {
        for ( i = 0; i < *pnLeaves; i++ )
            if ( pLeaves[i] == iObj ) return 1;
        if ( *pnLeaves >= nMax ) return 0;
        pLeaves[(*pnLeaves)++] = iObj;
        return 1;
    }
    if ( !Gia_ObjIsAnd(pObj) ) return 0;
    id0 = Gia_ObjFaninId0( pObj, iObj );
    id1 = Gia_ObjFaninId1( pObj, iObj );
    if ( !Poly_CollectSupport( p, id0, pLeaves, pnLeaves, nMax ) ) return 0;
    if ( !Poly_CollectSupport( p, id1, pLeaves, pnLeaves, nMax ) ) return 0;
    return 1;
}

static word Poly_ComputeTruth( Gia_Man_t * p, int iRoot, int * pLeaves, int nLeaves )
{
    int nObjs = Gia_ManObjNum(p);
    word * pTT;
    int * pDone;
    int i, id0, id1;
    Gia_Obj_t * pObj;
    word res;

    pTT   = ABC_ALLOC( word, nObjs );
    pDone = ABC_CALLOC( int, nObjs );
    for ( i = 0; i < nObjs; i++ ) pTT[i] = 0;

    for ( i = 0; i < nLeaves; i++ )
    {
        pTT[pLeaves[i]] = Poly_VarTT( i );
        pDone[pLeaves[i]] = 1;
    }
    pTT[0] = 0; pDone[0] = 1;

    // topo eval via DFS stack simulation: iterate objects 1..root
    for ( i = 1; i <= iRoot; i++ )
    {
        pObj = Gia_ManObj( p, i );
        if ( pDone[i] ) continue;
        if ( !Gia_ObjIsAnd(pObj) ) continue;
        id0 = Gia_ObjFaninId0( pObj, i );
        id1 = Gia_ObjFaninId1( pObj, i );
        if ( !pDone[id0] || !pDone[id1] ) continue; // incomplete; will retry below
        {
            word a = pTT[id0], b = pTT[id1];
            if ( Gia_ObjFaninC0(pObj) ) a = ~a;
            if ( Gia_ObjFaninC1(pObj) ) b = ~b;
            pTT[i] = a & b;
            pDone[i] = 1;
        }
    }
    // second pass for any missed (should be rare with topo ids)
    for ( i = 1; i <= iRoot; i++ )
    {
        pObj = Gia_ManObj( p, i );
        if ( pDone[i] || !Gia_ObjIsAnd(pObj) ) continue;
        id0 = Gia_ObjFaninId0( pObj, i );
        id1 = Gia_ObjFaninId1( pObj, i );
        if ( pDone[id0] && pDone[id1] )
        {
            word a = pTT[id0], b = pTT[id1];
            if ( Gia_ObjFaninC0(pObj) ) a = ~a;
            if ( Gia_ObjFaninC1(pObj) ) b = ~b;
            pTT[i] = a & b;
            pDone[i] = 1;
        }
    }

    res = pDone[iRoot] ? (pTT[iRoot] & Poly_MaskN( nLeaves )) : 0;
    ABC_FREE( pTT );
    ABC_FREE( pDone );
    return res;
}

int Poly_GiaExtractCuts( void * pGiaVoid, Poly_Cut_t * pCuts, int nMaxCuts )
{
    Gia_Man_t * p = (Gia_Man_t *)pGiaVoid;
    Gia_Obj_t * pObj;
    int i, n = 0, k;
    if ( !p || !pCuts || nMaxCuts <= 0 ) return 0;

    Gia_ManForEachAnd( p, pObj, i )
    {
        int leaves[POLY_MAX_VARS];
        int nLeaves = 0;
        if ( n >= nMaxCuts ) break;
        // try support sizes 2..6
        for ( k = 2; k <= POLY_MAX_VARS; k++ )
        {
            nLeaves = 0;
            if ( !Poly_CollectSupport( p, i, leaves, &nLeaves, k ) )
                continue;
            if ( nLeaves < 2 || nLeaves > k ) continue;
            // accept only exact size match for diversity of cut sizes
            if ( nLeaves != k && k < POLY_MAX_VARS ) continue;
            pCuts[n].RootId  = i;
            pCuts[n].nLeaves = nLeaves;
            memcpy( pCuts[n].Leaves, leaves, sizeof(int) * nLeaves );
            pCuts[n].Truth = Poly_ComputeTruth( p, i, leaves, nLeaves );
            n++;
            break;
        }
    }
    return n;
}

ABC_NAMESPACE_IMPL_END
