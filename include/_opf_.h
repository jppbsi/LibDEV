#ifndef _OPF_H
#define _OPF_H

#include "dev.h"

/* Supervised OPF with k-nn adjacency relation */
double opfknn_LearningK(Agent *a, va_list arg); /* It learns the k-neighbourhod size (parameter k) */

/* Unsupervised OPF with k-nn adjacency relation */
double OPFcluster_Optimization(Agent *a, va_list arg); /* It optimizes the parameter kmax for OPF_CLUSTER */

/* OPF Pruning */
double OPFpruning_ensemble(Agent *a, va_list arg); /* It executes a OPF Ensemble-pruning and it outputs the best classifiers */

//-------------------------------------------------------
// Changes for the CEC '19 paper.
// Struct used to initialize agents.
typedef struct Class_list_{

    int nelems; // number of elements on the list.
    int *index; // Index of the node in the subgraph.
    int *position; // Position of the node in the full graph.
    int *flag; // (0) not used or (1) used.

}Class_list;

SearchSpace *CreateInitializeSearchSpaceOPF(Subgraph *sg, float perc, int opt_id, int m);

//-------------------------------------------------------

/***********************************************/



#endif
