/*
   ODE_sys_CASES_33 differs from ODE_sys_CASES_1.c in two features:
   a. this ODE system does keep track of accummulated cases (A). 
   b. this ODE system incorporate rainfall dynamics through the added
   equation for a fluctuation carrying capacity, y[K]:
   
   dydt[K] =  P->K_A * P->K_p - P->K_E * y[K];              --- K ---
*/
#include <MODEL.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

int 
function (double t, const double y[], double dydt[],
	  void *params)
{
  /* HUMAN POPULATION IN NUMBERS... 
     A lest 8 dynamic variables (including malaria clinical cases, C):
     y[0], S, Number of susceptible humans 
     y[1] to y[n_H], I, Number of latent humans (those incubating malaria)
     y[n_H+1], I, Number of infectious (to mosquitoes) humans.
     y[n_H+2], R, Number of recorvered (from disease) humans.
     
     If k = n_H+2,
     y[k+1], L, Number of Larves
     y[k+2], X, Number of non-infected mosquitoes
     y[k+3] to y[k+3+n_V-1], V_1 to V_{n_V}, Number of infected but latent mosquitoes
     y[k+3+n_V], W, Number of infectious (to the humans) mosquitoes 

     In latex format, the ODE system is as follows:

\begin{eqnarray}

     \frac{dS}{dt} &=& B - \beta\,S + \sigma\,R -\delta\,S + \rho\,C\nonumber\\
     \frac{dE}{dt} &=& \beta\,S - \delta\,E -\gamma\,E\nonumber\\
     \frac{dI}{dt} &=& (1-\xi)\,\gamma\,E - \eta\,\beta\,\,I + \nu\,\,C - r\,\,I-\Psi\,\,I-\,\delta\,I\nonumber\\
     \frac{dR}{dt} &=& -\sigma R + r\,\,I -\delta\,R\nonumber\\
     \frac{dC}{dt} &=& \xi\,\gamma\,E + \eta\,\beta\,I -\nu\,C - \rho\,C-\alpha\,\,C -\delta\,C
\end{eqnarray}
  */
  int i; 
  int S, E, I,R,C,A;
  int L,X,U,W;
  int K;
  double f, M,H;
  double M_Fecundity, L_Devel;

  Parameter_Table * P = (Parameter_Table *)params;


  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);
  H = total_Humans(y, P);
  /* Total human population */
  P->H = H;

  P->H_Beta  = Beta_Function(P, y[W]);  
  P->H_Sigma = Queu_Function_Sigma(P, y[W], P->H_Sigma_0, P->W_Sigma);
  P->H_Recov = Queu_Function_Recovery(P, y[W], P->H_Recov_0, P->W_Recov);
     
  dydt[0] = - P->H_Beta*y[0] + P->H_Birth*H - P->H_Delta*y[0] + P->H_Sigma*y[R] + P->H_Rho*y[C];  /* S   */

  dydt[1] = + P->H_Beta*y[0] - P->n_H*P->H_Gamma*y[1] - P->H_Delta*y[1];                          /* E_1 */  
  for(i=2; i<=P->n_H; i++){                                                                       /* E_n */
    dydt[i] = P->n_H*P->H_Gamma*y[i-1] - P->n_H*P->H_Gamma*y[i] - P->H_Delta*y[i];
  }    

  dydt[I] = - P->H_Eta *P->H_Beta*y[I] + P->H_Nu*y[C] + (1.-P->H_Xhi)*P->n_H*P->H_Gamma*y[I-1] - P->H_Recov*y[I] - P->H_Delta*y[I]; 
		       
  dydt[R] = P->H_Recov *y[I] - P->H_Sigma *y[R] - P->H_Delta*y[R];                    /* R   */
  
  dydt[C] = +P->H_Eta*P->H_Beta*y[I] + P->H_Xhi*P->n_H*P->H_Gamma*y[I-1] -P->H_Nu*y[C]  
    -P->H_Delta*y[C] -P->H_Rho*y[C];

  /* Applying time dependence to mosquito Parameters ...*/
  M_Fecundity = P->M_Fecundity; 
  L_Devel     = P->L_Devel;
  
  //M_Fecundity = Fecundity_Mosquito_00(t, P); //M_Fecundity = P->M_Fecundity;
  //L_Devel  = L_Devel_Mosquito(t, P); //L_Devel     = P->L_Devel;

  M = 0.;
  for(i=X; i<= W; i++) M += y[i];

  dydt[L] =   M_Fecundity *M* (1 - y[L]/y[K]) - P->L_Delta*y[L] - L_Devel*y[L];      /* L   */ 
  
  /* Fraction of infectious humans, f */
  f = (y[I] + y[C])/ P->H;

  dydt[X] = - P->M_a*P->M_c*f*y[X] - P->M_Delta*y[X] + L_Devel*y[L] + P->M_Imm;      /* X   */
  
  dydt[U] = P->M_a*P->M_c*f*y[X]- P->M_Delta*y[U] - P->n_V*P->M_Gamma*y[U];          /* V_1 */   
  for(i=U+1; i < W; i++){                                                            /* V_n */
    dydt[i] = + P->n_V*P->M_Gamma*y[i-1] - P->M_Delta*y[i] - P->n_V*P->M_Gamma*y[i]; 
  }

  dydt[W] =  P->n_V*P->M_Gamma*y[W-1] - P->M_Delta*y[W];                             /* W   */ 

  dydt[A] = +P->H_Eta*P->H_Beta*y[I] + P->H_Xhi*P->n_H*P->H_Gamma*y[I-1];            /* A   */
  
  dydt[K] =  P->K_A * P->K_p - P->K_E * y[K];                                        /* K   */
 
  return GSL_SUCCESS;
}
