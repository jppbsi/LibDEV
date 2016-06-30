#include "_dbn_.h"

/* Deep Belief Networks */
/* Note that a DBN with 1 layer is the same as a RBM (Restricted Boltzmann Machine) */

/* It executes a Bernoulli-Bernoulli DBN and returns the reconstruction error
Parameters: [g, op, L, Param, n_epochs, batch_size, n_gibbs_sampling, eta_bound]
g: dataset in the OPF format
op: 1 - CD | 2 - PCD | 3 - FPCD
L: number of RBMs
n_epochs: number of epochs for training
batch_size: size of the mini-batch
n_gibbs_sampling: number of iterations for contrastive divergence
eta_bound: learning rate boundaries matrix */

double Bernoulli_BernoulliDBN4Reconstruction(Agent *a, va_list arg){
    int i, j, op, L, n_epochs, batch_size, n_gibbs_sampling, *n_hidden_units;
    double **eta_bound;
    double reconstruction_error;
    DBN *d = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;
    
    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    op = va_arg(arg,int);
    L = va_arg(arg,int);
    n_epochs = va_arg(arg,int);
    batch_size = va_arg(arg,int);
    n_gibbs_sampling = va_arg(arg,int);
    eta_bound = va_arg(arg, double **);
    n_hidden_units = (int *)calloc(L, sizeof(int));
    
    j = 0;
    for(i = 0; i < L; i++){
        n_hidden_units[i] = a->x[j]; j+=4;
    }
        
    d = CreateNewDBN(g->nfeats, n_hidden_units, g->nlabels, L);
    InitializeDBN(d);
    j = 1;
    for(i = 0; i < d->n_layers; i++){
        d->m[i]->eta = a->x[j]; j++;
        d->m[i]->lambda = a->x[j]; j++;
        d->m[i]->alpha = a->x[j]; j+=2;
        d->m[i]->eta_min = eta_bound[0][i];
        d->m[i]->eta_max = eta_bound[1][i];
    }
        
    D = Subgraph2Dataset(g);
    
    switch (op){
        case 1:
            reconstruction_error = BernoulliDBNTrainingbyContrastiveDivergence(D, d, n_epochs, n_gibbs_sampling, batch_size);
        break;
        case 2:
            reconstruction_error = BernoulliDBNTrainingbyPersistentContrastiveDivergence(D, d, n_epochs, n_gibbs_sampling, batch_size);
        break;
        case 3:
            reconstruction_error = BernoulliDBNTrainingbyFastPersistentContrastiveDivergence(D, d, n_epochs, n_gibbs_sampling, batch_size);
        break;
    }
    
    DestroyDBN(&d);
    DestroyDataset(&D);
    free(n_hidden_units);
    
    fprintf(stderr,"\nReconstruction error: %lf ", reconstruction_error);
    return reconstruction_error;
}

/* It executes a Bernoulli-Bernoulli DBN with Dropout and returns the reconstruction error
Parameters: [g, op, L, Param, n_epochs, batch_size, n_gibbs_sampling, eta_bound]
g: dataset in the OPF format
op: 1 - CD | 2 - PCD | 3 - FPCD
L: number of RBMs
n_epochs: number of epochs for training
batch_size: size of the mini-batch
n_gibbs_sampling: number of iterations for contrastive divergence
eta_bound: learning rate boundaries matrix */

double Bernoulli_BernoulliDBN4ReconstructionWithDropout(Agent *a, va_list arg){
    int i, j, op, L, n_epochs, batch_size, n_gibbs_sampling, *n_hidden_units;
    double **eta_bound, *p, *q;
    double reconstruction_error;
    DBN *d = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;
    
    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    op = va_arg(arg,int);
    L = va_arg(arg,int);
    n_epochs = va_arg(arg,int);
    batch_size = va_arg(arg,int);
    n_gibbs_sampling = va_arg(arg,int);
    eta_bound = va_arg(arg, double **);
    n_hidden_units = (int *)calloc(L, sizeof(int));
    p = (double *)calloc(L, sizeof(double));
    q = (double *)calloc(L, sizeof(double));
    
    j = 0;
    for(i = 0; i < L; i++){
        n_hidden_units[i] = a->x[j]; j+=6;
    }
        
    d = CreateNewDBN(g->nfeats, n_hidden_units, g->nlabels, L);
    InitializeDBN(d);
    j = 1;
    for(i = 0; i < d->n_layers; i++){
        d->m[i]->eta = a->x[j]; j++;
        d->m[i]->lambda = a->x[j]; j++;
        d->m[i]->alpha = a->x[j]; j++;
        p[i] = a->x[j]; j++;
        q[i] = a->x[j]; j+=2;
        d->m[i]->eta_min = eta_bound[0][i];
        d->m[i]->eta_max = eta_bound[1][i];
    }
        
    D = Subgraph2Dataset(g);
    
    switch (op){
        case 1:
            reconstruction_error = BernoulliDBNTrainingbyContrastiveDivergenceWithDropout(D, d, n_epochs, n_gibbs_sampling, batch_size, p, q);
        break;
        case 2:
            reconstruction_error = BernoulliDBNTrainingbyPersistentContrastiveDivergenceWithDropout(D, d, n_epochs, n_gibbs_sampling, batch_size, p, q);
        break;
        case 3:
            reconstruction_error = BernoulliDBNTrainingbyFastPersistentContrastiveDivergenceWithDropout(D, d, n_epochs, n_gibbs_sampling, batch_size, p, q);
        break;
    }
    
    DestroyDBN(&d);
    DestroyDataset(&D);
    free(n_hidden_units);
    free(p);
    free(q);
    
    fprintf(stderr,"\nReconstruction error: %lf ", reconstruction_error);
    return reconstruction_error;
}
/***********************************************/