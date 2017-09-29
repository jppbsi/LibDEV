#include "dev.h"

int main(int argc, char **argv)
{

    if (argc != 4)
    {
        fprintf(stderr, "\nusage CombinatorialOPF <training set> <testing set> <input combinatorial matrix>\n");
        exit(-1);
    }

    int i, j, acc_index, m, n;
    double time_comb, classification_accuracy, overall_accuracy = 0, **r;
    timer tic, toc;
    FILE *f = NULL;
    Subgraph *Train = NULL, *Test = NULL, *newTrain = NULL, *newTest = NULL;

    Train = ReadSubgraph(argv[1]);
    Test = ReadSubgraph(argv[2]);

    fprintf(stderr, "\nInitializing combinatorial OPF ... ");

    f = fopen(argv[3], "r");
    fscanf(f, "%d\n", &n);
    m = pow(2, n);
    r = (double **)calloc(m, sizeof(double *));
    for (i = 0; i < m; i++)
        r[i] = (double *)calloc(n, sizeof(double));

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            fscanf(f, "%lf ", &r[i][j]);
        }
        fscanf(f, "\n");
    }
    fclose(f);
    fprintf(stderr, "\nOk\n");

    fflush(stderr);
    fprintf(stderr, "\nRunning OPF ... ");

    f = fopen("final_accuracy.txt", "a");
    gettimeofday(&tic, NULL);
    for (i = 0; i < m; i++)
    {
        newTrain = CreateSubgraphFromSelectedFeatures(Train, r[i]);
        newTest = CreateSubgraphFromSelectedFeatures(Test, r[i]);
        opf_OPFTraining(newTrain);
        opf_OPFClassifying(newTrain, newTest);
        classification_accuracy = opf_Accuracy(newTest);
        fprintf(f, "%lf\n", classification_accuracy);
        if (classification_accuracy > overall_accuracy)
        {
            overall_accuracy = classification_accuracy;
            acc_index = i;
        }
    }
    gettimeofday(&toc, NULL);
    fclose(f);
    fflush(stderr);
    fprintf(stderr, "\nOK\n");

    time_comb = ((toc.tv_sec - tic.tv_sec) * 1000.0 + (toc.tv_usec - tic.tv_usec) * 0.001) / 1000.0;
    fprintf(stdout, "\nCombination time: %f seconds\n", time_comb);
    fflush(stderr);

    f = fopen("best_feats.txt", "a");
    fprintf(f, "%d ", n);
    for (i = 0; i < n; i++)
    {
        fprintf(f, "%d ", (int)r[acc_index][i]);
    }
    fprintf(f, "\n");
    fclose(f);

    fflush(stderr);
    fprintf(stderr, "\nDeallocating memory ...");
    DestroySubgraph(&Train);
    DestroySubgraph(&Test);
    DestroySubgraph(&newTrain);
    DestroySubgraph(&newTest);
    fflush(stderr);
    fprintf(stderr, "\nOK\n");

    f = fopen("combination.time", "a");
    fprintf(f, "%f\n", time_comb);
    fclose(f);

    return 0;
}