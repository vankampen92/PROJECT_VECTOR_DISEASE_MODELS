#include "../Include/MODEL.h"
/* B E G I N :  Human submodel */
double Infectious_Human_asymptotic_Fraction(Parameter_Table *P)
{
  /* Fraction of infectious human, y, if all mosquitoes, M, were to be infectious */
  double y;
  double M, B,g,g_H,z,q;

  M = Total_Mosquito_Steady_State(P); 

  B = P->H_Beta = Beta_Function(P, M);
  P->H_Recov = Queu_Function_Recovery(P, M, P->H_Recov_0, P->W_Recov);
  P->H_Sigma = Queu_Function_Sigma(P, M, P->H_Sigma_0, P->W_Sigma);
  
  g_H = P->n_H * P->H_Gamma /(P->n_H * P->H_Gamma + P->H_Delta);  
  g   = pow(g_H,(double)P->n_H);
  
  z = z_Function(P); q = q_Function(P);

  y = B*(P->H_Nu+ (1-P->H_Xhi)*(P->H_Rho+P->H_Delta)+ P->H_Eta*B+ P->H_Xhi*(P->H_Recov+P->H_Delta) )/q/(1+z) * g;

  return (y);
}

double Infectious_Human_Steady_State_Fraction(const double W, Parameter_Table *P)
{
  double y, B, g, g_H, z, q;
  
  B = P->H_Beta = Beta_Function(P, W);
  P->H_Recov = Queu_Function_Recovery(P, W, P->H_Recov_0, P->W_Recov);
  P->H_Sigma = Queu_Function_Sigma(P, W, P->H_Sigma_0, P->W_Sigma);
  
  g_H = P->n_H * P->H_Gamma /(P->n_H * P->H_Gamma + P->H_Delta);  
  g   = pow(g_H,(double)P->n_H);
  
  z = z_Function(P); q = q_Function(P);
  
  y = B*(P->H_Nu+ (1-P->H_Xhi)*(P->H_Rho+P->H_Delta)+ P->H_Eta*B+ P->H_Xhi*(P->H_Recov+P->H_Delta) )/q/(1+z) * g;

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

