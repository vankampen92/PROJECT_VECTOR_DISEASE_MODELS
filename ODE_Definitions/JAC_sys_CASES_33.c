/* 
   JAC_sys_CASES_3.c differs from CASES_1 in the accummulated number of
   cases and there is an equation for the evolution of the karrrying
   capacity.

*/

#include <MODEL.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

#define BETA_DERIVATIVE (Beta_Derivative_1(P,y[W]))

int 
jacobian (double t, const double y[], double *dfdy, double dfdt[],
	  void *params)
{
  /* HUMAN POPULATION IN NUMBERS... 
     A lest 7 dynamic variables:
     y[0], S, Number of susceptible humans 
     y[1] to y[n_H], I, Number of latent humans (those incubating malaria)
     y[n_H+1], I, Number of infectious (to mosquitoes) humans.
     y[n_H+2], R, Number of recorvered (from disease) humans.
     y[n_H+3], C, Number of cases (clinical malaria) humans
     
     If k = n_H+3,
     y[k+1], L, Number of Larves
     y[k+2], X, Number of non-infected mosquitoes
     y[k+3] to y[k+3+n_V-1], V_1 to V_{n_V}, Number of infected but latent mosquitoes
     y[k+3+n_V], W, Number of infectious (to humans) mosquitoes 
  
     M, Total mosquito population.
     H, Total human population.
     K, Fluctuation carryig capacity.

  */
  void evaluating_JACOBIAN_Matrix(gsl_matrix *, const double *, double, int, Parameter_Table *);
  int i,k,W,A;
  double M,H, H_2, K, Q_Sigma_Deriv, Q_Recov_Deriv;
  Parameter_Table * P;
  gsl_matrix_view dfdy_mat;
  gsl_matrix * m;

  P = (Parameter_Table *)params;
  W = P->n_H + 3 + 3 + P->n_V; /* If n_H = N_V = 1, then W = 8   */
  A = W + 1;                   /* A, labelling accumulated cases */
  k = P->n_H + 3;
  
  dfdy_mat = gsl_matrix_view_array(dfdy, W+3, W+3);
  m = &dfdy_mat.matrix;

  /* Setting the Jacobian matrix evaluated at (y[0], ..., y[W], y[A]) */

  /* Optimally, this Function should be inline... */
  evaluating_JACOBIAN_Matrix(m, y, t, W, P); 
  /* End of setting the Jacobian matrix evaluated at (y[0], ..., y[W]) */

  return GSL_SUCCESS;
}

