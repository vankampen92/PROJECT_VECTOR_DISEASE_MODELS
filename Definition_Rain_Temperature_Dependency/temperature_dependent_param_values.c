#include "../Include/MODEL.h"

#if defined WATER_MATURATION_DELAY
#define WATER_MATURATION (1.0)
#else
#define WATER_MATURATION (0.0)
#endif

void Temperature_Dependent_Parameter_Values( Parameter_Table * P, double Temperature, double T___SHIFT, 
					     double D___RAIN, double R___RAIN )         
{
  int i;
  double R, R_A;
  double T, T_A;
  double K_0;

  /*
    For i>0:

    If I[i] == 1, it means that for the i-th feature is 
    controled by the environmental temperature.

    If I[i] == 0, it means that the i-th feature is controled
    by an effected up shifted temperature (indoors temperature)

    I[0] is the switcher controling rainfall: It is not meaningful
    in this context. 

  */
  T = Temperature;                 
/*
 * T.   Temperature at time t in Celsius degrees 
 */
#if defined T_SHIFT_TEMPERATURE 
  T_A = T + T___SHIFT;
#else
  T_A = T + (1.0 - P->R_T.x) * T___SHIFT;
#endif
/*
 * T_A. Temperature at time t in Celsius degrees 
 * (effective temperature for adult mosquitoes) 
 */

  R   = R___RAIN;                  /* R___RAIN is a precipitaion value per unit time */ 
  R_A = R___RAIN - D___RAIN;       /* D___RAIN tells about how far away the actual rain R
				      from the (moving) average rain R_A is. When D___RAIN
				      is positive the actual rain R is greater than the moving
				      average rain R_A and there are wash-out effects
				      to consider, depending on the P->M_Delta_R (adult mosquitoes)
				      or P->L_Delta_R (mosquito larvas) parameters.
				   */ 
  for(i=0; i < P->no_I; i++){  
    assert(P->I[i] == 1 || P->I[i] == 0);
  }
  
  /* (1) */
  if(P->I[0] == 1){
    //printf("(0)");
    P->K_p     = R___RAIN; 	/* R___RAIN is the daily rain intensity */
    
#if defined WATER_MATURATION_DELAY
  P->K_0 = P->K_A * ( P->K_p / P->K_E  * P->K_Maturation/(P->K_E + P->K_Maturation) );
#else
  P->K_0 = P->K_A * P->K_p / P->K_E ;
#endif
  }
  
  /* (2) */ 
  if(P->I[1] == 1){
    //printf("(1)");
    P->M_Delta = Adult_Mosquito_Mortality(T) + P->I[8] * P->M_Delta_R * Heavy_OverRain(R, R_A);
  }
  else{
    P->M_Delta = Adult_Mosquito_Mortality(T_A) + P->I[8] * P->M_Delta_R * Heavy_OverRain(R, R_A);
  }
  
  if(P->I[2] == 1){ 		/* D___RAIN measures the effect of
				   overrain on larva mortality 
				   D___RAIN is the difference 
				   between the actual daily rain 
				   intensity and the 12-moths moving
				   averaged daily rain intensity. 
				*/
    //printf("(2-3-4)");
    /* (3) */   /* P->L_Delta = P->L_Delta_P  +  f(Rain)  +  f(Temp) */
    P->L_Delta = P->L_Delta_P +  P->I[3] * P->L_Delta_R * Heavy_OverRain(R, R_A) + P->I[4] *Larva_Mosquito_Mortality(T); 
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

#if defined GONO_INDOORS 
    P->M_a     = Gonotrophic_Cycle_Agam_Indoor(T_A);
#else
    P->M_a     = Gonotrophic_Cycle_P(P->R_T.x, T_A); 
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
}

