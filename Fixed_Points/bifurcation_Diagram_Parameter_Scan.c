#include <MODEL.h>

int B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M___P_A_R_A_M_E_T_E_R___S_C_A_N( Parameter_Table * P,
									 int No_of_POINTS_1,
									 int Input_Parameter_1,
									 int No_of_POINTS_2,
									 int Input_Parameter_2,
									 int Output_Variable,
									 double EPSILON )
{
  /* This function calculates a 3DIM bifurcation diagram for Output Variable.
     This is done by using as a 2DIM scan of the parameter space defined
     by Input_Parameter_1 and Input_Parameter_2.

     Input parameters are labeled according to the input (model) parameters labels
     as it appears in all the assing_[].c functions.

     The output of the program generates 3 files:

     bifurcation_Diagram_LOWER_[Output_Variable].dat,
     bifurcation_Diagram_INTER_[Output_Variable].dat, and
     bifurcation_Diagram_UPPER_[Output_Variable].dat, with

     (x, y, z_LOWER), (x, y, z_INTER), and (x, y, z_UPPER), respectively.

     The key input parameter here is:

     . Output_Variable

     which means that only a single bifurcation diagram is calculated, plotted, and saved
     for that output variable.

     The output of this function also generates 3D representation of the bifurcation
     through the function:

     C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S( P->CPG, ... );
     (see line 138)

     This function save the 3 column files:

	bifurcation_Diagram_LOWER_SHEET_[n].dat
	bifurcation_Diagram_INTER_SHEET_[n].dat
	bifurcation_Diagram_UPPER_SHEET_[n].dat

      where 'n' again represents the index of the output variable (n = Output_Variable) and
      where the three different surfaces (corresponding to the LOWER, INTER, and UPPER
      branches of the stationary solution) are saved in this format

				x   y   z = Value of Output_Variable at (x, y)
                               ... ... ...

      These last three files contain only the points where each of the three different
      sheets (lower, intermediate, and upper) are defined over the (x,y)-plane.

      In addition, this function also saves bifurcation curves separtately in the files: 
      
      bifuCURVES_Lower_[n].dat
      bifuCURVES_Inter_[n].dat
      bifuCURVES_Upper_[n].dat

      where [n] stands for different slices, from n=0 to n=No_of_POINTS_2-1, along one 
      dimension of the parameter space defined by Input_Parameter_2. If No_of_POINTS_2
      is too high you will get as many files!!! 
   */
  double z_LOWER, z_INTER, z_UPPER;
  double Value, Value_0, Value_1;
  int i,j, k, n;

  int N_Lower, N_Upper, N_Inter;
  double * x_Lower;
  double * x_Inter;
  double * x_Upper;
  double * y_Lower;
  double * y_Inter;
  double * y_Upper;
  double * y_k;
  /*         bifurcation_Diagram_LOWER_SHEET_n.dat */
  /*         bifurcation_Diagram_INTER_SHEET_n.dat */
  /*         bifurcation_Diagram_LOWER_SHEET_n.dat */
  char * File_Name = (char *)malloc( 100 * sizeof(char) );
  File_Name[0] = '\0';
  fitxer (File_Name, "bifurcation_Diagram_LOWER_SHEET_", Output_Variable, ".dat");
  FILE * fB_0 = fopen ( File_Name, "a" );

  File_Name[0] = '\0';
  fitxer (File_Name, "bifurcation_Diagram_INTER_SHEET_", Output_Variable, ".dat");
  FILE * fB_1 = fopen ( File_Name, "a" );

  File_Name[0] = '\0';
  fitxer (File_Name, "bifurcation_Diagram_UPPER_SHEET_", Output_Variable, ".dat");
  FILE * fB_2 = fopen ( File_Name, "a" );

  /* BEGIN : Allocating memory for saving data to plot a bifurcation  * * * * * * */
  /*         diagram for each variable  * * * * * * * * * * * * * * * * * * * * * */
  double      *** z_SOL  = (double ***)malloc( No_of_POINTS_2 * sizeof(double **) );
  for( i = 0; i < No_of_POINTS_2; i++){

    z_SOL[i] = (double **)malloc( No_of_POINTS_1 * sizeof(double *) );

    for( j = 0; j < No_of_POINTS_1; j++) {
      z_SOL[i][j] = (double *)malloc( 3 * sizeof(double) );
    }
  }

  double       ** z_BIF  = (double  **)malloc( 3 * sizeof(double *) );
  for( j = 0; j < 3; j++) {
      z_BIF[j] = (double *)malloc( No_of_POINTS_1 * sizeof(double) );
  }

  double       ** z_BIF_GRID  = (double  **)malloc( 3 * sizeof(double *) );
  for( j = 0; j < 3; j++) {
      z_BIF_GRID[j] = (double *)malloc( No_of_POINTS_1 * No_of_POINTS_2 * sizeof(double) );
  }

  double * x_Data  = (double *)malloc(No_of_POINTS_1 * sizeof(double) );
  double * y_Data  = (double *)malloc(No_of_POINTS_2 * sizeof(double) );
  /*   END : Allocating memory for saving dynamical data * * * * * */
  
  n = 0;
  for( k = 0; k < No_of_POINTS_2; k++ ) {

    Boundary(Input_Parameter_2, &Value_0, &Value_1);

    Value = Value_0 + k * (Value_1 - Value_0)/(double)(No_of_POINTS_2 - 1);
    y_Data[k]= Value;

    AssignVectorEntry_to_Structure(P, Input_Parameter_2, Value);

    Boundary(Input_Parameter_1, &Value_0, &Value_1);

      for( j = 0; j < No_of_POINTS_1; j++ ){

	Value = Value_0 + j * (Value_1 - Value_0)/(double)(No_of_POINTS_1 - 1);
	x_Data[j] = Value;

	AssignVectorEntry_to_Structure(P, Input_Parameter_1, Value);


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

	B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M( P, &z_LOWER, &z_INTER, &z_UPPER, Output_Variable,
					       EPSILON );

	z_SOL[k][j][0] = z_LOWER; z_SOL[k][j][1] = z_INTER; z_SOL[k][j][2] = z_UPPER;

	z_BIF[0][j]    = z_LOWER;    z_BIF[1][j] = z_INTER;    z_BIF[2][j] = z_UPPER;

	printf(" z_LOWER = %g\tz_INTER = %g\tz_UPPER = %g\n", z_LOWER, z_INTER, z_UPPER);

	z_BIF_GRID[0][n]  = z_LOWER;
	z_BIF_GRID[1][n]  = z_INTER;
	z_BIF_GRID[2][n]  = z_UPPER;
	n++;
      }

#if defined CPGPLOT_REPRESENTATION
      /* 2-DIM bifurcation diagram */
      C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_E_P_R_E_C_A_T_E_D ( P, No_of_POINTS_1,
									      x_Data, z_BIF,
									      Output_Variable,
									      Input_Parameter_1,
									      Input_Parameter_2 );
      // Press_Key();
#endif

      x_Lower  = (double *)calloc(No_of_POINTS_1, sizeof(double) );
      x_Inter  = (double *)calloc(No_of_POINTS_1, sizeof(double) );
      x_Upper  = (double *)calloc(No_of_POINTS_1, sizeof(double) );

      y_Lower  = (double *)calloc(No_of_POINTS_1, sizeof(double) );
      y_Inter  = (double *)calloc(No_of_POINTS_1, sizeof(double) );
      y_Upper  = (double *)calloc(No_of_POINTS_1, sizeof(double) );

      y_k      = (double *)calloc(No_of_POINTS_1, sizeof(double) );
      
      Separating_Bifurcation_Branches ( EPSILON,
					x_Data, z_BIF[0], z_BIF[1], z_BIF[2], No_of_POINTS_1,
					x_Lower, y_Lower, &N_Lower,
					x_Inter, y_Inter, &N_Inter,
					x_Upper, y_Upper, &N_Upper );

      for(i=0; i<N_Lower; i++) y_k[i] = y_Data[k];  
      Saving_to_File_double_3Col("bifuCURVES_Lower_", x_Lower, y_k, y_Lower, N_Lower, k);

      for(i=0; i<N_Inter; i++) y_k[i] = y_Data[k];  
      Saving_to_File_double_3Col("bifuCURVES_Inter_", x_Inter, y_k, y_Inter, N_Inter, k);

      for(i=0; i<N_Upper; i++) y_k[i] = y_Data[k];  
      Saving_to_File_double_3Col("bifuCURVES_Upper_", x_Upper, y_k, y_Upper, N_Upper, k);

#if defined CPGPLOT_REPRESENTATION
      /* 2-DIM bifurcation diagram */
      C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M ( P,
									x_Lower, y_Lower, N_Lower,
									x_Inter, y_Inter, N_Inter,
									x_Upper, y_Upper, N_Upper,
									Output_Variable,
									Input_Parameter_1,
									Input_Parameter_2 );
      // Press_Key();
#endif
      for( j = 0; j < N_Lower; j++ )
	fprintf(fB_0, "%g\t%g\t%g\n", x_Lower[j], y_Data[k], y_Lower[j]);

      for( j = 0; j < N_Inter; j++ )
	fprintf(fB_1, "%g\t%g\t%g\n", x_Inter[j], y_Data[k], y_Inter[j]);

      for( j = 0; j < N_Upper; j++ )
	fprintf(fB_2, "%g\t%g\t%g\n", x_Upper[j], y_Data[k], y_Upper[j] );

      free(x_Lower); free(x_Inter); free(x_Upper);
      free(y_Lower); free(y_Inter); free(y_Upper);  free(y_k); 
      // Press_Key();
  }
  fclose(fB_0); fclose(fB_1); fclose(fB_2);

#if defined CPGPLOT_REPRESENTATION
  /* BEGIN : 2D GRID cpgplot representation */
  /*********************************************************************/
  /* Annotation of the plot: x label, y label, z label and title */
  P->CPG->X_label   = P->Name_Parameters[Input_Parameter_1];
  P->CPG->Y_label   = P->Name_Parameters[Input_Parameter_2];
  P->CPG->Title     = P->Variable_Name[Output_Variable];
  P->CPG->W_label[0]= '\0';
  char * p_Name     = strcat( P->CPG->W_label, P->Variable_Name[Output_Variable]);
  /*********************************************************************/
  int FIRST_PLOT = 0;
  for( j = 0; j < 3; j++){
    Boundary(Input_Parameter_1, &Value_0, &Value_1);
    P->CPG->ORIGIN_X    = Value_0;
    P->CPG->X_Dimension = (Value_1 - Value_0);

    Boundary(Input_Parameter_2, &Value_0, &Value_1);
    P->CPG->ORIGIN_Y = Value_0;
    P->CPG->Y_Dimension = (Value_1 - Value_0);

    P->CPG->x_GRID  = No_of_POINTS_1;
    P->CPG->y_GRID  = No_of_POINTS_2;

    P->CPG->W_label   = P->Variable_Name[Output_Variable];

    double i_PLOT  = 0.0;

    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S( P->CPG,
							    z_BIF_GRID[j],
							    FIRST_PLOT,
							    P->CPG->CPG_SCALE_W,
							    P->CPG->CPG_RANGE_W_0,
							    P->CPG->CPG_RANGE_W_1,
							    i_PLOT );
    FIRST_PLOT = 1;
    printf("Press any key..."); getchar();
  }
  /*   END :                                */
#endif

  /* BEGIN : Saving 3 columns Files:  */
  /*         bifurcation_Diagram_LOWER_n.dat */
  /*         bifurcation_Diagram_INTER_n.dat */
  /*         bifurcation_Diagram_LOWER_n.dat */
  File_Name = (char *)malloc( 100 * sizeof(char) );
  File_Name[0] = '\0';
  fitxer (File_Name, "bifurcation_Diagram_LOWER_", Output_Variable, ".dat");
  FILE * fp_0 = fopen ( File_Name, "w" );

  File_Name[0] = '\0';
  fitxer (File_Name, "bifurcation_Diagram_INTER_", Output_Variable, ".dat");
  FILE * fp_1 = fopen ( File_Name, "w" );

  File_Name[0] = '\0';
  fitxer (File_Name, "bifurcation_Diagram_UPPER_", Output_Variable, ".dat");
  FILE * fp_2 = fopen ( File_Name, "w" );

  for( k = 0; k < No_of_POINTS_2; k++ ) {
      for( j = 0; j < No_of_POINTS_1; j++ ){
	fprintf(fp_0, "%g\t%g\t%g\n", x_Data[j], y_Data[k], z_SOL[k][j][0]);
	fprintf(fp_1, "%g\t%g\t%g\n", x_Data[j], y_Data[k], z_SOL[k][j][1]);
	fprintf(fp_2, "%g\t%g\t%g\n", x_Data[j], y_Data[k], z_SOL[k][j][2]);
      }
  }
  fclose(fp_0); fclose(fp_1); fclose(fp_2);

  /* BEGIN : Freeing previous allocated memory */
  for(i = 0; i < No_of_POINTS_2; i++) {
    for( j = 0; j < No_of_POINTS_1; j++){ free (z_SOL[i][j]); }
    free (z_SOL[i]);
  }
  free(z_SOL);

  for( j = 0; j < 3; j++){ free (z_BIF[j]); free (z_BIF_GRID[j]); }
  free (z_BIF);
  free (z_BIF_GRID);

  free(x_Data); free(y_Data);
  /*   END : End freeing allocated memory */

  return(0);
}
