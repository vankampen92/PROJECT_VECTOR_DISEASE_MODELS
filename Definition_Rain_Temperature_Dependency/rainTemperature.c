#include "../Include/MODEL.h"

void rainTemp_Parameters(Parameter_Table *P , double t)
{
  int i;
  double R, R_A;
  double T, T_A;
  double K_0;
  static double t_0 = 0.;
  static int No_Calls = 0;

  /*
    For i>0:

    If I[i] == 1, it means that for the i-th feature it is the
    environmental temperature corrected for elevation the one
    that controls the dyamics. 
    
    If I[i] == 0, it means that for the i-th feature it is an
    effected upshifted temperature (such as the indoors temperature) 
    the one that controls the dynamics. 

    I[0] is the switcher controling rainfall:

    If I[0] == 1, then rainfall controls mosquito-carrying capacity.
    If I[0] == 0, then carrying capacity is independent from rainfall.
  */

  T = temperature_Day(P, t) + P->R_T.T_ELEVATION; /* 
						     T.   Temperature at time t in Celsius degrees 
						     (corrected for a different elevation) 
						  */
                                                  /* 
						     T_A. Temperature at time t in Celsius degrees 
						     (effective temperature for adult mosquitoes) 
						  */
#if defined T_SHIFT_TEMPERATURE 
  T_A = T + P->R_T.TEMP__SHIFT;                  
#else
  T_A = T + (1.0 - P->R_T.x) * P->R_T.TEMP__SHIFT;
#endif

  R   = rain_Day(P, t); 
  R_A = rain_Day_Smooth(P, t);

  for(i=0; i < P->no_I; i++){  
    assert(P->I[i] == 1 || P->I[i] == 0);
  }

  /* (1) */
  if(P->I[0] == 1){
    //printf("(0)");
    P->K_p     = R;
  }
  
  /* (2) */ 
  if(P->I[1] == 1){
    //printf("(1)");
    P->M_Delta = Adult_Mosquito_Mortality(T) + P->I[8] * P->M_Delta_R * Heavy_OverRain(R, R_A);
  }
  else{
    P->M_Delta = Adult_Mosquito_Mortality(T_A) + P->I[8] * P->M_Delta_R * Heavy_OverRain(R, R_A);                 
  }
  
  if(P->I[2] == 1){
    //printf("(2-3-4)");
    /* (3) */   /* P->L_Delta = P->L_Delta_P + f(Rain)                       + f(Temp) */
    P->L_Delta = P->L_Delta_P + P->I[3] * P->L_Delta_R * Heavy_OverRain(R, R_A) + P->I[4] *Larva_Mosquito_Mortality(T); 
  }
  else{
    P->L_Delta = P->L_Delta_P;
  }
  
  /* (4) */
  if(P->I[5] == 1){
#if defined GONO_INDOORS
    P->M_a     = Gonotrophic_Cycle_Agam_Indoor(T);
#else
    P->M_a     = Gonotrophic_Cycle_P(P->R_T.x, T);
#endif 
 
    P->M_Fecundity = P->M_NoEggs * P->M_a;
  }
  else{
   /* Obsolete Relationship" 
    *      P->M_a     = Gonotrophic_Cycle(T_A);  
    */  
#if defined GONO_INDOORS
    P->M_a     = Gonotrophic_Cycle_Agam_Indoor(T_A);
#else
    P->M_a     = Gonotrophic_Cycle_P(P->R_T.x, T_A); //Gonotrophic_Cycle(T_A); //Gonotrophic_Cycle_Agam_Indoor(T_A);
#endif
 
    P->M_Fecundity = P->M_NoEggs * P->M_a;
  }

  /* (5) */ 
    if(P->I[6] == 1){
    //printf("(6)");
    P->M_Gamma = Plasmodium_Development(T);
  }
  else{
    P->M_Gamma = Plasmodium_Development(T_A);
  }
  
  /* (6) */ 
  if(P->I[7] == 1){
    //printf("(7)");
    P->L_Devel = Larva_Mosquito_Development(T);
  }
  else{
    P->L_Devel = Larva_Mosquito_Development(T_A);
  }

  No_Calls++;
}

double OverRain(double R, RainTemp R_T)
{
  double x;
  /* Over daily rain with respect average rain */ 
  
  x = R - R_T.Ave_Rain/R_T.T_i/ 10.0;
  
  if(x > 0)
    return(x);
  else
    return(0.0);

}

double Heavy_OverRain(double R, double R_A)
{
  double x;
  /* Over daily rain with respect 12 month moving average rain */ 
  
  x = R - R_A;
  
  if(x > 0)
    return(x);
  else
    return(0.0);
}

