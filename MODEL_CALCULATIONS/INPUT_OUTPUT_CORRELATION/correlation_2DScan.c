#include "../../Include/MODEL.h"

/// #defined SAVING_SLICES_TO_FILE
/// #defined SHOWING_SLICES


double Maximum_Lag_Correlation_double_Vector(double * y_0, double * y_1, int N, double * covar, int * max_LAG);
double Maximum_Lag_Correlation_double_Vector_Annual(double * y_0, double * y_1, int N);

float * customized_contour_levels( Parameter_CPGPLOT * C );

int C_O_R_R_E_L_A_T_I_O_N___D_O_U_B_L_E___S_C_A_N( Parameter_Table * P,
						   int No_of_POINTS_1,
						   int Input_Parameter_1,
						   int No_of_POINTS_2,
						   int Input_Parameter_2)
{
  int max_LAG;
  double max_Time_LAG;
  double covariance;
  double Value, Value_0, Value_1, AVE_0, VAR_0;
  int i,j,k,l,n;

  int No_of_POINTS = No_of_POINTS_1 * No_of_POINTS_2;
  /*
     This function scan two parameter, (x,y), between their boundary values
     according to their definition in boundary_XX.c from ./Definition_Parameter_Space,
     evaluating, for each pair (x,y), the correlation between a varying environmental
     forcing variable and an output variable. These two output variables are given
     as command line arguments, -n 2 -v0 [label variable 1] -v1 [label variable 2],
     where these labels are defined in definition_Output_Variables.c. Notice that
     the number of output variables has to be 2, ( P->SUB_OUTPUT_VARIABLES = 2).
     Otherwise serious problems occur. Remember than the label of the first output
     variable has to be 30 and -TP [label model parameter] will contain the true
     fluctuating parameter, whose values will be saved as the first (-v0) output 
     variable. 

     The correlation calculation depends on the input parameters and all the
     other model parameters, but the rest of the other parameters are kept constant.

     Input parameters are given as labels corresponding to any given input (model) 
     parameter from the list appearing in all the assing_[---].c and boundary functions.

     This function saves (provided SAVING_SLICES_TO_FILE is defined): 

     . Correlation slices in Correlation_Scan_Slice_[n].dat
     . Covariance slices in Covariance_Scan_Slice_[n].dat
     where n = 0, ..., No_of_POINTNS_2
     
     Three column x y z files are always saved for 3D or heat plots:
     
     . correlation_2DScan.dat
     . covariance_2DScan.dat 
     . max_Time_LAG_2DScan.dat     
 
  */
  /* BEGIN : Allocating memory for saving data * * * * * * * * * * * * */
  double * y_0  = (double  *)calloc( No_of_POINTS, sizeof(double) );
  double * Y_0  = (double  *)calloc( No_of_POINTS, sizeof(double) );
  double * y_1  = (double  *)calloc( No_of_POINTS, sizeof(double) );
  double * y_2  = (double  *)calloc( No_of_POINTS, sizeof(double) );

  double * y_STD  = (double  *)calloc( P->T->I_Time, sizeof(double) );

  double * x_Data    = (double *)calloc(No_of_POINTS_1, sizeof(double) );
  double * y_Data    = (double *)calloc(No_of_POINTS_2, sizeof(double) );

  double      ** r_COVAR  = (double **)malloc( No_of_POINTS_2 * sizeof(double *) );
  for( i = 0; i < No_of_POINTS_2; i++){
    r_COVAR[i] = (double *)calloc( No_of_POINTS_1, sizeof(double) );
  }
  double      ** r_CORR  = (double **)malloc( No_of_POINTS_2 * sizeof(double *) );
  for( i = 0; i < No_of_POINTS_2; i++){
    r_CORR[i] = (double *)calloc( No_of_POINTS_1, sizeof(double) );
  }
  /*   END : Allocating memory for saving dynamical data * * * * * */

  assert ( P->SUB_OUTPUT_VARIABLES == 2 );

  // printf( "Rainfall Intensity (mm/day) = %g\n", P->K_p);
  // printf( "Average rainfall Intensity (mm/day) = %g\n", P->K_Mean_Value);
  // Press_Key();

  /* BEGIN : Calculation of Sampled Points per Forcing Period */
  int Sampling_Points_per_Period;
  double Dt; /* Time Sampling Interval */

  Dt = (P->T->Time_1 - P->T->Time_0) / (double)(P->T->I_Time-1);

  Sampling_Points_per_Period = (int)(P->K_Period/Dt);

  printf(" Sampling Points per Forcing Period (1 year): %d\n",
	 Sampling_Points_per_Period);

  Press_Key();
  /*   END : -------------------------------------------------*/

  n=0;
  for( i = 0; i < No_of_POINTS_2; i++ ){

     Boundary(Input_Parameter_2, &Value_0, &Value_1);

     Value = Value_0 + i * (Value_1 - Value_0)/(double)(No_of_POINTS_2 - 1);
     y_Data[i]= Value;

     AssignVectorEntry_to_Structure(P, Input_Parameter_2, Value);

     if (Input_Parameter_2 == 12) P->M_a_Mean_Value  = P->M_a;
     if (Input_Parameter_2 == 25) P->K_Mean_Value    = P->K_0;
     if (Input_Parameter_2 == 51) P->Temp_Mean_Value = P->Temp;

     Boundary(Input_Parameter_1, &Value_0, &Value_1);

     for( j = 0; j < No_of_POINTS_1; j++ ){

       Value = Value_0 + j * (Value_1 - Value_0)/(double)(No_of_POINTS_1 - 1);
       x_Data[j]   = Value;

       AssignVectorEntry_to_Structure(P, Input_Parameter_1, Value);
       
       if (Input_Parameter_1 == 12) P->M_a_Mean_Value  = P->M_a;
       if (Input_Parameter_1 == 25) P->K_Mean_Value    = P->K_0;
       if (Input_Parameter_1 == 51) P->Temp_Mean_Value = P->Temp;

       /* M_O_D_E_L___S_I_M_P_L_E ( P ) and M_O_D_E_L( P ) are almost identical,
          being the latter faster than the former */
       //M_O_D_E_L___S_I_M_P_L_E ( P );
       M_O_D_E_L( P );

#if defined CPGPLOT_REPRESENTATION
       /* This CPGPLOT plotting function uses:
	  Table->Vector_Model_Variables_MultiStability[0] );
	  Table->Vector_Model_Variables_MultiStability[1] );
	  Table->Vector_Model_Variables_MultiStability[2] );
	  If not calculated before, there should be at least allocated!!! 
       */
       int TIMES        = P->T->I_Time;
       /* Input_Parameter. The value of this model parameter appears in the title */
       C_P_G___S_U_B___P_L_O_T_T_I_N_G___C_U_S_T_O_M_I_Z_E_D___T_I_T_L_E ( P, 
									   TIMES, 
									   P->CPG->x_Time, 
									   P->CPG->y_Time,
									   Input_Parameter_1 );
#endif
       
       for( k=0; k <  P->T->I_Time; k++) y_STD[k] = P->CPG->y_Time[1][k];
       y_0[n]  = Maximum_Lag_Correlation_double_Vector( P->CPG->y_Time[0], y_STD,
							P->T->I_Time, &covariance, &max_LAG );
       y_1[n]  = covariance; // Maximum_Lag_Correlation_double_Vector_Annual( P->CPG->y_Time[0], P->CPG->y_Time[1], P->T->I_Time );
       moving_Average_double_Vector( P->CPG->y_Time[1], y_STD, P->T->I_Time,
				     Sampling_Points_per_Period) ;
       for( k=0; k <  P->T->I_Time; k++) y_STD[k] = P->CPG->y_Time[1][k] - y_STD[k];
       Y_0[n]  = Maximum_Lag_Correlation_double_Vector( P->CPG->y_Time[0], y_STD,
							P->T->I_Time, &covariance, &max_LAG );
       r_CORR[i][j]  = y_0[n];

       r_COVAR[i][j] = y_1[n];

       max_Time_LAG = (max_LAG%Sampling_Points_per_Period) * Dt;
       y_2[n]  = max_Time_LAG;

       printf(" Parameter Values (%s = %g)\t(%s = %g)\n",
	      P->Name_Parameters[Input_Parameter_1], x_Data[j],
	      P->Name_Parameters[Input_Parameter_2], y_Data[i] );
       printf(" Maximum Time Lag (days): %g\n", max_Time_LAG);
       printf(" Maximum Lag Correlation = %g\t Maximum Lag Covariance = %g\n", y_0[n], y_1[n]);
       printf(" -----------------\n");

       n++;
     }
#if defined SAVING_SLICES_TO_FILE
     Saving_to_File_double("Correlation_Scan_Slice_", x_Data, r_CORR[i], No_of_POINTS_1, i);
     Saving_to_File_double("Covariance_Scan_Slice_", x_Data, r_COVAR[i], No_of_POINTS_1, i);
#endif
#if defined SHOWING_SLICES
     //plot(x_Data, r_CORR[i], No_of_POINTS_1);
#endif
  }

  /* BEGIN : Saving to File  */
  FILE * fp_0 = fopen ( "correlation_2DScan.dat", "w" );
  FILE * fp_1 = fopen ( "covariance_2DScan.dat", "w" );
  FILE * fp_2 = fopen ( "max_Time_LAG_2DScan.dat", "w" );
  n = 0;
  for( k = 0; k < No_of_POINTS_2; k++ ) {
      for( j = 0; j < No_of_POINTS_1; j++ ){
	fprintf(fp_0, "%g\t%g\t%g\n", x_Data[j], y_Data[k], y_0[n]);
	fprintf(fp_1, "%g\t%g\t%g\n", x_Data[j], y_Data[k], y_1[n] );
	fprintf(fp_2, "%g\t%g\t%g\n", x_Data[j], y_Data[k], y_2[n] );
        n++;
      }
  }
  fclose(fp_0);  fclose(fp_1);  fclose(fp_2);
  /*   END : Saving to File */

#if defined CPGPLOT_REPRESENTATION
 /* BEGIN : CPGPLOT_REPRESENTATION : 2D GRID PLOTTING */
 /*********************************************************************/
  P->CPG->X_label   = P->Name_Parameters[Input_Parameter_1];
  P->CPG->Y_label   = P->Name_Parameters[Input_Parameter_2];
  /*********************************************************************/
  Boundary(Input_Parameter_1, &Value_0, &Value_1);
  P->CPG->ORIGIN_X    = Value_0;
  P->CPG->X_Dimension = (Value_1 - Value_0);
  
  Boundary(Input_Parameter_2, &Value_0, &Value_1);
  P->CPG->ORIGIN_Y = Value_0;
  P->CPG->Y_Dimension = (Value_1 - Value_0);
  
  P->CPG->x_GRID  = No_of_POINTS_1;
  P->CPG->y_GRID  = No_of_POINTS_2;
  
  int Output_Variable  = P->IO_VARIABLE_LIST[0];
  P->CPG->W_label   = P->Variable_Name[Output_Variable];
  
  int FIRST_PLOT = 0;
  double i_PLOT  = 0.0;
  C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S( P->CPG,
							y_0,
							FIRST_PLOT,
							P->CPG->CPG_SCALE_W,
							P->CPG->CPG_RANGE_W_0,
							P->CPG->CPG_RANGE_W_1,
							i_PLOT );
  Press_Key();
  FIRST_PLOT = 1;
  P->CPG->AUTOMATIC_CONTOUR = 0;
  /* If AUTOMATIC_CONTOUR is 0, the user should customized contours through
     the function customized_contour_levels(...);
  */
  P->CPG->contour_level = customized_contour_levels ( P->CPG );
  C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___C_O_N_T_O_U_R( P->CPG,
							  y_0,
							  FIRST_PLOT,
							  P->CPG->CPG_SCALE_W,
							  P->CPG->CPG_RANGE_W_0,
							  P->CPG->CPG_RANGE_W_1,
							  i_PLOT );
  /* Freeing P->CPG->contour_level in:
   * CPGPLOT___G_R_I_D___P_L_O_T_T_I_N_G___C_O_N_T_O_U_R( ... )
   */
  /*   END : ----------------------------------------- */
#endif
  
  /* BEGIN : Freeing previous allocated memory */
  free (y_0);  free(Y_0); 
  free (y_1);
  free (y_2);
  free (y_STD);
  free(x_Data);
  free(y_Data);
  for(i = 0; i < No_of_POINTS_2; i++) free (r_CORR[i]);
  free(r_CORR);
  for(i = 0; i < No_of_POINTS_2; i++) free (r_COVAR[i]);
  free(r_COVAR);
  /*   END : End freeing allocated memory */
  
  return(0);
}

float * customized_contour_levels( Parameter_CPGPLOT * C )
{
    int i;

    /* for (i=0; i < C->NC; i++) { */
    /*   clevels[i] = 1.0; */
    /* } */
    /* Two contour levels */
    C->NC = 5;             /* Default value 10 (see include.CPG.default.c) */

    float * clevels = (float *)calloc( C->NC, sizeof(float) );

    clevels[0] = 0.9;   /* Lags ...*/
    clevels[1] = 0.8;
    clevels[2] = 0.6;
    clevels[3] = 0.4;
    clevels[4] = 0.2;

    return(clevels);
}
