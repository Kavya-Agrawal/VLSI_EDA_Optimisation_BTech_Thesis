/**CFile****************************************************************

  FileName    [polyTruth.c]

  PackageName [POLYPHONY]

  Synopsis    [Exact truth-table evaluation + GIA decode for circuit programs.]

  Notes       [For k<=6, a 64-bit word covers the full TT. Evaluation is pure
               bitwise AND/NOT over elementary variable TTs -- microsecond-fast
               and the exactness guarantee of the whole system.]

***********************************************************************/

#include "aig/gia/gia.h"
#include "poly_abc.h"

ABC_NAMESPACE_IMPL_START

////////////////////////////////////////////////////////////////////////
///                     INTERNAL HELPERS                               ///
////////////////////////////////////////////////////////////////////////

// Elementary variable truth tables for nVars<=6 (standard ABC ordering).
static word Poly_VarTruth( int v, int nVars )
{
    // Period of 1s for variable v in a 2^nVars table.
    // Matches Kit / ABC convention: var0 flips every 1, var1 every 2, etc.
    static word s_Truths6[6] = {
        ABC_CONST(0xAAAAAAAAAAAAAAAA),
        ABC_CONST(0xCCCCCCCCCCCCCCCC),
        ABC_CONST(0xF0F0F0F0F0F0F0F0),
        ABC_CONST(0xFF00FF00FF00FF00),
        ABC_CONST(0xFFFF0000FFFF0000),
        ABC_CONST(0xFFFFFFFF00000000)
    };
    (void)nVars;
    assert( v >= 0 && v < 6 );
    return s_Truths6[v];
}

static inline word Poly_Mask( int nVars )
{
    if ( nVars >= 6 ) return ~(word)0;
    return ((word)1 << (1 << nVars)) - 1;
}

////////////////////////////////////////////////////////////////////////
///                     PUBLIC API                                     ///
////////////////////////////////////////////////////////////////////////

int Poly_ProgEvalTruth( Poly_Prog_t * pProg, word * pOutTruth )
{
    word NodeTT[POLY_MAX_VARS + POLY_MAX_GATES];
    int i, nVars, nGates, lit, var, compl;
    word t;

    if ( !pProg || !pOutTruth ) return 0;
    nVars  = pProg->nVars;
    nGates = pProg->nGates;
    if ( nVars < 1 || nVars > POLY_MAX_VARS ) return 0;
    if ( nGates < 0 || nGates > POLY_MAX_GATES ) return 0;

    for ( i = 0; i < nVars; i++ )
        NodeTT[i] = Poly_VarTruth( i, nVars );

    for ( i = 0; i < nGates; i++ )
    {
        word a, b;
        lit = pProg->LitA[i];
        var = Abc_Lit2Var( lit ); compl = Abc_LitIsCompl( lit );
        if ( var < 0 || var >= nVars + i ) return 0;   // forward reference illegal
        a = NodeTT[var]; if ( compl ) a = ~a;

        lit = pProg->LitB[i];
        var = Abc_Lit2Var( lit ); compl = Abc_LitIsCompl( lit );
        if ( var < 0 || var >= nVars + i ) return 0;
        b = NodeTT[var]; if ( compl ) b = ~b;

        NodeTT[nVars + i] = a & b;
    }

    lit = pProg->OutLit;
    var = Abc_Lit2Var( lit ); compl = Abc_LitIsCompl( lit );
    if ( var < 0 || var >= nVars + nGates ) return 0;
    t = NodeTT[var]; if ( compl ) t = ~t;

    *pOutTruth = t & Poly_Mask( nVars );
    return 1;
}

int Poly_ProgIsEquivalent( Poly_Prog_t * pProg, word Target )
{
    word got;
    if ( !Poly_ProgEvalTruth( pProg, &got ) )
        return 0;
    return (got & Poly_Mask( pProg->nVars )) == (Target & Poly_Mask( pProg->nVars ));
}

void * Poly_ProgToGia( Poly_Prog_t * pProg )
{
    Gia_Man_t * pNew;
    int i, * pLits, lit;
    if ( !pProg ) return NULL;

    pNew = Gia_ManStart( pProg->nVars + pProg->nGates + 2 );
    Gia_ManHashAlloc( pNew );
    pLits = ABC_ALLOC( int, pProg->nVars + pProg->nGates );

    for ( i = 0; i < pProg->nVars; i++ )
        pLits[i] = Gia_ManAppendCi( pNew );

    for ( i = 0; i < pProg->nGates; i++ )
    {
        int aVar = Abc_Lit2Var( pProg->LitA[i] );
        int bVar = Abc_Lit2Var( pProg->LitB[i] );
        int aLit = Abc_LitNotCond( pLits[aVar], Abc_LitIsCompl( pProg->LitA[i] ) );
        int bLit = Abc_LitNotCond( pLits[bVar], Abc_LitIsCompl( pProg->LitB[i] ) );
        pLits[pProg->nVars + i] = Gia_ManHashAnd( pNew, aLit, bLit );
    }

    lit = Abc_LitNotCond( pLits[Abc_Lit2Var(pProg->OutLit)], Abc_LitIsCompl(pProg->OutLit) );
    Gia_ManAppendCo( pNew, lit );
    Gia_ManHashStop( pNew );
    ABC_FREE( pLits );
    return (void *)pNew;
}

ABC_NAMESPACE_IMPL_END
