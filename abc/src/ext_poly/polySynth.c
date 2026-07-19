/**CFile****************************************************************

  FileName    [polySynth.c]

  PackageName [POLYPHONY]

  Synopsis    [Non-neural fallback synthesizer: produce diverse verified
               equivalents of a k-input truth table (k<=6).]

  Notes       [Strategies:
                 1. Shannon expansion on each variable (nVars variants)
                 2. Direct AND/OR/XOR recognition for simple TTs
                 3. Randomized SOP-ish AND-OR builds with different term orders
               Every candidate is checked with Poly_ProgIsEquivalent before
               being kept -- exactness is never compromised.]

***********************************************************************/

#include <string.h>
#include "poly_abc.h"

ABC_NAMESPACE_IMPL_START

////////////////////////////////////////////////////////////////////////
///                     SMALL HELPERS                                  ///
////////////////////////////////////////////////////////////////////////

static inline word Poly_MaskN( int nVars )
{
    if ( nVars >= 6 ) return ~(word)0;
    return ((word)1 << (1 << nVars)) - 1;
}

static void Poly_ProgClear( Poly_Prog_t * p, int nVars )
{
    int i;
    memset( p, 0, sizeof(*p) );
    p->nVars = nVars;
    p->OutLit = 0;
    for ( i = 0; i < POLY_MAX_GATES; i++ )
        p->LitA[i] = p->LitB[i] = 0;
}

static int Poly_ProgAddAnd( Poly_Prog_t * p, int litA, int litB )
{
    int g;
    if ( p->nGates >= POLY_MAX_GATES ) return -1;
    g = p->nGates++;
    p->LitA[g] = litA;
    p->LitB[g] = litB;
    p->nSize = p->nGates;
    return Abc_Var2Lit( p->nVars + g, 0 );
}

// Keep if equivalent and not a duplicate of an already-kept program.
static int Poly_TryKeep( Poly_Prog_t * cand, word Target,
                         Poly_Prog_t * pOut, int nHave, int nMax )
{
    int i;
    if ( nHave >= nMax ) return nHave;
    if ( !Poly_ProgIsEquivalent( cand, Target ) ) return nHave;
    for ( i = 0; i < nHave; i++ )
    {
        if ( pOut[i].nGates == cand->nGates &&
             pOut[i].OutLit == cand->OutLit &&
             memcmp( pOut[i].LitA, cand->LitA, sizeof(int)*cand->nGates ) == 0 &&
             memcmp( pOut[i].LitB, cand->LitB, sizeof(int)*cand->nGates ) == 0 )
            return nHave; // duplicate
    }
    pOut[nHave] = *cand;
    return nHave + 1;
}

////////////////////////////////////////////////////////////////////////
///                     STRATEGY 1: constants / single lit             ///
////////////////////////////////////////////////////////////////////////

static int Poly_SynthConstOrLit( int nVars, word Target,
                                 Poly_Prog_t * pOut, int nHave, int nMax )
{
    Poly_Prog_t p;
    word mask = Poly_MaskN( nVars );
    int v;

    if ( (Target & mask) == 0 )
    {
        Poly_ProgClear( &p, nVars );
        p.OutLit = Abc_Var2Lit( 0, 1 ); // ~x0 & x0 style? use const0 via x&~x
        // Build const0 = x0 & ~x0
        Poly_ProgClear( &p, nVars );
        p.OutLit = Poly_ProgAddAnd( &p, Abc_Var2Lit(0,0), Abc_Var2Lit(0,1) );
        nHave = Poly_TryKeep( &p, Target, pOut, nHave, nMax );
    }
    if ( (Target & mask) == mask )
    {
        // const1 = ~(x0 & ~x0)
        Poly_ProgClear( &p, nVars );
        {
            int z = Poly_ProgAddAnd( &p, Abc_Var2Lit(0,0), Abc_Var2Lit(0,1) );
            p.OutLit = Abc_LitNot( z );
        }
        nHave = Poly_TryKeep( &p, Target, pOut, nHave, nMax );
    }
    // single PI or ~PI
    for ( v = 0; v < nVars; v++ )
    {
        word tv = 0;
        Poly_ProgClear( &p, nVars );
        p.OutLit = Abc_Var2Lit( v, 0 );
        if ( Poly_ProgEvalTruth( &p, &tv ) && (tv & mask) == (Target & mask) )
            nHave = Poly_TryKeep( &p, Target, pOut, nHave, nMax );

        Poly_ProgClear( &p, nVars );
        p.OutLit = Abc_Var2Lit( v, 1 );
        if ( Poly_ProgEvalTruth( &p, &tv ) && (tv & mask) == (Target & mask) )
            nHave = Poly_TryKeep( &p, Target, pOut, nHave, nMax );
    }
    return nHave;
}

////////////////////////////////////////////////////////////////////////
///                     STRATEGY 2: 2-input AND/OR/XOR                 ///
////////////////////////////////////////////////////////////////////////

static int Poly_SynthTwoInput( int nVars, word Target,
                               Poly_Prog_t * pOut, int nHave, int nMax )
{
    int a, b, ca, cb;
    Poly_Prog_t p;
    if ( nVars < 2 ) return nHave;
    for ( a = 0; a < nVars; a++ )
    for ( b = a + 1; b < nVars; b++ )
    for ( ca = 0; ca < 2; ca++ )
    for ( cb = 0; cb < 2; cb++ )
    {
        int litA = Abc_Var2Lit( a, ca );
        int litB = Abc_Var2Lit( b, cb );
        // AND
        Poly_ProgClear( &p, nVars );
        p.OutLit = Poly_ProgAddAnd( &p, litA, litB );
        nHave = Poly_TryKeep( &p, Target, pOut, nHave, nMax );
        // OR = ~(~a & ~b)
        Poly_ProgClear( &p, nVars );
        {
            int t = Poly_ProgAddAnd( &p, Abc_LitNot(litA), Abc_LitNot(litB) );
            p.OutLit = Abc_LitNot( t );
        }
        nHave = Poly_TryKeep( &p, Target, pOut, nHave, nMax );
        // XOR = (a|b) & ~(a&b)
        Poly_ProgClear( &p, nVars );
        {
            int aandb = Poly_ProgAddAnd( &p, litA, litB );
            int nor   = Poly_ProgAddAnd( &p, Abc_LitNot(litA), Abc_LitNot(litB) );
            int aorb  = Abc_LitNot( nor );
            p.OutLit  = Poly_ProgAddAnd( &p, aorb, Abc_LitNot(aandb) );
        }
        nHave = Poly_TryKeep( &p, Target, pOut, nHave, nMax );
        if ( nHave >= nMax ) return nHave;
    }
    return nHave;
}

////////////////////////////////////////////////////////////////////////
///                     STRATEGY 3: Shannon expansions                 ///
////////////////////////////////////////////////////////////////////////

// Recursively build f = ~x_v & f0 | x_v & f1 as an AIG program.
// For the prototype we expand one level and implement cofactors as
// minterm OR-of-ANDs (exact but not minimal -- diversity source #1).

static int Poly_BuildMintermSOP( Poly_Prog_t * p, int nVars, word Target )
{
    int nMinterms = 1 << nVars;
    int m, first = -1;
    word mask = Poly_MaskN( nVars );
    Target &= mask;

    for ( m = 0; m < nMinterms; m++ )
    {
        int litAnd = -1, v;
        if ( !((Target >> m) & 1) ) continue;
        // AND of literals for this minterm
        for ( v = 0; v < nVars; v++ )
        {
            int lit = Abc_Var2Lit( v, !((m >> v) & 1) );
            if ( litAnd < 0 ) litAnd = lit;
            else              litAnd = Poly_ProgAddAnd( p, litAnd, lit );
            if ( litAnd < 0 ) return -1;
        }
        if ( first < 0 ) first = litAnd;
        else
        {
            // OR = ~(~a & ~b)
            int t = Poly_ProgAddAnd( p, Abc_LitNot(first), Abc_LitNot(litAnd) );
            if ( t < 0 ) return -1;
            first = Abc_LitNot( t );
        }
    }
    if ( first < 0 )
    {
        // const0
        first = Poly_ProgAddAnd( p, Abc_Var2Lit(0,0), Abc_Var2Lit(0,1) );
    }
    p->OutLit = first;
    return 0;
}

static int Poly_SynthShannonAndSOP( int nVars, word Target,
                                    Poly_Prog_t * pOut, int nHave, int nMax )
{
    Poly_Prog_t p;
    int pivot;

    // Full SOP
    Poly_ProgClear( &p, nVars );
    if ( Poly_BuildMintermSOP( &p, nVars, Target ) == 0 )
        nHave = Poly_TryKeep( &p, Target, pOut, nHave, nMax );

    // Shannon on each pivot: f = ~x f0 + x f1, with SOP cofactors
    for ( pivot = 0; pivot < nVars && nHave < nMax; pivot++ )
    {
        word f0 = 0, f1 = 0, bit;
        int m, nM = 1 << nVars;
        int litF0, litF1, t;
        Poly_Prog_t p0, p1;

        for ( m = 0; m < nM; m++ )
        {
            if ( !((Target >> m) & 1) ) continue;
            bit = (word)1 << (m & ~(1 << pivot));  // clear pivot bit in index for cofactor packing is messy;
            // Simpler: extract cofactor by evaluating Target with x_pivot fixed.
            (void)bit;
        }
        // Extract cofactors properly: for each assignment of the other vars
        {
            int nOther = nVars; // we'll just rebuild SOP for restricted TTs
            word t0 = 0, t1 = 0;
            int nHalf = 1 << (nVars - 1);
            // Use simulation-style: for each full minterm
            for ( m = 0; m < nM; m++ )
            {
                if ( !((Target >> m) & 1) ) continue;
                if ( (m >> pivot) & 1 ) t1 |= ((word)1 << m);
                else                    t0 |= ((word)1 << m);
            }
            // Build two SOPs then MUX: out = ~xp&f0 | xp&f1
            Poly_ProgClear( &p0, nVars );
            Poly_ProgClear( &p1, nVars );
            if ( Poly_BuildMintermSOP( &p0, nVars, t0 ) != 0 ) continue;
            if ( Poly_BuildMintermSOP( &p1, nVars, t1 ) != 0 ) continue;

            // Merge p0 and p1 into p: copy gates, remap is identity since shared PI namespace
            Poly_ProgClear( &p, nVars );
            {
                int g;
                int map0[POLY_MAX_GATES], map1[POLY_MAX_GATES];
                for ( g = 0; g < p0.nGates; g++ )
                {
                    int nl = Poly_ProgAddAnd( &p, p0.LitA[g], p0.LitB[g] );
                    map0[g] = Abc_Lit2Var( nl );
                    (void)map0;
                }
                litF0 = p0.OutLit; // still valid: PIs same, AND ids shifted? NO - we appended in order
                // Actually because we appended p0 gates first, OutLit of p0 still refers to correct nodes.
                litF0 = p0.OutLit;
                for ( g = 0; g < p1.nGates; g++ )
                {
                    // Remap gate fanins that pointed to p1's AND nodes
                    int a = p1.LitA[g], b = p1.LitB[g];
                    int aV = Abc_Lit2Var(a), bV = Abc_Lit2Var(b);
                    if ( aV >= nVars ) a = Abc_Var2Lit( aV + p0.nGates, Abc_LitIsCompl(a) );
                    if ( bV >= nVars ) b = Abc_Var2Lit( bV + p0.nGates, Abc_LitIsCompl(b) );
                    Poly_ProgAddAnd( &p, a, b );
                    map1[g] = p.nGates - 1;
                    (void)map1;
                }
                {
                    int oV = Abc_Lit2Var( p1.OutLit );
                    if ( oV >= nVars ) litF1 = Abc_Var2Lit( oV + p0.nGates, Abc_LitIsCompl(p1.OutLit) );
                    else              litF1 = p1.OutLit;
                }
                // out = (~xp & f0) | (xp & f1)
                {
                    int a0 = Poly_ProgAddAnd( &p, Abc_Var2Lit(pivot,1), litF0 );
                    int a1 = Poly_ProgAddAnd( &p, Abc_Var2Lit(pivot,0), litF1 );
                    t = Poly_ProgAddAnd( &p, Abc_LitNot(a0), Abc_LitNot(a1) );
                    p.OutLit = Abc_LitNot( t );
                }
            }
            nHave = Poly_TryKeep( &p, Target, pOut, nHave, nMax );
            (void)nHalf; (void)t0; (void)t1;
        }
    }
    return nHave;
}

////////////////////////////////////////////////////////////////////////
///                     STRATEGY 4: random AND-OR variants             ///
////////////////////////////////////////////////////////////////////////

static unsigned Poly_Rng = 0xA5A5F00Du;
static unsigned Poly_Rand()
{
    Poly_Rng ^= Poly_Rng << 13;
    Poly_Rng ^= Poly_Rng >> 17;
    Poly_Rng ^= Poly_Rng << 5;
    return Poly_Rng;
}

static int Poly_SynthRandom( int nVars, word Target,
                             Poly_Prog_t * pOut, int nHave, int nMax, int nTries )
{
    int t;
    for ( t = 0; t < nTries && nHave < nMax; t++ )
    {
        Poly_Prog_t p;
        int g, nGates = 1 + (Poly_Rand() % (nVars + 3));
        if ( nGates > POLY_MAX_GATES ) nGates = POLY_MAX_GATES;
        Poly_ProgClear( &p, nVars );
        for ( g = 0; g < nGates; g++ )
        {
            int maxNode = nVars + g;
            int a = Poly_Rand() % maxNode;
            int b = Poly_Rand() % maxNode;
            int ca = Poly_Rand() & 1;
            int cb = Poly_Rand() & 1;
            Poly_ProgAddAnd( &p, Abc_Var2Lit(a, ca), Abc_Var2Lit(b, cb) );
        }
        {
            int o = Poly_Rand() % (nVars + nGates);
            p.OutLit = Abc_Var2Lit( o, Poly_Rand() & 1 );
        }
        nHave = Poly_TryKeep( &p, Target, pOut, nHave, nMax );
    }
    return nHave;
}

////////////////////////////////////////////////////////////////////////
///                     PUBLIC                                         ///
////////////////////////////////////////////////////////////////////////

int Poly_SynthFallback( int nVars, word Target, Poly_Prog_t * pOut, int nMax )
{
    int nHave = 0;
    if ( !pOut || nMax <= 0 ) return 0;
    if ( nVars < 1 || nVars > POLY_MAX_VARS ) return 0;

    nHave = Poly_SynthConstOrLit( nVars, Target, pOut, nHave, nMax );
    nHave = Poly_SynthTwoInput( nVars, Target, pOut, nHave, nMax );
    nHave = Poly_SynthShannonAndSOP( nVars, Target, pOut, nHave, nMax );
    nHave = Poly_SynthRandom( nVars, Target, pOut, nHave, nMax, 64 );
    return nHave;
}

ABC_NAMESPACE_IMPL_END
