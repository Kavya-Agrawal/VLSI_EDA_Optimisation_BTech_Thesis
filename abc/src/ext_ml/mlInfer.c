/**CFile****************************************************************

  FileName    [mlInfer.c]

  PackageName [SYNAPSE: neural optimization co-processor for ABC.]

  Synopsis    [Inference abstraction: ONNX Runtime backend OR a built-in
               analytic fallback model.]

  Notes       [Build default = fallback (no ML dependencies at all, runs
               anywhere). Build with `make ABC_USE_ONNX=1` and link ONNX
               Runtime to enable neural inference from a trained model.
               Either way the public API is identical, so the decision
               hooks never care which backend is live.]

***********************************************************************/

#include <math.h>

#include "ml_abc.h"

#ifdef ABC_USE_ONNX
  #include <onnxruntime_c_api.h>
#endif

ABC_NAMESPACE_IMPL_START

////////////////////////////////////////////////////////////////////////
///                    SMALL MATH HELPERS                              ///
////////////////////////////////////////////////////////////////////////

static inline float Ml_Sigmoid( float x ) { return 1.0f / (1.0f + expf(-x)); }

////////////////////////////////////////////////////////////////////////
///                    ONNX BACKEND (optional)                         ///
////////////////////////////////////////////////////////////////////////

#ifdef ABC_USE_ONNX

// Opaque handle stored in Ml_Man_t::pOnnx
typedef struct Ml_Onnx_t_ Ml_Onnx_t;
struct Ml_Onnx_t_
{
    const OrtApi *  pApi;
    OrtEnv *        pEnv;
    OrtSessionOptions * pOpts;
    OrtSession *    pSession;      // synapse.onnx (multi-head)
    OrtMemoryInfo * pMemInfo;
};

static int Ml_OnnxLoad( Ml_Man_t * p )
{
    Ml_Onnx_t * o = ABC_CALLOC( Ml_Onnx_t, 1 );
    o->pApi = OrtGetApiBase()->GetApi( ORT_API_VERSION );
    if ( o->pApi == NULL ) { ABC_FREE(o); return 0; }
    o->pApi->CreateEnv( ORT_LOGGING_LEVEL_WARNING, "synapse", &o->pEnv );
    o->pApi->CreateSessionOptions( &o->pOpts );
    o->pApi->SetIntraOpNumThreads( o->pOpts, 1 );
    if ( o->pApi->CreateSession( o->pEnv, p->pModelPath, o->pOpts, &o->pSession ) != NULL )
    {
        // failed to load -> clean up and fall back
        if ( o->pOpts ) o->pApi->ReleaseSessionOptions( o->pOpts );
        if ( o->pEnv )  o->pApi->ReleaseEnv( o->pEnv );
        ABC_FREE( o );
        return 0;
    }
    o->pApi->CreateCpuMemoryInfo( OrtArenaAllocator, OrtMemTypeDefault, &o->pMemInfo );
    p->pOnnx = o;
    return 1;
}

static void Ml_OnnxFree( Ml_Man_t * p )
{
    Ml_Onnx_t * o = (Ml_Onnx_t *)p->pOnnx;
    if ( o == NULL ) return;
    if ( o->pMemInfo ) o->pApi->ReleaseMemoryInfo( o->pMemInfo );
    if ( o->pSession ) o->pApi->ReleaseSession( o->pSession );
    if ( o->pOpts )    o->pApi->ReleaseSessionOptions( o->pOpts );
    if ( o->pEnv )     o->pApi->ReleaseEnv( o->pEnv );
    ABC_FREE( o );
    p->pOnnx = NULL;
}

// Run a single-output float model on one input vector; returns output[0].
static float Ml_OnnxRunVec( Ml_Man_t * p, const char * pInName, const char * pOutName,
                            const float * pVec, int nVec )
{
    Ml_Onnx_t * o = (Ml_Onnx_t *)p->pOnnx;
    OrtValue * pIn = NULL, * pOut = NULL;
    int64_t shape[2]; float * pData = NULL; float result = 0.0f;
    const char * inNames[1]; const char * outNames[1];
    shape[0] = 1; shape[1] = nVec;
    o->pApi->CreateTensorWithDataAsOrtValue( o->pMemInfo, (void*)pVec,
        (size_t)nVec * sizeof(float), shape, 2,
        ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, &pIn );
    inNames[0] = pInName; outNames[0] = pOutName;
    o->pApi->Run( o->pSession, NULL, inNames, (const OrtValue* const*)&pIn, 1,
                  outNames, 1, &pOut );
    if ( pOut )
    {
        o->pApi->GetTensorMutableData( pOut, (void**)&pData );
        if ( pData ) result = pData[0];
        o->pApi->ReleaseValue( pOut );
    }
    if ( pIn ) o->pApi->ReleaseValue( pIn );
    return result;
}

#endif // ABC_USE_ONNX

////////////////////////////////////////////////////////////////////////
///                    ANALYTIC FALLBACK MODEL                         ///
////////////////////////////////////////////////////////////////////////

// Transparent linear-in-features proxy for PotentialHead. This is what runs
// when no trained model is loaded; it lets the whole pipeline execute today
// and doubles as the "heuristic baseline" in ablations. See docs/DESIGN.md 2.
static float Ml_FallbackPotential( Ml_Man_t * p, const float * f )
{
    int i; double acc = 0.0;
    for ( i = 0; i < ML_NODE_FEAT_DIM; i++ )
        acc += p->AnalyticW[i] * f[i];
    return Ml_Sigmoid( (float)acc - 0.5f );
}

// Fallback candidate score: prefer divisors that are functionally similar
// (high sim agreement), structurally close, and in the transitive fan-in.
static float Ml_FallbackRank( const float * pPair )
{
    float score = 0.0f;
    score += 1.20f * pPair[4];   // simulation agreement (functional match)
    score += 0.50f * pPair[2];   // in TFI
    score += 0.40f * pPair[3];   // shallower than root
    score -= 0.60f * pPair[6];   // penalize large |level gap|
    score += 0.30f * pPair[10];  // positive-unate hint
    return Ml_Sigmoid( score );
}

// Fallback window pay-off: reconvergence + reuse pressure + MFFC ownership.
static float Ml_FallbackWindow( const float * f )
{
    float s = 0.0f;
    s += 0.9f * f[14];   // reconvergence
    s += 0.5f * f[2];    // fanout / reuse
    s += 0.6f * f[7];    // MFFC ownership
    s += 0.3f * f[11];   // local density
    return Ml_Sigmoid( s - 0.4f );
}

////////////////////////////////////////////////////////////////////////
///                    PUBLIC INFERENCE API                            ///
////////////////////////////////////////////////////////////////////////

void Ml_InferInit( Ml_Man_t * p )
{
    p->pOnnx = NULL;
#ifdef ABC_USE_ONNX
    if ( p->Backend == ML_BACKEND_ONNX && p->pModelPath != NULL )
    {
        if ( Ml_OnnxLoad( p ) )
            return;                       // ONNX active
        // load failed -> silently degrade to fallback
    }
#endif
    p->Backend = ML_BACKEND_FALLBACK;
}

void Ml_InferQuit( Ml_Man_t * p )
{
#ifdef ABC_USE_ONNX
    if ( p->pOnnx )
        Ml_OnnxFree( p );
#endif
    p->pOnnx = NULL;
}

float Ml_InferPotential( Ml_Man_t * p, const float * pNodeFeat )
{
    p->nNodesScored++;
#ifdef ABC_USE_ONNX
    if ( p->Backend == ML_BACKEND_ONNX && p->pOnnx )
        return Ml_OnnxRunVec( p, "node_feat", "potential", pNodeFeat, ML_NODE_FEAT_DIM );
#endif
    return Ml_FallbackPotential( p, pNodeFeat );
}

float Ml_InferRankScore( Ml_Man_t * p, const float * pRootFeat,
                         const float * pCandFeat, const float * pPairFeat )
{
    // The deployed ranker consumes the ML_DIV_FEAT_DIM pair features directly
    // (the "encode-once" embedding path is the documented research upgrade;
    //  see docs/DESIGN.md section 5). root/cand feats are reserved for it.
    (void)pRootFeat; (void)pCandFeat;
#ifdef ABC_USE_ONNX
    if ( p->Backend == ML_BACKEND_ONNX && p->pOnnx )
        return Ml_OnnxRunVec( p, "rank_feat", "score", pPairFeat, ML_DIV_FEAT_DIM );
#endif
    return Ml_FallbackRank( pPairFeat );
}

float Ml_InferWindowPayoff( Ml_Man_t * p, const float * pNodeFeat )
{
#ifdef ABC_USE_ONNX
    if ( p->Backend == ML_BACKEND_ONNX && p->pOnnx )
        return Ml_OnnxRunVec( p, "node_feat", "window_payoff", pNodeFeat, ML_NODE_FEAT_DIM );
#endif
    return Ml_FallbackWindow( pNodeFeat );
}

ABC_NAMESPACE_IMPL_END

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                  ///
////////////////////////////////////////////////////////////////////////
