#include "dev.h"

int main(int argc, char **argv)
{
    if (argc != 8)
    {
        fprintf(stderr, "\nUsage: OPFknn <training set> <validating set> <testing set> <search space configuration file for OPF cluster> \
                <search space configuration file for EPNN> <output best parameters file name> <output results file name>");
        exit(-1);
    }

    SearchSpace *s_cluster = NULL, *s_epnn = NULL;
    int i, j, kmax;
    float accuracy;
    double sigma, radius;
    char fileName[256];
    FILE *f = NULL;
    Subgraph *Train = NULL, *Val = NULL, *Merge = NULL, *Test = NULL;

    gsl_vector *alpha = NULL;
    gsl_vector *lNode = NULL;
    gsl_vector *nGaussians = NULL;
    gsl_vector *nsample4class = NULL;
    gsl_vector *root = NULL;
    gsl_vector **gaussians = (gsl_vector **)malloc(2 * sizeof(gsl_vector *));
    gaussians[0] = NULL;
    gaussians[1] = NULL;

    s_cluster = ReadSearchSpaceFromFile(argv[4], _PSO_);
    s_epnn = ReadSearchSpaceFromFile(argv[5], _PSO_);

    /* Loading datasets */
    Train = ReadSubgraph(argv[1]);
    Val = ReadSubgraph(argv[2]);
    Merge = opf_MergeSubgraph(Train, Val);

    fprintf(stderr, "\nInitializing search spaces ... ");
    InitializeSearchSpace(s_cluster, _PSO_);
    InitializeSearchSpace(s_epnn, _PSO_);
    fprintf(stderr, "\nOk\n");

    /* Running optimization for OPF clustering */
    fprintf(stderr, "\nRunning PSO for OPF clustering ...");
    runPSO(s_cluster, OPFcluster_Optimization, Train, Val);
    kmax = (int)s_cluster->g[0];
    opf_ResetSubgraph(Train);
    fprintf(stderr, "\nOk\n");

    /* Running optimization for EPNN */
    fprintf(stderr, "\nRunning PSO for EPNN ...");
    fprintf(stderr, "\nOk\n");

    if (kmax)
    {
        fprintf(stderr, "\nClustering with kmax ... ");
        gaussians = opfcluster4epnn(Train, gaussians, kmax);
        nGaussians = gaussians[0];
        root = gaussians[1];
    }
    else
    {
        /* Set gaussians = nlabels if not clustering */
        nGaussians = loadLabels(Train);
    }
    /* Ordered list labels based in the OPF cluster or by number of classes in training set */
    lNode = orderedListLabel(Train, nGaussians, root);
    /* Count sample for classes */
    nsample4class = countClasses(Train, nGaussians, root);

    runPSO(s_epnn, EPNN_Optimization, Train, Val, lNode, nsample4class, nGaussians);
    sigma = s_epnn->g[0];
    radius = s_epnn->g[1];

    /* Training step */
    gsl_vector_free(nGaussians);
    gsl_vector_free(root);
    gsl_vector_free(lNode);
    gsl_vector_free(nsample4class);
    if (kmax)
    {
        gaussians = opfcluster4epnn(Merge, gaussians, kmax);
        nGaussians = gaussians[0];
        root = gaussians[1];
    }
    else
    {
        /* Set gaussians = nlabels if not clustering */
        nGaussians = loadLabels(Merge);
    }
    fprintf(stderr, "\nComputing Hyper-Sphere with radius: %lf ...", radius);
    lNode = orderedListLabel(Merge, nGaussians, root);
    nsample4class = countClasses(Merge, nGaussians, root);
    alpha = hyperSphere(Merge, radius);
    fprintf(stderr, "\nOK\n");

    /* Testing step */
    Test = ReadSubgraph(argv[3]);
    fprintf(stderr, "\nInitializing EPNN with best paramaters ... ");
    epnn(Merge, Test, sigma, lNode, nsample4class, alpha, nGaussians);
    fprintf(stderr, "\nOk\n");

    /* Accuracy step */
    fprintf(stderr, "\nComputing accuracy ...");
    accuracy = opf_Accuracy(Test);
    fprintf(stderr, "\nAccuracy: %.2f%%", accuracy * 100);

    fprintf(stderr, "\nSaving outputs ... ");
    sprintf(fileName, "%s.acc", argv[7]);
    f = fopen(fileName, "a");
    fprintf(f, "%f\n", accuracy * 100);
    fclose(f);
    f = fopen(argv[6], "a");
    fprintf(f, "%d ", 3);
    fprintf(f, "%d %lf %lf\n", kmax, sigma, radius);
    fclose(f);
    fprintf(stderr, "Ok!\n");

    DestroySearchSpace(&s_cluster, _PSO_);
    DestroySearchSpace(&s_epnn, _PSO_);
    DestroySubgraph(&Train);
    DestroySubgraph(&Val);
    DestroySubgraph(&Merge);
    DestroySubgraph(&Test);
    gsl_vector_free(alpha);
    gsl_vector_free(lNode);
    gsl_vector_free(nsample4class);
    gsl_vector_free(nGaussians);
    gsl_vector_free(root);
    free(gaussians);

    return 0;
}