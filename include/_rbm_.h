#ifndef _RBM_H
#define _RBM_H

#include "dev.h"

/* Restricted Boltzmann Machines */

double BernoulliRBM(Agent *a, va_list arg); /* It executes a Bernoulli RBM and returns the reconstruction error of the label unit */
double BernoulliRBMWithDropout(Agent *a, va_list arg); /* It executes a Bernoulli RBM with Dropout and returns the reconstruction error of the label unit */
double BernoulliRBMWithDropconnect(Agent *a, va_list arg); /* It executes a Bernoulli RBM with Dropconnect and returns the reconstruction error of the label unit */
double BernoulliDRBM(Agent *a, va_list arg); /* It executes a Bernoulli DRBM and returns the classification error of the label unit */
double BernoulliDRBMWithDropout(Agent *a, va_list arg); /* It executes a Bernoulli DRBM with Dropout and returns the classification error of the label unit */
double Gaussian_BernoulliDRBM(Agent *a, va_list arg); /* It executes a Gaussian-Bernoulli DRBM and returns the classification error of the label unit */
double Gaussian_BernoulliDRBMWithDropout(Agent *a, va_list arg); /* It executes a Gaussian-Bernoulli DRBM with Dropout and returns the classification error of the label unit */
double Gaussian_BernoulliRBM(Agent *a, va_list arg); /* It executes a Gaussian-Bernoulli RBM and returns the reconstruction error of the label unit */
double Gaussian_BernoulliRBMWithDropout(Agent *a, va_list arg); /* It executes a Gaussian-Bernoulli RBM with Dropout and returns the reconstruction error of the label unit */
/***********************************************/

#endif