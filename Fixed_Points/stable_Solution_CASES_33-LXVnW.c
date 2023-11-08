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
  int w,k;
  double S,E_1,I,R,C,S1,I1,S2,I2,S3,I3;
  int a,K;
  double L,X,V_1;
  double B; /* Force of infection */
  double M,H;
  double g, g_M,g_H,z,q;
  double E_Total;

  k = P->n_H + 3;
  w = P->n_H + 3 + 3 + P->n_V;          /* Total no of classes */
  a = w + 1;                            /* Accumulated cases   */
  K = a + 1;                            /* Carrying capacity   */

  H = P->H;                             /* Total Human Population */
  M = Total_Mosquito_Steady_State(P);   /* Total Mosquito Population */
  B = P->H_Beta = Beta_Function(P, W);
  P->H_Recov = Queu_Function_Recovery( P, W, P->H_Recov_0, P->W_Recov );
  P->H_Sigma = Queu_Function_Sigma( P, W, P->H_Sigma_0, P->W_Sigma );
  
  g_H = P->n_H * P->H_Gamma /(P->n_H * P->H_Gamma + P->H_Delta);  
  g   = pow(g_H,(double)P->n_H);
  g_M = P->n_V * P->M_Gamma /(P->n_V * P->M_Gamma + P->M_Delta);
 
  z = z_Function(P); q = q_Function(P);
  
  S = Y[0] = 1./(1+z) * H;                                                        /* S   */
  
  E_1 = Y[1] = B/(P->H_Delta + P->n_H*P->H_Gamma) * S;                            /* E_1 */

  E_Total = B/P->H_Delta*(1-g)* S;

  for(i=2; i<=P->n_H; i++){                                                       /* E_n */
    Y[i] = pow(g_H, (double)(i-1)) * E_1;
  }   
  
  /* Stable values: Humans*/
  I = Y[P->n_H+1] = B *(P->H_Nu + (1.-P->H_Xhi)*(P->H_Rho+P->H_Delta))/q * g * S;  /* I   */

  R = Y[P->n_H+2] = P->H_Recov / (P->H_Sigma + P->H_Delta) * I;                    /* R   */

  C = Y[k] = B* (P->H_Eta*B + P->H_Xhi*(P->H_Recov+P->H_Delta))/q *g * S;          /* C   */
  
  /*
    double E = total_Exposed(Y, P);
    printf("Total exposed (E), %g\t E=Beta/Delta * (1-g) = %g\n", E, E_Total);
  */

  /* Stable values: Mosquitoes */
  L = Y[k+1]   = P->M_Delta / P->L_Devel * M;                                      /* L   */  
                            
  X = Y[k+2]   = P->M_Delta /(P->M_c * P->M_a * y + P->M_Delta) * M;               /* X   */
  
  V_1 = Y[k+3] = P->M_c * P->M_a * y / (P->n_V * P->M_Gamma + P->M_Delta) * X;     /* V_1 */    

  for(i=k+4; i < w; i++){                                                          /* V_n */  /* n=2, ..., n_V */
    j = (i-(k+2));                                                                 /* V_j */
    Y[i] = pow(g_M, (double)(j-1)) * V_1; 
  }
  
  Y[w] = W;                                                                        /* W   */
  /* Accumulated cases will depend on the accumulation period. Conventionaly,
     we make it zero here
  */
  Y[a] = 0.0;                                                                      /* A   */
  Y[K] = P->K_A * P->K_p / P->K_E;                                                 /* K   */   
} 

double C_fixed_Points(Parameter_Table *P, double EPSILON)
{
  double x;
  int C, W;
  double W_1, y_1;
  double *y_Sol;

  W = 3 + P->n_H + 3 + P->n_V;
  y_Sol = dvector(0,W);

  if (Feasibility_Condition_M(P) == 1) {

    W_y_fixed_Points_Lower(P, EPSILON, &W_1, &y_1);
    //W_y_fixed_Points_Upper(P, EPSILON, &W_1, &y_1);  
  
    stable_Solution(y_1, W_1, P, y_Sol);

  }
  else{

    stable_Solution_Free_Disease(P, y_Sol);
  }

  C = P->n_H + 3;
  x = y_Sol[C];
  
  free_dvector(y_Sol, 0,W);
  return(x);
}

#if defined K_L_E_I_N

void stable_Solution_Free_Disease(Parameter_Table *P, double *Y)
{
  int i,S,E_1,E_2,I,R,C,L,X,U,W,K,A;
  double M;

  S_E_I_R_C___L_X_U_W_A___K___C_O_D_E_S___K_L_E_I_N(P,  &S, &E_1, &I, &R, &C, &E_2, &L, &X, &U, &W, &A, &K);

  Y[0] = P->H;                   /* S   */
  
  Y[1] = 0.0;                            /* E_1 */
  
  for(i=2; i<=P->n_H; i++){              /* E_n */
    Y[i] = 0.0;
  }

  Y[I] = 0.0;                            /* I   */

  Y[R] = 0.0;                            /* R   */

  Y[C] = 0.0;                            /* C   */

  for(i=E_2;   i<= E_2+P->n_H-1; i++) Y[i] = 0.0;
  
  /* Mosquito */

  if (Feasibility_Condition_M(P)== 1){
    M = Total_Mosquito_Steady_State(P); 
  } 
  else{
    M = 0.0;   
  }

  Y[L]  = P->M_Delta / P->L_Devel * M;   /* L   */ 
  
  Y[X]  = M;                             /* X   */
  
  for(i = U; i < W; i++){                /* V_1 to V_n */
    Y[i] = 0.0; 
  }

  Y[W] = 0.0;                            /* W   */
  /* Accumulated cases will depend on the accumulation period. Conventionaly,
     we make it zero here
  */
  Y[A] = 0.0;                                                                      /* A   */
  Y[K] = P->K_A * P->K_p / P->K_E;                                                 /* K   */   
}

void Human_Population_Initial_Conidition_from_Parameter_Table(Parameter_Table *P, double *Y)
{
  static int INDIVIDU = 0; 

  int i,S,E,E_1,E_2,I,R,C,L,X,U,W,A,K;

  double g_H, H, E_x, x, y;
                          /*    L a b e l s      */  
  
  S_E_I_R_C___L_X_U_W_A___K___C_O_D_E_S___K_L_E_I_N(P,  &S, &E_1, &I, &R, &C, &E_2, &L, &X, &U, &W, &A, &K);
    
  H = P->H;
 
  //printf(" BEGIN: Total Population from initial Condition (stable_Solutions_Cases.c): %g\n", H);

  /* Initial values for number of humans at each class */

  x = (P->s__0 + P->i__0 + P->c__0 + P->e__0 + P->e__2);
  y = 1.0/H;

  if( x > 1){ /* Renormalization occurs... */
    
    P->s__0 = P->s__0 / x * (1.0 - y);
    P->e__0 = P->e__0 / x * (1.0 - y);
    P->i__0 = P->i__0 / x * (1.0 - y);
    P->c__0 = P->c__0 / x * (1.0 - y);
    P->e__2 = P->e__2 / x * (1.0 - y);

  }

  g_H = P->n_H * P->H_Gamma /(P->n_H * P->H_Gamma + P->H_Delta);  
 
  x   = ( 1.0 - pow(g_H, (double)(P->n_H)) ) / ( 1.0 - g_H );

  Y[S] = P->s__0 * H;                                                        /* S   */
  
  Y[E_1] =  E_x  = P->e__0 * H / x;                                          /* E_1 */

  for(i=2; i<=P->n_H; i++){                                                 
    Y[i] = pow(g_H, (double)(i-1)) * E_x;
  }   
 
  Y[I] = P->i__0 * H; 

  Y[R] = (1.0 - P->s__0 - P->i__0 - P->c__0 - P->e__2 - P->e__0) * H; 

  Y[C] = P->c__0 * H; 

  Y[E_2] =  E_x  = P->e__2 * H / x;                                          /* E_2 */

  for(i=E_2+1; i<=E_2+P->n_H-1; i++){                                              
    Y[i] = pow(g_H, (double)(i-1)) * E_x;
  }   

  /* x = P->s__0 + P->i__0 + P->c__0 + P->e__0 + + P->e__2 + Y[R]/H ; */

  /*   H = total_Humans(Y, P); */

  /*   printf(" INDIVIDU: %d\nSum of fractions [x] = %g\t s = %g, e_1 = %g, i = %g, c = %g, e_2 = %g\n",   */
  /* 	 INDIVIDU, x, P->s__0,  P->e__0,  P->i__0, P->c__0, P->e__2);  */
  /*   printf(" Total Population from initial conditions (stable_Solutions_Cases.c): %g\n", H); */
  
  /* if( x > 1.0 || x == 1.0 ){ */

  /*       printf(" Sum of fractions [x] = %g\t s = %g, e_1 = %g, i = %g, c = %g, e_2 = %g\n",   */
  /*        x, P->s__0,  P->e__0,  P->i__0, P->c__0, P->e__2);  */
  /*       assert(x <= 1.0); */

  /*     } */
  /* 
     for(i=0; i<=K; i++) { printf("y[%d]=%g ", i, Y[i]); }
     printf("\n");
     printf(" END: Total Population from initial conditions (stable_Solutions_Cases.c): %g\n", H);
  */
  /* if (INDIVIDU < GA_POPULATION)  */
  /*     INDIVIDU++; */
  /* else */
  /*     INDIVIDU = 0; */
}

#else

void stable_Solution_Free_Disease(Parameter_Table *P, double *Y)
{
  int i,I,R,C,L,X,U,W,A,K;
  double M;
                        /*    L a b e l s      */  
  I = 1 + P->n_H;      /***********************/             /* I   */
  R = 2 + P->n_H;     /***********************/              /* R   */
  C = 3 + P->n_H;    /***********************/               /* C   */
  L = C + 1;        /***********************/                /* L  */
  X = C + 2;       /***********************/                 /* X  */
  U = C + 3;      /***********************/                  /* U, first latent mosquito class */
  W = C + 3 + P->n_V;                                        /* W  Infectious class  */
  A = W + 1;                                                 /* A, accumulated cases */
  K = A + 1;                                                 /* K, carrying capacity */
  
  Y[0] = P->H;                   /* S   */
  
  Y[1] = 0.0;                            /* E_1 */
  for(i=2; i<=P->n_H; i++){              /* E_n */
    Y[i] = 0.0;
  }

  Y[I] = 0.0;                            /* I   */

  Y[R] = 0.0;                            /* R   */

  Y[C] = 0.0;                            /* C   */

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
  
  Y[A] = 0.0;                            /* A   */
  Y[K] = P->K_A * P->K_p / P->K_E;       /* K   */   
}

#endif
