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

void evaluating_JACOBIAN_Matrix(gsl_matrix * m, const double *y, double t, int W, Parameter_Table * P)
{
  int i,k, K;
  double W_N, M,H, H_2, Q_Sigma_Deriv, Q_Recov_Deriv;
  int L, X, U, I, R, C, A;

  /* Setting the Jacobian matrix evaluated at (y[0], ..., y[W]) */
  /* First, setting entries to zero... */
  gsl_matrix_set_zero(m); 
                        /*    L a b e l s      */  
  I = 1 + P->n_H;      /***********************/             /* I   */
  R = 2 + P->n_H;     /***********************/              /* R   */
  C = 3 + P->n_H;    /***********************/               /* C   */
  L = C + 1;        /***********************/                /* L  */
  X = C + 2;       /***********************/                 /* X  */
  U = C + 3;      /***********************/                  /* U, first latent mosquito class */
  //W = C + 3 + P->n_V;                                      /* W  Infectious class */
  A = W + 1;                                                 /* A, accumulated number of cases */
  K = A + 1;    /***********************/                    /* K, Fluctuating Karrying capacity */ 
 
#ifndef TIME_DEPENDENCE
  P->L_Delta     = P->L_Delta_P;
#endif
 
  /* Total human population */
  H = y[0]+y[I]+y[R]+y[C]; for(i=1; i<= P->n_H; i++) H += y[i];
  P->H = H;
  H_2 = H*H;
  /* Total mosquito population */
  M = 0.;
  for(i = C+2; i <= W; i++) M += y[i];

  W_N = P->M_a * y[W]/H;
  P->H_Beta =  Beta_Function(P, y[W]); 
  P->H_Sigma = Queu_Function_Sigma(P, y[W], P->H_Sigma_0, P->W_Sigma);
  P->H_Recov = Queu_Function_Recovery(P, y[W], P->H_Recov_0, P->W_Recov);
  Q_Sigma_Deriv = Derivative_Queu_Function_Sigma(W_N, P->H_Sigma_0, P->W_Sigma);
  Q_Recov_Deriv = Derivative_Queu_Function_Recovery(W_N, P->H_Recov_0, P->W_Recov);

  /* S row: Let dSdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */  
  gsl_matrix_set(m, 0,0, P->H_Birth - P->H_Delta - P->H_Beta);
  
  for(i=1; i<=P->n_H; i++)
    gsl_matrix_set(m, 0,i, P->H_Birth); 

  gsl_matrix_set(m, 0, I, P->H_Birth);
  gsl_matrix_set(m, 0, R, P->H_Birth + P->H_Sigma);
  gsl_matrix_set(m, 0, C, P->H_Birth + P->H_Rho);

  /* Zeros from (0,P->n_H+3+1) to (0,P->n_H+3+3+P->n_V-1) */
  gsl_matrix_set(m, 0, W, -y[0]*BETA_DERIVATIVE + y[R]*P->M_a/H*Q_Sigma_Deriv);
  
  /* E_{1} row: Let dE_{1}dt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, 1, 0, P->H_Beta);
  gsl_matrix_set(m, 1, 1, -P->H_Delta -P->n_H*P->H_Gamma);
  gsl_matrix_set(m, 1, W, y[0]*BETA_DERIVATIVE);

  /* From row E_{2} to row E_{n_H} */
  for(i=2; i<=P->n_H; i++){
    gsl_matrix_set(m, i, i-1, P->n_H*P->H_Gamma);
    gsl_matrix_set(m, i, i, -P->H_Delta-P->n_H*P->H_Gamma);
  }
  
  /* I row: Let dIdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, I, I-1, (1.-P->H_Xhi) * P->n_H*P->H_Gamma);
  gsl_matrix_set(m, I, I,  -P->H_Delta -P->H_Recov - P->H_Eta * P->H_Beta);
  gsl_matrix_set(m, I, C,   P->H_Nu);
  gsl_matrix_set(m, I, W,  -P->H_Eta*y[I]*BETA_DERIVATIVE -y[I]*P->M_a/H*Q_Recov_Deriv);
  
  /* R row: Let dRdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, R, I,  P->H_Recov);
  gsl_matrix_set(m, R, R, -P->H_Delta-P->H_Sigma);
  gsl_matrix_set(m, R, W,  P->M_a/H *(y[I]*Q_Recov_Deriv-y[R]*Q_Sigma_Deriv) );

  /* C row: Let dCdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, C, I-1, P->H_Xhi*P->n_H*P->H_Gamma );
  gsl_matrix_set(m, C, I,   P->H_Eta * P->H_Beta);
  gsl_matrix_set(m, C, C,  -P->H_Delta -P->H_Nu -P->H_Rho);
  gsl_matrix_set(m, C, W,   P->H_Eta*y[I]*BETA_DERIVATIVE);
  
  /* L row: Let dLdt be equal to F(), then the entries are defined 
     to dFdS to dFdW */

  gsl_matrix_set(m, L, L, -P->M_Fecundity*M/y[K] - P->L_Delta- P->L_Devel);
  for(i=L+1; i<= W; i++) 
    gsl_matrix_set(m, L, i, P->M_Fecundity*(1.-y[L]/y[K]));
  
  gsl_matrix_set(m, L, K, +P->M_Fecundity * M * y[L]/y[K]/y[K]); 

  /* X row: Let dXdt be equal to F(), then the entries are defined 
     to dFdS to dFdW */
  for(i=0; i<=C; i++){
    if(i == I || i == C)
      gsl_matrix_set(m, X, i, P->M_c*P->M_a*y[X]*(y[I]+y[C])/H_2 - P->M_c*P->M_a*y[X]/H);
    else
      gsl_matrix_set(m, X, i, P->M_c*P->M_a*y[X]*(y[I]+y[C])/H_2);
  }
  gsl_matrix_set(m, X, L, P->L_Devel);
  gsl_matrix_set(m, X, X, -P->M_Delta - P->M_c*P->M_a*(y[I]+y[C])/H);
  
  /* V_{1} row: Let dV_{1}dt be equal to F(), then the entries are defined 
     to dFdS to dFdW */
  for(i=0; i<=C; i++){
    if(i == I || i == C)
      gsl_matrix_set(m, U, i, -P->M_c*P->M_a*y[X]*(y[I]+y[C])/H_2 + P->M_c*P->M_a*y[X]/H);
    else
      gsl_matrix_set(m, U, i, -P->M_c*P->M_a*y[X]*(y[I]+y[C])/H_2);
  }
  gsl_matrix_set(m, U, X, P->M_c*P->M_a*(y[I]+y[C])/H);
  gsl_matrix_set(m, U, U, -P->M_Delta - P->n_V*P->M_Gamma);

  /* From row V_{2} to row V_{n_V} */
  for(i=U+1; i<W; i++){
    gsl_matrix_set(m, i, i-1, P->n_V*P->M_Gamma);
    gsl_matrix_set(m, i, i, -P->M_Delta-P->n_V*P->M_Gamma);
  }
  
  /* W row: Let dWdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, W, W-1, P->n_V*P->M_Gamma);
  gsl_matrix_set(m, W, W, -P->M_Delta);
  
  /* A row: accumulated cases... */
  /* A row: Let dCdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, A, I-1, P->H_Xhi*P->n_H*P->H_Gamma );
  gsl_matrix_set(m, A, I,   P->H_Eta * P->H_Beta);
  gsl_matrix_set(m, A, W,   P->H_Eta*y[I]*BETA_DERIVATIVE);

  /* End of setting the Jacobian matrix evaluated at (y[0], ..., y[W], y[W+1]) */

  /* K row: Karrying capacity */
  gsl_matrix_set(m, K, K, -P->K_E); 
}


