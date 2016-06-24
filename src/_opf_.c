#include "_opf_.h"

/* Supervised OPF with k-nn adjacency relation */

/* It learns the k-neighbourhod size (parameter k)
Parameters:
k: neighborhood size
Train: training graph
Val: validating graph */
double opfknn_LearningK(Agent *a, ...){
    double error;
    va_list arg;
    int k;
    Subgraph *Train = NULL, *Val = NULL;
    
    va_start(arg, a);
    
    Train = va_arg(arg, Subgraph *);
    Val = va_arg(arg, Subgraph *);
    k = a->x[0];
    
    Train->bestk = k;
    opf_CreateArcs(Train, Train->bestk);
    opf_PDF(Train);
    opf_OPFClustering4SupervisedLearning(Train);
    opf_DestroyArcs(Train);
  
    opf_OPFknnClassify(Train, Val);
    error = (double)opf_Accuracy(Val);
    
    return 1/error;
}
/***********************************************/