#ifndef _DBN_H
#define _DBN_H

#include "dev.h"

/* Deep Belief Networks */

double Bernoulli_BernoulliDBN4Reconstruction(Agent *a, va_list arg); /* It executes a Bernoulli-Bernoulli DBN and returns the reconstruction error */
double Bernoulli_BernoulliDBN4ReconstructionWithDropout(Agent *a, va_list arg); /* It executes a Bernoulli-Bernoulli DBN with Dropout and returns the reconstruction error */
double Bernoulli_BernoulliDBN4ReconstructionWithDropconnect(Agent *a, va_list arg); /* It executes a Bernoulli-Bernoulli DBN with Dropconnect and returns the reconstruction error */
/***********************************************/

#endif