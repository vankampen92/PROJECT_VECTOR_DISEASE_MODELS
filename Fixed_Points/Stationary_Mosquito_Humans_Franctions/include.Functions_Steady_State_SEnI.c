// #include "../Include/MODEL.h"
/* B E G I N :   Human submodel */
double Infectious_Human_asymptotic_Fraction(Parameter_Table *P)
{
  double y; 
  double M,B;
  double Theta;

  Theta = (double)P->n_H * P->H_Gamma / (P->H_Delta + (double)P->n_H * P->H_Gamma);

  M = Total_Mosquito_Steady_State(P); 
  B = P->H_Beta = Beta_Function(P, M);
  P->H_Recov = Queu_Function_Recovery(P, M, P->H_Recov_0, P->W_Recov);

  y = B * P->H_Delta * pow(Theta, (double)P->n_H) / ( (P->H_Recov + P->H_Delta )*(B + P->H_Delta) - P->H_Recov * B * pow(Theta, (double)P->n_H) ); 
  
  return (y);
}

double Infectious_Human_Steady_State_Fraction(const double W, Parameter_Table *P)
{
  double y, B, Theta;
  
  B = P->H_Beta = Beta_Function(P, W);  

  P->H_Recov = Queu_Function_Recovery(P, W, P->H_Recov_0, P->W_Recov);
  
  Theta = (double)P->n_H * P->H_Gamma / (P->H_Delta + (double)P->n_H * P->H_Gamma);
  
  y = B * P->H_Delta * pow(Theta, (double)P->n_H) / ( (P->H_Recov + P->H_Delta )*(B + P->H_Delta) - P->H_Recov * B * pow(Theta, (double)P->n_H) ); 

  return (y);
}
/* E N D :   Human submodel */ 
