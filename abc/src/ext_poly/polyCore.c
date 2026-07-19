/**CFile****************************************************************

  FileName    [polyCore.c]

  PackageName [POLYPHONY]

  Synopsis    [Singleton manager + auto-registration with the ABC frame.]

***********************************************************************/

#include "base/main/main.h"
#include "base/main/mainInt.h"
#include "base/cmd/cmd.h"
#include "poly_abc.h"

ABC_NAMESPACE_IMPL_START

static Poly_Man_t * s_pPoly = NULL;

extern void Poly_Register( Abc_Frame_t * pAbc );

Poly_Man_t * Poly_ManGet()
{
    if ( s_pPoly ) return s_pPoly;
    s_pPoly = ABC_CALLOC( Poly_Man_t, 1 );
    s_pPoly->fEnabled  = 0;
    s_pPoly->fVerbose  = 0;
    s_pPoly->nSamples  = 8;
    s_pPoly->nKeep     = 4;
    s_pPoly->nMaxGates = 16;
    return s_pPoly;
}

void Poly_ManFree()
{
    if ( !s_pPoly ) return;
    ABC_FREE( s_pPoly->pModelPath );
    ABC_FREE( s_pPoly );
    s_pPoly = NULL;
}

static void Poly_FrameInit( Abc_Frame_t * pAbc ) { Poly_Register( pAbc ); }
static void Poly_FrameQuit( Abc_Frame_t * pAbc ) { (void)pAbc; Poly_ManFree(); }

static Abc_FrameInitializer_t s_PolyInit =
{
    Poly_FrameInit,
    Poly_FrameQuit,
    NULL, NULL
};

void Poly_ModuleBootstrap()
{
    Abc_FrameAddInitializer( &s_PolyInit );
}

#if defined(__GNUC__) || defined(__clang__)
__attribute__((constructor))
static void Poly_AutoBootstrap() { Poly_ModuleBootstrap(); }
#endif

ABC_NAMESPACE_IMPL_END
