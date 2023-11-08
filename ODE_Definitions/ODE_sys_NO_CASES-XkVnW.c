#include <MODEL.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

int 
function (double t, const double y[], double dydt[],
	  void *params)
{
  /* HUMAN POPULATION IN NUMBERS... 
     A lest 7 dynamic variables (no clinical malaria):
     y[0], S, Number of susceptible humans 
     y[1] to y[n_H], I, Number of latent humans (those incubating malaria)
     y[n_H+1], I, Number of infectious (to mosquitoes) humans.
     y[n_H+2], R, Number of recorvered (from disease) humans.
     
     If k = n_H+2,
     y[k+1], L, Number of Larves
     y[k+2], X, Number of non-infected mosquitoes
     y[k+3] to y[k+3+n_V-1], V_1 to V_{n_V}, Number of infected but latent mosquitoes
     y[k+3+n_V], W, Number of infectious (to the humans) mosquitoes 
  */
  int i,k;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3;
  int L,X,U,W;
  int A,K;
  double f, f_E, M,H;
  double K_0, M_Fecundity, L_Devel;

  Parameter_Table * P = (Parameter_Table *)params;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P,
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,
					   &L, &X, &U, &W, 
					   &A, &K);

  /* B E G I N : Negative Value Control:
     The evaluation of the ODE system makes NO SENSE if any y[i] is negative.
     The function below controls for all y[i] being positive and if any is a little bit 
     negative, then is made equal to zero. 
  */
  assert(P->MODEL_STATE_VARIABLES == K+1); 
  Apply_Negative_Control(y, P->MODEL_STATE_VARIABLES);
  /*     E N D ---------------------------------------------------------------------------*/
  
  /* Total human population */
  H = total_Humans ( y, P);
  P->H = H;

#include <include.ODE_sys_NO_CASES.c>
  
/* Fraction of infectious humans, f */
  f = y[I] / P->H; 

#include <include.ODE_sys_XkVnW.c>

  return GSL_SUCCESS;
}
