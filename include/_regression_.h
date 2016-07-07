#ifndef _REGRESSION_H
#define _REGRESSION_H

#include "dev.h"

/* Common functions */
void LoadData(char *fileName, double ***X, double **Y, int *m, int *n); /* It loads the data */

/* Linear Regression */
double LinearRegression_Optimization(Agent *a, va_list arg); /* It fits a linear regression model as the error function optimized by an optimization technique */

/* Logistic Regression */
double LogisticRegression_Optimization(Agent *a, va_list arg); /* It fits a logistic regression model as the error function optimized by an optimization technique */
/***********************************************/

#endif