#include <MODEL.h>

extern gsl_rng * r;

void Human_Population_Initial_Condition_from_Parameter_Table(Parameter_Table * P, double *Y)
{
  int S,E,E_1,E_2,I,R,C,S1,I1,S2,I2,S3,I3;
  int L,X,U,W,A;
  int K;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P,
					   &S, &E, &I, &R, &C,
					   &S1, &I1, &S2, &I2, &S3, &I3,
					   &L, &X, &U, &W, &A, &K);

  Y[S1] = P->s1__0;
  Y[I1] = P->i1__0;
  Y[S2] = P->s2__0;
  Y[I2] = P->i2__0;
  Y[S3] = P->s3__0;
  Y[I3] = P->i3__0;
  Y[R]  = P->r__0;
  
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
    double g_H, H, x, y;

    H = P->H;

    y = (P->s1__0 + P->i1__0 + P->s2__0 + P->i2__0 + P->s3__0 + P->i3__0 + P->r__0 );
    for( i = 0; i <= C; i++ ) Y[i] = Y[i]/y * P->H;
    
    /* Rescaled Initial Conditions */
    P->s1__0   = Y[S1];
    P->i1__0   = Y[I1];
    P->s2__0   = Y[S2];
    P->i2__0   = Y[I2];
    P->s3__0   = Y[S3];
    P->i3__0   = Y[I3];
    P->r__0    = Y[R];
}




