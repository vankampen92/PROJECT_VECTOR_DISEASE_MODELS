// #include "../Include/MODEL.h"

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
