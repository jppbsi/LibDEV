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

//-------------------------------------------------------
// Changes for the CEC '19 paper.

/* It initializes an allocated search space
Parameters:
sg: training subgraph
classes_list: list of lists of elements of each class.
perc: percentage of samples tobe used as prototypes
opt_id: identifier of the optimization technique
m: number of agents */
SearchSpace *CreateInitializeSearchSpaceOPF(Subgraph *sg, Class_list *classes_list, float perc, int opt_id, int m){

   int i, j, k, el;


   // Counting the number of samples of each class.
   int *nelems = AllocIntArray(sg->nlabels + 1);

   for (i = 0; i < sg->nnodes; i++) {
      nelems[sg->node[i].truelabel]++;
   }


   // Allocates memory space for each class list
   // according to the number of samples.
   printf("- Allocating memory space for each class list. # classes found: %d \n", sg->nlabels);
   //Class_list classes_list[sg->nlabels+1];
   //classes_list = malloc(sizeof(Class_list)*(sg->nlabels+1));

   for (i = 1; i <= sg->nlabels; i++) {
      classes_list[i].nelems = nelems[i];
      classes_list[i].index = AllocIntArray(nelems[i]);
      classes_list[i].position = AllocIntArray(nelems[i]);
      classes_list[i].flag = AllocIntArray(nelems[i]);
   }


   // Populates the lists.
   printf("- Populating lists.\n");
   int *list_position = AllocIntArray(sg->nlabels + 1); // It only stores the current position on each list.

   for (i = 0; i < sg->nnodes; i++) {
      int curr_pos = list_position[sg->node[i].truelabel]; // current position on the list.

      classes_list[sg->node[i].truelabel].index[curr_pos] = i;
      classes_list[sg->node[i].truelabel].position[curr_pos] = sg->node[i].position;

      list_position[sg->node[i].truelabel]++;
   }


   // Computes the number of samples to be taken
   // as prototypes for each class.
   int n = 0; // number of decision variables.
   printf("- Computing number of prototypes for each class. Using %.2f of samples as prototypes...\n", perc);
   int *nprots = AllocIntArray(sg->nlabels + 1);

   for (i = 1; i <= sg->nlabels; i++) {
      nprots[i] = MAX((int)(perc * classes_list[i].nelems), 1);

      classes_list[i].nprots = nprots[i]; // Sets the number of prototypes for the given class.
      n += nprots[i];
   }


   // Proper search space initialization
   printf("- Proper search space initialization...\n");
   SearchSpace *s = NULL;
   s = CreateSearchSpace(m, n, opt_id);

   // For each agent... 
   int dvar;
   for (k = 0; k < s->m; k++) {
       //printf("Agent %d...\n", k);
      // Random selection of the samples.
      // Given a class 'i'...
      dvar = 0;

      for (i = 1; i <= sg->nlabels; i++) {
         // Select 'nprots[i]' samples.
         for (j = 0; j < classes_list[i].nprots; j++) {
            do {
               el = RandomInteger(0, classes_list[i].nelems - 1);
            } while(classes_list[i].flag[el] == 1);

            // Sets decision variable value.
            s->a[k]->x[dvar] = (double)el;
            //s->a[k]->x[dvar] = classes_list[i].position[el];

            classes_list[i].flag[el] = 1;
            dvar++;
         }
      }

      for (i = 1; i <= sg->nlabels; i++) {
         for (j = 0; j < classes_list[i].nelems; j++) {
            classes_list[i].flag[j] = 0;
         }
      }
   }

   // Setting 'LOWER' and 'UPPER' bounds of each decision variable.
   dvar = 0;
   for (i = 1; i <= sg->nlabels; i++) {
      // For the position concerning class 'i'...
      for (j = 0; j < classes_list[i].nprots; j++) {
         s->LB[dvar] = 0.0;
         s->UB[dvar] = (double)classes_list[i].nelems - 1;
         dvar++;
      }
   }

   printf("All done!\n\n");

   return s;

}

// Function to set the prototypes.
void opt_OPFPrototypes(Subgraph *sg, Class_list *classes_list, Agent *a)
{
      int i, j, pos;
      int node_idx_list;
      int node_idx;

      for (i = 1; i <= sg->nlabels; i++) {
	 pos = 0;
         for (j = 0; j < classes_list[i].nprots; j++) {
            node_idx_list = (int)a->x[pos]; // Gets the position in the class list.
            node_idx = classes_list[i].index[node_idx_list];// Gets the index in the subgraph.

            sg->node[node_idx].status = opf_PROTOTYPE;

            pos++;
         }
      }  
}

void opt_OPFTraining(Subgraph *sg, Class_list *classes_list, Agent *a)
{
  int p, q, i;
  float tmp, weight;
  RealHeap *Q = NULL;
  float *pathval = NULL;

  // compute optimum prototypes
  opt_OPFPrototypes(sg, classes_list, a);

  // initialization
  pathval = AllocFloatArray(sg->nnodes);

  Q = CreateRealHeap(sg->nnodes, pathval);

  for (p = 0; p < sg->nnodes; p++)
  {
    if (sg->node[p].status == opf_PROTOTYPE)
    {
      sg->node[p].pred = NIL;
      pathval[p] = 0;
      sg->node[p].label = sg->node[p].truelabel;
      InsertRealHeap(Q, p);
    }
    else
    { // non-prototypes
      pathval[p] = FLT_MAX;
    }
  }

  // IFT with fmax
  i = 0;
  while (!IsEmptyRealHeap(Q))
  {
    RemoveRealHeap(Q, &p);

    sg->ordered_list_of_nodes[i] = p;
    i++;
    sg->node[p].pathval = pathval[p];

    for (q = 0; q < sg->nnodes; q++)
    {
      if (p != q)
      {
        if (pathval[p] < pathval[q])
        {
          if (!opf_PrecomputedDistance)
            weight = opf_ArcWeight(sg->node[p].feat, sg->node[q].feat, sg->nfeats);
          else
            weight = opf_DistanceValue[sg->node[p].position][sg->node[q].position];
          tmp = MAX(pathval[p], weight);
          if (tmp < pathval[q])
          {
            sg->node[q].pred = p;
            sg->node[q].label = sg->node[p].label;
            UpdateRealHeap(Q, q, tmp);
          }
        }
      }
    }
  }

  DestroyRealHeap(&Q);
  free(pathval);
}

double OPFPrototypes_Optimization(Agent *a, va_list arg)
{
    double error;
    Subgraph *Train = NULL, *Val = NULL;
    Class_list *classes_list = NULL;

    Train = va_arg(arg, Subgraph *);
    Val = va_arg(arg, Subgraph *);
    classes_list = va_arg(arg, Class_list *);

    opt_OPFTraining(Train, classes_list, a);
    opf_OPFClassifying(Train, Val);
    error = (double)opf_Accuracy(Val);

    return 1 / error;
}

//-------------------------------------------------------


/***********************************************/
