#include "dev.h"
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        fprintf(stderr, "\nusage OPFTeste <training set> <evaluating set> <testing set> <opt_id>\n");
        exit(-1);
    }

    // -----------------------------------------------------------------
    // MAIN PARAMETERS:

    int opt_id = atoi(argv[4]);     // Optimization algorithm
    float perc = 0.2;  // Percentage of samples of each class to be used as prototypes.
    int m = 20;			// # of agents.

	// DEFAULT: m = 15, perc = 0.05.

    // -----------------------------------------------------------------

    int p;
	char alg[10];

    double time_opt, time_eval, time_test;
    timer tic, toc;

    Subgraph *Train = NULL, *Evaluate = NULL, *Test = NULL;
    Train = ReadSubgraph(argv[1]);
    Evaluate = ReadSubgraph(argv[2]);
    Test = ReadSubgraph(argv[3]);


    Class_list *classes_list = malloc(sizeof(Class_list)*(Train->nlabels+1));

    SearchSpace *s = CreateInitializeSearchSpaceOPF(Train, classes_list, perc, opt_id, m);
    s->iterations = 5;

    switch (opt_id){
        case _PSO_:
			strcpy(alg, "_PSO_");

            s->w = 0.7;
            s->w_min = 0.5;
            s->w_max = 1.5;
            s->c1 = 1.7;
            s->c2 = 1.7;

            fflush(stderr);
            fprintf(stderr, "\nRunning _PSO_ ... ");
            gettimeofday(&tic, NULL);

            runPSO(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);

            break;

        case _BA_:
			strcpy(alg, "_BA_");

			s->f_min = 0;
			s->f_max = 0;
			s->r = 0.5;
			s->A = 1.5;

            fflush(stderr);
            fprintf(stderr, "\nRunning _BA_ ... ");
            gettimeofday(&tic, NULL);

            runBA(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);

            break;

        case _FPA_:
			strcpy(alg, "_FPA_");

            s->beta = 1.5;
            s->p = 0.8;

            fflush(stderr);
            fprintf(stderr, "\nRunning _FPA_ ... ");
            gettimeofday(&tic, NULL);

            runFPA(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);

            break;

        case _FA_:
			// Not working!

			/*strcpy(alg, "_FA_");

            s->alpha = 0.2;
            s->beta = 1;
            s->gamma = 1;

            fflush(stderr);
            fprintf(stderr, "\nRunning _FA_ ... ");
            gettimeofday(&tic, NULL);

            runFA(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);*/

            break;

        case _CS_:
			strcpy(alg, "_CS_");

            s->beta = 1.5;
            s->p = 0.25;
            s->alpha = 0.8;

            fflush(stderr);
            fprintf(stderr, "\nRunning _CS_ ... ");
            gettimeofday(&tic, NULL);

            runCS(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);

            break;

        case _GP_:
        case _GA_:
			strcpy(alg, "_GA_");

            s->pMutation = 0.2;

            fflush(stderr);
            fprintf(stderr, "\nRunning _GA_ ... ");
            gettimeofday(&tic, NULL);

            runGA(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);

            break;

        case _BHA_:
			strcpy(alg, "_BHA_");

            fflush(stderr);
            fprintf(stderr, "\nRunning _BHA_ ... ");
            gettimeofday(&tic, NULL);

            runBHA(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);

            break;

        case _WCA_:
        case _MBO_:
        case _ABC_:
			strcpy(alg, "_ABC_");

            s->limit = 10;

            fflush(stderr);
            fprintf(stderr, "\nRunning _ABC_ ... ");
            gettimeofday(&tic, NULL);

            runABC(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);

            break;

        case _BSO_:
			strcpy(alg, "_BSO_");

            s->k = 7;
            s->p_one_cluster = 0.8;
            s->p_one_center = 0.4;
            s->p_two_centers = 0.5;

            fflush(stderr);
            fprintf(stderr, "\nRunning _BSO_ ... ");
            gettimeofday(&tic, NULL);

            runBSO(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);

            break;

        case _JADE_:
        case _COBIDE_:
        case _BSA_:
			strcpy(alg, "_BSA_");

            s->mix_rate = 1.0;
            s->F = 3;

            fflush(stderr);
            fprintf(stderr, "\nRunning _BSA_ ... ");
            gettimeofday(&tic, NULL);

            runBSA(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);

            break;

        case _ABO_:
        case _HS_:
			strcpy(alg, "_HS_");

            s->HMCR = 0.7;
            s->PAR = 0.7;
            s->PAR_min = 0;
            s->PAR_max = 1;
            s->bw = 10;
            s->bw_min = 0;
            s->bw_max = 20;

            fflush(stderr);
            fprintf(stderr, "\nRunning _HS_ ... ");
            gettimeofday(&tic, NULL);

            runHS(s, OPFPrototypes_Optimization, Train, Evaluate, classes_list);

            break;

        case _LOA_:

            break;

        default:
            fprintf(stderr, "\nInvalid optimization identifier @CreateAgent\n.");
            return NULL;
            break;
    }

    gettimeofday(&toc, NULL);
    fflush(stderr);
    fprintf(stderr, "\nOK\n");

    time_opt = ((toc.tv_sec - tic.tv_sec) * 1000.0 + (toc.tv_usec - tic.tv_usec) * 0.001) / 1000.0;
    fprintf(stdout, "\nOptimization time: %f seconds\n", time_opt);
    fflush(stderr);

    // -----------------------------------------------------------------
    // Info about number of portotypes of each class.

    int counter[Train->nlabels];
    int non_prot = 0;

    for (p = 0; p < Train->nlabels; p++) {
        counter[p] = 0;
    }
    for (p = 0; p < Train->nnodes; p++) {
        if (Train->node[p].status==opf_PROTOTYPE){
            counter[Train->node[p].truelabel-1] += 1;
        } else {
            non_prot++;
        }
    }

    for (p = 0; p < Train->nlabels; p++) {
        printf("\n- # prototypes for class %d: %d", (p+1), counter[p]);
    }
    printf("\n- # NON-prototypes: %d\n\n", non_prot);

    // -----------------------------------------------------------------
    // Classification on evaluation set.

    gettimeofday(&tic, NULL);
    opf_OPFClassifying(Train, Evaluate);
    gettimeofday(&toc, NULL);

    time_eval = ((toc.tv_sec - tic.tv_sec) * 1000.0 + (toc.tv_usec - tic.tv_usec) * 0.001) / 1000.0;

    double acc_eval = (double)opf_Accuracy(Evaluate);
    acc_eval = acc_eval * 100;
    fprintf(stdout, "\nFinal accuracy on Eval: %.2f%%\n\n", acc_eval);

    // -----------------------------------------------------------------
    // Classification on testing set.

    gettimeofday(&tic, NULL);
    opf_OPFClassifying(Train, Test);
    gettimeofday(&toc, NULL);

    time_test = ((toc.tv_sec - tic.tv_sec) * 1000.0 + (toc.tv_usec - tic.tv_usec) * 0.001) / 1000.0;

    double acc_test = (double)opf_Accuracy(Test);
    acc_test = acc_test * 100;
    fprintf(stdout, "\nFinal accuracy: %.2f%%\n\n", acc_test);

    // -----------------------------------------------------------------
    // Saves accuracies, and optimization and classification times.
	// technique <accuracy_evaluation_set> <accuracy_testing_set> <optimization_time> <classification_time_evaluation_set> <classification_time_testing_set>

    FILE *f = NULL;
    f = fopen("results.res", "a");
    fprintf(f, "%s %lf %lf %f %f %f\n", alg, acc_eval, acc_test, time_opt, time_eval, time_test);
    fclose(f);

    // -----------------------------------------------------------------
    // Deallocates memory.

    fflush(stderr);
    fprintf(stderr, "\nDeallocating memory ...");
    //DestroySubgraph(&Train);
    //DestroySubgraph(&Evaluate);
    //DestroySubgraph(&Test);
    fflush(stderr);
    fprintf(stderr, "\nOK\n");

    DestroySearchSpace(&s, opt_id);

    // -----------------------------------------------------------------

    return 0;
}
