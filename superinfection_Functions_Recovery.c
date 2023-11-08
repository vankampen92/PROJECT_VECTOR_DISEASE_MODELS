#include <MODEL.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

//#define BREAK_if_W_is_NEGATIVE

#define EPSILON 1.0e-20

#if defined NON_SUPERINFECTION_RECOVERY

double Queu_Function_Recovery(Parameter_Table *P, double W, double F_0, double T)
{
  return (F_0);
}

double Derivative_Queu_Function_Recovery(double B, double F_0, double T)
{
  /* First derivative with respect to B */
  /* T, Threshold in biting intesity (B) over which F will be P->H_Delta */
  return (0.0);
}

double Queu_Function_Fraction_Infectious_Mosquitoes_Recovery(Parameter_Table *P, double W, double F_0, double T)
{
  return (F_0);
}    

#else //with SUPERINFECTION in the RECOVERY RATE/

double Queu_Function_Recovery(Parameter_Table * P, double W, double F_0, double T)
{
  double F; 

  F = Queu_Function(P, W, F_0, T);
  
  return(F);
}

double Derivative_Queu_Function_Recovery(double B, double F_0, double T)
{
  double F;

  F = Derivative_Queu_Function(B, F_0, T);

  return (F);
}

double Queu_Function_Fraction_Infectious_Mosquitoes_Recovery (Parameter_Table *P, double W, double F_0, double T)
{
  double (F);

  F = Queu_Function_Fraction_Infectious_Mosquitoes( P, W, F_0, T );

  return (F);
}
#endif
