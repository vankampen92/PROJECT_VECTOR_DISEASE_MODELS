#include "../Include/MODEL.h"
#include "extern.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>

double q_Function(Parameter_Table *P)
{
  double q;

  q = P->H_Eta*P->H_Beta*(P->H_Rho+P->H_Delta) + (P->H_Recov+P->H_Delta)*(P->H_Nu+P->H_Rho+P->H_Delta);

  return(q);
}

double z_Function(Parameter_Table *P)
{
  double z, q, g, g_H;
  
  q = q_Function(P);

  g_H = P->n_H * P->H_Gamma /(P->n_H * P->H_Gamma + P->H_Delta);  
  g   = pow(g_H,(double)P->n_H);

  z = P->H_Beta*((1-g)/g/P->H_Delta + (P->H_Nu+(1.-P->H_Xhi)*(P->H_Rho+P->H_Delta))/q *(1. + P->H_Recov/(P->H_Sigma+P->H_Delta)) + (P->H_Eta*P->H_Beta + P->H_Xhi*(P->H_Recov+P->H_Delta))/q) *g;

  return(z);
}

void stable_Solution_Free_Disease(Parameter_Table *P, double *Y)
{
  int i,I,R,C,L,X,U,W;
  double M;
                        /*    L a b e l s      */
  I = 1 + P->n_H;      /***********************/             /* I   */
  R = 2 + P->n_H;     /***********************/              /* R   */  
  L = R + 1;        /***********************/                /* L  */
  X = R + 2;       /***********************/                 /* X  */
  U = R + 3;      /***********************/                  /* U, first latent mosquito class */
  W = R + 3 + P->n_V;                                        /* W  Infectious class */

  Y[0] = P->H;                           /* S   */

  Y[1] = 0.0;                            /* E_1 */
  for(i=2; i<=P->n_H; i++){              /* E_n */
    Y[i] = 0.0;
  }

  Y[I] = 0.0;                            /* I   */

  Y[R] = 0.0;                            /* R   */

  /* Mosquito */

  if (Feasibility_Condition_M(P)== 1){
    M = Total_Mosquito_Steady_State(P);
  }
  else{
    M = 0.0;
  }

  Y[L]  = P->M_Delta / P->L_Devel * M;   /* L   */

  Y[X]  = M;                             /* X   */

  Y[U]  = 0.0;                           /* V_1 */
  for(i=C+4; i < W; i++){                /* V_n */
    Y[i] = 0.0;
  }
  Y[W] = 0.0;                            /* W   */
}
