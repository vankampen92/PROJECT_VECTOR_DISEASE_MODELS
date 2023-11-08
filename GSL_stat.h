/* My GSL definitions for common utilities */
#ifndef THE_BASIC_C_HEADER_FILES
#define THE_BASIC_C_HEADER_FILES
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#endif

#ifndef GSL_HEADER_FILES
#define GSL_HEADER_FILES
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector.h>
#endif

void GSL_Init_Random_Seed(const gsl_rng * r);
void GSL_Init_Random_Seed_from_File(const gsl_rng * r);

int da_gsl_vector_isnan(const gsl_vector * y);
int da_vector_isnan( double *y, int n );


