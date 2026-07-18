/**CFile****************************************************************

  FileName    [mlCore.c]

  PackageName [SYNAPSE: neural optimization co-processor for ABC.]

  Synopsis    [Singleton manager, configuration, and module bootstrap.]

  Notes       [The module self-registers before main() via a constructor
               that installs an Abc_FrameInitializer_t, so no edits to the
               giant abc.c are required. See docs/INTEGRATION.md.]

***********************************************************************/

#include "base/main/main.h"
#include "base/main/mainInt.h"
#include "base/cmd/cmd.h"
#include "ml_abc.h"

ABC_NAMESPACE_IMPL_START

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                                ///
////////////////////////////////////////////////////////////////////////

static Ml_Man_t * s_pMlMan = NULL;   // process-wide singleton

// Implemented in mlCmd.c (declared here where Abc_Frame_t is in scope).
extern void Ml_Register( Abc_Frame_t * pAbc );

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                           ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Lazy accessor for the SYNAPSE manager.]

  Description [Allocates on first use with safe defaults: disabled, fallback
               backend, no data collection. Turning it on is done via the
               'ml_config' command so stock ABC behaviour is untouched.]

***********************************************************************/
Ml_Man_t * Ml_ManGet()
{
    int i;
    if ( s_pMlMan != NULL )
        return s_pMlMan;
    s_pMlMan = ABC_CALLOC( Ml_Man_t, 1 );
    s_pMlMan->fEnabled    = 0;
    s_pMlMan->fVerbose    = 0;
    s_pMlMan->fCollect    = 0;
    s_pMlMan->Backend     = ML_BACKEND_FALLBACK;
    s_pMlMan->pModelPath  = NULL;
    s_pMlMan->pOnnx       = NULL;
    s_pMlMan->pCollectPath= NULL;
    s_pMlMan->pCollectFile= NULL;
    // Analytic-fallback weights: a transparent linear proxy of "node value".
    // These mirror what a trained PotentialHead is expected to emphasize
    // (MFFC ownership, level slack, reuse pressure). See docs/DESIGN.md 2.
    for ( i = 0; i < ML_NODE_FEAT_DIM; i++ )
        s_pMlMan->AnalyticW[i] = 0.0;
    s_pMlMan->AnalyticW[2]  =  0.35; // fanout / reuse pressure
    s_pMlMan->AnalyticW[7]  =  0.60; // MFFC size (how much this node owns)
    s_pMlMan->AnalyticW[9]  =  0.25; // level slack
    s_pMlMan->AnalyticW[11] =  0.20; // local density
    s_pMlMan->AnalyticW[14] =  0.30; // reconvergence -> resub/mfs opportunity
    Ml_InferInit( s_pMlMan );
    return s_pMlMan;
}

/**Function*************************************************************

  Synopsis    [Releases the singleton and any backend resources.]

***********************************************************************/
void Ml_ManFree()
{
    if ( s_pMlMan == NULL )
        return;
    Ml_CollectClose( s_pMlMan );
    Ml_InferQuit( s_pMlMan );
    ABC_FREE( s_pMlMan->pModelPath );
    ABC_FREE( s_pMlMan->pCollectPath );
    ABC_FREE( s_pMlMan );
    s_pMlMan = NULL;
}

/**Function*************************************************************

  Synopsis    [Frame initializer hooks: start/stop with the ABC frame.]

***********************************************************************/
static void Ml_FrameInit( Abc_Frame_t * pAbc )
{
    Ml_Register( pAbc );          // add ml_* commands to the command table
}

static void Ml_FrameQuit( Abc_Frame_t * pAbc )
{
    Ml_ManFree();
}

// The initializer record; registered before main() by the constructor below.
static Abc_FrameInitializer_t s_MlFrameInit =
{
    Ml_FrameInit,   // pInitCallback
    Ml_FrameQuit,   // pDestCallback
    NULL, NULL      // linked-list pointers (filled by Abc_FrameAddInitializer)
};

/**Function*************************************************************

  Synopsis    [Automatic registration before main() (GCC/Clang constructor).]

  Description [Under MSVC (no __attribute__((constructor))) the fallback is
               to call Ml_ModuleBootstrap() explicitly from your embedding
               code, or add the initializer from Abc_Init. Both paths are
               documented in docs/INTEGRATION.md.]

***********************************************************************/
void Ml_ModuleBootstrap()
{
    Abc_FrameAddInitializer( &s_MlFrameInit );
}

#if defined(__GNUC__) || defined(__clang__)
__attribute__((constructor))
static void Ml_AutoBootstrap() { Ml_ModuleBootstrap(); }
#endif

ABC_NAMESPACE_IMPL_END

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                  ///
////////////////////////////////////////////////////////////////////////
