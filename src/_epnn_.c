#include "_epnn_.h"

/* Enhanced Probabilistic Neural Network */

/* It optimizes the sigma and radius for EPNN with OPF
Parameters:
Train: training graph
Val: evaluating graph
lNode: ordered list labels based in the OPF cluster or by number of classes in training set
nsample4class: count sample for classes
nGaussians: number of gaussians (number of labels obtained in OPF cluster)
sigma: sigma is the spread of the Gaussian function
radius: for Hyper-Sphere in Enhanced Probabilistic Neural Network */
double EPNN_Optimization(Agent *a, va_list arg){
    double error, sigma, radius;
    Subgraph *Train = NULL, *Val = NULL;
    gsl_vector *lNode = NULL, *alpha = NULL, *nsample4class = NULL, *nGaussians = NULL;
    
    Train = va_arg(arg, Subgraph *);
    Val = va_arg(arg, Subgraph *);
    lNode = va_arg(arg, gsl_vector *);
    nsample4class = va_arg(arg, gsl_vector *);
    nGaussians = va_arg(arg, gsl_vector *);
    sigma = a->x[0];
    radius = a->x[1];
    
    alpha = hyperSphere(Train, radius); /* It calculates the hyper-sphere with radius r for each training node */
	
    /* Enhanced probabilistic neural network with local decision circles based on the Parzen-window estimation */
    epnn(Train, Val, sigma, lNode, nsample4class, alpha, nGaussians); 

    error = (double)opf_Accuracy(Val);
    
    gsl_vector_free(alpha);

    return 1/error;
}
/***********************************************/