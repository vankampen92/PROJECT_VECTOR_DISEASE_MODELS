/* 
   JAC_sys_MacDonaldRoss.c is characterized by the following features:
   
   Jacobian corresponding to the ODE system implemented in ODE_sys_MacDonaldRoss.c:
 
   JACOBIAN_matrix_MacDonaldRoss.c needs to be compiled
   together with JAC_sys_MacDonaldRoss.c (but not the other
   way around). In JACOBIAN_matrix_MacDonaldRoss.c you will find
   the actual evaluation of the JACOBIAN matrix:
   
   evaluating_Jacobian_Matrix(m, y, t, W, P);
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
  int i,W;
  double M,H, H_2, K, Q_Sigma_Deriv, Q_Recov_Deriv;
  Parameter_Table * P;
  gsl_matrix_view dfdy_mat;
  gsl_matrix * m;

  P = (Parameter_Table *)params;
  W = 1; /* Label for Infectious Mosquitoes */
  
  dfdy_mat = gsl_matrix_view_array(dfdy, 2, 2);
  m = &dfdy_mat.matrix;

  /* Setting the Jacobian matrix evaluated at (y[0], ..., y[W]) */

  /* Optimally, this Function should be inline... */
  evaluating_JACOBIAN_Matrix(m, y, t, 1, P);
  /* End of setting the Jacobian matrix evaluated at (y[0], ..., y[W]) */
  
  return GSL_SUCCESS;
}

