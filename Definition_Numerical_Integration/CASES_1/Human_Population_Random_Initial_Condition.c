#include <MODEL.h>

extern gsl_rng * r;

void Human_Population_Random_Initial_Condition(Parameter_Table * P, double *Y)
{
  int S,E,E_1,E_2,I,R,C,S1,I1,S2,I2,S3,I3;
  int L,X,U,W;
  int A, K;
  double Value_0, Value_1;
  
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P,  
					    &S, &E, &I, &R, &C,
					    &S1, &I1, &S2, &I2, &S3, &I3,
					    &L, &X, &U, &W, &A, &K);

  Boundary(35, &Value_0, &Value_1); P->s__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(36, &Value_0, &Value_1); P->e__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(37, &Value_0, &Value_1); P->i__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(37, &Value_0, &Value_1); P->c__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(38, &Value_0, &Value_1); P->r__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  
  Y[S] = P->s__0; 
  Y[E] = P->e__0; 
  Y[I] = P->i__0; 
  Y[R] = P->c__0; 
  Y[C] = P->r__0; 
  
  R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( P, 
							    S, E, I, R, C,
							    S1, I1, S2, I2, S3, I3,
							    L, X, U, W, A, K, 
							    Y );
}






