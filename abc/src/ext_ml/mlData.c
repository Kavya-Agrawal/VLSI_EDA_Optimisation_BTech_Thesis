/**CFile****************************************************************

  FileName    [mlData.c]

  PackageName [SYNAPSE: neural optimization co-processor for ABC.]

  Synopsis    [Training-data collection at decision points.]

  Notes       [Writes CSV rows: <task>,<label>,f0,...,fk  consumed by
               python/data/dataset.py. Enabled with `ml_config -c <file>`.
               Zero overhead when collection is off.]

***********************************************************************/

#include "ml_abc.h"

ABC_NAMESPACE_IMPL_START

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                           ///
////////////////////////////////////////////////////////////////////////

void Ml_CollectOpen( Ml_Man_t * p, const char * pFileName )
{
    Ml_CollectClose( p );
    p->pCollectFile = (void *)fopen( pFileName, "wb" );
    if ( p->pCollectFile )
    {
        p->fCollect = 1;
        ABC_FREE( p->pCollectPath );
        p->pCollectPath = Abc_UtilStrsav( (char *)pFileName );
        fprintf( (FILE *)p->pCollectFile, "# SYNAPSE training data: task,label,features...\n" );
    }
}

void Ml_CollectClose( Ml_Man_t * p )
{
    if ( p->pCollectFile )
    {
        fclose( (FILE *)p->pCollectFile );
        p->pCollectFile = NULL;
    }
    p->fCollect = 0;
}

void Ml_CollectRow( Ml_Man_t * p, Ml_Task_t Task,
                    const float * pFeat, int nFeat, double Label )
{
    FILE * pFile;
    int i;
    if ( !p->fCollect || p->pCollectFile == NULL )
        return;
    pFile = (FILE *)p->pCollectFile;
    fprintf( pFile, "%d,%.6f", (int)Task, Label );
    for ( i = 0; i < nFeat; i++ )
        fprintf( pFile, ",%.6f", pFeat[i] );
    fprintf( pFile, "\n" );
}

ABC_NAMESPACE_IMPL_END

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                  ///
////////////////////////////////////////////////////////////////////////
