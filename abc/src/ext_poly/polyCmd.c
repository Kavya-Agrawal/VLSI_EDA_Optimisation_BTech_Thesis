/**CFile****************************************************************

  FileName    [polyCmd.c]

  PackageName [POLYPHONY]

  Synopsis    [Commands: poly_config / poly_extract / poly_synth / poly_stats.]

***********************************************************************/

#include "base/main/main.h"
#include "base/main/mainInt.h"
#include "base/cmd/cmd.h"
#include "aig/gia/gia.h"
#include "misc/extra/extra.h"
#include "poly_abc.h"

ABC_NAMESPACE_IMPL_START

static int Poly_CommandConfig ( Abc_Frame_t * pAbc, int argc, char ** argv );
static int Poly_CommandExtract( Abc_Frame_t * pAbc, int argc, char ** argv );
static int Poly_CommandSynth  ( Abc_Frame_t * pAbc, int argc, char ** argv );
static int Poly_CommandStats  ( Abc_Frame_t * pAbc, int argc, char ** argv );

void Poly_Register( Abc_Frame_t * pAbc )
{
    Cmd_CommandAdd( pAbc, "POLYPHONY", "poly_config",  Poly_CommandConfig,  0 );
    Cmd_CommandAdd( pAbc, "POLYPHONY", "poly_extract", Poly_CommandExtract, 0 );
    Cmd_CommandAdd( pAbc, "POLYPHONY", "poly_synth",   Poly_CommandSynth,   0 );
    Cmd_CommandAdd( pAbc, "POLYPHONY", "poly_stats",   Poly_CommandStats,   0 );
}

static int Poly_CommandConfig( Abc_Frame_t * pAbc, int argc, char ** argv )
{
    Poly_Man_t * p = Poly_ManGet();
    int c;
    Extra_UtilGetoptReset();
    while ( ( c = Extra_UtilGetopt( argc, argv, "edvn:k:g:h" ) ) != EOF )
    {
        switch ( c )
        {
        case 'e': p->fEnabled = 1; break;
        case 'd': p->fEnabled = 0; break;
        case 'v': p->fVerbose ^= 1; break;
        case 'n': p->nSamples = atoi( globalUtilOptarg ); break;
        case 'k': p->nKeep    = atoi( globalUtilOptarg ); break;
        case 'g': p->nMaxGates= atoi( globalUtilOptarg ); break;
        case 'h': default: goto usage;
        }
    }
    Abc_Print( 1, "POLYPHONY: enabled=%d verbose=%d samples=%d keep=%d max_gates=%d\n",
        p->fEnabled, p->fVerbose, p->nSamples, p->nKeep, p->nMaxGates );
    return 0;
usage:
    Abc_Print( -2, "usage: poly_config [-edvh] [-n num] [-k num] [-g num]\n" );
    Abc_Print( -2, "\t-e/-d  : enable / disable\n" );
    Abc_Print( -2, "\t-n num : samples to try per cut\n" );
    Abc_Print( -2, "\t-k num : max equivalents to keep\n" );
    Abc_Print( -2, "\t-g num : max gates per program\n" );
    return 1;
}

static int Poly_CommandExtract( Abc_Frame_t * pAbc, int argc, char ** argv )
{
    Poly_Man_t * p = Poly_ManGet();
    Gia_Man_t * pGia = Abc_FrameReadGia( pAbc );
    Poly_Cut_t * pCuts;
    int n, i, c, nShow = 5;
    Extra_UtilGetoptReset();
    while ( ( c = Extra_UtilGetopt( argc, argv, "N:h" ) ) != EOF )
    {
        switch ( c )
        {
        case 'N': nShow = atoi( globalUtilOptarg ); break;
        case 'h': default: goto usage;
        }
    }
    if ( !pGia )
    {
        Abc_Print( -1, "poly_extract: no GIA. Run \"&get\" first.\n" );
        return 1;
    }
    pCuts = ABC_CALLOC( Poly_Cut_t, POLY_MAX_CUTS );
    n = Poly_GiaExtractCuts( pGia, pCuts, POLY_MAX_CUTS );
    p->nCutsSeen += n;
    Abc_Print( 1, "POLYPHONY: extracted %d cuts (showing up to %d):\n", n, nShow );
    for ( i = 0; i < n && i < nShow; i++ )
        Abc_Print( 1, "  cut#%d root=%d leaves=%d truth=0x%016llx\n",
            i, pCuts[i].RootId, pCuts[i].nLeaves, (unsigned long long)pCuts[i].Truth );
    ABC_FREE( pCuts );
    return 0;
usage:
    Abc_Print( -2, "usage: poly_extract [-N num] [-h]\n" );
    return 1;
}

static int Poly_CommandSynth( Abc_Frame_t * pAbc, int argc, char ** argv )
{
    Poly_Man_t * p = Poly_ManGet();
    Poly_Prog_t progs[POLY_MAX_PROGRAMS];
    int nVars = 3, n, i, c;
    word Target = 0;
    int fHasT = 0;
    Extra_UtilGetoptReset();
    while ( ( c = Extra_UtilGetopt( argc, argv, "K:T:h" ) ) != EOF )
    {
        switch ( c )
        {
        case 'K': nVars = atoi( globalUtilOptarg ); break;
        case 'T':
            Target = (word)strtoull( globalUtilOptarg, NULL, 0 );
            fHasT = 1;
            break;
        case 'h': default: goto usage;
        }
    }
    if ( nVars < 1 || nVars > POLY_MAX_VARS )
    {
        Abc_Print( -1, "poly_synth: K must be in 1..%d\n", POLY_MAX_VARS );
        return 1;
    }
    // default demo TT: XOR of all inputs (or AND if K=1)
    if ( !fHasT )
    {
        int m, nM = 1 << nVars;
        Target = 0;
        for ( m = 0; m < nM; m++ )
        {
            int bits = 0, v;
            for ( v = 0; v < nVars; v++ ) bits ^= (m >> v) & 1;
            if ( bits ) Target |= ((word)1 << m);
        }
    }
    n = Poly_SynthFallback( nVars, Target, progs, p->nKeep > 0 ? p->nKeep : POLY_MAX_PROGRAMS );
    p->nProgsTried += 64; // fallback tries internally
    p->nProgsKept  += n;
    p->nEquivFound += n;
    Abc_Print( 1, "POLYPHONY: K=%d target=0x%016llx -> %d verified equivalent programs:\n",
        nVars, (unsigned long long)Target, n );
    for ( i = 0; i < n; i++ )
    {
        word got = 0;
        Poly_ProgEvalTruth( &progs[i], &got );
        Abc_Print( 1, "  prog#%d gates=%d out_lit=%d truth=0x%016llx %s\n",
            i, progs[i].nGates, progs[i].OutLit, (unsigned long long)got,
            Poly_ProgIsEquivalent( &progs[i], Target ) ? "OK" : "FAIL" );
    }
    return 0;
usage:
    Abc_Print( -2, "usage: poly_synth [-K num] [-T hex] [-h]\n" );
    Abc_Print( -2, "\t-K num : number of inputs (default 3)\n" );
    Abc_Print( -2, "\t-T hex : target truth table (default = XOR)\n" );
    return 1;
}

static int Poly_CommandStats( Abc_Frame_t * pAbc, int argc, char ** argv )
{
    Poly_Man_t * p = Poly_ManGet();
    Abc_Print( 1, "POLYPHONY stats: cuts=%d tried=%d kept=%d equiv=%d\n",
        p->nCutsSeen, p->nProgsTried, p->nProgsKept, p->nEquivFound );
    return 0;
}

ABC_NAMESPACE_IMPL_END
