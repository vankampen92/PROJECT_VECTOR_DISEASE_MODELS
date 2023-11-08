#include <MODEL.h>

extern gsl_rng * r;

void Human_Population_Random_Initial_Condition(Parameter_Table * P, double *Y)
{
  int S,E,E_1,E_2,I,R,C,S1,I1,S2,I2,S3,I3;
  int L,X,U,W;
  int A, K;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P,
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  &L, &X, &U, &W, &A, &K);

  /* Initial values for number of humans at each class */
  /* Parameters Defining Initial Conditions: Fracions of S, E, I, and R  */
  /* 35 */ //double s__0;
  /* 36 */ //double e__0;
  /* 37 */ //double i__0;
  /* 38 */ //double c__0;

  double Value_0, Value_1;

  Boundary(52, &Value_0, &Value_1); P->s1__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(53, &Value_0, &Value_1); P->i1__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(54, &Value_0, &Value_1); P->s2__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(55, &Value_0, &Value_1); P->i2__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(56, &Value_0, &Value_1); P->s3__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(57, &Value_0, &Value_1); P->i3__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(57, &Value_0, &Value_1); P->i3__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(38, &Value_0, &Value_1); P->r__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  
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
