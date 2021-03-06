#include "_opf_.h"

/* Supervised OPF with k-nn adjacency relation */

/* It learns the k-neighbourhod size (parameter k)
Parameters:
k: neighborhood size
Train: training graph
Val: validating graph */
double opfknn_LearningK(Agent *a, va_list arg)
{
    double error;
    int k;
    Subgraph *Train = NULL, *Val = NULL;

    Train = va_arg(arg, Subgraph *);
    Val = va_arg(arg, Subgraph *);
    k = a->x[0];

    Train->bestk = k;

    opf_CreateArcs(Train, Train->bestk);
    opf_PDF(Train);
    opf_OPFClustering4SupervisedLearning(Train);
    opf_DestroyArcs(Train);

    opf_OPFknnClassify(Train, Val);
    error = (double)opf_Accuracy(Val);

    return 1 / error;
}

/* Unsupervised OPF with k-nn adjacency relation */

/* It optimizes the parameter kmax for OPF_CLUSTER
Parameters:
Train: training graph
Val: validating graph
kmax: maximum degree for the knn graph */
double OPFcluster_Optimization(Agent *a, va_list arg)
{
    int kmax, i;
    double error;
    Subgraph *Train = NULL, *Val = NULL;

    Train = va_arg(arg, Subgraph *);
    Val = va_arg(arg, Subgraph *);
    kmax = a->x[0];

    opf_BestkMinCut(Train, 1, kmax); /* default kmin = 1 */

    opf_OPFClustering(Train);

    if (Train->node[0].truelabel != 0)
    {
        Train->nlabels = 0;
        for (i = 0; i < Train->nnodes; i++)
        {
            if (Train->node[i].root == i)
                Train->node[i].label = Train->node[i].truelabel;
            else
                Train->node[i].label = Train->node[Train->node[i].root].truelabel;
        }
        for (i = 0; i < Train->nnodes; i++)
        {
            if (Train->node[i].label > Train->nlabels)
                Train->nlabels = Train->node[i].label;
        }
    }
    else
        for (i = 0; i < Train->nnodes; i++)
            Train->node[i].truelabel = Train->node[i].label + 1;

    opf_OPFClassifying(Train, Val);
    error = (double)opf_Accuracy(Val);

    return 1 / error;
}

/* It executes a OPF Ensemble-pruning and it outputs the best classifiers
Parameters:
Train: vector of subgraphs of training set in the OPF format
Val: evaluation set in the OPF format
*/
double OPFpruning_ensemble(Agent *a, va_list arg)
{

    double acc = 0.0, lambda = 0.0, micro = 0.0, SL = 0.0;
    int i, j, n = 0, pass = 0, DL = 0, *psi = NULL, *poll_label = NULL;
    Subgraph **ensembleTrain = NULL, *ensembleVal = NULL;

    ensembleTrain = va_arg(arg, Subgraph **);
    ensembleVal = va_arg(arg, Subgraph *);
    n = va_arg(arg, int);

    psi = (int *)calloc(n, sizeof(int)); /* For ensemble-pruning in LibOPT-plus to LibOPF */

    for (i = 0; i < n; i++)
        micro += a->x[i];

    for (i = 0; i < n; i++)
    {
        micro /= n; /* Mean of the weights of the classifiers */
        for (i = 0; i < n; i++)
        {
            if (a->x[i] < micro)
            {
                DL++;                            /* DL is the number of classifiers whose weight is less than micro */
                SL += pow((a->x[i] - micro), 2); /* Squaring the difference */
            }
        }
        SL = sqrt((1 / (double)DL) * SL);
        lambda = micro - SL;
        for (i = 0; i < n; i++)
        {
            if (a->x[i] > lambda)
            {
                psi[i] = 1;
                pass = 1;
            }
            else
                psi[i] = 0;
        }
    }

    /* Ensembling labels */
    if (pass)
    {
        int **ensemble_label = (int **)malloc(ensembleVal->nnodes * sizeof(int *));
        for (i = 0; i < ensembleVal->nnodes; i++)
            ensemble_label[i] = AllocIntArray(n + 1);
        for (i = 0; i < n; i++)
        {
            if (psi[i])
            {
                opf_OPFClassifying(ensembleTrain[i], ensembleVal);
                for (j = 0; j < ensembleVal->nnodes; j++)
                {
                    ensemble_label[j][i] = ensembleVal->node[j].label;
                    ensembleVal->node[j].label = 0;
                }
            }
        }

        /* Majority voting */
        int k, aux, label = 0;
        poll_label = (int *)calloc((ensembleVal->nlabels + 1), sizeof(int));
        for (i = 0; i < ensembleVal->nnodes; i++)
        {
            aux = 0;
            for (j = 0; j < n; j++)
            {
                if (psi[j])
                    poll_label[ensemble_label[i][j]]++;
            }
            for (k = 0; k <= ensembleVal->nlabels; k++)
            {
                if (poll_label[k] > aux)
                {
                    aux = poll_label[k];
                    label = k;
                }
                poll_label[k] = 0;
            }
            ensembleVal->node[i].label = label;
        }

        for (i = 0; i < ensembleVal->nnodes; i++)
            free(ensemble_label[i]);
        free(ensemble_label);
        free(poll_label);
        acc = opf_Accuracy(ensembleVal);
    }
    else
    {
        printf("\nThere is no classification requirement in this step!\n");
        acc = 0.000001;
    }
    free(psi);

    return (1 / acc);
}
/***********************************************/