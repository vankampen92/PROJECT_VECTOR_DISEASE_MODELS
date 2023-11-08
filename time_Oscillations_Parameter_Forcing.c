#include "./Include/MODEL.h"

extern gsl_rng * r;

double Sinusoidal_Oscillation(double t, double E, double K_Mean, double K_Var, double T)
{
  double value;

  // E = gsl_ran_gaussian(r, K_var); 
  /* This function returns a Gaussian random variate, with mean zero 
     and standard deviation K_var */
  
  value = K_Mean *(1.0 + E * sin(2.*M_PI*t/T)); //gsl_ran_gaussian(r, K_Var);

  return (value);
}

double Double_Sinusoidal_Oscillation(double t, double E, double K_Mean, double K_Var, double T)
{
  double value;
  double A;

  //A = E * gsl_rng_uniform(r);

  A = E * sin(   M_PI*t/T + M_PI/5.0  );

  //A = E;

  value = K_Mean * ( 1 + A * sin(2.*M_PI*t/T) ); //gsl_ran_gaussian(r, K_Var);

  return (value);
}

double K_p_Precipitation(double t, Parameter_Table * P)
{
  /* Sinusoidal oscillation in both carrying capacity and amplitude of oscillation (A) */
  /* A time variable carrying capacity */
  double E, K, K_Mean, K_Var;

  K_Mean = P->K_Mean_Value; /* K_p (see values_HumaMos.c) */
  K_Var  = P->K_Sigma;
  E = P->K_Seasonal_Intensity;

  // K = Sinusoidal_Oscillation(t, E, K_Mean, K_Var, P->K_Period);

  K = Double_Sinusoidal_Oscillation(t, E, K_Mean, K_Var, P->K_Period); 

  return (K);
}

double K_Mosquito(double t, Parameter_Table * P)
{
  /* A time variable carrying capacity */
  double E, K, K_Mean, K_Var;

  K_Mean = P->K_Mean_Value; /* K_0 (see values_HumaMos.c) */
  K_Var  = P->K_Sigma;
  E = P->K_Seasonal_Intensity;

  K = Sinusoidal_Oscillation(t, E, K_Mean, K_Var, P->K_Period);

  //K = Double_Sinusoidal_Oscillation(t, E, K_Mean, K_Var, P->K_Period);
  return (K);
}

double Fecundity_Mosquito_00(double t, Parameter_Table * P)
{
  /* A time variable carrying capacity */
  double E, K, K_Mean, K_Var;

  K_Mean = P->K_Mean_Value; /* K_0 can have long term trend itself */
  K_Var  = P->K_Sigma;
  E = P->K_Seasonal_Intensity;

  K = Sinusoidal_Oscillation(t, E, K_Mean, K_Var, P->K_Period);

  return (K);
}

double L_Devel_Mosquito(double t, Parameter_Table * P)
{
  /* A time variable carrying capacity */
  double E, K, K_Mean, K_Var;

  K_Mean = P->K_Mean_Value ; /* K_0 can have long term trend itself */
  K_Var  = P->K_Sigma;
  E = P->K_Seasonal_Intensity;

  K = Sinusoidal_Oscillation(t, E, K_Mean, K_Var, P->K_Period);

  return (K);
}

/* double  */
/* K_Derivative(double t, Parameter_Table * P) */
/* { */
/*   double E, K_D, K_Mean, K_Var; */
/*   double Jump_Value; */
/*   E = 0.; */

/*   K_Mean = P->K_0; */
/*   K_Var  = P->K_Sigma; */

/*   Jump_Value = (P->Tr.value_1 - P->Tr.value_0)/(P->Tr.time_1-P->Tr.time_0);  */

/*   K_D = Jump_Value * (1. + E*cos(2.*M_PI*t/P->K_Period))  */
/*     - K_Mean*E*sin(2.*M_PI*t/P->K_Period)*(2.*M_PI/P->K_Period); */

/*   //if(E == 0. && P->Linear_Trend_Epsilon == 0.) K_D = 0.; */

/*   return(K_D); */
/* } */
