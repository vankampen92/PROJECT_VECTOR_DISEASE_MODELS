// #include "../Include/MODEL.h"
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
