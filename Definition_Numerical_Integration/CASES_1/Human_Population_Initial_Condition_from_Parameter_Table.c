#include <MODEL.h>

extern gsl_rng * r;

void Human_Population_Initial_Condition_from_Parameter_Table(Parameter_Table * P, double *Y)
{
  int S,E,E_1,E_2,I,R,C,S1,I1,S2,I2,S3,I3;
  int L,X,U,W;
  int A, K;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P,  
					    &S, &E, &I, &R, &C,
					    &S1, &I1, &S2, &I2, &S3, &I3,
					    &L, &X, &U, &W, &A, &K);
  Y[S] = P->s__0;
  Y[E] = P->e__0;
  Y[I] = P->i__0;
  Y[R] = P->r__0;
  Y[C] = P->c__0;
  
  R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( P, 
							    S, E, I, R, C,
							    S1, I1, S2, I2, S3, I3,
							    L, X, U, W, A, K, 
							    Y );
}
  
void R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( Parameter_Table * P, 
							       int S, int E, int I, int R, int C,
							       int S1, int I1, int S2, int I2,
							       int S3, int I3, 
							       int L, int X, int U, int W, 
							       int A, int K, 
							       double * Y)
{
    int i;
    double g_H, E_x, x, y;
    
    y = (P->s__0 + P->e__0 + P->i__0 + P->c__0 + P->r__0);
    for( i = 0; i <= C; i++ ) Y[i] = Y[i]/y * P->H;
    
    g_H  = P->n_H * P->H_Gamma /(P->n_H * P->H_Gamma + P->H_Delta);  
    x    = ( 1.0 - g_H) / ( 1.0 - pow(g_H, (double)(P->n_H)) ) ;
    E_x  = Y[E] * x;
    
    Y[E] = E_x;                                                    /* E_1 */
    for(i=1+E; i < I; i++) Y[i] = pow(g_H, (double)(i-1)) * E_x;  /* E_n */
    
    /* Rescaled Initial Conditions */
    P->s__0   = Y[S];
    P->e__0   = Y[E];
    P->i__0   = Y[I];
    P->r__0   = Y[R];
    P->c__0   = Y[C];
}


