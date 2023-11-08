#include <MODEL.h>

int B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M___S_I_M_P_L_E___S_C_A_N( Parameter_Table *P,
								   int No_of_POINTS,
								   int Output_Variable,
								   int Input_Parameter,
								   double EPSILON )
{
  double y_LOWER, y_INTER, y_UPPER;
  double Value, Value_0, Value_1;
  int i,j, k;

  /* This function calculates a bifurcation diagram for a given Output Variable and a
     given Input Parameter.

     Input parameter is the label of any given input (model) parameters from
     the list appearing in all the assing_[].c functions

     Function Ouput:

     . A 4 column file named: "bifurcation_SOL_[Output_Variable].dat" is saved.

     . Three different files containing the three different branches (lower, intermediate,
     and upper) of the bifurcation diagram, for example:

     bifurcation_OUTPUT_VARIABLE_3_LOWER_Bifurcation_Parameter_12.dat
     bifurcation_OUTPUT_VARIABLE_3_INTER_Bifurcation_Parameter_12.dat
     bifurcation_OUTPUT_VARIABLE_3_UPPER_Bifurcation_Parameter_12.dat
  */

  /* BEGIN : Allocating memory for saving data to plot a bifurcation  * * * * * * */
  double       ** y_BIF  = (double  **)malloc( 3 * sizeof(double *) );
  for( j = 0; j < 3; j++) {
      y_BIF[j] = (double *)malloc( No_of_POINTS * sizeof(double) );
  }
  double * x_Data  = (double *)malloc(No_of_POINTS * sizeof(double) );
  /*   END : Allocating memory for saving dynamical data * * * * * */

  //Boundary(Input_Parameter, &Value_0, &Value_1);
  Value_0 = P->S->Value_0;
	Value_1 = P->S->Value_1;
	
  for( j = 0; j < No_of_POINTS; j++ ){

    Value = Value_0 + j * (Value_1 - Value_0)/(double)(No_of_POINTS - 1);

    AssignVectorEntry_to_Structure(P, Input_Parameter, Value);

#if defined LXVnW
	P->M_Fecundity = P->M_a * P->M_NoEggs;
#endif
#if defined XkVnW
	P->M_Fecundity = P->M_a * P->M_NoEggs;
#endif
#if defined XVnW
        /* Total mosquito population constant */
	P->M_Fecundity = P->M_Delta;
#endif
#if defined XW
	/* Total mosquito population constant */
	P->M_Fecundity = P->M_Delta;
#endif

    B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M( P, &y_LOWER, &y_INTER, &y_UPPER, Output_Variable,
					   EPSILON );

    x_Data[j] = Value;

    y_BIF[0][j]    = y_LOWER;    y_BIF[1][j] = y_INTER;    y_BIF[2][j] = y_UPPER;

    printf(" y_LOWER = %g\ty_INTER = %g\ty_UPPER = %g\n", y_LOWER, y_INTER, y_UPPER);
  }

  /* BEGIN : Saving to a single four column file  */
  Saving_to_File_double_4Col("bifurcation_OUTPUT_VARIABLE_",
			     x_Data, y_BIF[0], y_BIF[1], y_BIF[2], No_of_POINTS, Output_Variable);
  /*   END : Saving to File */

  /* BEGIN : Calculating the first derivative of each branch of the Output_Variable
             with respect to the Input_Parameter (bifurcation parameter)            */
  if( Output_Variable == 5 ){
    char * file_Derivative = (char *)calloc( 100, sizeof(char) );;
    char * f;

    for ( k = 0; k<3; k++ ) {

      file_Derivative[0]='\0';
      if ( k == 0 ) f = strcat(file_Derivative, "Derivative_of_EIR_LOWER_");
      if ( k == 1 ) f = strcat(file_Derivative, "Derivative_of_EIR_INTER_");
      if ( k == 2 ) f = strcat(file_Derivative, "Derivative_of_EIR_UPPER_");

      double * Derivative = (double *)calloc( No_of_POINTS, sizeof(double) );
      double * x_Data_Der = (double *)calloc( No_of_POINTS, sizeof(double) );

      for (j=0; j < (No_of_POINTS-1); j++) {
	Derivative[j] = (y_BIF[k][j+1] - y_BIF[k][j]) / (x_Data[j+1] - x_Data[j]);
	x_Data_Der[j] = (x_Data[j+1] + x_Data[j]) / 2.0;
      }
      for (j=0; j < (No_of_POINTS-1); j++) {
	Derivative[j] = (y_BIF[k][j+1] + y_BIF[k][j]) / 2.0 + x_Data_Der[j] * Derivative[j];
      }
      Saving_to_File_double( file_Derivative, x_Data_Der, Derivative, No_of_POINTS-1, Output_Variable );

      free(Derivative);
      free(x_Data_Der);
    }

    free(file_Derivative);
  }
  /*   END :                                                                        */

  /* BEGIN : Saving to files  */
  Saving_Bifurcation_Files( "bifurcation_OUTPUT_VARIABLE_",
			    Input_Parameter,
			    x_Data, y_BIF[0], No_of_POINTS,
			    x_Data, y_BIF[1], No_of_POINTS,
			    x_Data, y_BIF[2], No_of_POINTS,
			    Output_Variable );

  int N_Lower, N_Upper, N_Inter;
  double * x_Lower  = (double *)calloc(No_of_POINTS, sizeof(double) );
  double * x_Inter  = (double *)calloc(No_of_POINTS, sizeof(double) );
  double * x_Upper  = (double *)calloc(No_of_POINTS, sizeof(double) );

  double * y_Lower  = (double *)calloc(No_of_POINTS, sizeof(double) );
  double * y_Inter  = (double *)calloc(No_of_POINTS, sizeof(double) );
  double * y_Upper  = (double *)calloc(No_of_POINTS, sizeof(double) );

  Separating_Bifurcation_Branches ( EPSILON,
				    x_Data, y_BIF[0], y_BIF[1], y_BIF[2], No_of_POINTS,
				    x_Lower, y_Lower, &N_Lower,
				    x_Inter, y_Inter, &N_Inter,
				    x_Upper, y_Upper, &N_Upper );

  Saving_Bifurcation_Files( "BIF_SEPARATED_BRANCH_OUTPUT_VARIABLE_",
			    Input_Parameter,
			    x_Lower, y_Lower, N_Lower,
			    x_Inter, y_Inter, N_Inter,
			    x_Upper, y_Upper, N_Upper,
			    Output_Variable );

#if defined CPGPLOT_REPRESENTATION
  C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M ( P,
								    x_Lower, y_Lower, N_Lower,
								    x_Inter, y_Inter, N_Inter,
								    x_Upper, y_Upper, N_Upper,
								    Output_Variable,
								    Input_Parameter,
								    25 );
#endif

  free(x_Lower); free(x_Inter); free(x_Upper);
  free(y_Lower); free(y_Inter); free(y_Upper);
  /*   END : Saving to File */

  /* BEGIN : Freeing previous allocated memory */
  for( j = 0; j < 3; j++){ free (y_BIF[j]);}
  free (y_BIF);

  free(x_Data);
  /*   END : End freeing allocated memory */

  return(0);
}
