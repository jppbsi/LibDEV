#include "dev.h"

int main(int argc, char **argv)
{

    if (argc != 5)
    {
        fprintf(stderr, "\nusage FeatureSelection <training set> <evaluating set> <testing set> <search space configuration file>\n");
        exit(-1);
    }

    SearchSpace *s = NULL;
    int i;
    double time_opt, time_classify, classification_error;
    timer tic, toc;
    FILE *f = NULL;
    TransferFunc optTransfer = NULL;
    Subgraph *Train = NULL, *Evaluate = NULL, *Merge = NULL, *Test = NULL, *newTrain = NULL, *newTest = NULL;

    Train = ReadSubgraph(argv[1]);
    Evaluate = ReadSubgraph(argv[2]);
    Test = ReadSubgraph(argv[3]);
    s = ReadSearchSpaceFromFile(argv[4], _BSO_);
    optTransfer = S2TransferFunction;

    for (i = 0; i < Train->nfeats; i++)
    {
        s->LB[i] = -20;
        s->UB[i] = 20;
    }

    fprintf(stderr, "\nInitializing search space ... ");
    InitializeSearchSpace(s, _BSO_);
    fprintf(stderr, "\nOk\n");

    fflush(stderr);
    fprintf(stderr, "\nRunning BSO ... ");
    gettimeofday(&tic, NULL);
    runBSO(s, FeatureSelectionOPF, Train, Evaluate, optTransfer);
    gettimeofday(&toc, NULL);
    fflush(stderr);
    fprintf(stderr, "\nOK\n");

    time_opt = ((toc.tv_sec - tic.tv_sec) * 1000.0 + (toc.tv_usec - tic.tv_usec) * 0.001) / 1000.0;
    fprintf(stdout, "\nOptimization time: %f seconds\n", time_opt);
    fflush(stderr);

    Merge = opf_MergeSubgraph(Train, Evaluate);

    fflush(stderr);
    fprintf(stderr, "\nWriting new training and testing sets ...\n");
    newTrain = CreateSubgraphFromSelectedFeatures(Merge, s->g);
    newTest = CreateSubgraphFromSelectedFeatures(Test, s->g);
    fprintf(stderr, "\nTraining set\n");
    WriteSubgraph(newTrain, "training.bso.dat");
    fprintf(stderr, "\n\nTesting set\n");
    WriteSubgraph(newTest, "testing.bso.dat");
    fflush(stderr);
    fprintf(stderr, "\nOK\n");

    opf_OPFTraining(newTrain);
    gettimeofday(&tic, NULL);
    opf_OPFClassifying(newTrain, newTest);
    gettimeofday(&toc, NULL);
    classification_error = opf_Accuracy(newTest);

    time_classify = ((toc.tv_sec - tic.tv_sec) * 1000.0 + (toc.tv_usec - tic.tv_usec) * 0.001) / 1000.0;
    fprintf(stdout, "\nClassification time: %f seconds\n", time_classify);
    fflush(stderr);

    f = fopen("best_feats.txt", "a");
    fprintf(f, "%d %d", newTrain->nfeats, (int)s->g[0]);
    for (i = 1; i < Train->nfeats; i++)
    {
        fprintf(f, " %d", (int)s->g[i]);
    }
    fprintf(f, "\n");
    fclose(f);

    fprintf(stderr, "\nAccuracy: %.2lf%%\n", 100 * classification_error);
    f = fopen("final_accuracy.txt", "a");
    fprintf(f, "%lf\n", classification_error);
    fclose(f);

    fflush(stderr);
    fprintf(stderr, "\nDeallocating memory ...");
    DestroySubgraph(&Train);
    DestroySubgraph(&Evaluate);
    DestroySubgraph(&Merge);
    DestroySubgraph(&Test);
    DestroySubgraph(&newTrain);
    DestroySubgraph(&newTest);
    fflush(stderr);
    fprintf(stderr, "\nOK\n");

    f = fopen("optimization.time", "a");
    fprintf(f, "%f %f\n", time_opt, time_classify);
    fclose(f);

    DestroySearchSpace(&s, _BSO_);

    return 0;
}
