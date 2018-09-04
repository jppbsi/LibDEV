#include "dev.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "\nusage OPFTeste <training set> <evaluating set> <testing set>\n");
        exit(-1);
    }

    double time_opt, time_classify, classification_error;
    timer tic, toc;
    FILE *f = NULL;
    Subgraph *Train = NULL, *Evaluate = NULL, *Test = NULL;

    Train = ReadSubgraph(argv[1]);
    Evaluate = ReadSubgraph(argv[2]);
    Test = ReadSubgraph(argv[3]);

    float perc = 0.25;
    int m = 15;

    Class_list *classes_list = malloc(sizeof(Class_list)*(Train->nlabels+1));

    SearchSpace *s = CreateInitializeSearchSpaceOPF(Train, classes_list, perc, _PSO_, m);

    fprintf(stderr, "\n nprots: %d ", classes_list[1].nprots);

    s->iterations = 10;
    s->w = 0.7;
    s->w_min = 0.5;
    s->w_max = 1.5;
    s->c1 = 1.7;
    s->c2 = 1.7;
    
    fflush(stderr);
    fprintf(stderr, "\nRunning AIWPSO ... ");
    gettimeofday(&tic, NULL);
    runAIWPSO(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);
    gettimeofday(&toc, NULL);
    fflush(stderr);
    fprintf(stderr, "\nOK\n");

    time_opt = ((toc.tv_sec - tic.tv_sec) * 1000.0 + (toc.tv_usec - tic.tv_usec) * 0.001) / 1000.0;
    fprintf(stdout, "\nOptimization time: %f seconds\n", time_opt);
    fflush(stderr);

    fflush(stderr);
    fprintf(stderr, "\nDeallocating memory ...");
    DestroySubgraph(&Train);
    DestroySubgraph(&Evaluate);
    DestroySubgraph(&Test);
    fflush(stderr);
    fprintf(stderr, "\nOK\n");

    f = fopen("optimization.time", "a");
    fprintf(f, "%f %f\n", time_opt, time_classify);
    fclose(f);

    DestroySearchSpace(&s, _PSO_);

    return 0;
}
