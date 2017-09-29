#include "_rbm_.h"

/* Restricted Boltzmann Machines */

/* It executes a Bernoulli RBM and returns the reconstruction error of the label unit
Parameters: [g, op, n_epochs, n_gibbs_sampling, batch_size]
g: dataset in the OPF format
op: 1 - CD | 2 - PCD | 3 - FPCD
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size */
double BernoulliRBM(Agent *a, va_list arg)
{
    int op, n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double *eta_bound, reconstruction_error;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;

    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    op = va_arg(arg, int);
    n_epochs = va_arg(arg, int);
    batch_size = va_arg(arg, int);
    n_gibbs_sampling = va_arg(arg, int);
    eta_bound = va_arg(arg, double *);

    n_hidden_units = a->x[0];
    m = CreateRBM(g->nfeats, n_hidden_units, 1);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    m->eta_min = eta_bound[0];
    m->eta_max = eta_bound[1];

    D = Subgraph2Dataset(g);

    InitializeWeights(m);
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);

    switch (op)
    {
    case 1:
        reconstruction_error = BernoulliRBMTrainingbyContrastiveDivergence(D, m, n_epochs, n_gibbs_sampling, batch_size);
        break;
    case 2:
        reconstruction_error = BernoulliRBMTrainingbyPersistentContrastiveDivergence(D, m, n_epochs, n_gibbs_sampling, batch_size);
        break;
    case 3:
        reconstruction_error = BernoulliRBMTrainingbyFastPersistentContrastiveDivergence(D, m, n_epochs, n_gibbs_sampling, batch_size);
        break;
    }

    DestroyRBM(&m);
    DestroyDataset(&D);

    fprintf(stderr, "\nReconstruction error: %lf ", reconstruction_error);
    return reconstruction_error;
}

/* It executes a Bernoulli RBM with Dropout and returns the reconstruction error of the label unit
Parameters: [g, op, n_epochs, n_gibbs_sampling, batch_size]
g: dataset in the OPF format
op: 1 - CD | 2 - PCD | 3 - FPCD
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size */
double BernoulliRBMWithDropout(Agent *a, va_list arg)
{
    int op, n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double *eta_bound, reconstruction_error, p;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;

    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    op = va_arg(arg, int);
    n_epochs = va_arg(arg, int);
    batch_size = va_arg(arg, int);
    n_gibbs_sampling = va_arg(arg, int);
    eta_bound = va_arg(arg, double *);

    n_hidden_units = a->x[0];
    m = CreateRBM(g->nfeats, n_hidden_units, 1);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    m->eta_min = eta_bound[0];
    m->eta_max = eta_bound[1];
    p = a->x[4];

    D = Subgraph2Dataset(g);

    InitializeWeights(m);
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);

    switch (op)
    {
    case 1:
        reconstruction_error = BernoulliRBMTrainingbyContrastiveDivergencewithDropout(D, m, n_epochs, 1, batch_size, p);
        break;
    case 2:
        reconstruction_error = BernoulliRBMTrainingbyPersistentContrastiveDivergencewithDropout(D, m, n_epochs, n_gibbs_sampling, batch_size, p);
        break;
    case 3:
        reconstruction_error = BernoulliRBMTrainingbyFastPersistentContrastiveDivergencewithDropout(D, m, n_epochs, n_gibbs_sampling, batch_size, p);
        break;
    }

    DestroyRBM(&m);
    DestroyDataset(&D);

    fprintf(stderr, "\nReconstruction error: %lf ", reconstruction_error);
    return reconstruction_error;
}

/* It executes a Bernoulli RBM with Dropconnect and returns the reconstruction error of the label unit
Parameters: [g, op, n_epochs, n_gibbs_sampling, batch_size]
g: dataset in the OPF format
op: 1 - CD | 2 - PCD | 3 - FPCD
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size */
double BernoulliRBMWithDropconnect(Agent *a, va_list arg)
{
    int op, n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double *eta_bound, reconstruction_error, p;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;

    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    op = va_arg(arg, int);
    n_epochs = va_arg(arg, int);
    batch_size = va_arg(arg, int);
    n_gibbs_sampling = va_arg(arg, int);
    eta_bound = va_arg(arg, double *);

    n_hidden_units = a->x[0];
    m = CreateRBM(g->nfeats, n_hidden_units, 1);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    m->eta_min = eta_bound[0];
    m->eta_max = eta_bound[1];
    p = a->x[4];

    D = Subgraph2Dataset(g);

    InitializeWeights(m);
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);

    switch (op)
    {
    case 1:
        reconstruction_error = BernoulliRBMTrainingbyContrastiveDivergencewithDropconnect(D, m, n_epochs, 1, batch_size, p);
        break;
    case 2:
        reconstruction_error = BernoulliRBMTrainingbyPersistentContrastiveDivergencewithDropconnect(D, m, n_epochs, n_gibbs_sampling, batch_size, p);
        break;
    case 3:
        reconstruction_error = BernoulliRBMTrainingbyFastPersistentContrastiveDivergencewithDropconnect(D, m, n_epochs, n_gibbs_sampling, batch_size, p);
        break;
    }

    DestroyRBM(&m);
    DestroyDataset(&D);

    fprintf(stderr, "\nReconstruction error: %lf ", reconstruction_error);
    return reconstruction_error;
}

/* It executes a Bernoulli DRBM and returns the classification error of the label unit
Parameters: [g, n_epochs, n_gibbs_sampling, batch_size]
g: dataset in the OPF format
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size */
double BernoulliDRBM(Agent *a, va_list arg)
{
    int n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double classification_error, *eta_bound;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;

    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    n_epochs = va_arg(arg, int);
    batch_size = va_arg(arg, int);
    n_gibbs_sampling = va_arg(arg, int);
    eta_bound = va_arg(arg, double *);

    n_hidden_units = a->x[0];
    m = CreateRBM(g->nfeats, n_hidden_units, g->nlabels);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    m->eta_min = eta_bound[0];
    m->eta_max = eta_bound[1];

    D = Subgraph2Dataset(g);

    InitializeWeights(m);
    InitializeLabelWeights(m);
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);
    InitializeBias4LabelUnits(m);

    classification_error = DiscriminativeBernoulliRBMTrainingbyContrastiveDivergence(D, m, n_epochs, n_gibbs_sampling, batch_size);

    DestroyRBM(&m);
    DestroyDataset(&D);

    fprintf(stderr, "\nClassification error: %lf ", classification_error);
    return classification_error;
}

/* It executes a Bernoulli DRBM with Dropout and returns the classification error of the label unit
Parameters: [g, n_epochs, n_gibbs_sampling, batch_size]
g: dataset in the OPF format
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size */
double BernoulliDRBMWithDropout(Agent *a, va_list arg)
{
    int n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double classification_error, *eta_bound, p;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;

    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    n_epochs = va_arg(arg, int);
    batch_size = va_arg(arg, int);
    n_gibbs_sampling = va_arg(arg, int);
    eta_bound = va_arg(arg, double *);

    n_hidden_units = a->x[0];
    m = CreateRBM(g->nfeats, n_hidden_units, g->nlabels);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    m->eta_min = eta_bound[0];
    m->eta_max = eta_bound[1];
    p = a->x[4];

    D = Subgraph2Dataset(g);

    InitializeWeights(m);
    InitializeLabelWeights(m);
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);
    InitializeBias4LabelUnits(m);

    classification_error = DiscriminativeBernoulliRBMTrainingbyContrastiveDivergencewithDropout(D, m, n_epochs, n_gibbs_sampling, batch_size, p);

    DestroyRBM(&m);
    DestroyDataset(&D);

    fprintf(stderr, "\nClassification error: %lf ", classification_error);
    return classification_error;
}

/* It executes a Gaussian-Bernoulli DRBM and returns the classification error of the label unit
Parameters: [g, n_epochs, n_gibbs_sampling, batch_size, sigma]
g: dataset in the OPF format
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size
sigma: input array with the variances associated to each visible unit */
double Gaussian_BernoulliDRBM(Agent *a, va_list arg)
{
    int n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double classification_error, *eta_bound, *sigma;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;

    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    n_epochs = va_arg(arg, int);
    batch_size = va_arg(arg, int);
    n_gibbs_sampling = va_arg(arg, int);
    sigma = va_arg(arg, double *);
    eta_bound = va_arg(arg, double *);

    n_hidden_units = a->x[0];
    m = CreateNewDRBM(g->nfeats, n_hidden_units, g->nlabels, sigma);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    m->eta_min = eta_bound[0];
    m->eta_max = eta_bound[1];

    D = Subgraph2Dataset(g);

    InitializeWeights(m);
    InitializeLabelWeights(m);
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);
    InitializeBias4LabelUnits(m);

    classification_error = DiscriminativeGaussianBernoulliRBMTrainingbyContrastiveDivergence(D, m, n_epochs, n_gibbs_sampling, batch_size);

    DestroyDRBM(&m);
    DestroyDataset(&D);

    fprintf(stderr, "\nClassification error: %lf ", classification_error);
    return classification_error;
}

/* It executes a Gaussian-Bernoulli DRBM with Dropout and returns the classification error of the label unit
Parameters: [g, n_epochs, n_gibbs_sampling, batch_size, sigma]
g: dataset in the OPF format
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size
sigma: input array with the variances associated to each visible unit */
double Gaussian_BernoulliDRBMWithDropout(Agent *a, va_list arg)
{
    int n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double classification_error, *eta_bound, p, *sigma;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;

    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    n_epochs = va_arg(arg, int);
    batch_size = va_arg(arg, int);
    n_gibbs_sampling = va_arg(arg, int);
    sigma = va_arg(arg, double *);
    eta_bound = va_arg(arg, double *);

    n_hidden_units = a->x[0];
    m = CreateNewDRBM(g->nfeats, n_hidden_units, g->nlabels, sigma);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    m->eta_min = eta_bound[0];
    m->eta_max = eta_bound[1];
    p = a->x[4];

    D = Subgraph2Dataset(g);

    InitializeWeights(m);
    InitializeLabelWeights(m);
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);
    InitializeBias4LabelUnits(m);

    classification_error = DiscriminativeGaussianBernoulliRBMTrainingbyContrastiveDivergencewithDropout(D, m, n_epochs, n_gibbs_sampling, batch_size, p);

    DestroyDRBM(&m);
    DestroyDataset(&D);

    fprintf(stderr, "\nClassification error: %lf ", classification_error);
    return classification_error;
}

/* It executes a Gaussian-Bernoulli RBM and returns the reconstruction error of the label unit
Parameters: [g, n_epochs, n_gibbs_sampling, batch_size, sigma]
g: dataset in the OPF format
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size
sigma: input array with the variances associated to each visible unit */
double Gaussian_BernoulliRBM(Agent *a, va_list arg)
{
    int n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double reconstruction_error, *eta_bound, *sigma;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;

    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    n_epochs = va_arg(arg, int);
    batch_size = va_arg(arg, int);
    n_gibbs_sampling = va_arg(arg, int);
    sigma = va_arg(arg, double *);
    eta_bound = va_arg(arg, double *);

    n_hidden_units = a->x[0];
    m = CreateNewDRBM(g->nfeats, n_hidden_units, g->nlabels, sigma);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    m->eta_min = eta_bound[0];
    m->eta_max = eta_bound[1];

    D = Subgraph2Dataset(g);

    InitializeWeights(m);
    InitializeLabelWeights(m);
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);
    InitializeBias4LabelUnits(m);

    reconstruction_error = GaussianBernoulliRBMTrainingbyContrastiveDivergence(D, m, n_epochs, n_gibbs_sampling, batch_size);

    DestroyDRBM(&m);
    DestroyDataset(&D);

    fprintf(stderr, "\nReconstruction error: %lf ", reconstruction_error);
    return reconstruction_error;
}

/* It executes a Gaussian-Bernoulli RBM with Dropout and returns the reconstruction error of the label unit
Parameters: [g, n_epochs, n_gibbs_sampling, batch_size, sigma]
g: dataset in the OPF format
n_epochs: numer of epochs for training
n_gibbs_sampling: number of iterations for contrastive divergence
batch_size: mini-batch size
sigma: input array with the variances associated to each visible unit */
double Gaussian_BernoulliRBMWithDropout(Agent *a, va_list arg)
{
    int n_hidden_units, n_epochs, n_gibbs_sampling, batch_size;
    double reconstruction_error, *eta_bound, p, *sigma;
    RBM *m = NULL;
    Subgraph *g = NULL;
    Dataset *D = NULL;

    /* reading input parameters */
    g = va_arg(arg, Subgraph *);
    n_epochs = va_arg(arg, int);
    batch_size = va_arg(arg, int);
    n_gibbs_sampling = va_arg(arg, int);
    sigma = va_arg(arg, double *);
    eta_bound = va_arg(arg, double *);

    n_hidden_units = a->x[0];
    m = CreateNewDRBM(g->nfeats, n_hidden_units, g->nlabels, sigma);
    m->eta = a->x[1];
    m->lambda = a->x[2];
    m->alpha = a->x[3];
    m->eta_min = eta_bound[0];
    m->eta_max = eta_bound[1];
    p = a->x[4];

    D = Subgraph2Dataset(g);

    InitializeWeights(m);
    InitializeLabelWeights(m);
    InitializeBias4HiddenUnits(m);
    InitializeBias4VisibleUnitsWithRandomValues(m);
    InitializeBias4LabelUnits(m);

    reconstruction_error = GaussianBernoulliRBMTrainingbyContrastiveDivergencewithDropout(D, m, n_epochs, n_gibbs_sampling, batch_size, p);

    DestroyDRBM(&m);
    DestroyDataset(&D);

    fprintf(stderr, "\nReconstruction error: %lf ", reconstruction_error);
    return reconstruction_error;
}
/***********************************************/