#include "dev.h"

int main(int argc, char **argv)
{
    if (argc != 12)
    {
        fprintf(stderr, "\nUsage: TensorDBM <training set> <testing set> <output results file name> <cross-validation iteration number> \
                <search space configuration file> <output best parameters file name> <n_epochs> <batch_size> \
                <number of iterations for Constrastive Divergence> <1 - CD | 2 - PCD | 3 - FPCD> <number of DBM layers>");
        exit(-1);
    }

    SearchSpace *s = NULL;
    int i, j, z;
    int iteration = atoi(argv[4]), n_epochs = atoi(argv[7]), batch_size = atoi(argv[8]), n_gibbs_sampling = atoi(argv[9]), op = atoi(argv[10]);
    int n_layers = atoi(argv[11]), *n_hidden_units;
    double **eta_bound, errorTrain, errorTest;
    FILE *f = NULL;
    Subgraph *Train = NULL, *Test = NULL;
    Dataset *DatasetTrain = NULL, *DatasetTest = NULL;
    DBM *d = NULL;

    Train = ReadSubgraph(argv[1]);
    Test = ReadSubgraph(argv[2]);
    DatasetTrain = Subgraph2Dataset(Train);
    DatasetTest = Subgraph2Dataset(Test);

    s = ReadSearchSpaceFromFile(argv[5], _PSO_);

    eta_bound = (double **)calloc(2, sizeof(double *));
    for (i = 0; i < 2; i++)
        eta_bound[i] = (double *)calloc(n_layers, sizeof(double));
    z = 1;
    for (i = 0; i < n_layers; i++)
    {
        eta_bound[0][i] = s->LB[z];
        eta_bound[1][i] = s->UB[z];
        z += 4;
    }

    s->t_g = CreateTensor(s->n, _QUATERNION_);
    for (i = 0; i < s->m; i++)
    {
        s->a[i]->t = CreateTensor(s->n, _QUATERNION_); /* It allocates a new tensor for each agent */
        s->a[i]->t_v = CreateTensor(s->n, _QUATERNION_);
        s->a[i]->t_xl = CreateTensor(s->n, _QUATERNION_);
    }

    fprintf(stderr, "\nInitializing search space ... ");
    InitializeTensorSearchSpace(s, _QUATERNION_);
    fprintf(stderr, "\nOk\n");

    fprintf(stderr, "\nRunning TensorPSO ... ");
    //runPSO(s, Bernoulli_BernoulliDBM4Reconstruction, Train, op, n_layers, n_epochs, batch_size, n_gibbs_sampling, eta_bound);
    if (CheckSearchSpace(s, _PSO_))                                                                                                                   /* It checks whether the search space is valid or not */
        runTensorPSO(s, _QUATERNION_, Bernoulli_BernoulliDBM4Reconstruction, Train, op, n_layers, n_epochs, batch_size, n_gibbs_sampling, eta_bound); /* It minimizes function Sphere */

    fprintf(stderr, "\n\nRunning TensorDBM with best parameters on training set ... ");
    n_hidden_units = (int *)calloc(n_layers, sizeof(int));
    j = 0;
    for (i = 0; i < n_layers; i++)
    {
        n_hidden_units[i] = s->g[j];
        j += 4;
    }
    d = CreateNewDBM(Train->nfeats, n_hidden_units, Train->nlabels, n_layers);
    InitializeDBM(d);
    j = 1;
    for (i = 0; i < d->n_layers; i++)
    {
        d->m[i]->eta = s->g[j];
        j++;
        d->m[i]->lambda = s->g[j];
        j++;
        d->m[i]->alpha = s->g[j];
        j += 2;
        d->m[i]->eta_min = eta_bound[0][i];
        d->m[i]->eta_max = eta_bound[1][i];
    }

    errorTrain = GreedyPreTrainingDBM(DatasetTrain, d, n_epochs, n_gibbs_sampling, batch_size, op);

    fprintf(stderr, "\n\nRunning TensorDBM for reconstruction on testing set ... ");
    errorTest = BernoulliDBMReconstruction(DatasetTest, d);
    fprintf(stderr, "\nOK\n");

    fprintf(stderr, "\nTraining error: %lf\nTesting error: %lf\n", errorTrain, errorTest);

    fprintf(stderr, "\nSaving outputs ... ");
    f = fopen(argv[3], "a");
    fprintf(f, "%d %lf %lf\n", iteration, errorTrain, errorTest);
    fclose(f);

    f = fopen(argv[6], "a");
    fprintf(f, "%d ", s->n);
    for (i = 0; i < s->n; i++)
        fprintf(f, "%lf ", s->g[i]);
    fprintf(f, "\n");
    fclose(f);
    fprintf(stderr, "Ok!\n");

    DestroyTensor(&s->t_g, s->n);
    for (i = 0; i < s->m; i++)
    {
        DestroyTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */
        DestroyTensor(&s->a[i]->t_v, s->n);
        DestroyTensor(&s->a[i]->t_xl, s->n);
    }

    for (i = 0; i < 2; i++)
        free(eta_bound[i]);
    free(eta_bound);
    free(n_hidden_units);
    DestroySearchSpace(&s, _PSO_);
    DestroyDataset(&DatasetTrain);
    DestroyDataset(&DatasetTest);
    DestroySubgraph(&Train);
    DestroySubgraph(&Test);
    DestroyDBM(&d);

    return 0;
}
