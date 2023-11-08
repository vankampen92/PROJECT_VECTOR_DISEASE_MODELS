/*
   JACOBIAN_matrix_CASES_1.c is a companion file of JAC_sys_CASES_1.c
   and it is characterized by the following features:

   Jacobian corresponding to the ODE system implemented in ODE_sys_CASES_1.c:

   1. The recovery of CASES from clinical treatment. In ODE_sys_CASES_1.c, recovered individuals
   through treatment do no develop immunity at all, but reenter the susceptible class.

   2. Different possibilites to implement the dependence of the force of infection,
   $\beta$, on the mosquito infectious population, y[W], through a #define BETA_DERIVATIVE

   The Jacobian does not have any explicity dependence on time.

   Notice that JACOBIAN_matrix_CASES_1.c could be compiled
   independently from JAC_sys_CASES_1.c, but not the other
   way around.
*/
#include <MODEL.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

#define BETA_DERIVATIVE (Beta_Derivative_1(P,y[W]))

void evaluating_JACOBIAN_Matrix( gsl_matrix * m, const double *y, double t, int W_DUMMY,
				 Parameter_Table * P)
{
  int i,k;
  double W_N, M, H, H_2;
  double f; /* Infectious Humans */
  int S, E, I, R, C;
	int S1, I1, S2, I2, S3, I3;
  int L, X, U, W;
  int A, K;


  /* Setting the Jacobian matrix evaluated at (y[0], ..., y[W]) */
  /* First, setting entries to zero... */
  gsl_matrix_set_zero(m);

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P,
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,
					   &L, &X, &U, &W,
					   &A, &K);

  /* Total human population: C O N S T A N T */
  H = total_Humans ( y, P);
  P->H = H;
	H_2 = H*H;

  /* Total mosquito population */
  M = 0.;
  for(i = X; i <= W; i++) M += y[i];

  W_N = P->M_a * y[W]/H;

  P->H_Beta =  Beta_Function(P, y[W]);
  P->H_Recov = P->H_Recov_0;

#include  <include.JAC_sys_SnInR.c>

  f = (y[I1] + P->H_mM_c*y[I2] + pow(P->H_mM_c, 2)*y[I3]) / H;

#include  <include.JAC_sys_LXVnW.c>

  /* End of setting the Jacobian matrix evaluated at (y[0], ..., y[W]) */
}
