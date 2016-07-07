#include "dev.h"

int main(int argc, char **argv){

    if(argc != 7){
        fprintf(stderr,"\nusage LogisticRegression <training set> <testing set> <output results file name> <cross-validation iteration number> \
                <search space configuration file> <output best parameters file name>\n");
        exit(-1);
    }
    
    SearchSpace *s = NULL;
    int i, j, iteration = atoi(argv[4]), m_train, n_train, m_test, n_test;
    double alpha, errorTrain, errorTest, *w = NULL;
    double **XTrain = NULL, **XTest = NULL;
    double *YTrain = NULL, *YTest = NULL;
    Subgraph *Train = NULL, *Test = NULL;
    FILE *f = NULL;
    
    LoadData(argv[1], &XTrain, &YTrain, &m_train, &n_train);
    LoadData(argv[1], &XTest, &YTest, &m_test, &n_test);
    w = (double *)calloc(n_train, sizeof(double));
    
    /* mapping training data to LibOPF format */
    Train = CreateSubgraph(m_train);
    Train->nfeats = n_train;
    Train->nlabels = 2;
    for(i = 0; i < m_train; i++){
        Train->node[i].feat = AllocFloatArray(n_train);
        for(j = 0; j < n_train; j++)
                Train->node[i].feat[j] = XTrain[i][j];
        Train->node[i].truelabel = YTrain[i]; 
    }
    
    /* mapping testing data to LibOPF format */
    Test = CreateSubgraph(m_test);
    Test->nfeats = n_test;
    Test->nlabels = 2;
    for(i = 0; i < m_test; i++){
        Test->node[i].feat = AllocFloatArray(n_test);
        for(j = 0; j < n_test; j++)
            Test->node[i].feat[j] = XTest[i][j];
        Test->node[i].truelabel = YTest[i]; 
    }
        
    w = (double *)calloc(Train->nfeats, sizeof(double));
    
    s = ReadSearchSpaceFromFile(argv[5], _PSO_);
    
    fprintf(stderr,"\nInitializing search space ... ");
    InitializeSearchSpace(s, _PSO_);
    fprintf(stderr,"\nOk\n");
    
    fprintf(stderr,"\nRunning PSO ... ");
    runPSO(s, LogisticRegression_Optimization, Train, w);
    fprintf(stderr,"\nOK\n");
    
    fprintf(stderr,"\n\nRunning Logistic Regression with best learning rate ... ");
    alpha = s->g[0];
    errorTrain = LogisticRegression_Fitting(Train, alpha, w);
    Logistic_Regression4Classification(Test, w);
    errorTest = 0;
    for(i = 0; i < m_test; i++){
        if(Test->node[i].truelabel != Test->node[i].label) /* Misclassification occurs */
	    errorTest++;
    }
    errorTest = (1-errorTest/Test->nnodes)*100;
    fprintf(stderr,"\nOK\n");
    
    fprintf(stderr,"\nTraining error: %lf\nTesting accuracy: %.2lf%%\n", errorTrain, errorTest);
    
    fprintf(stderr, "\nSaving outputs ... ");
    f = fopen(argv[3], "a");
    fprintf(f,"%d %lf %lf\n", iteration, errorTrain, errorTest);
    fclose(f);
    
    f = fopen(argv[6], "a");
    fprintf(f,"%d ", s->n);
    for(i = 0; i < s->n; i++)
        fprintf(f, "%lf ", s->g[i]);
    fprintf(f, "\n");
    fclose(f);
    fprintf(stderr, "Ok!\n");

    for (i = 0; i < m_train; i++)
        free(XTrain[i]);
    free(XTrain);
    free(YTrain);
    for (i = 0; i < m_test; i++)
        free(XTest[i]);
    free(XTest);
    free(YTest);
    free(w);
    DestroySubgraph(&Train);
    DestroySubgraph(&Test);
    DestroySearchSpace(&s, _PSO_);
    
    return 0;
}