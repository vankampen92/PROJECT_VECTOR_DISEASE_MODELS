#include "./Include/SIC_MALARIA.h"

#define GAMBIAE
  
double Adult_Mosquito_Mortality(double T)
{
  /* M_Delta = F(T), where F(T)  
     is a linear function of the temperature */
  double rate;

  rate = 1./(-4.4 + 1.31*T -0.03*T*T);
  
  return (rate);
} 

double Larva_Mosquito_Mortality(double T)
{
  /* L_Delta = F(T), where F(T)  
     is a linear function of the temperature */
  double rate;
  double d_14;	
  double d_16;	

  d_14 = 0.0488;
  d_16 = 0.0392;

  if(T < 14.0){
    rate = 1.1946 - 0.0804 * T;
  }
  else if(T >= 14.0 && T <= 16.0){
    rate = d_14 + (d_16 - d_14)/2.0 * (T - 14.0); 
  }
  else if(T > 16.0 && T <= 20.0){
    rate = (0.0392 + 0.0402 + 0.0402)/3.;
  }
  else if(T > 20.0 && T < 34.0){
    rate = -0.062157 + 0.0052243 * T;
  }
  else{
    printf(" Temperature out of range in  Larva_Mosquito_Mortality(T)\n");
    printf(" in rainTemperature_Dependence.c\t Temperature = %g\n", T);
    exit(0);
  }

  return (rate);
} 

double Gonotrophic_Cycle_P(double x, double T)
{
  int i;
  double rate, D, b, m_AVE, m_2nd;
  double Delta_Temperature[4]={2.2, 3.2, 2.3, 3.0};
  double a_AVE[4]={0.26, 0.4, 0.12, 0.145};
  double a_2nd[4]={0.33, 0.48, 0.15, 0.19};
  double T_o[4]={20.8, 21.6, 18.7, 19.2};
  double T_e[4];
  
  m_AVE = 0.085;
  m_2nd = 0.1002;
  
  D = 0.0;
  for(i=0; i<4; i++) {
    T_e[i] = T_o[i] + (1. - x) * Delta_Temperature[i];
    D     += (a_AVE[i] - m_AVE * T_e[i]);
  }
  b = D / 4.0;
 
#if defined GAMBIAE
  rate = m_AVE * T + b;
#else
  printf("Error in paramResponse_Curves.c: Gonotrophic_Cycle_P() function only works for A. GAMBIAE\n");
  exit(0);
#endif  

  if(rate < 0) {
    //printf("Biting rate is negative, a = %g\n", rate); 
    //printf("a = %4.2g ,", rate); 
    //printf("Effective Temperature, T_e = %g\n", T);
    //printf("x parameter (T_e = T_o + (1-x)*T_i), x = %g\n", x);
    rate = 0.0; 
  }
  
  return (rate);
} 


double Gonotrophic_Cycle(double T)
{
  double rate;

#if defined GAMBIAE
  rate = Gonotrophic_Cycle_Agam(T);
#else
  rate = Gonotrophic_Cycle_Aalb(T);
#endif  

  if(rate < 0) rate = 0.0;
  
  return (rate);
} 

double Gonotrophic_Cycle_Agam_Indoor(double T)
{
   /* M_a = F(T), 
      where F(T) is a linear function of the temperature */
  double rate;
  
  rate = 0.091678 * T - 1.7982 ;

  if(rate < 0) rate = 0.0;
  
  return (rate);
} 

double Gonotrophic_Cycle_Agam(double T)
{
   /* M_a = F(T), 
      where F(T) is a linear function of the temperature */
  double rate;
  
  rate = 0.10872 * T - 1.895;

  if(rate < 0) rate = 0.0;
  
  return (rate);
} 

double Gonotrophic_Cycle_Aalb(double T)
{
  /* M_a = F(T), 
     where F(T) is a linear function of the temperature */
  double rate;

  rate = 0.01168*T - 0.0021423;

  if(rate < 0) rate = 0.0;

  return (rate);
} 

double Plasmodium_Development(double T)
{
  /* P_Devel = F(T), 
     where F(T) is a linear function of the temperature */
  double rate;
  
  rate = 0.009*T - 0.1441; /* /Plasmodium falciparum/ */ 
  
  //rate = 0.009*T - 0.1380; /* /Plasmodium vivax/ */ 

  return (rate);
} 

double Larva_Mosquito_Development(double T)
{
  /* L_Devel = F(T), 
     where F(T) is a linear function of the temperature */
  double rate;
  
  rate = 0.00554*T - 0.06737;
  
  return (rate);
} 

double Carrying_Capacity_Larvae(ParamSet *P, double t_0, double t)
{
  /* K_0 = F(T), 
     where F(T) is a linear function of the temperature */
  /* Input times are given in days */

  double K, K_i, t_i, K_0;
  double p, p_0;

  K_0 = P->K_0;             /* Initial Carrying Capacity             */
  p   = rain_Day(P, t);     /* Monthly Rain corresponding to day t   */
  //p_0 = rain_Day(P, t_0); /* Monthly Rain corresponding to day t_0 */
  
  P->K_p = p; /* Rain per day */
  K = P->K_A*P->K_p/P->K_E + (K_0 - P->K_A*P->K_p/P->K_E) * exp(-P->K_E*(t - t_0));   

  /* Is there an intermediate time where average time precipitation change?
  if(p == p_0){
    P->K_p = p;   //Rain per day
    K = P->K_A*P->K_p/P->K_E + (K_0 - P->K_A*P->K_p/P->K_E) * exp(-P->K_E*(t - t_0));   
  }
  else{
    t_i = Intermediate_Time(P, t_0, t);

    P->K_p = p_0; //Rain per day
    K_i    = P->K_A*P->K_p/P->K_E + (K_0 - P->K_A*P->K_p/P->K_E) * exp(-P->K_E*(t_i - t_0)); 

    P->K_p = p;   //Rain per day 
    K      = P->K_A*P->K_p/P->K_E + (K_i - P->K_A*P->K_p/P->K_E) * exp(-P->K_E*(t - t_i)); 
  }
  */

  return (K);
}



