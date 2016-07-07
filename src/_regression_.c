#include "_regression_.h"

/* Common functions */

/* It loads the data
Parameters: [fileName, X, Y, m, n]
fileName: opf file dataset
X: input data
Y: target values:
m: matrix first dimension
n: matrix second dimension */
void LoadData(char *fileName, double ***X, double **Y, int *m, int *n){
        FILE *fp = NULL;
        int i,j, m_tmp, n_tmp;
        double value;
        double **X_tmp = *X;
        double *Y_tmp = *Y;
        
        fp = fopen(fileName, "r");
        if(!fp){
                fprintf(stderr,"\nunable to open file %s\n", fileName);
                exit(-1);
        }
        
        fscanf(fp,"%d %d", &m_tmp, &n_tmp);
        X_tmp = (double **)calloc(m_tmp, sizeof(double *));
        for (i = 0; i < m_tmp; i++)
                X_tmp[i] = (double *)calloc(n_tmp+1, sizeof(double)); /* Adding extra dimension for x0 */
        Y_tmp = (double *)calloc(m_tmp, sizeof(double));
                        
        for(i = 0; i < m_tmp; i++){
                fscanf(fp,"%lf",&value); /* Reading the target first */
                Y_tmp[i] = value;
                X_tmp[i][0] = 1; /* Setting up x0 value */
                for (j = 1; j < n_tmp+1; j++){
                        fscanf(fp,"%lf",&value);
                        X_tmp[i][j] = value; /* Reading input features */
                }
        }            
        fclose(fp);
        *X = X_tmp;
        *Y = Y_tmp;
        *m = m_tmp;
        *n = n_tmp;
}

/* Linear Regression */

/* It fits a linear regression model as the error function optimized by an optimization technique
Parameters: [X, Y, m, n, w]
X: input data
Y: target values
m: matrix first dimension
n: matrix second dimension
w: parameters of the linear function */
double LinearRegression_Optimization(Agent *a, va_list arg){
    int i, j, m, n;
    double alpha, error, *w, **X, *Y;
    
    X = va_arg(arg, double **);
    Y = va_arg(arg, double *);
    m = va_arg(arg, int);
    n = va_arg(arg, int);
    w = va_arg(arg, double *);
    
    alpha = a->x[0];
   
    error = LinearRegression_Fitting(X, Y, m, n, alpha, w);
    
    return error;
}
/***********************************************/