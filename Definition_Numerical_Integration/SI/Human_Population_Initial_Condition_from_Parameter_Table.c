#include <MODEL.h>

extern gsl_rng * r;

void Human_Population_Initial_Condition_from_Parameter_Table(Parameter_Table * P, double *Y)
{
  int S,E,E_1,E_2,I,R,C,S1,I1,S2,I2,S3,I3;
  int L,X,U,W,A;
  int K;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P,  
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  &L, &X, &U, &W, &A, &K);
 
  /* Initial values for number of humans at each class */
  /* Parameters Defining Initial Conditions: Fracions of S, E, I, and R 
   double s__0;
   double e__0;
   double i__0;
   double c__0;
  */

  R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( P, 
							    S, E, I, R, C, S1, I1, S2, I2, S3, I3,L, X, U, W, A, K, 
							    Y );
}

void Human_Population_Random_Initial_Condition_from_Parameter_Table(Parameter_Table * P, double *Y)
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

  Boundary(35, &Value_0, &Value_1); P->s__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(36, &Value_0, &Value_1); P->e__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(37, &Value_0, &Value_1); P->i__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);
  Boundary(38, &Value_0, &Value_1); P->c__0 = Value_0 + gsl_rng_uniform(r) * (Value_1 - Value_0);

  R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( P, 
							    S, E, I, R, C, S1, I1, S2, I2, S3, I3,L, X, U, W, A, K, 
							    Y );
}
  
void R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( Parameter_Table * P, 
								 int S, int E, int I, int R, int C,  int S1, int I1, int S2, int I2, int S3, int I3,
								 int L, int X, int U, int W, 
								 int A, int K, 
								 double * Y)
{
    int i;
    double g_H, H, E_x, x, y;

    H = P->H;
    
#if defined CASES_1   
    x = (P->s__0 + P->e__0 + P->i__0 + P->c__0 );
#endif
#if defined NO_CASES   
    x = (P->s__0 + P->e__0 + P->i__0 );
#endif
#if defined SEnI  
    x = (P->s__0 + P->e__0 + P->i__0);
#endif
#if defined SI   
    x = (P->s__0 + P->i__0 );
#endif

    y =0.0;

#if defined CASES_1   
    // y = + 1.0/H;
    y = gsl_rng_uniform(r);
#endif 
#if defined NO_cASES
    // y = + 1.0/H;
    y = gsl_rng_uniform(r);
#endif 

    /* Renormalization occurs... */
    P->s__0 = P->s__0 / x * (1.0 - y);
    P->e__0 = P->e__0 / x * (1.0 - y);
    P->i__0 = P->i__0 / x * (1.0 - y);
    P->c__0 = P->c__0 / x * (1.0 - y);

    g_H = P->n_H * P->H_Gamma /(P->n_H * P->H_Gamma + P->H_Delta);  
 
    x   = ( 1.0 - pow(g_H, (double)(P->n_H)) ) / ( 1.0 - g_H );

#if defined ODE
    Y[S] = P->s__0 * H;                                                        /* S   */
#endif

#ifndef SI     
    Y[E] =  E_x  = P->e__0 * H / x;                                            /* E_1 */
    
    for(i=1+E; i < I; i++){                                                    /* E_n */
      Y[i] = pow(g_H, (double)(i-1)) * E_x;
    }   
#endif 
    
    Y[I] = P->i__0 * H; 
 
#if defined CASES_33
    Y[R] = (1.0 - P->s__0 - P->i__0 - P->c__0 - P->e__0) * H; 
    
    Y[C] = P->c__0 * H;
#endif

#if defined CASES_1   
    Y[R] = (1.0 - P->s__0 - P->i__0 - P->c__0 - P->e__0) * H; 
    
    Y[C] = P->c__0 * H; 
#endif

#if defined NO_CASES
    Y[R] = (1.0 - P->s__0 - P->i__0 - P->e__0) * H; 
#endif

#if defined SEnI
    Y[I] = (1.0 - P->s__0 - P->e__0) * H;  
#endif

#if defined SI
    Y[I] = (1.0 - P->s__0) * H;  
#endif

    /* x = P->s__0 + P->i__0 + P->c__0 + P->e__0 + Y[R]/H ; */
    
    /* if( x > 1.0 || x == 1.0 ){ */
    
    /*     printf(" Sum of fractions [x] = %g\t s = %g, e = %g, i = %g, c = %g\n",  x, P->s__0,  P->e__0,  P->i__0, P->c__0); */
    /*     assert(x <= 1.0); */
    
    /*   } */
}


