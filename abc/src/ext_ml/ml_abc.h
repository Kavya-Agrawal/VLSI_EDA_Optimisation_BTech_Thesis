/**CFile****************************************************************

  FileName    [ml_abc.h]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [SYNAPSE: neural optimization co-processor for ABC.]

  Synopsis    [Public API + shared feature specification for the ext_ml module.]

  Author      [SYNAPSE research prototype]

  Affiliation [BTP - ML for EDA]

  Notes       [This header is the single source of truth for feature
               dimensions on the C side; it MUST stay in sync with
               python/config.py. See docs/DESIGN.md section 4.]

***********************************************************************/

#ifndef ABC__ext_ml__ml_abc_h
#define ABC__ext_ml__ml_abc_h

////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                  ///
////////////////////////////////////////////////////////////////////////

#include "misc/util/abc_global.h"

ABC_NAMESPACE_HEADER_START

////////////////////////////////////////////////////////////////////////
///                         PARAMETERS                                 ///
////////////////////////////////////////////////////////////////////////

// Feature dimensions -- keep identical to python/config.py
#define ML_NODE_FEAT_DIM   16   // per-node structural + functional features
#define ML_DIV_FEAT_DIM    12   // per-candidate (divisor/cut/window) pair features
#define ML_EDGE_ATTR_DIM    1   // per-edge attribute (fanin complement bit)
#define ML_EMB_DIM         64   // encoder embedding width (cached per node)

// Operating modes for the inference backend
typedef enum {
    ML_BACKEND_FALLBACK = 0,    // built-in analytic model (no ML deps)
    ML_BACKEND_ONNX     = 1     // ONNX Runtime loaded from a trained model
} Ml_Backend_t;

// Which decision the ranker is scoring (lets one head serve several passes)
typedef enum {
    ML_TASK_POTENTIAL = 0,      // node value (non-myopic)
    ML_TASK_RESUB_DIV = 1,      // resubstitution divisor ranking
    ML_TASK_MFS_WINDOW = 2,     // don't-care window pay-off gating
    ML_TASK_CUT_RANK  = 3       // technology-mapping cut ranking
} Ml_Task_t;

////////////////////////////////////////////////////////////////////////
///                    STRUCTURE DEFINITIONS                           ///
////////////////////////////////////////////////////////////////////////

// Global configuration / session state (singleton, owned by mlCore.c)
typedef struct Ml_Man_t_ Ml_Man_t;
struct Ml_Man_t_
{
    int            fEnabled;        // master on/off (hooks are no-ops when 0)
    int            fVerbose;        // logging
    int            fCollect;        // dump training data at decision points
    Ml_Backend_t   Backend;         // fallback vs onnx
    char *         pModelPath;      // path to synapse.onnx (onnx backend)
    void *         pOnnx;           // opaque Ml_Onnx_t* (see mlInfer.c), or NULL
    char *         pCollectPath;    // where ml_collect dumps features
    void *         pCollectFile;    // FILE* handle while collecting
    // running counters (for ml_stats)
    int            nNodesScored;
    int            nCandsReranked;
    int            nWindowsGated;
    int            nWindowsSkipped;
    double         AnalyticW[ML_NODE_FEAT_DIM]; // fallback linear weights
};

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DECLARATIONS                          ///
////////////////////////////////////////////////////////////////////////

/*=== mlCore.c ===============================================================*/
extern Ml_Man_t *  Ml_ManGet();                    // lazy singleton accessor
extern void        Ml_ManFree();
// Ml_Register( Abc_Frame_t * ) is declared in mlCore.c / mlCmd.c where the
// frame type is visible (kept out of this header to avoid an extra include).

/*=== mlFeatures.c ===========================================================*/
// Extract ML_NODE_FEAT_DIM features for every object id (0..nObjs-1); non-AND
// rows are zeroed. Returns a freshly-allocated float array of size
// nObjs*ML_NODE_FEAT_DIM (row-major). Caller frees with ABC_FREE.
extern float *     Ml_GiaExtractNodeFeatures( void * pGia, int * pnObjs );
// Fill one divisor/candidate pair-feature row (ML_DIV_FEAT_DIM floats).
extern void        Ml_FillPairFeatures( void * pGia, int RootId, int CandId,
                                        unsigned * pRootSim, unsigned * pCandSim,
                                        int nSimWords, float * pOut );
// Convenience: dump the whole current GIA feature matrix + edges to a file.
extern int         Ml_GiaDumpFeatures( void * pGia, const char * pFileName );

/*=== mlInfer.c ==============================================================*/
extern void        Ml_InferInit( Ml_Man_t * p );   // load onnx or arm fallback
extern void        Ml_InferQuit( Ml_Man_t * p );
// Non-myopic node value from a node feature row.
extern float       Ml_InferPotential( Ml_Man_t * p, const float * pNodeFeat );
// Candidate score (higher = try first). pPairFeat has ML_DIV_FEAT_DIM entries.
extern float       Ml_InferRankScore( Ml_Man_t * p, const float * pRootFeat,
                                      const float * pCandFeat, const float * pPairFeat );
// Window pay-off probability in [0,1] for mfs gating.
extern float       Ml_InferWindowPayoff( Ml_Man_t * p, const float * pNodeFeat );

/*=== mlData.c ===============================================================*/
extern void        Ml_CollectOpen( Ml_Man_t * p, const char * pFileName );
extern void        Ml_CollectClose( Ml_Man_t * p );
extern void        Ml_CollectRow( Ml_Man_t * p, Ml_Task_t Task,
                                  const float * pFeat, int nFeat, double Label );

/*=== mlCmd.c (command implementations, registered from mlCore.c) ============*/
// (declared static in mlCmd.c; only the registrar is exported via Ml_Register)

/*=== hook entry points used by patched core passes (e.g. abcResub.c) ========*/
// Returns 1 if the ML resub-divisor reranking hook is active.
extern int         Ml_HookResubActive();
// Reorder the divisor vector (Vec_Ptr_t of Abc_Obj_t*) in-place by predicted
// payoff so promising divisors are tried first. No-op unless enabled; NEVER
// changes correctness (ABC's exact checks still validate every attempt).
extern void        Ml_HookResubRerank( void * pNtk, void * pRoot, void * vDivs );

ABC_NAMESPACE_HEADER_END

#endif

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                  ///
////////////////////////////////////////////////////////////////////////
