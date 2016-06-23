#include "_opf_.h"

/* Supervised OPF with k-nn adjacency relation */

/* It learns the k-neighbourhod size (parameter k)
Parameters:
Train: training graph
Val: validating graph
k: neighborhood size */
double opfknn_LearningK(Subgraph *Train, Subgraph *Val, int k){
    double error;
    
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