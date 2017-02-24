#include "_dbm_.h"

/* Deep Boltzmann Machines */

/* It executes a Bernoulli-Bernoulli DBM and returns the reconstruction error
Parameters: [g, op, L, n_epochs, batch_size, n_gibbs_sampling, eta_bound]
g: dataset in the OPF format
op: 1 - CD | 2 - PCD | 3 - FPCD
L: number of RBMs
n_epochs: number of epochs for training
batch_size: size of the mini-batch
n_gibbs_sampling: number of iterations for contrastive divergence
eta_bound: learning rate boundaries matrix */
double Bernoulli_BernoulliDBM4Reconstruction(Agent *a, va_list arg){
    int i, j, op, L, n_epochs, batch_size, n_gibbs_sampling, *n_hidden_units;
    double **eta_bound;
    double reconstruction_error;
    DBM *d = NULL;
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

    d = CreateNewDBM(g->nfeats, n_hidden_units, g->nlabels, L);
    InitializeDBM(d);
    j = 1;
    for(i = 0; i < d->n_layers; i++){
        d->m[i]->eta = a->x[j]; j++;
        d->m[i]->lambda = a->x[j]; j++;
        d->m[i]->alpha = a->x[j]; j+=2;
        d->m[i]->eta_min = eta_bound[0][i];
        d->m[i]->eta_max = eta_bound[1][i];
    }

    D = Subgraph2Dataset(g);

    reconstruction_error = GreedyPreTrainingDBM(D, d, n_epochs, n_gibbs_sampling, batch_size, op);

    DestroyDBM(&d);
    DestroyDataset(&D);
    free(n_hidden_units);

    fprintf(stderr,"\nReconstruction error: %lf ", reconstruction_error);
    return reconstruction_error;
}

/* It executes a Bernoulli-Bernoulli DBM with Dropout and returns the reconstruction error
Parameters: [g, op, L, n_epochs, batch_size, n_gibbs_sampling, eta_bound]
g: dataset in the OPF format
op: 1 - CD | 2 - PCD | 3 - FPCD
L: number of RBMs
n_epochs: number of epochs for training
batch_size: size of the mini-batch
n_gibbs_sampling: number of iterations for contrastive divergence
eta_bound: learning rate boundaries matrix */
double Bernoulli_BernoulliDBM4ReconstructionWithDropout(Agent *a, va_list arg){
    int i, j, op, L, n_epochs, batch_size, n_gibbs_sampling, *n_hidden_units;
    double **eta_bound, *p;
    double reconstruction_error;
    DBM *d = NULL;
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

    j = 0;
    for(i = 0; i < L; i++){
        n_hidden_units[i] = a->x[j]; j+=5;
    }

    d = CreateNewDBM(g->nfeats, n_hidden_units, g->nlabels, L);
    InitializeDBM(d);
    j = 1;
    for(i = 0; i < d->n_layers; i++){
        d->m[i]->eta = a->x[j]; j++;
        d->m[i]->lambda = a->x[j]; j++;
        d->m[i]->alpha = a->x[j]; j++;
        p[i] = a->x[j]; j+=2;
        d->m[i]->eta_min = eta_bound[0][i];
        d->m[i]->eta_max = eta_bound[1][i];
    }

    D = Subgraph2Dataset(g);

    reconstruction_error = GreedyPreTrainingDBMwithDropout(D, d, n_epochs, n_gibbs_sampling, batch_size, op, p);

    DestroyDBM(&d);
    DestroyDataset(&D);
    free(n_hidden_units);
    free(p);

    fprintf(stderr,"\nReconstruction error: %lf ", reconstruction_error);
    return reconstruction_error;
}

/* It executes a Bernoulli-Bernoulli DBM with Dropconnect and returns the reconstruction error
Parameters: [g, op, L, n_epochs, batch_size, n_gibbs_sampling, eta_bound]
g: dataset in the OPF format
op: 1 - CD | 2 - PCD | 3 - FPCD
L: number of RBMs
n_epochs: number of epochs for training
batch_size: size of the mini-batch
n_gibbs_sampling: number of iterations for contrastive divergence
eta_bound: learning rate boundaries matrix */
double Bernoulli_BernoulliDBM4ReconstructionWithDropconnect(Agent *a, va_list arg){
    int i, j, op, L, n_epochs, batch_size, n_gibbs_sampling, *n_hidden_units;
    double **eta_bound, *p;
    double reconstruction_error;
    DBM *d = NULL;
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

    j = 0;
    for(i = 0; i < L; i++){
        n_hidden_units[i] = a->x[j]; j+=5;
    }

    d = CreateNewDBM(g->nfeats, n_hidden_units, g->nlabels, L);
    InitializeDBM(d);
    j = 1;
    for(i = 0; i < d->n_layers; i++){
        d->m[i]->eta = a->x[j]; j++;
        d->m[i]->lambda = a->x[j]; j++;
        d->m[i]->alpha = a->x[j]; j++;
        p[i] = a->x[j]; j+=2;
        d->m[i]->eta_min = eta_bound[0][i];
        d->m[i]->eta_max = eta_bound[1][i];
    }

    D = Subgraph2Dataset(g);

    reconstruction_error = GreedyPreTrainingDBMwithDropconnect(D, d, n_epochs, n_gibbs_sampling, batch_size, op, p);

    DestroyDBM(&d);
    DestroyDataset(&D);
    free(n_hidden_units);
    free(p);

    fprintf(stderr,"\nReconstruction error: %lf ", reconstruction_error);
    return reconstruction_error;
}
/***********************************************/
