/*
   JAC_sys_CASES_3.c differs from CASES_1 in the accummulated number of
   cases and there is an equation for the evolution of the carrying
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
     y[0], S1, Number of susceptible humans (S1 class)
     y[1], I1, Number of infectious humans (I1 class)
     y[2], S2, Number of susceptible humans (S2 class).
     y[3], I2, Number of infectious humans (I2 class).
     y[4], S3, Number of susceptible humans (S3 class).
     y[5], I3, Number of infectious humans (I3 class).
     y[6], R, Number of recorvered (from disease) humans.

     If k = 6,
     y[k+1], L, Number of Larves
     y[k+2], X, Number of non-infected mosquitoes
     y[k+3], V, Number of infected but latent mosquitoes
     y[k+4], W, Number of infectious (to humans) mosquitoes

     M, Total mosquito population.
     H, Total human population.
     K, Fluctuation carryig capacity.

  */
  void evaluating_JACOBIAN_Matrix(gsl_matrix *, const double *, double, int, Parameter_Table *);
  int i;

  int S, E, I, R, C, S1, I1, S2, I2, S3, I3;
  int L,X,U,W;
  int A, K, H, H_2;

  Parameter_Table * P;
  gsl_matrix_view dfdy_mat;
  gsl_matrix * m;

  P = (Parameter_Table *)params;
	H = P->H;
	H_2 = H*H;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P,
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,
					   &L, &X, &U, &W,
					   &A, &K);

  dfdy_mat = gsl_matrix_view_array(dfdy, W+1, W+1);
  m = &dfdy_mat.matrix;

  /* Setting the Jacobian matrix evaluated at (y[0], ..., y[W], y[A]) */

  /* Optimally, this Function should be inline... */
  evaluating_JACOBIAN_Matrix(m, y, t, W, P);
  /* End of setting the Jacobian matrix evaluated at (y[0], ..., y[W]) */

  return GSL_SUCCESS;
}
