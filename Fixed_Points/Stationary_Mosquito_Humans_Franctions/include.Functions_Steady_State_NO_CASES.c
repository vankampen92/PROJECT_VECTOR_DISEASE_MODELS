// #include <MODEL.h>

/* B E G I N :   Human submodel */
double Infectious_Human_asymptotic_Fraction(Parameter_Table *P)
{
  /* Fraction of infectious human, y, if all mosquitoes, M, were to be infectious */
  double y, Rho;
  
  Rho = 1. + P->H_Delta/P->n_H/P->H_Gamma;

  assert( pow(Rho, (double)P->n_H) > 1 );

  y = 1./pow(Rho,(double)P->n_H);

  return (y);
}

double Infectious_Human_Steady_State_Fraction(const double W, Parameter_Table *P)
{
  double y, B, Rho;
  
  B = P->H_Beta = Beta_Function(P, W);  
  P->H_Recov = Queu_Function_Recovery(P, W, P->H_Recov_0, P->W_Recov);
  P->H_Sigma = Queu_Function_Sigma(P, W, P->H_Sigma_0, P->W_Sigma);
  Rho = 1. + P->H_Delta/P->n_H/P->H_Gamma;
  
  y = P->H_Recov / (P->H_Sigma  + P->H_Delta) + (1.+P->H_Recov/P->H_Delta)*( pow(Rho,P->n_H)*(1.+P->H_Delta/B) - 1.); 

  y = 1./(1. + y);

  return (y);
}
/* E N D :   Human submodel */ 
