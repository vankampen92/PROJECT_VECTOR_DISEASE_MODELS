#include "../Include/MODEL.h"

double Total_Mosquito_Dynamic_State(Parameter_Table *P, double *y)
{
  int i;
  double M;

  int S, E, E_1, E_2, I, R, C, S1, I1, S2, I2, S3, I3, L, X, U, W, A, K;

  
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P,  &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  &L, &X, &U, &W, &A, &K);

  M = 0.;
  for(i = X; i<=W; i++) M += y[i];

  return (M);
}

int Feasibility_Condition_M(Parameter_Table *P)
{

  int Y;
  double a, M;

#if defined LXVnW
  a = P->M_Fecundity/P->M_Delta - (1.0 + P->L_Delta/P->L_Devel);

  if ( a > 0.0 ){
    Y=1;
  }
  else{
    Y=0;
  }
#endif

#if defined XkVnW
  assert(P->K_0 >= 0.0);

  M = P->K_0 * (1.0 - P->M_Delta/P->M_Fecundity );

  if ( M < 0.0 )  Y = 0;  // Mosquito Populatio is not viable!!!
  else            Y = 1;
#endif

  /* When mosquito population is constant, it is always feasible */
  /* XVnW and XW stand for mosquito models where mosquito population is
     hold constant */
#if defined XVnW
  Y = 1;
#endif

#if defined XW
  Y = 1;
#endif

  return(Y);
}

double Total_Mosquito_Steady_State(Parameter_Table *P)
{
  double M;

  M = -1.0;

#if defined LXVnW
  assert(P->K_0 >= 0.0);

  if(Feasibility_Condition_M(P) == 1){
    M = P->K_0*(P->M_Fecundity*P->L_Devel - P->M_Delta*(P->L_Devel + P->L_Delta))/P->M_Fecundity/P->M_Delta;
  }
  else{
    M = 0.0;
  }
#endif

#if defined XkVnW
  assert(P->K_0 >= 0.0);

  M = P->K_0 * (1.0 - P->M_Delta/P->M_Fecundity );

  if ( M < 0.0 )  M = 0.0;  // Mosquito Populatio is not viable!!!

#endif

#if defined XVnW
  M = P->m * P->H;
#endif

#if defined XW
  M = P->m * P->H;
#endif

  if ( M == (-1.0) ) {
    printf(" L77: Fatal Error in function ""Total_Mosquito_Steady_State ( Parameter_Table * P )"" from Functions_Steady_State_Mosquito.c\n");
    printf(" The program will be interrupted\n");
    exit(0);
  }

  return(M);
}

double Total_Larva_Stable_State(Parameter_Table *P)
{
  double L;

  L = P->K_0 * (1. - (1.+ P->L_Delta/P->L_Devel) *P->M_Delta/P->M_Fecundity);

  return (L);
}
