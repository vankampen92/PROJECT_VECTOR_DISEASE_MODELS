/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

/* This code calculates basins of attraction in case of bi-stability. 
   This is done only for the case where we have only two equations 
   because this allows to visualize the phase space in a 2D plot. 

   ## (SOLUTION SI-XW)
   Compilation: 

   . ~$ make BASIN=RANDOM_SCAN TYPE_of_MAIN=_FULL DRAW=DRAW_LINES_PHASE_DIAGRAM JACOBIAN=ODE_RESTRICTED_JACOBIAN H_MODEL=SI M_MODEL=XW

   Execution:
  
   . ~$ rm Parameter_Trend.dat
   . ~$ ./ODE_RESTRICTED_JACOBIAN_SI-XW_RANDOM_INITIAL_CONDITION_RANDOM_SCAN_FULL -R0 $2 -S0 19 -n 2 -v0 3 -v1 5 -v2 30 -G0 1 -G1 1 -G5 1 -G6 0.0 -G7 1.0 -t0 4 -t1 0.0 -t2 5000.0  -G8 1 -G9 8 -G10 1 -G11 7 -G12 1 -H1 1.5E-5 -H2 1.5E-5 -H3 6.7E-4 -H4 0.01 -H5 0 -H7 0.00005 -M0 0.33 -M1 0.1 -M2 0.05 -M3 0.05 -M9 0.6 -P0 0   -TP 12 -TY -1
*/

gsl_rng * r; /* Global generator defined in main.c */

int main(int argc, char **argv)
{
  double x, y;
  int i,k,j, n;
  Parameter_Space Space;
  Parameter_Table Table;
  Time_Control Time;
#if defined APPLYING_TREND
  Trend_Control * Tr;
#endif
  P_ARG = &Table;

#include "default.c"    

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

#if defined CASES_33
  K_Mean_Value         = K_p;
#else
  K_Mean_Value         = K_0;
#endif

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  P_A_R_A_M_E_T_E_R___S_P_A_C_E___A_L_L_O_C( &Space, &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___U_P_L_O_A_D( &Space, &Table, A_n, A_d);
  printf(" Parameter_Space structure has been correctly allocated and initiated\n");
    
  /* It the dynamics is temperature/rainful driven, the corresponding
     data structure should be also allocated and initiated here 
     (at least, after initiating Parameter_Table structure)
  */
  /* */
  printf(" Time_Control structure will be allocated: \n");
  printf(" %d output variables of length %d points will be allocated\n", SUB_OUTPUT_VARIABLES, I_Time);
  T_I_M_E___C_O_N_T_R_O_L___A_L_L_O_C( &Time, &Table, I_Time);
  T_I_M_E___C_O_N_T_R_O_L___U_P_L_O_A_D( &Time, &Table, I_Time);
  printf(" Time_Control structure has been correctly allocated and initiated\n");

#if defined APPLYING_TREND
  printf(" Trend_Control structure will be allocated: \n");
  Tr = (Trend_Control *)malloc( 1 * sizeof(Trend_Control) ); 
  T_R_E_N_D___C_O_N_T_R_O_L___U_P_L_O_A_D( Tr, &Table);
  int Input_Parameter = Tr->Tr_Input_Parameter; 
  //int Input_Parameter = 12;
  //S_E_T_U_P___T_R_E_N_D___T_R_I_A_N_G_L_E (Tr, &Time, Input_Parameter ); 
  S_E_T_U_P___T_R_E_N_D___F_R_E_E___T_R_I_A_N_G_L_E (Tr, &Time, Input_Parameter ); 
  printf(" Trend_Control structure has been correctly allocated and initiated\n");
#endif

#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, "?" );
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif

#include <gsl_random_number_Setup.c>
#if defined VERBOSE
  /* BEGIN: Checking Random Number Generator Setup */
  for(i=0; i<10; i++){
    printf( "f(%d)=%g, ", i, gsl_rng_uniform(r) );
    printf( "f_GAUS(%d)=%g\n", i, gsl_ran_gaussian(r, 1.0) );
  }
  printf("\n");Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif

  /* BEGIN : Writing Latex Table */
  write_Parameter_Table___RANGES___VALUES___LATEX ( "Latex_Parameter_Table.tex", 
						    "TYPE_of_BOUNDARY", 
						    &Table, 
						    Space.P_MAX->data, 
						    Space.P_min->data, 
						    Space.nPar );  
  /*   END : End writing         */
  Press_Key();
  
  int N_0, N_1;
  int Type_of_Calculation; 
  int No_of_POINTS_0, No_of_POINTS_1;
  double * W_GRID; 
  double *  X_0; double *  Y_0;  double *  X_1; double *  Y_1;

  Type_of_Calculation = 0;
  No_of_POINTS_0 = 300;  No_of_POINTS_1 = 300;
  int No_of_POINTS_GRID = No_of_POINTS_0 * No_of_POINTS_1 ;
  W_GRID = (double *)calloc( No_of_POINTS_GRID, sizeof(double) );

  X_0 = (double *)calloc( No_of_POINTS_GRID, sizeof(double) ); 
  Y_0 = (double *)calloc( No_of_POINTS_GRID, sizeof(double) );  
  X_1 = (double *)calloc( No_of_POINTS_GRID, sizeof(double) ); 
  Y_1 = (double *)calloc( No_of_POINTS_GRID, sizeof(double) ); 

  int Status = B_A_S_I_N___o_f___A_T_T_R_A_C_T_I_O_N ( Type_of_Calculation, 
						       &Table, 
						       No_of_POINTS_0, X_0, Y_0,
						       No_of_POINTS_1, X_1, Y_1,
						       Table.Realizations, W_GRID, 
						       &N_0, &N_1 );
  printf (" %d points have been assigned to a basin of attraction\n", 
	    N_0 + N_1);
  printf (" Lower Basin: N_0 = %d\t Upper Basin: N_1 = %d\n", N_0, N_1 );


  printf (" Total Scanned Points: N = %d\n", No_of_POINTS_GRID);
  if ( No_of_POINTS_GRID > (N_0 + N_1) )  {
    printf(" Some assignations failed\n");
    printf(" Calculations printing out a hyphon (-) do not succeed in assigning\n");
    printf(" the initial point to a basin of attraction!\n");
  }

  /*********************************************************************/
#if defined CPGPLOT_REPRESENTATION
  double w_MAX = Infectious_Mosquito_Steady_State( 1.0, &Table );

  if(Table.CPG->CPG_LABEL_TYPES == 0){
    int k_1 = Table.IO_VARIABLE_LIST[1];
    int k_0 = Table.IO_VARIABLE_LIST[0];

    Table.CPG->X_label   = Table.Variable_Name[k_1]; 
    Table.CPG->Y_label   = Table.Variable_Name[k_0]; 
  }
  
  Table.CPG->x_GRID   = No_of_POINTS_1;  Table.CPG->y_GRID   = No_of_POINTS_0;
  Table.CPG->ORIGIN_X = 0.0;             Table.CPG->ORIGIN_Y = 0.0;
  
  Table.CPG->X_Dimension = w_MAX / (double)Table.POPULATION; 
  Table.CPG->Y_Dimension = 1.0;

  /* Y dimension: Infectious fraction of humans             */
  /* X dimension: Number of infectious mosquitoes per human */  
  int FIRST_PLOT = 0;  
  double i_PLOT  = 0.0;
  int no_of_COLORS = 3;
  double * COLOR_STATES = (double *)calloc( no_of_COLORS, sizeof(double) );
  COLOR_STATES[0] = 3.0; COLOR_STATES[1] = 2.0; COLOR_STATES[2] = 8.0; 
  C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___R_E_C_T_A_N_G_L_E_S( Table.CPG,
								W_GRID, 
								FIRST_PLOT,
								no_of_COLORS, 
								COLOR_STATES,
								i_PLOT );
  /* BEGIN : Writing Files * * * * * * * * * * * * * * * * * * * * * * * * * * */
    n = 0;
    FILE * fp = fopen("Basins_of_Attraction.dat","w"); 
    for( k = 0; k < No_of_POINTS_0; k++ ) {
      y = (double)(k+1)/(double)No_of_POINTS_0;
      for( j = 0; j < No_of_POINTS_1; j++ ){
	x = w_MAX * (double)(j+1)/(double)No_of_POINTS_1 / Table.H; 
	fprintf(fp, "%g\t%g\t%g\n", x, y, W_GRID[n++]);
      }
    }
    fclose(fp);
  /*   END : ------------------------------------------------------------------*/
  free( COLOR_STATES );
  free( X_0 ); free (Y_0);  free( X_1 ); free (Y_1); 
  free( W_GRID);
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES);
  T_I_M_E___C_O_N_T_R_O_L___F_R_E_E( &Time, &Table );
  /*********************************************************************/

  I_Time = 40000;
  Table.CPG = (Parameter_CPGPLOT *)malloc( 1 * sizeof(Parameter_CPGPLOT) );
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___A_L_L_O_C ( Table.CPG, SUB_OUTPUT_VARIABLES, I_Time );
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___U_P_L_O_A_D ( Table.CPG );
  
  T_I_M_E___C_O_N_T_R_O_L___A_L_L_O_C( &Time, &Table,   I_Time);
  T_I_M_E___C_O_N_T_R_O_L___U_P_L_O_A_D( &Time, &Table, I_Time);

  Type_of_Calculation = 2;
  if ( Type_of_Calculation == 1 ) {

    W_GRID = (double *)calloc( Table.Realizations, sizeof(double) );
    
    X_0 = (double *)calloc( Table.Realizations, sizeof(double) ); 
    Y_0 = (double *)calloc( Table.Realizations, sizeof(double) );  
    X_1 = (double *)calloc( Table.Realizations, sizeof(double) ); 
    Y_1 = (double *)calloc( Table.Realizations, sizeof(double) ); 
    
    Status = B_A_S_I_N___o_f___A_T_T_R_A_C_T_I_O_N ( Type_of_Calculation, 
						     &Table, 
						     Table.Realizations, X_0, Y_0,
						     Table.Realizations, X_1, Y_1,
						     Table.Realizations, W_GRID, 
						     &N_0, &N_1 );
  }
  if ( Type_of_Calculation == 2 ) {
    
    No_of_POINTS_0 = 30;  No_of_POINTS_1 = 5;
    int No_of_POINTS_GRID = 2*No_of_POINTS_0 + 2 * No_of_POINTS_1 ;
    W_GRID = (double *)calloc( No_of_POINTS_GRID, sizeof(double) );

    X_0 = (double *)calloc( No_of_POINTS_GRID, sizeof(double) ); 
    Y_0 = (double *)calloc( No_of_POINTS_GRID, sizeof(double) );  
    X_1 = (double *)calloc( No_of_POINTS_GRID, sizeof(double) ); 
    Y_1 = (double *)calloc( No_of_POINTS_GRID, sizeof(double) ); 

    int Status = B_A_S_I_N___o_f___A_T_T_R_A_C_T_I_O_N ( Type_of_Calculation, 
							 &Table, 
							 No_of_POINTS_0, X_0, Y_0,
							 No_of_POINTS_1, X_1, Y_1,
							 Table.Realizations, W_GRID, 
							 &N_0, &N_1 );
    Table.Realizations = No_of_POINTS_GRID;
  }
  
  printf (" Total Scanned Points: N = %d\n", Table.Realizations);
  if ( Table.Realizations > (N_0 + N_1) )  {
    printf(" Some assignations failed\n");
    printf(" Calculations printing out a hyphon (-) do not succeed in assigning\n");
    printf(" the initial point to a basin of attraction!\n");
  }

  /* FIRST_PLOT = 1;                                                               */
  /* Table.CPG->x_GRID   = No_of_POINTS_1;  Table.CPG->y_GRID   = No_of_POINTS_0;  */
  /* Table.CPG->ORIGIN_X = 0.0;             Table.CPG->ORIGIN_Y = 0.0;             */
   
  /* Table.CPG->X_Dimension = w_MAX / (double)Table.POPULATION;                    */
  /* Table.CPG->Y_Dimension = 1.0;                                                 */
   
  /* Table.CPG->type_of_Symbol  = 23;                                              */
  /* Table.CPG->type_of_Width   = 2;                                               */
  /* Table.CPG->color_Index     = 7;  /\* 14: Dark gray *\/                        */
  /* C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_U_B_R_E_G_I_O_N ( Table.CPG,       */
  /* 							          FIRST_PLOT,      */
  /* 							          X_0, Y_0, N_0 ); */
  /* FIRST_PLOT = 1; */
  /* Table.CPG->type_of_Symbol  = 23;                                              */
  /* Table.CPG->type_of_Width   = 2;                                               */
  /* Table.CPG->color_Index = 8;                                                   */
  /* C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_U_B_R_E_G_I_O_N ( Table.CPG,       */
  /* 							          FIRST_PLOT,      */
  /* 							          X_1, Y_1, N_1 ); */
  /* E N D : --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */ 
  
  free( X_0 ); free (Y_0);
  free( X_1 ); free (Y_1); 
  free( W_GRID);
#endif
  /*********************************************************************/

  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif  

  //T_I_M_E___C_O_N_T_R_O_L___F_R_E_E( &Time, &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___F_R_E_E( &Space );

#if defined APPLYING_TREND
  T_R_E_N_D___C_O_N_T_R_O_L___F_R_E_E( Tr );
#endif
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}





