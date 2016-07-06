#include "_opf_.h"

/* Supervised OPF with k-nn adjacency relation */

/* It learns the k-neighbourhod size (parameter k)
Parameters:
k: neighborhood size
Train: training graph
Val: validating graph */
double opfknn_LearningK(Agent *a, va_list arg){
    double error;
    int k;
    Subgraph *Train = NULL, *Val = NULL;
        
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

/* Unsupervised OPF with k-nn adjacency relation */

/* It optimizes the parameter kmax for OPF_CLUSTER
Parameters:
Train: training graph
Val: validating graph
kmax: maximum degree for the knn graph */
double OPFcluster_Optimization(Agent *a, va_list arg){
    int kmax, i;
    double error;
    Subgraph *Train = NULL, *Val = NULL;

    Train = va_arg(arg, Subgraph *);
    Val = va_arg(arg, Subgraph *);
    kmax = a->x[0];
	
    opf_BestkMinCut(Train, 1, kmax); /* default kmin = 1 */
	
    opf_OPFClustering(Train);
	
    if (Train->node[0].truelabel!=0){
        Train->nlabels = 0;
        for (i = 0; i < Train->nnodes; i++){
            if (Train->node[i].root==i)
                Train->node[i].label = Train->node[i].truelabel;
            else
                Train->node[i].label = Train->node[Train->node[i].root].truelabel;
        }
        for (i = 0; i < Train->nnodes; i++){
            if (Train->node[i].label > Train->nlabels)
                Train->nlabels = Train->node[i].label;
        }
    }
    else
        for (i = 0; i < Train->nnodes; i++)
            Train->node[i].truelabel = Train->node[i].label+1;
  
    opf_OPFClassifying(Train, Val);
    error = (double)opf_Accuracy(Val);
    
    return 1/error;
}
/***********************************************/