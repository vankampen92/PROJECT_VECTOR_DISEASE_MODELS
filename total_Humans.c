#include <MODEL.h>

#if defined K_L_E_I_N

double total_Humans(const double *y, Parameter_Table * P)
{
  int i;
  int E_2;
  double H; /* Total Human Population */
  
  E_2 = 4 + P->n_H; 

  /* Total human population */
  H = y[0] + y[1+P->n_H] + y[2+P->n_H] + y[3+P->n_H]; 
  
  for(i=1;     i<= P->n_H; i++)       H += y[i];
  for(i=E_2;   i<= E_2+P->n_H-1; i++) H += y[i];
  
  P->H = H;
#if defined VERBOSE
  printf(" Total population (from total_Humans.c) : %g\n", H);
#endif
  return (H);
}

double total_Exposed(double *y, Parameter_Table *P)
{
  int i;
  double E; /* Total Human Population */
  
  /* Total human population */

  for(i=1;     i<= P->n_H; i++)     E += y[i];

  return (E);
}

double total_Exposed_2(double *y, Parameter_Table *P)
{
  int i;
  double E; /* Total Human Population */
  int E_2;

  E_2 = 4 + P->n_H; /***********************/                 /*  E_2 */
  
  /* Total human population */
  
  for(i=E_2;   i<= E_2+P->n_H-1; i++) E += y[i];

  return (E);
}

#else 

#if defined MacDonaldRoss
double total_Humans(const double *y, Parameter_Table *P)
{
  double H; /* Total Human Population */

  H = P->H;

  return (H);	
}
#else

double total_Humans(const double *y, Parameter_Table *P)
{
  double H; /* Total Human Population */
           
#ifndef ODE_RESTRICTED_JACOBIAN
  int i;
  
  int S; int E; int I; int R; int C; int S1; int I1; int S2; int I2; int S3; int I3;  
  int L; int X; int U; int W; 
  int A; 
  int K;

  /* Code definitions and dimension of the state model variables */
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  &L, &X, &U, &W,  &A, &K);  

  K = L - 1;  /* Numerical label of the last human class */

  /* If there is no Larva stage, then the last human class is 'X - 1' 
     For models without larval stage, then, by definition, L = X 
     (see model_Variables_Code.c)    	
  */	
  H = 0.;
  for(i = 0; i<=K; i++){
     H += y[i];
  }
  
  /* printf("Dynamic Population: %g\t Population parameter: %d\n", H, P->POPULATION);  */
  /* printf("M_Fecundity = %g\t M_Delta = %g\n", P->M_Fecundity, P->M_Delta);          */
  /* printf("H_Birth     = %g\t H_Delta = %g\n", P->H_Birth, P->H_Delta);              */
 
  H = (double)P->POPULATION; 
	
#else 
  
  H = (double)P->POPULATION;

#endif
  return (H);
}

/* #if defined NO_CASES */

/* double total_Humans(const double *y, Parameter_Table *P) */
/* { */
/*   int i; */
/*   int K; */
/*   double H; /\* Total Human Population *\/ */

/*   K = P->n_H + 2;  /\* Numerical label of the last human class *\/ */
  
/*   /\* A small number of infectious humans *\/ */
/*   H = 0.; */
/*   for(i = 0; i<=K; i++){ */
/*      H += y[i];       */
/*   } */

/*   return (H); */
/* } */

/* #else */

/* double total_Humans(const double *y, Parameter_Table *P) */
/* { */
/*   int i; */
/*   int K; */
/*   double H; /\* Total Human Population *\/ */

/*   K = P->n_H + 3; */

/*   /\* A small number of infectious humans *\/ */
/*   H = 0.; */
/*   for(i = 0; i<=K; i++){ */
/*      H += y[i]; */
/*   } */

/*   return (H); */
/* } */
/* #endif */

double total_Exposed(double *y, Parameter_Table *P)
{
  int i;
  double y_E; 
  int S; int E; int I; int R; int C; int S1; int I1; int S2; int I2; int S3; int I3;
  int L; int X; int U; int W;
  int A;
  int K;

  /* Code definitions and dimension of the state model variables */
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  &L, &X, &U, &W,  &A, &K);
 
  /* A small number of infectious humans */
  y_E = 0.;
  for(i = E; i < I; i++){
    y_E += y[i];      
  }

  return (y_E);
}
#endif

#endif
