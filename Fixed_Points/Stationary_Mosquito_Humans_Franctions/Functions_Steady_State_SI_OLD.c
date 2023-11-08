#include "../Include/MODEL.h"
/* B E G I N :   Human submodel */
double Infectious_Human_asymptotic_Fraction(Parameter_Table *P)
{
  double M,B;
  double y;
  
  M = Total_Mosquito_Steady_State(P); 
  B = P->H_Beta = Beta_Function(P, M);
  P->H_Recov = Queu_Function_Recovery(P, M, P->H_Recov_0, P->W_Recov);
  
  y = B /(P->H_Recov + B + P->H_Delta);

  return (y);
}

double Infectious_Human_Steady_State_Fraction(const double W, Parameter_Table *P)
{
  double y, B;
  
  B = P->H_Beta = Beta_Function(P, W);  
  P->H_Recov = Queu_Function_Recovery(P, W, P->H_Recov_0, P->W_Recov);
  
  y = B /(P->H_Recov + B + P->H_Delta);

  return (y);
}
/* E N D :   Human submodel */ 
/* Note that the dynamics of the mosquito is the same in CASES_33 as in CASES_1.
   All that changes is the dynamics within the human population. This is why 
   the next two functions are the same in both cases 
*/
/* B E G I N :  Mosquito submodel */
double Infectious_Mosquito_Steady_State(const double y, Parameter_Table *P)
{
  double M, W, g;

  g = P->n_V * P->M_Gamma /(P->n_V * P->M_Gamma + P->M_Delta);
  M = Total_Mosquito_Steady_State(P);

  W = M *P->M_a*P->M_c * y/(P->M_Delta + P->M_a*P->M_c * y) * pow(g,(double)P->n_V);

  return(W);
}

double Inverted_Mosquito_Steady_State(const double W, Parameter_Table *P)
{
  /* This function is only the inversion of the previous one */

  double y;
  double g;
  double M, w;
  
  M = Total_Mosquito_Steady_State(P);
  g = P->n_V * P->M_Gamma /(P->n_V * P->M_Gamma + P->M_Delta);
  g = pow(g,(double)P->n_V);
  w = W/M;
  
  y = 1./g * P->M_Delta * w/P->M_c/P->M_a/(1.- 1./g*w);

  return (y); 
}
/* E N D :  Mosquito submodel */
