#include "dev.h"

int main(int argc, char **argv){

    if(argc != 6){
        fprintf(stderr,"\nusage LinearRegression <training set> <output results file name> <cross-validation iteration number> \
                <search space configuration file> <output best parameters file name>\n");
        exit(-1);
    }
    
    SearchSpace *s = NULL;
    int i, iteration = atoi(argv[3]), m, n;
    double **X = NULL;
    double alpha, errorTrain, *Y = NULL, *w = NULL;
    FILE *f = NULL;
        
    LoadData(argv[1], &X, &Y, &m, &n);
    w = (double *)calloc(n+1, sizeof(double));
    
    s = ReadSearchSpaceFromFile(argv[4], _PSO_);
    
    fprintf(stderr,"\nInitializing search space ... ");
    InitializeSearchSpace(s, _PSO_);
    fprintf(stderr,"\nOk\n");
    
    fprintf(stderr,"\nRunning PSO ... ");
    runPSO(s, LinearRegression_Optimization, X, Y, m, n, w);
    fprintf(stderr,"\nOK\n");
    
    fprintf(stderr,"\n\nRunning Linear Regression with best learning rate ... ");
    alpha = s->g[0];
    errorTrain = LinearRegression_Fitting(X, Y, m, n, alpha, w);
    fprintf(stderr,"\nOK\n");
    
    fprintf(stderr,"\nTraining error: %lf\n", errorTrain);
    
    fprintf(stderr, "\nSaving outputs ... ");
    f = fopen(argv[2], "a");
    fprintf(f,"%d %lf\n", iteration, errorTrain);
    fclose(f);
    
    f = fopen(argv[5], "a");
    fprintf(f,"%d ", s->n);
    for(i = 0; i < s->n; i++)
        fprintf(f, "%lf ", s->g[i]);
    fprintf(f, "\n");
    fclose(f);
    fprintf(stderr, "Ok!\n");

    free(w);
    for (i = 0; i < m; i++)
	free(X[i]);
    free(X);
    free(Y);
    DestroySearchSpace(&s, _PSO_);
    
    return 0;
}