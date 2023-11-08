#include <MODEL.h>

#define FECUNDITY_CORRECTION
       
double R_0_MacDonaldRoss(Parameter_Table *P)
{
  /* Cases ara taken into consideration */
  double R, R_1,R_2;
  double M,H,e,m;

  H = P->H;
  M = Total_Mosquito_Steady_State(P);
  P->m = M/H;

  R = P->M_b*P->M_c* P->M_a*P->M_a* P->m / P->M_Delta /( P->H_Delta + P->H_Recov_0 );
 
  return(R);
}

double R_AronMay(Parameter_Table *P)
{
  /* Aron and May (1982) */
  double R, R_2;
  double M,H;
    
#ifndef TIME_DEPENDENCE
  P->L_Delta     = P->L_Delta_P;
#endif

#if defined FECUNDITY_CORRECTION
  P->M_Fecundity = Fecundity_Correction ( P );
#endif

  H = P->H;
  M = Total_Mosquito_Steady_State(P);

  R = P->M_a*P->M_a * P->M_b*P->M_c* M/H * 1./P->M_Delta/(P->H_Delta+P->H_Recov_0) *
    exp(- 1./P->M_Gamma * P->M_Delta);

  return(R);
}

double R_0(Parameter_Table *P)
{
  /* 
     R_0 in the absence of detection and treatment: 
     H_Xhi = 0.0 and H_Rho = 0.0 
  */
  double R, R_2;
  double M,H;
  
#ifndef TIME_DEPENDENCE
  P->L_Delta     = P->L_Delta_P;
#endif

#if defined FECUNDITY_CORRECTION
  P->M_Fecundity = Fecundity_Correction ( P );
#endif

  H = P->H;
  M = Total_Mosquito_Steady_State(P);

  R = P->M_a *sqrt(P->M_b*P->M_c* M/H)* sqrt(1./P->M_Delta/(P->H_Delta+P->H_Recov_0)) *
    pow(P->n_V * P->M_Gamma/(P->n_V * P->M_Gamma + P->M_Delta), (double)P->n_V/2.) *
    pow(P->n_H * P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta+P->H_Recov_0), (double)P->n_H/2.);

  return(R);
}

double R_0_e_1(Parameter_Table *P)
{
  /* Cases ara taken into consideration */
  double R, R_1,R_2;
  double M,H,e,m;

#ifndef TIME_DEPENDENCE
  P->L_Delta     = P->L_Delta_P;
#endif

#if defined FECUNDITY_CORRECTION
  P->M_Fecundity = Fecundity_Correction ( P );
#endif

  e = 1.;
  H = P->H;
  M = Total_Mosquito_Steady_State(P);
  m = M/H;

  R_1 = Vectorial_Capacity_Next_Gen_Matrix( m, P );

  R_2 = (1-P->H_Xhi)*1./(P->H_Recov_0+P->H_Delta)*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Recov_0),(double)P->n_H) + P->H_Xhi*(1-e)*(P->H_Nu+P->H_Delta)/((P->H_Delta+P->H_Recov_0)*(P->H_Nu-P->H_Recov_0))*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Recov_0),(double)P->n_H) + P->H_Xhi*(1-e)*(P->H_Recov_0+P->H_Delta)/((P->H_Delta+P->H_Nu)*(P->H_Nu-P->H_Recov_0))*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Nu),(double)P->n_H)+P->H_Xhi*e*1./(P->H_Rho+P->H_Delta)*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Rho),(double)P->n_H);

  R = sqrt(R_1 * R_2);
 
  return(R);
}

double R_0_Next_Gen_Matrix_Threshold_b(Parameter_Table *P)
{
  double R, R_1,R_2;
  double M,H,e;
  double b;

#ifndef TIME_DEPENDENCE
  P->L_Delta     = P->L_Delta_P;
#endif

#if defined FECUNDITY_CORRECTION
  P->M_Fecundity = Fecundity_Correction ( P );
#endif

  e = P->H_Rho/(P->H_Rho + P->H_Nu);
  H = P->H;
  M = Total_Mosquito_Steady_State(P); 
  b = P->M_a/(H*P->M_b + P->M_a);
  
  R_1 = P->M_a*P->M_a * b * P->M_c * 1./P->M_Delta* M/H * pow( P->n_V * P->M_Gamma/(P->n_V * P->M_Gamma + P->M_Delta), (double)P->n_V);

  R_2 = (1-P->H_Xhi)*1./(P->H_Recov_0+P->H_Delta)*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Recov_0),(double)P->n_H) + P->H_Xhi*(1-e)*(P->H_Nu+P->H_Delta)/((P->H_Delta+P->H_Recov_0)*(P->H_Nu-P->H_Recov_0))*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Recov_0),(double)P->n_H) + P->H_Xhi*(1-e)*(P->H_Recov_0+P->H_Delta)/((P->H_Delta+P->H_Nu)*(P->H_Nu-P->H_Recov_0))*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Nu),(double)P->n_H)+P->H_Xhi*e*1./(P->H_Rho+P->H_Delta)*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Rho),(double)P->n_H);

  R = sqrt(R_1 * R_2);
  
  return(R);
}

double R_0_Next_Gen_Matrix(Parameter_Table *P)
{
  double R, R_1,R_2;
  double M,H,e;
  double m;
  
#ifndef TIME_DEPENDENCE
  P->L_Delta     = P->L_Delta_P;
#endif

#if defined FECUNDITY_CORRECTION
  P->M_Fecundity = Fecundity_Correction ( P );
#endif

  e = P->H_Rho/(P->H_Rho + P->H_Nu);
  H = P->H;
  M = Total_Mosquito_Steady_State(P); 
  m  = M/H;
  
  R_1 = Vectorial_Capacity_Next_Gen_Matrix( m, P );

  R_2 = (1-P->H_Xhi)*1./(P->H_Recov_0+P->H_Delta)*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Recov_0),(double)P->n_H) + P->H_Xhi*(1-e)*(P->H_Nu+P->H_Delta)/((P->H_Delta+P->H_Recov_0)*(P->H_Nu-P->H_Recov_0))*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Recov_0),(double)P->n_H) + P->H_Xhi*(1-e)*(P->H_Recov_0+P->H_Delta)/((P->H_Delta+P->H_Nu)*(P->H_Nu-P->H_Recov_0))*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Nu),(double)P->n_H)+P->H_Xhi*e*1./(P->H_Rho+P->H_Delta)*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Rho),(double)P->n_H);

  R = sqrt(R_1 * R_2);

  return(R);
}

double R_0_Next_Gen_Matrix_2(Parameter_Table *P)
{
  /* Exactly the same as R_0_Next_Gen_Matrix(), but to the power of two */
  double R, R_1,R_2;
  double M,H, e, m;

#ifndef TIME_DEPENDENCE
  P->L_Delta     = P->L_Delta_P;
#endif

#if defined FECUNDITY_CORRECTION
  P->M_Fecundity = Fecundity_Correction ( P );
#endif

  e = P->H_Rho/(P->H_Rho + P->H_Nu);
  H = P->H;
  M = Total_Mosquito_Steady_State(P); 
  m = M/H;

  R_1 = Vectorial_Capacity_Next_Gen_Matrix( m, P );

  R_2 = (1-P->H_Xhi)*1./(P->H_Recov_0+P->H_Delta)*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Recov_0),(double)P->n_H) + P->H_Xhi*(1-e)*(P->H_Nu+P->H_Delta)/((P->H_Delta+P->H_Recov_0)*(P->H_Nu-P->H_Recov_0))*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Recov_0),(double)P->n_H) + P->H_Xhi*(1-e)*(P->H_Recov_0+P->H_Delta)/((P->H_Delta+P->H_Nu)*(P->H_Nu-P->H_Recov_0))*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Nu),(double)P->n_H)+P->H_Xhi*e*1./(P->H_Rho+P->H_Delta)*pow( P->n_H*P->H_Gamma/(P->n_H * P->H_Gamma + P->H_Delta + P->H_Rho),(double)P->n_H);

  R = R_1 * R_2;
  
  return(R);
}

double R_0_Next_Gen_Matrix_Bis(Parameter_Table *P)
{
  double e, R, R_b;

#ifndef TIME_DEPENDENCE
  P->L_Delta     = P->L_Delta_P;
#endif

#if defined FECUNDITY_CORRECTION
  P->M_Fecundity = Fecundity_Correction ( P );
#endif
 
  e = P->H_Rho/(P->H_Rho + P->H_Nu);

  R = R_0(P) * sqrt((1.-P->H_Xhi) + P->H_Xhi*( (1-e)*(P->H_Nu+P->H_Delta)/(P->H_Nu-P->H_Recov_0)*(1. + (P->H_Recov_0+P->H_Delta)*(P->H_Recov_0+P->H_Delta)/(P->H_Nu+P->H_Delta)/(P->H_Nu+P->H_Delta) * pow((P->n_H*P->H_Gamma + P->H_Recov_0 + P->H_Delta)/(P->n_H*P->H_Gamma + P->H_Nu + P->H_Delta), (double)P->n_H)) + e *(P->H_Delta+P->H_Recov_0)/(P->H_Delta+P->H_Rho)*pow((P->n_H*P->H_Gamma +P->H_Recov_0+P->H_Delta)/(P->n_H*P->H_Gamma + P->H_Rho+P->H_Delta), (double)P->n_H)));

  return (R);
}

double R_0_Threshold(Parameter_Table *P)
{
  double R, e;
  
#ifndef TIME_DEPENDENCE
  P->L_Delta     = P->L_Delta_P;
#endif

  e = P->H_Rho/(P->H_Rho + P->H_Nu);

  R = (1.-P->H_Xhi) + P->H_Xhi*( (1-e)*(P->H_Nu+P->H_Delta)/(P->H_Nu-P->H_Recov_0)*(1. + (P->H_Recov_0+P->H_Delta)*(P->H_Recov_0+P->H_Delta)/(P->H_Nu+P->H_Delta)/(P->H_Nu+P->H_Delta) * pow((P->n_H*P->H_Gamma + P->H_Recov_0 + P->H_Delta)/(P->n_H*P->H_Gamma + P->H_Nu + P->H_Delta), (double)P->n_H)) + e *(P->H_Delta+P->H_Recov_0)/(P->H_Delta+P->H_Rho)*pow((P->n_H*P->H_Gamma +P->H_Recov_0+P->H_Delta)/(P->n_H*P->H_Gamma + P->H_Rho+P->H_Delta), (double)P->n_H));

  R = 1./R;

  return (R);
}

double Vectorial_Capacity_Next_Gen_Matrix (double m, Parameter_Table *P) 
{
  double x;

#ifndef TIME_DEPENDENCE
  P->L_Delta     = P->L_Delta_P;
#endif
  
  x = m * P->M_a*P->M_a * P->M_b*P->M_c * 1./P->M_Delta * pow( P->n_V * P->M_Gamma/(P->n_V * P->M_Gamma + P->M_Delta), (double)P->n_V);
          
  return( x );
}

double Fecundity_Correction (Parameter_Table * P)
{
  /* In some situations, it is necessary to assume that fecundity is proportional to the biting rate, 
     rather than being them two independent parameters */
    double Fecundity = P->M_a * P->M_NoEggs; 

    printf("Fecundity = %g\n", Fecundity);
    
    return (Fecundity);
}
