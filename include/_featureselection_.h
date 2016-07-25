#ifndef _FEATURESELECTION_H
#define _FEATURESELECTION_H

/* Transfer functions ID's */
/* 0 stands for default case, used to create the best graphs after optimization process */
#define _S1_ 1
#define _S2_ 2
#define _S3_ 3
#define _S4_ 4
#define _V1_ 5
#define _V2_ 6
#define _V3_ 7
#define _V4_ 8

#include "dev.h"

/* Feature Selection */

Subgraph *CreateSubgraphFromSelectedFeatures(Subgraph *sg, double *feat, int transfer_id); /* It creates a subgraph from selected features */

double *S1TransferFunction(double *x, int n, int *nfeats); /* Transfer function S1 */
double *S2TransferFunction(double *x, int n, int *nfeats); /* Transfer function S2 */
double *S3TransferFunction(double *x, int n, int *nfeats); /* Transfer function S3 */
double *S4TransferFunction(double *x, int n, int *nfeats); /* Transfer function S4 */
double *V1TransferFunction(double *x, int n, int *nfeats); /* Transfer function V1 */
double *V2TransferFunction(double *x, int n, int *nfeats); /* Transfer function V2 */
double *V3TransferFunction(double *x, int n, int *nfeats); /* Transfer function V3 */
double *V4TransferFunction(double *x, int n, int *nfeats); /* Transfer function V4 */

double FeatureSelection(Agent *a, va_list arg); /* It executes Feature Selection with OPF evaluation */
/***********************************************/

#endif