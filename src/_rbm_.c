#include "_rbm_.h"

/* Restricted Boltzmann Machines */

/* It executes a Bernoulli DRBM and returns the reconstruction error of the label unit
Parameters: [g, n_epochs, n_gibbs_sampling, batch_size]
g: dataset in the OPF format
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size */
double BernoulliDRBM(Agent *a, va_list arg){
    int n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double classification_error;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;
    
    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    n_epochs = va_arg(arg,int);
    batch_size = va_arg(arg,int);
    n_gibbs_sampling = va_arg(arg,int);
    
    n_hidden_units = a->x[0];
    m = CreateRBM(g->nfeats, n_hidden_units, g->nlabels);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    
    D = Subgraph2Dataset(g);
    
    InitializeWeights(m);
    InitializeLabelWeights(m);    
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);
    InitializeBias4LabelUnits(m);
    
    classification_error = DiscriminativeBernoulliRBMTrainingbyContrastiveDivergence(D, m, n_epochs, n_gibbs_sampling, batch_size);
    
    DestroyRBM(&m);
    DestroyDataset(&D);
    
    fprintf(stderr,"\nClassification error: %lf ", classification_error);
    return classification_error;
}

/* It executes a Bernoulli DRBM with Dropout and returns the reconstruction error of the label unit
Parameters: [g, n_epochs, n_gibbs_sampling, batch_size]
g: dataset in the OPF format
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size */
double BernoulliDRBMWithDropout(Agent *a, va_list arg){
    int n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double classification_error, p, q;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;
    
    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    n_epochs = va_arg(arg,int);
    batch_size = va_arg(arg,int);
    n_gibbs_sampling = va_arg(arg,int);
    
    n_hidden_units = a->x[0];
    m = CreateRBM(g->nfeats, n_hidden_units, g->nlabels);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    p = a->x[4];
    q = a->x[5];
    
    D = Subgraph2Dataset(g);
    
    InitializeWeights(m);
    InitializeLabelWeights(m);    
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);
    InitializeBias4LabelUnits(m);
    
    classification_error = DiscriminativeBernoulliRBMTrainingbyContrastiveDivergencewithDropout(D, m, n_epochs, n_gibbs_sampling, batch_size, p, q);
    
    DestroyRBM(&m);
    DestroyDataset(&D);
    
    fprintf(stderr,"\nClassification error: %lf ", classification_error);
    return classification_error;
}

/* It executes a Gaussian-Bernoulli DRBM and returns the reconstruction error of the label unit
Parameters: [g, n_epochs, n_gibbs_sampling, batch_size, sigma]
g: dataset in the OPF format
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size
sigma: input array with the variances associated to each visible unit */
double Gaussian_BernoulliDRBM(Agent *a, va_list arg){
    int n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double classification_error, *sigma;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;
    
    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    n_epochs = va_arg(arg,int);
    batch_size = va_arg(arg,int);
    n_gibbs_sampling = va_arg(arg,int);
    sigma = va_arg(arg, double *);
    
    n_hidden_units = a->x[0];
    m = CreateNewDRBM(g->nfeats, n_hidden_units, g->nlabels, sigma);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    
    D = Subgraph2Dataset(g);
    
    InitializeWeights(m);
    InitializeLabelWeights(m);    
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);
    InitializeBias4LabelUnits(m);
    
    classification_error = DiscriminativeGaussianBernoulliRBMTrainingbyContrastiveDivergence(D, m, n_epochs, n_gibbs_sampling, batch_size);
    
    DestroyDRBM(&m);
    DestroyDataset(&D);
    
    fprintf(stderr,"\nClassification error: %lf ", classification_error);
    return classification_error;
}

/* It executes a Gaussian-Bernoulli DRBM with Dropout and returns the reconstruction error of the label unit
Parameters: [g, n_epochs, n_gibbs_sampling, batch_size, sigma]
g: dataset in the OPF format
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size
sigma: input array with the variances associated to each visible unit */
double Gaussian_BernoulliDRBMWithDropout(Agent *a, va_list arg){
    int n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double classification_error, p, q, *sigma;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;
    
    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    n_epochs = va_arg(arg,int);
    batch_size = va_arg(arg,int);
    n_gibbs_sampling = va_arg(arg,int);
    sigma = va_arg(arg, double *);
    
    n_hidden_units = a->x[0];
    m = CreateNewDRBM(g->nfeats, n_hidden_units, g->nlabels, sigma);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    p = a->x[4];
    q = a->x[5];
    
    D = Subgraph2Dataset(g);
    
    InitializeWeights(m);
    InitializeLabelWeights(m);    
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);
    InitializeBias4LabelUnits(m);
    
    classification_error = DiscriminativeGaussianBernoulliRBMTrainingbyContrastiveDivergencewithDropout(D, m, n_epochs, n_gibbs_sampling, batch_size, p, q);
    
    DestroyDRBM(&m);
    DestroyDataset(&D);
    
    fprintf(stderr,"\nClassification error: %lf ", classification_error);
    return classification_error;
}
/***********************************************/