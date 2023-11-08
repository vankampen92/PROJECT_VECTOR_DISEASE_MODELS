#include "../Include/MODEL.h"

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

int Feasibility_Condition_H(Parameter_Table *P, double W, double y)
{
  
  int Y;
  double a, B;
    
  B = Beta_Function(P, W);
  P->H_Beta = B;

  a = z_Function(P);
        
  if ( (a > 0.0) && (W > 0.0) && (y > 0.0) && (y < 1.0) ){
    Y=1;
  }
  else{
    Y=0;
  }  
  
  return(Y);
}

void stable_Solution(double y, double W, Parameter_Table *P, double *Y)
{
  /* 
     This function returns the values of the different population fractions
     (mosquitoes and humans) at equilibrium 
  */
  int i,j;
  
  double S,E_1,I,R,C,S1,I1,S2,I2,S3,I3;
  
  double L,X,V_1;
  double B; /* Force of infection */
  double M,H;
  double g, g_M,g_H,z,q;
  double E_Total;

  int S_; int E_; int I_; int R_; int C_; int S1_; int I1_; int S2_; int I2_; int S3_; int I3_;  
  int L_; int X_; int U_; int W_; int A_; 
  int K_;
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P, 
					    &S_, &E_, &I_, &R_, &C_, &S1_, &I1_, &S2_, &I2_, &S3_, &I3_,  
					    &L_, &X_, &U_, &W_, &A_, 
					    &K_);

  H = P->H;                             /* Total Human Population */
  B = P->H_Beta = Beta_Function(P, W);
  P->H_Recov = Queu_Function_Recovery(P, W, P->H_Recov_0, P->W_Recov);
  P->H_Sigma = Queu_Function_Sigma(P, W, P->H_Sigma_0, P->W_Sigma);
  
  g_H = P->n_H * P->H_Gamma /(P->n_H * P->H_Gamma + P->H_Delta);  
  g   = pow(g_H,(double)P->n_H);
 
  z = z_Function(P); q = q_Function(P);
  
#if defined ODE    
  S = Y[S_] = 1./(1+z) * H;                                                  /* S   */
#else
  S = 1./(1+z) * H;                                                          /* S   */
#endif
  
   E_1 = Y[E_] = B/(P->H_Delta + P->n_H*P->H_Gamma) * S;                     /* E_1 */

  E_Total = B/P->H_Delta*(1-g)* S;

  for(i=1+E_; i < I_; i++){                                                  /* E_n */
    Y[i] = pow(g_H, (double)(i-1)) * E_1;
  }   
  
  /* Stable values: Humans*/
  I = Y[I_] = B *(P->H_Nu + (1.-P->H_Xhi)*(P->H_Rho+P->H_Delta))/q * g * S;  /* I   */

  R = Y[R_] = P->H_Recov / (P->H_Sigma + P->H_Delta) * I;                    /* R   */

  C = Y[C_] = B* (P->H_Eta*B + P->H_Xhi*(P->H_Recov+P->H_Delta))/q *g * S;   /* C   */


  /* Stable values: Mosquitoes */
  M = Total_Mosquito_Steady_State(P);   /* Total Mosquito Population */
  g_M = P->n_V * P->M_Gamma /(P->n_V * P->M_Gamma + P->M_Delta);
  
  Stable_Solution_Partial_Mosquito_Constant_Population( P, M, g_M, y, W, 
					                L_, W_, Y );                                                  
} 

void stable_Solution_Free_Disease(Parameter_Table *P, double * Y)
{
  int i,S,E,I,R,C,S1,I1,S2,I2,S3,I3,L,X,U,W;

  int K,A;
  double M;
  /*    L a b e l s      */  
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P, 
					    &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					    &L, &X, &U, &W, 
					    &A, &K);
#if defined ODE  
  Y[S] = P->H;                           /* S   */
#endif
  
  Y[E] = 0.0;                            /* E_1 */
  for(i=1+E; i < I; i++){                /* E_n */
    Y[i] = 0.0;
  }

  Y[I] = 0.0;                            /* I   */

  Y[R] = 0.0;                            /* R   */

  Y[C] = 0.0;                            /* C   */

  /* Mosquito */

  M = Total_Mosquito_Steady_State(P); 

  Stable_Solution_Partial_Mosquito_Constant_Population_Free_Disease (P, M, X, W, Y );
}

double C_fixed_Points(Parameter_Table *P, double EPSILON)
{
  double x;
  double W_1, y_1;

  int S,E,I,R,C,S1,I1,S2,I2,S3,I3,L,X,U,W;
  int A,K;
  /*    L a b e l s      */  
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P, 
					    &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					    &L, &X, &U, &W, 
					    &A, &K);

  double * y_Sol = (double *)calloc( (W+1), sizeof(double));

  if (Feasibility_Condition_M(P) == 1) {

    W_y_fixed_Points_Lower(P, EPSILON, &W_1, &y_1);
    //W_y_fixed_Points_Upper(P, EPSILON, &W_1, &y_1);  
  
    stable_Solution(y_1, W_1, P, y_Sol);

  }
  else{

    stable_Solution_Free_Disease(P, y_Sol);
  }

  x = y_Sol[C];
  
  free(y_Sol);
  return(x);
}
