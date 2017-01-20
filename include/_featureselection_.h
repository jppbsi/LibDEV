#ifndef _FEATURESELECTION_H
#define _FEATURESELECTION_H

#include "dev.h"

/* Feature Selection */

Subgraph *CreateSubgraphFromSelectedFeatures(Subgraph *sg, double *feat); /* It creates a subgraph from selected features */

typedef Subgraph* (*TransferFunc)(Subgraph *sg, double *feat); /* Pointer to transfer functions */
Subgraph *S1TransferFunction(Subgraph *sg, double *feat); /* Transfer function S1 */
Subgraph *S2TransferFunction(Subgraph *sg, double *feat); /* Transfer function S2 */
Subgraph *S3TransferFunction(Subgraph *sg, double *feat); /* Transfer function S3 */
Subgraph *S4TransferFunction(Subgraph *sg, double *feat); /* Transfer function S4 */
Subgraph *V1TransferFunction(Subgraph *sg, double *feat); /* Transfer function V1 */
Subgraph *V2TransferFunction(Subgraph *sg, double *feat); /* Transfer function V2 */
Subgraph *V3TransferFunction(Subgraph *sg, double *feat); /* Transfer function V3 */
Subgraph *V4TransferFunction(Subgraph *sg, double *feat); /* Transfer function V4 */
double FeatureSelectionOPF(Agent *a, va_list arg); /* It executes Feature Selection with OPF evaluation */

double *HammingTransfer(double *feat, int n); /* Hamming Transfer function based on S2 */
double FeatureSelectionHamming(Agent *a, va_list arg); /* It executes Feature Selection with Hamming Distance evaluation */
/***********************************************/

#endif