#ifndef _OPF_H
#define _OPF_H

#include "dev.h"

/* Supervised OPF with k-nn adjacency relation */
double opfknn_LearningK(Agent *a, va_list arg); /* It learns the k-neighbourhod size (parameter k) */
/***********************************************/

#endif