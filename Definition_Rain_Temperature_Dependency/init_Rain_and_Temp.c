#include "../Include/MODEL.h"
#include "../Include/include.extern.par.RainTemp.h"

//#define PRINT_OUT

void init_Rain_and_Temperature(Parameter_Table *P, char *F_1, char *F_2, char *F_3, char *F_4)
{
  /* 
     Rain and Temperature structure will contain the observed time series of rain, 
     temperature and cases. 
  */ 
  int i_POINTS, i,k;
  int NO_of_TERMS;
  double SUM_C, SUM_R, SUM_T;
  FILE *fp; 
  double EMPIRICAL_AVE, EMPIRICAL_VAR, EMPIRICAL_AbDEV;

  /* Temperature Parameters */
  P->R_T.TEMP__SHIFT = TEMP__SHIFT;/* Celcius degrees */ 
                                   /* This is to take into account a difference
	                              between the environmetal true temperature, 
	                              which is controling outdoors developing larvas 
	                              and an effective higher temperature, which 	
	                              is affecting indoors mosquito adult stage
                                    */  
  P->R_T.T_ELEVATION = T_ELEVATION;/* Celcius degrees */ 

  /* n = 48  */ P->R_T.x             = x;

  printf("[T_ELEVATION = %g]   This is to mimic a temperature time series\n\tcorresponding to a higher (or lower) location:\n\tAll the time series values will be shifted %g degrees down (or up)\n", 
	 T_ELEVATION, T_ELEVATION); 
	                           /* This is to mimic a temperature time series   
                                      corresponding to a higher or lower location:
                                      All the series is shifted down (or up) 
	                              T_ELEVATION 
	                           */
  /* Time-dependent parameter Data */
  P->R_T.No     = NO_of_POINTS;     
  P->R_T.No_Ave = NO_of_POINTS_AVE;
  P->R_T.No_Ini = NO_of_POINTS_AVE; /* Initial number of point to estimate the initial condition */
  P->R_T.T_i    = T_INCREMENT;
  P->R_T.INITIAL_YEAR = INITIAL_YEAR; 

  P->R_T.Rain   = (double *)malloc( NO_of_POINTS * sizeof(double) );
  P->R_T.Temp = (double *)malloc( NO_of_POINTS * sizeof(double) );
  P->R_T.Rain_Smooth = (double *)malloc( NO_of_POINTS * sizeof(double) );
  P->R_T.Temp_Smooth = (double *)malloc( NO_of_POINTS * sizeof(double) );
  P->R_T.Case = (double *)malloc( NO_of_POINTS * sizeof(double) );
  
  /* Daily integration */
  P->R_T.Time = (double *)malloc( NO_of_POINTS * sizeof(double) );
  P->R_T.Days = (double *)malloc( (NO_of_POINTS+1) * sizeof(double) );
  P->R_T.Year = (double *)malloc( (NO_of_POINTS+1) * sizeof(double) );
  P->R_T.DDMM = (Day_Month_RAIN *)malloc ( NO_of_POINTS * 31 * sizeof( Day_Month_RAIN) );

  /* Average Seasonal Cycle */
  P->R_T.Rain_Ave = (double *)malloc(NO_of_POINTS_AVE * sizeof(double) );
  P->R_T.Temp_Ave = (double *)malloc(NO_of_POINTS_AVE * sizeof(double) );
  P->R_T.Time_Ave = (double *)malloc(NO_of_POINTS_AVE * sizeof(double) );
  P->R_T.Case_Ave = (double *)malloc(NO_of_POINTS_AVE * sizeof(double) );

  P->R_T.Rain_Var = (double *)malloc(NO_of_POINTS_AVE * sizeof(double) );
  P->R_T.Temp_Var = (double *)malloc(NO_of_POINTS_AVE * sizeof(double) );
  P->R_T.Case_Var = (double *)malloc(NO_of_POINTS_AVE * sizeof(double) );

  /* Reading from files */
  Reading_from_File_double_TwoCol(F_1, P->R_T.Time, P->R_T.Rain, NO_of_POINTS);
  Reading_from_File_double_TwoCol(F_2, P->R_T.Time, P->R_T.Temp, NO_of_POINTS);
  Reading_from_File_double_TwoCol(F_3, P->R_T.Time, P->R_T.Case, NO_of_POINTS);
 
#if defined PRINT_OUT
  printf("Data files:\n");
  printf("... ... ... %s\n", F_1);
  printf("... ... ... %s\n", F_2);
  printf("... ... ... %s\n", F_3);

  for(i=0; i<NO_of_POINTS; i++){
    printf("Time = %g\tRain = %g\t Temp = %g\t Case = %g\n", 
	   P->R_T.Time[i], P->R_T.Rain[i], P->R_T.Temp[i], P->R_T.Case[i]);
  }
  Press_Key();
#endif

  /* Calculation Averages for the whole period */  
  P->R_T.Ave_Rain = Average_double_Vector(P->R_T.Rain, NO_of_POINTS);
  P->R_T.Ave_Temp = Average_double_Vector(P->R_T.Temp, NO_of_POINTS);
  P->R_T.Ave_Case = Average_double_Vector(P->R_T.Case, NO_of_POINTS);

  int Month_Shift = 12 * ( INITIAL_YEAR - P->R_T.Time[0] );
  
  Average_Variance_and_Absolute_Deviation_double_Vector(P->R_T.Case, Month_Shift,  
							NO_of_POINTS, 
							&EMPIRICAL_AVE, &EMPIRICAL_VAR, &EMPIRICAL_AbDEV); 
  P->R_T.EMPIRICAL_AVE = EMPIRICAL_AVE;
  P->R_T.EMPIRICAL_VAR = EMPIRICAL_VAR;
  P->R_T.EMPIRICAL_AbDEV = EMPIRICAL_AbDEV;

  /* Calculating a year-based moving average for the temperature */
  printf(" Calculating a yearly-based moving average for the temperature...\n");

  moving_Average_double_Vector(P->R_T.Temp, P->R_T.Temp_Smooth, NO_of_POINTS, 12);

#if defined PRINT_OUT
  printf("Saving yearly-based moving average from temperuture time series data...\n");
#endif
  Saving_to_File_double("movAVE_Temp", P->R_T.Time, P->R_T.Temp_Smooth, NO_of_POINTS, 0);

  /* Calculating a year-based moving average for the rainfall */
  printf(" Calculating a yearly-based moving average for the rainfall...\n");

  moving_Average_double_Vector(P->R_T.Rain, P->R_T.Rain_Smooth, NO_of_POINTS, 12);

#if defined PRINT_OUT
  printf("Saving yearly-based moving average from rainfall time series data...\n");
#endif
  Saving_to_File_double("movAVE_Rain", P->R_T.Time, P->R_T.Rain_Smooth, NO_of_POINTS, 0);  

#if defined SHOW_SEASONAL_CYCLE
  for(i=0; i < NO_of_POINTS_AVE; i++) P->R_T.Time_Ave[i] = (double)i + 1.0; //P->R_T.Time_Ave[i]; 
  A_V_E_R_A_G_E___S_E_A_S_O_N_A_L___C_Y_C_L_E ( "Rain_Seasonal.dat", NO_of_POINTS, 
   					        NO_of_POINTS_AVE, P->R_T.Rain, P->R_T.Rain_Ave, P->R_T.Rain_Var ); 
  A_V_E_R_A_G_E___S_E_A_S_O_N_A_L___C_Y_C_L_E ( "Temp_Seasonal.dat", NO_of_POINTS, 
					        NO_of_POINTS_AVE, P->R_T.Temp, P->R_T.Temp_Ave, P->R_T.Temp_Var ); 
  A_V_E_R_A_G_E___S_E_A_S_O_N_A_L___C_Y_C_L_E ( "Case_Seasonal.dat", NO_of_POINTS, 
					        NO_of_POINTS_AVE, P->R_T.Case, P->R_T.Case_Ave, P->R_T.Case_Var ); 
#endif

#if defined DAILY_TIME_INTEGRATION
  i_POINTS = NO_of_POINTS/NO_of_POINTS_AVE;

  printf("  D A I L Y   T I M E   I N T E G R A T I O N ");
  printf("  Number of points in the time series: %d\n", NO_of_POINTS);
  printf("  Number of moths in a year cycle: %d\n", NO_of_POINTS_AVE);
  printf("  Total number of (complete) years to be consisered: %d\n", i_POINTS);
  printf("  Initial year for all numerical integrations: %g\n", P->R_T.INITIAL_YEAR);
  printf("  Preprocessing needed for DAILY TIME INTEGRATION...\n");
  //Press_Key();
 
  setting_proper_daily_time(P, NO_of_POINTS);
  
  /* Reading Daily Rainfall */
  //pre_processing_daily_Rain(F_4, P, NO_of_POINTS);

  processing_Daily_Rain_Hail_File(F_4, P, NO_of_POINTS);
  
  printf(" R a i n --- T e m p e r a t u r e   D a t a   S t r u c t u  r e\n");
  printf(" h a s   b e e n   S U C C E S S F U L L Y   s e t   u p\n");
  printf(" N O W ...   Exiting function:\n");
  printf(" init_Rain_and_Temperature(Parameter_Table *P, char *F_1, char *F_2, char *F_3, char *F_4)\n");
#if defined VERY_VERBOSE
  Press_Key();
#endif
#endif
}

void print_average_Seasonality(Parameter_Table *P, char *F_1, char *F_2, char *F_3)
{
  int i, NO_of_POINTS, NO_of_POINTS_AVE;

  NO_of_POINTS = P->R_T.No;
  NO_of_POINTS_AVE = P->R_T.No_Ave;
  
  /* Checking good reading...*/

  printf("The following data have been successfully read from files:\n");
  printf("... %s\n", F_1);
  printf("... %s\n", F_2);
  printf("... %s\n", F_3);

  for(i=0; i<NO_of_POINTS; i++){
    printf("Time: %g  Rain (mm): %g Temperature: %g --- Cases: %g\n", 
	   P->R_T.Time[i], P->R_T.Rain[i], P->R_T.Temp[i], P->R_T.Case[i]);
  }
  
  printf("\n Average seasonal cycle...\n");

  for(i=0; i<NO_of_POINTS_AVE; i++){
    printf("Month %d Time (y): %g  Rain (mm): %g Temperature: %g --- Cases: %g\n", 
	   1+i, P->R_T.Time_Ave[i], P->R_T.Rain_Ave[i], P->R_T.Temp_Ave[i], P->R_T.Case_Ave[i]);
  }

}

void alloc_Rain_and_Temperature(Parameter_Table *P, int NO, int NO_AVE)
{
  /* . NO, number of rows in the data file (total number of data points */
  /* . NO_AVE, number of month (12) of a year */

  P->R_T.Rain   = (double *)malloc( NO * sizeof(double) );
  P->R_T.Temp = (double *)malloc( NO * sizeof(double) );
  P->R_T.Rain_Smooth = (double *)malloc( NO * sizeof(double) );
  P->R_T.Temp_Smooth = (double *)malloc( NO * sizeof(double) );
  P->R_T.Case = (double *)malloc( NO * sizeof(double) );
  
  P->R_T.Time = (double *)malloc( NO * sizeof(double) );
  P->R_T.Days = (double *)malloc( (NO+1) * sizeof(double) );
  P->R_T.Year = (double *)malloc( (NO+1) * sizeof(double) );
  P->R_T.DDMM = (Day_Month_RAIN *)malloc ( NO * 31 * sizeof( Day_Month_RAIN) );

  /* Average Seasonal Cycle */
  P->R_T.Rain_Ave = (double *)malloc(NO_AVE * sizeof(double) );
  P->R_T.Temp_Ave = (double *)malloc(NO_AVE * sizeof(double) );
  P->R_T.Time_Ave = (double *)malloc(NO_AVE * sizeof(double) );
  P->R_T.Case_Ave = (double *)malloc(NO_AVE * sizeof(double) );

}

void free_Rain_and_Temperature(Parameter_Table *P)
{
  free (P->R_T.Rain);
  free (P->R_T.Temp);
  free (P->R_T.Case);
  free (P->R_T.Temp_Smooth);
  free (P->R_T.Rain_Smooth);

  free (P->R_T.Time);
  free (P->R_T.Days);
  free (P->R_T.Year);
  free (P->R_T.DDMM);

  free (P->R_T.Rain_Ave);
  free (P->R_T.Temp_Ave);
  free (P->R_T.Time_Ave);
  free (P->R_T.Case_Ave);

  free (P->R_T.Rain_Var);
  free (P->R_T.Temp_Var);
  free (P->R_T.Case_Var);
}
