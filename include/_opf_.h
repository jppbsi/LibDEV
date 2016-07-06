#ifndef _OPF_H
#define _OPF_H

#include "dev.h"

/* Supervised OPF with k-nn adjacency relation */
double opfknn_LearningK(Agent *a, va_list arg); /* It learns the k-neighbourhod size (parameter k) */

/* Unsupervised OPF with k-nn adjacency relation */
double OPFcluster_Optimization(Agent *a, va_list arg); /* It optimizes the parameter kmax for OPF_CLUSTER */
/***********************************************/

#endif