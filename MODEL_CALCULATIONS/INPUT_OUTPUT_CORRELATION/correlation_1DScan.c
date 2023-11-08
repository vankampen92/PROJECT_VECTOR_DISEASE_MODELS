#include "../../Include/MODEL.h"

#define FISHING_and_SAVING_TIME_EVO
/* 
   This driver runs a number of stochastic realizations
   or replicates of a given stochatic model. 
   After all realizations are done, some averages
   for some model output variables are calculated
   and, if required, represented by using the PGPLOT 
   library
*/
double Maximum_Lag_Correlation_double_Vector(double * y_0, double * y_1, int N, 
                                             double * corr, int * max_LAG);
double Maximum_Lag_Correlation_double_Vector_Annual(double * y_0, double * y_1, int N);

int C_O_R_R_E_L_A_T_I_O_N___S_I_M_P_L_E___S_C_A_N( Parameter_Table * P, 
						   int No_of_POINTS, 
						   int Input_Parameter,
						   double Value_0,
						   double Value_1 ) 
{
  int max_LAG;
  double max_Time_LAG;
  double covariance;
  double Value, AVE_0, VAR_0;
  int i,j, k;
  
  /* 
     This function scan one parameter [Input_Parameter] bxetween Value_0 and Value_1, 
     evaluating, for each value, the correlation between a environmentally varying, 
     forcing variable and a model output variable. There are a number of output variables 
     available, which should be given as command line arguments: for instance: 
     -n 3 -v0 [label variable 1] -v1 [label variable 2] -v2 [label variable 3]
     where these labels are defined in definition_Output_Variables.c. Notice that
     n has to be always n = 3, for efficiency. 
     Note: -v0 should be always 30 and -v1 contains the first true output variable.
           30 is a magic number meaning there will be a forcing parameter whose 
	   dynamics will be stored as the first output variable 
	   (see definition_OutPut_Variables.c for details). 
    
     The correlation calculation depends on the focal Input_Parameter and all the 
     other model parameters, but the rest of the other parameters are kept constant.
     
     Input parameter is the label of any given input (model) parameter from
     the list appearing in all the assing_[---].c and boundary functions.

     List of saved files: 
     
     . time_EVO_MOVING_AVERAGE_[n].dat 
     (provided FISHING_and_SAVING_TIME_EVO is defined)
     This file is a three column file:
                                time, y1, movave(y1), 
     where y1 is the main output variable (fractions of infectious humans, for example) 
     and mov(y1) represent its moving average.

     . time_EVO_STD_OSCILLATION_[n].dat
     This files is a three column file:
                                time, y0, y1-movave(y1)
     where y0 is the fluctuating model parameter and y1-movave(y1) is what remains after
     substracting to the output variable its corresponding moving average, where n goes 
     from 0 to No_of_POINTS_1. 

     . scan_CORRELATION_0.dat contains (x_Data, y_0)  
     . scan_COVARIANCE_0.dat contains (x_Data, y_1)
       
     . scan_CORRELATION__R_0.dat is a 2 column vector containing the relation between 
     x_Data_1 and the correlation along the transect of the parameter space explored 
     (input_Paramater). x_Data_1 can be, for instance, the output variable R_0. 
     
     . scan_CORRELATION__EIR_0.dat is a 2 column vector containing the relation between 
     x_Data_2 and the correlation along the transect of the parameter space explored 
     (input_Paramater). x_Data_2 can be another output variable, for instance, EIR.
  
     . scan_ForcingParemeter_vs_R_0.dat is a 2 column vector containing x_Data, x_Data_1 
     column vectors, where x_Data represent the values of the model parameter along the
     transect and x_Data_1 is an output variable. 

     . scan_ForcingParameter_vs_EIR_0.datis a 2 column vector containing x_Data, x_Data_2 
     column vectors, where x_Data represent the values of the model parameter along the
     transect and x_Data_2 is another output variable.    
  */

  /* BEGIN : Allocating memory for saving data * * * * * * * * * * * * */  
  double * y_0  = (double  *)malloc( No_of_POINTS * sizeof(double) );
  double * Y_0  = (double  *)malloc( No_of_POINTS * sizeof(double) );
  double * y_1  = (double  *)malloc( No_of_POINTS * sizeof(double) );

  double * y_2  = (double  *)malloc( P->T->I_Time * sizeof(double) );
  double * y_STD  = (double  *)calloc( P->T->I_Time, sizeof(double) ); 
  double * Time_Year = (double*)calloc( P->T->I_Time, sizeof(double) );
  
  double * x_Data    = (double *)malloc(No_of_POINTS * sizeof(double) ); 
  double * x_Data_1  = (double *)malloc(No_of_POINTS * sizeof(double) ); 
  double * x_Data_2  = (double *)malloc(No_of_POINTS * sizeof(double) ); 
  /*   END : Allocating memory for saving dynamical data * * * * * */

  printf( "Rainfall Intensity (mm/day) = %g\n", P->K_p);	  
  printf( "Average rainfall Intensity (mm/day) = %g\n", P->K_Mean_Value);	  
  
  /* BEGIN : Calculation of Sampled Points per Forcing Period */
  int Sampling_Points_per_Period;
  double Dt; /* Interval Sampling Time */

  Dt = (P->T->Time_1 - P->T->Time_0) / (double)(P->T->I_Time-1);

  Sampling_Points_per_Period = (int)(P->K_Period/Dt);

  printf(" Sampling Points per Forcing Period (1 year): %d\n",
         Sampling_Points_per_Period);

  Press_Key();
  /*   END : -------------------------------------------------*/

  assert( P->SUB_OUTPUT_VARIABLES > 2 );
  
  for( j = 0; j < No_of_POINTS; j++ ){
      
    Value = Value_0 + j * (Value_1 - Value_0)/(double)(No_of_POINTS - 1);
    
    AssignVectorEntry_to_Structure(P, Input_Parameter, Value);

    if (Input_Parameter == 12) P->M_a_Mean_Value  = P->M_a;
    if (Input_Parameter == 25) P->K_Mean_Value    = P->K_0;
    if (Input_Parameter == 51) P->Temp_Mean_Value = P->Temp;

    x_Data[j]   = Value;
    // Calculation of R_0 (labeled 19 in definition OutPut Variable)
    // for each new parameter set as the focal parameter (value) increases
    // -S4 [Label_Input_Parameer] -S5 [Value_0] -S6 [Value_1] 
    x_Data_1[j] = definition_OutPut_Variables(19, x_Data_1, 0.0, P);

    // Recovering the 2nd part of the dynamics in the variable y_2 */
    k = 0; 
    for( i=P->T->I_Time/2; i<P->T->I_Time; i++ ) {
      y_2[k] = P->CPG->y_Time[2][i];
      k++;
    }	     
    Average_and_Variance_double_Vector(y_2, P->T->I_Time/2, &AVE_0, &VAR_0 );	
    // This contains the average value of the 2nd part of the time series
    // of a fluctuating output variable entered as -v2 [Key] in the command
    // line. If -v2 21, then this variable is the EIR. 
    x_Data_2[j] = AVE_0;
    
    M_O_D_E_L___S_I_M_P_L_E( P );

#if defined CPGPLOT_REPRESENTATION 
    int TIMES        = P->T->I_Time;
    /* Input_Parameter. The value of this model parameter appears in the title */
    C_P_G___S_U_B___P_L_O_T_T_I_N_G___C_U_S_T_O_M_I_Z_E_D___T_I_T_L_E ( P, 
									TIMES, 
									P->CPG->x_Time, 
									P->CPG->y_Time,
									Input_Parameter );
    // Press_Key(); 
#endif
    
#if defined FISHING_and_SAVING_TIME_EVO
    for (k=0; k<P->T->I_Time; k++){
	Time_Year[k] = P->CPG->x_Time[k]/P->K_Period;
    }   
    int Save = 1;
    //printf( "Saving Time Evolution ?\n" );
    //printf( "Type either 1 for YES or 0 otherwise and, then, RETURN\n" );
    //scanf("%d" , &Save );
    if (Save == 1 ) {
        Saving_to_File_double_3Col("time_EVO_MOVING_AVERAGE_", Time_Year, P->CPG->y_Time[1], y_STD,  P->T->I_Time, j);
    }
#endif

    for( k=0; k <  P->T->I_Time; k++) y_STD[k] = P->CPG->y_Time[1][k]; 
    y_0[j]  = Maximum_Lag_Correlation_double_Vector( P->CPG->y_Time[0], y_STD, P->T->I_Time,
						     &covariance, &max_LAG );    
#if defined FISHING_and_SAVING_TIME_EVO
    if (Save == 1 ) {
        Saving_to_File_double_3Col("time_EVO_STD_OSCILLATION_", Time_Year, P->CPG->y_Time[0], y_STD,  P->T->I_Time, j);
    }
#endif    
    /* Removing the trend before calculating correlations */
    moving_Average_double_Vector( P->CPG->y_Time[1], y_STD, P->T->I_Time,
				  Sampling_Points_per_Period ) ;
    for( k=0; k <  P->T->I_Time; k++) y_STD[k] = P->CPG->y_Time[1][k] - y_STD[k];
    Y_0[j]  = Maximum_Lag_Correlation_double_Vector( P->CPG->y_Time[0], y_STD, P->T->I_Time,
						     &covariance, &max_LAG );    
    y_1[j]  = covariance; //Maximum_Lag_Correlation_double_Vector_Annual( P->CPG->y_Time[0], P->CPG->y_Time[1], P->T->I_Time );

    if(Input_Parameter  == 12)
      printf(" Maximum Lag Correlation [(a   = %g) (Value = %g)]    \t y_1(%d) = %g\n", P->M_a_Mean_Value, Value ,
	     j, y_1[j]);
    if(Input_Parameter  == 25)
      printf(" Maximum Lag Correlation [(K_0 = %g) (Value = %g)]    \t y_0(%d) = %g\n", P->K_Mean_Value, Value,
	     j, y_0[j]);

    printf(" Maximum lag (in number of sampling points): %d\n", max_LAG);
    max_Time_LAG = (double)(max_LAG%Sampling_Points_per_Period) * Dt; 	
    printf(" Maximum time lag (days): %g\n", max_Time_LAG);
    printf(" -----------------\n");
  }
    
  /* BEGIN : Saving to File  */
  Saving_to_File_double("scan_CORRELATION_", x_Data, y_0, No_of_POINTS, 0); 
  Saving_to_File_double("scan_COVARIANCE_", x_Data, y_1, No_of_POINTS, 0); 
#if defined CPGPLOT_REPRESENTATION
  int SAME_PLOT = 0;
  P->CPG->Title[0]='\0'; P->CPG->X_label[0]='\0'; P->CPG->Y_label[0]='\0';
  sprintf(P->CPG->Title, "%s vs %s raw correlation - K=%5.0f, T=%3.1f, Intensity= %.1f",
	  P->Variable_Name[P->IO_VARIABLE_LIST[1]],
	  P->Name_Parameters[P->Tr->Tr_Input_Parameter], 
	  P->K_Mean_Value, P->Temp_Mean_Value, P->K_Seasonal_Intensity );
  sprintf(P->CPG->X_label, "Input Parameter: %s", P->Name_Parameters[Input_Parameter]);
  sprintf(P->CPG->Y_label, "Correlation");
  P->CPG->type_of_Width = 8; 
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( P->CPG,
							SAME_PLOT,
							No_of_POINTS, 
							x_Data, y_0,
							P->CPG->X_label, 
							P->CPG->Y_label, 
							P->CPG->Title,
							0, 0 );
#endif
  
  /* These two files save correlation values as R and EIR increase as a consequencia
     of the Input Model Parameter increasing */ 
  Saving_to_File_double("scan_CORRELATION__R_", x_Data_1, y_0, No_of_POINTS, 0); 
  Saving_to_File_double("scan_CORRELATION__EIR_", x_Data_2, y_0, No_of_POINTS, 0);
#if defined CPGPLOT_REPRESENTATION
  sprintf(P->CPG->Title, "%s vs %s detrended correlation - K=%5.0f, T=%3.1f, Intensity= %.1f",
	  P->Variable_Name[P->IO_VARIABLE_LIST[1]],
	  P->Name_Parameters[P->Tr->Tr_Input_Parameter], 
	  P->K_Mean_Value, P->Temp_Mean_Value, P->K_Seasonal_Intensity );
  sprintf(P->CPG->X_label, "Input Parameter: %s", P->Name_Parameters[Input_Parameter]);
  sprintf(P->CPG->Y_label, "Correlation");
  P->CPG->type_of_Width = 8; 
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( P->CPG,
							SAME_PLOT,
							No_of_POINTS, 
							x_Data, Y_0,
							P->CPG->X_label, 
							P->CPG->Y_label, 
							P->CPG->Title,
							0, 0 );
#endif
	  
  /* These two files save the relation between the forcing parameter and two reponse 
     variables R and EIR (because -v2 21) calculated throughout the dynamics */
  Saving_to_File_double("scan_ForcingParemeter_vs_R_", x_Data, x_Data_1, No_of_POINTS, 0);
  Saving_to_File_double("scan_ForcingParameter_vs_EIR_", x_Data, x_Data_2, No_of_POINTS, 0);
#if defined CPGPLOT_REPRESENTATION
  P->CPG->Title[0]='\0'; P->CPG->X_label[0]='\0'; P->CPG->Y_label[0]='\0';
  sprintf(P->CPG->Title, "%s vs R_0 - K=%5.0f, T=%3.0f, Seasonal_Intensity= %.1f",
	  P->Name_Parameters[Input_Parameter],
	  P->K_Mean_Value, P->Temp_Mean_Value, P->K_Seasonal_Intensity );
  sprintf(P->CPG->X_label, "Input Parameter: %s", P->Name_Parameters[Input_Parameter]);
  sprintf(P->CPG->Y_label, "R_0");
  P->CPG->type_of_Width = 8; 
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( P->CPG,
							SAME_PLOT,
							No_of_POINTS, 
							x_Data, x_Data_1,
							P->CPG->X_label, 
							P->CPG->Y_label, 
							P->CPG->Title,
							0, 0 );
#endif
  /*   END : Saving to File */

  write_Param_Table_Default_Values( "Parameter_Table.tex", P, P->SUB_MODEL_PARAMETERS );
 
  /* BEGIN : Freeing previous allocated memory */
  free (y_0);  free(Y_0); 
  free (y_1);  free(y_2); free(y_STD); free( Time_Year) ;
  free(x_Data); 
  free(x_Data_1);
  free(x_Data_2);
  /*   END : End freeing allocated memory */

  return(0);
}

  
