/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                            David Alonso, 2017 (c)                         */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef THE_BASIC_C_HEADER_FILES
#define THE_BASIC_C_HEADER_FILES
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#endif

#if defined NUMERICAL_RECIPES
#ifndef NUMERICAL_RECIPES_LIBRARY
#define NUMERICAL_RECIPES_LIBRARY
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Numerical Recipes Header Files:                                           */
#include <nr.h>                                                           
#include <nrutil.h>                                                       
#include <complex.h>						            
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#endif
#endif

#ifndef GSL_HEADER_FILES
#define GSL_HEADER_FILES
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_sort.h>
#include <gsl/gsl_sort_vector.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_odeiv.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_complex.h>
#endif

#include <stat.h> 
#include <GSL_stat.h>

#if defined CPGPLOT_REPRESENTATION
/* General header file from PGPLOT distribution */
#include <cpgplot.h>
#include <cpgplot_UTL.h>
/* 
 * These header files contain function prototypes
 * of my hand-made cpgplot-based plotting procedures
 */
#if defined FILE_REPRESENTATION 
#include <Parameter_CPGPLOT_FILE.h>
#else
#include <Parameter_CPGPLOT.h>
#endif

#include <CPGPLOT___X_Y.h> 
#include <CPGPLOT___G_R_I_D.h>
#endif
