#include "../MODEL.h"

double Total_Mosquito_Fluctuating_Steady_State(Parameter_Table *P, double t)
{
  double M;
  double K_0;
  
  K_0 = K_Mosquito(t, P);
  
  M = K_0*(P->M_Fecundity*P->L_Devel - P->M_Delta*(P->L_Devel + P->L_Delta))/P->M_Fecundity/P->M_Delta;

  return(M);
}

double Infectious_Mosquito_Fluctuating_Steady_State(const double y, Parameter_Table *P, double t)
{
  double M, W, g;
  
  g = P->n_V * P->M_Gamma /(P->n_V * P->M_Gamma + P->M_Delta);
  M = Total_Mosquito_Fluctuating_Steady_State(P, t);

  W = M *P->M_a*P->M_c * y/(P->M_Delta + P->M_a*P->M_c * y) * pow(g,(double)P->n_V);

  return(W);
}
  

 
