#include "../Include/MODEL.h"

#define GAMBIAE /* Gonotrophic cycle of /A. gambiae/ */

/* 
   This function ( stored in rainTemp_ParamAverages.c )
   calculates the time dependent averages or point values
   at a particular time according to the time dependent 
   parameter as defined in the rainTemperature_[---].c
   corresponding file
*/

void average_Parameter_Values_SHIFT(Parameter_Table *P, int n_year, int n_Interval, const int *I)
{
  /* Parameters corresponding to the n-th interval. 
   * The length of the interval (n_Interval) is given in months 
   * Example:
   * 	n_year = 1;
   * 	n_Interval = 12;
   * 	Then, j = n_year * n_Interval + i gives the month
   * 	corresponding to the second year (n_year = 0, 1, 2, ...)
   */
#if defined GA_INI_CON

       /* Environmental-dependent parameters corresponding to the 
	  initial time are used to feed the initial condition or
	  state of the system */
       int t_0 = 0;
       double Temperature, T___SHIFT, R___RAIN, D___RAIN;
       
       t_0  = P->R_T.No_Ave * (int)(P->R_T.INITIAL_YEAR - P->R_T.Time[0]);
       
       if( P->R_T.No_Ave != 12 ){
	 printf(" Points are not monthly data\n");
	 printf(" Check your data input\n");
	 printf(" The program will exit\t"); Press_Key();
	 exit(0);
       }
       
       Temperature  = P->R_T.Temp[t_0]/10.0;	
       T___SHIFT    = P->R_T.TEMP__SHIFT;

#if defined MONTH_TIME_INTEGRATION
       R___RAIN     = P->R_T.Rain[t_0]/10.0/30.5; /* R___RAIN is the daily rain intensity */
       D___RAIN     = P->R_T.Rain_Smooth[t_0]/10.0/30.5;
#else
       double INITIAL_DAY;
       int Year_Shift  = (int)(P->R_T.INITIAL_YEAR - P->R_T.Time[0]);
       if (Year_Shift > 0)  INITIAL_DAY = P->R_T.Days[ Year_Shift*12 ];
       else                 INITIAL_DAY = 0.0;
       R___RAIN = rain_Day(P, INITIAL_DAY);
       D___RAIN = rain_Day_Smooth(P, INITIAL_DAY);
#endif

       Temperature_Dependent_Parameter_Values( P, Temperature, T___SHIFT,
					       D___RAIN, R___RAIN );
#else

  int i, j;
  double * data_TEMP = (double *)malloc( sizeof(double) * n_Interval );
  double * data_RAIN = (double *)malloc( sizeof(double) * n_Interval );

  for(i=0; i < n_Interval; i++){
    
    j  = n_year * n_Interval + i;
    
    data_TEMP[i] = P->R_T.Temp[j]; 
    data_RAIN[i] = P->R_T.Rain[j];

  }
  //printf(" Entering Parameter Average...");   
  //for(i=0; i<n_Interval; i++) printf("[R=%g, T=%g]  ", data_RAIN[i], data_TEMP[i]); Press_Key();
  effective_Parameters_Average(P, data_TEMP, data_RAIN, n_year, n_Interval, I);
  //printf(" Averages have been performed successfully..."); Press_Key();

  free(data_TEMP);
  free(data_RAIN);

#endif
}

void effective_Parameters_Average(Parameter_Table *P, double *data_TEMP, double *data_RAIN, int n_year, int n_Interval, const int *I)
{
  /* 
     The main parameter structure P is initialized 
     with the average temperature (and rainfall) 
     corresponding to the first n months of the serie */

  double T_obs, T, T_A, T_i, T_i_A, R_i, R, R_A, p, K, K_0, t_0, t_1;
  int i;
  double L_Delta, L_Delta_0, M_Delta;

  T_obs = P->R_T.T_i;  /* Interaval between data points */                              
  /* 
     T.   Temperature at time t in Celsius degrees 
     (corrected for a different elevation) 

     If I[no] == 1, it means that for the "no" feature it is the
     environmental temperature corrected for elevation the one
     that controls the dyamics. 

     If I[no] == 0, it means that for the "no" feature it is an
     effected up shifted temperature (indoors temperature) the one
     that controls the dynamics. 

  */
  T = Average_double_Vector(data_TEMP, n_Interval)/10. + P->R_T.T_ELEVATION;
  /* 
     T_A. Temperature at time t in Celsius degrees 
     (effective temperature for adult mosquitoes) 
  */

#if defined T_SHIFT_TEMPERATURE 
  T_A = T + P->R_T.TEMP__SHIFT;
#else
  T_A = T + (1.0 - P->R_T.x) * P->R_T.TEMP__SHIFT;
#endif

  R   = Average_double_Vector(data_RAIN, n_Interval)/10.0;
  
  /* I[0] (rainfall) */
  P->K_p = R/30.5;                   /* Average daily precipation over entire period */

#if defined WATER_MATURATION_DELAY
  P->K_0 = P->K_A * ( P->K_p / P->K_E  * P->K_Maturation/(P->K_E + P->K_Maturation) );
#else
  P->K_0 = P->K_A * P->K_p / P->K_E ;
#endif

  /* I[1] (M_Delta, mosquito adult mortality) */
  M_Delta = 0.0;
  for(i = n_Interval*n_year; i < (n_Interval * (n_year + 1)); i++){

    T_i   = P->R_T.Temp[i]/10. + P->R_T.T_ELEVATION;;  
    
    if(I[1] == 1){
      T_i_A = T_i;   
    }
    else{
#if defined T_SHIFT_TEMPERATURE 
      T_i_A = T + P->R_T.TEMP__SHIFT;
#else
      T_i_A = T + (1.0 - P->R_T.x) * P->R_T.TEMP__SHIFT;
#endif
    }
    
    R_i = P->R_T.Rain[i]/T_obs/10.0;
    R_A = P->R_T.Rain_Smooth[i]/T_obs/10.0;

    M_Delta += Adult_Mosquito_Mortality(T_i_A) + I[8] * P->M_Delta_R * Heavy_OverRain(R_i, R_A);
 
  }  
  P->M_Delta  = M_Delta/(double)n_Interval;
 
 
  /* I[2], L_Delta (larva mortality) */
  L_Delta_0 = 0.0;
  for(i = n_Interval*n_year; i< (n_Interval * (n_year+1)); i++){
    
    T_i   = P->R_T.Temp[i]/10. + P->R_T.T_ELEVATION;;  
    
    if(I[2] == 1){
      T_i_A = T_i;   
    }
    else{
#if defined T_SHIFT_TEMPERATURE 
      T_i_A = T + P->R_T.TEMP__SHIFT;
#else
      T_i_A = T + (1.0 - P->R_T.x) * P->R_T.TEMP__SHIFT;
#endif
    }   
    
    R_i = P->R_T.Rain[i]/T_obs/10.0;
    R_A = P->R_T.Rain_Smooth[i]/T_obs/10.0;

    L_Delta_0 += I[4] * Larva_Mosquito_Mortality(T_i_A) + I[3] * P->L_Delta_R * Heavy_OverRain(R_i, R_A);
    
  }
  P->L_Delta_0  = L_Delta_0/(double)n_Interval; /* The temperature effect */
  P->L_Delta    = P->L_Delta_0 + P->L_Delta_P;

  /* I[5], M_a and M_Fecundity (gonotrophic cycle) */ 

  if(I[5] == 1){
    T_A = T;   
  }
  else{
#if defined T_SHIFT_TEMPERATURE 
    T_A = T + P->R_T.TEMP__SHIFT;
#else
    T_A = T + (1.0 - P->R_T.x) * P->R_T.TEMP__SHIFT;
#endif
  } 
    /* Obsolete relationship: P->M_a   = Gonotrophic_Cycle(T_A); */
#if defined GONO_INDOORS
    P->M_a     = Gonotrophic_Cycle_Agam_Indoor(T_A); 
#else
    P->M_a     = Gonotrophic_Cycle_P(P->R_T.x, T_A);  
#endif
    
   P->M_Fecundity = P->M_NoEggs * P->M_a;

  /* I[6], M_Gamma, /Plasmodium/ development rate */
  if(I[6] == 1){
    T_A = T;   
  }
  else{
#if defined T_SHIFT_TEMPERATURE 
    T_A = T + P->R_T.TEMP__SHIFT;
#else
    T_A = T + (1.0 - P->R_T.x) * P->R_T.TEMP__SHIFT;
#endif
  }  
  P->M_Gamma = Plasmodium_Development(T_A);

  /* I[7], L_Devel, maturation rate of larves into adult mosquitoes */
  if(I[7] == 1){
    T_A = T;   
  }
  else{
#if defined T_SHIFT_TEMPERATURE 
    T_A = T + P->R_T.TEMP__SHIFT;
#else
    T_A = T + (1.0 - P->R_T.x) * P->R_T.TEMP__SHIFT;
#endif
  } 
  P->L_Devel = Larva_Mosquito_Development(T_A);
}

void average_Parameter_Values_nMonths_SHIFT(Parameter_Table * P, int n, const int * I)
{
  /* 
     The main parameter structure P is initialized 
     with the average temperature (and rainfall) 
     corresponding to the first n months of the serie */

  /* n, number of months in the average */
  /* n_First_Year, number of years at the beginning of the time series
     that are not considered in the evaluation of the averages
     (Year_Shift) */

  int n_First_Year;
  
  n_First_Year = P->R_T.INITIAL_YEAR - P->R_T.Time[0];

  average_Parameter_Values_SHIFT(P, n_First_Year, n, I);  
}
