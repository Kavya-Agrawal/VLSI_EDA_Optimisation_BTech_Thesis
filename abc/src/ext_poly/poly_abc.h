/**CFile****************************************************************

  FileName    [poly_abc.h]

  PackageName [POLYPHONY: diverse generative choice synthesis for ABC.]

  Synopsis    [Public API for extract → synthesize → verify → choices.]

***********************************************************************/

#ifndef ABC__ext_poly__poly_abc_h
#define ABC__ext_poly__poly_abc_h

#include "misc/util/abc_global.h"

ABC_NAMESPACE_HEADER_START

////////////////////////////////////////////////////////////////////////
///                         PARAMETERS                                 ///
////////////////////////////////////////////////////////////////////////

#define POLY_MAX_VARS      6     // prototype: k-input cuts, k <= 6
#define POLY_MAX_GATES     32    // max AND gates in a generated program
#define POLY_MAX_PROGRAMS  16    // max equivalent programs kept per TT
#define POLY_MAX_CUTS      256   // max cuts extracted for one pass

// A circuit program: sequence of 2-input ANDs over PI literals + AND lits,
// then an output literal. Literals use ABC encoding: 2*node + complement.
// Nodes 0..nVars-1 are PIs; nodes nVars..nVars+nGates-1 are ANDs.
typedef struct Poly_Prog_t_ Poly_Prog_t;
struct Poly_Prog_t_
{
    int   nVars;                         // number of PIs (k)
    int   nGates;                        // number of AND gates
    int   LitA[POLY_MAX_GATES];          // fanin0 lit of each gate
    int   LitB[POLY_MAX_GATES];          // fanin1 lit of each gate
    int   OutLit;                        // output literal
    int   nSize;                         // = nGates (compactness metric)
};

// One cut with its target truth table (for k<=6 one word covers 2^k bits).
typedef struct Poly_Cut_t_ Poly_Cut_t;
struct Poly_Cut_t_
{
    int   RootId;                        // GIA object id of the root
    int   nLeaves;
    int   Leaves[POLY_MAX_VARS];         // GIA object ids of leaves
    word  Truth;                         // target TT (low 2^nLeaves bits used)
};

typedef struct Poly_Man_t_ Poly_Man_t;
struct Poly_Man_t_
{
    int            fEnabled;
    int            fVerbose;
    int            nSamples;             // programs to try per cut
    int            nKeep;                // max equivalents to keep
    int            nMaxGates;            // reject programs larger than this
    char *         pModelPath;           // optional ONNX generator
    void *         pOnnx;
    // counters
    int            nCutsSeen;
    int            nProgsTried;
    int            nProgsKept;
    int            nEquivFound;
};

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DECLARATIONS                          ///
////////////////////////////////////////////////////////////////////////

/*=== polyCore.c =============================================================*/
extern Poly_Man_t * Poly_ManGet();
extern void         Poly_ManFree();
extern void         Poly_ModuleBootstrap();

/*=== polyTruth.c ============================================================*/
// Evaluate a program's truth table (k<=6) into *pOutTruth. Returns 1 on ok.
extern int          Poly_ProgEvalTruth( Poly_Prog_t * pProg, word * pOutTruth );
// 1 iff program realizes Target (low 2^nVars bits).
extern int          Poly_ProgIsEquivalent( Poly_Prog_t * pProg, word Target );
// Decode a verified program into a new GIA (PIs + ANDs + 1 PO). Caller stops it.
extern void *       Poly_ProgToGia( Poly_Prog_t * pProg );

/*=== polySynth.c ============================================================*/
// Fallback (non-neural) synthesizer: produce up to nMax verified equivalents
// of Target over nVars PIs. Returns number written into pOut[].
extern int          Poly_SynthFallback( int nVars, word Target,
                                        Poly_Prog_t * pOut, int nMax );

/*=== polyCuts.c =============================================================*/
// Extract up to nMaxCuts distinct k-input cuts (k in [2,POLY_MAX_VARS]) from
// the current GIA; fill pCuts[]. Returns count.
extern int          Poly_GiaExtractCuts( void * pGia, Poly_Cut_t * pCuts, int nMaxCuts );

/*=== polyCmd.c ==============================================================*/
// Registrar declared in polyCore.c / polyCmd.c where Abc_Frame_t is visible.

ABC_NAMESPACE_HEADER_END

#endif
