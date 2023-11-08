/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code calculate dominant periods and coherence numbers for a number 
   of human-mosquito models of malaria transmission.

   Compilation:
   
   . ~$ make TYPE_of_INDEX=_PR_19p

   Execution:

   . ~$ ./NO_CASES-LXVnW-ODE_RESTRICTED_JACOBIAN -H7 0.00001 -L2 4.0E4 -C3 0.2 -M1 0.8 -M2 0.2 -M3 0.06 -H2 4.5E-5 -H3 3.0E-3 -H4 9.0E-3 -H6 0.05 -H5 5 -P0 10 -P1 0.05 -S0 19 -n 1 -v0 19 -G0 1 -G1 1
*/

int main(int argc, char **argv)
{
  int i;
  Parameter_Space Space;
  Parameter_Table Table;
  
  P_ARG = &Table;

#include "default.c"    
  /* Extra default values */
  int No_of_POINTS_1    = 100;
  int Input_Parameter_1 = 12; /* (a, 12)  */
  int No_of_POINTS_2    = 100;
  int Input_Parameter_2 = 25;  /* (K_0, 25) (H_Gamma, 6) (H_nu, 11) (H_Recov_0, 4)*/
  
  //int Input_Parameter_2 = 28; /* K_p */
  int Output_Variable   = 3;  /* Fraction of Infectious Humans */
    
  I_Time                =  No_of_POINTS_1;

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  P_A_R_A_M_E_T_E_R___S_P_A_C_E___A_L_L_O_C( &Space, &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___U_P_L_O_A_D( &Space, &Table, A_n, A_d);
  printf(" Parameter_Space structure has been correctly allocated and initiated\n");

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

#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, "?" );
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif

  /* BEGIN : Evaluation of the largest (xmax) and the tiniest (xmin) 
     numbers my machine can handle 
  */
  float xmin, xmax;
  Calculation_of_Local_Machine_MAX_min_allowed_float_numbers (&xmin, &xmax);
  
  printf("My largest useable value without causing overflow is %f\n", xmax);
  printf("My tiniest useable value without causing overflow is %f\n", xmin);
  Table.nr___x_min = xmin;
  Table.nr___x_MAX = xmax;
  Press_Key();
  /*   END : Evaluation of xmax and ymin number causing overflow */

  double * W_GRID = (double *)malloc( No_of_POINTS_1 * No_of_POINTS_2 * sizeof(double) );
  int Status =  G_E_N_E_R_I_C___F_U_N_C_T_I_O_N___P_A_R_A_M_E_T_E_R___S_C_A_N( &Table, 
									       No_of_POINTS_1, Input_Parameter_1,
									       No_of_POINTS_2, Input_Parameter_2,
									       DOMINANT_PERIOD,
									       W_GRID,
									       "Dominant_Period.dat" );
#if defined CPGPLOT_REPRESENTATION
/* BEGIN : 2D GRID cpgplot representation */
  /*********************************************************************/
  Table.CPG->X_label   = Table.Name_Parameters[Input_Parameter_1]; 
  Table.CPG->Y_label   = Table.Name_Parameters[Input_Parameter_2]; 
  /*********************************************************************/
  Boundary(Input_Parameter_1, &Value_0, &Value_1);
  Table.CPG->ORIGIN_X    = Value_0;
  Table.CPG->X_Dimension = (Value_1 - Value_0);
  
  Boundary(Input_Parameter_2, &Value_0, &Value_1);
  Table.CPG->ORIGIN_Y = Value_0;
  Table.CPG->Y_Dimension = (Value_1 - Value_0);
  
  Table.CPG->x_GRID  = No_of_POINTS_1; 
  Table.CPG->y_GRID  = No_of_POINTS_2;
  
  // int Output_Variable  = Table.IO_VARIABLE_LIST[0];
  // Table.CPG->W_label   = Table.Variable_Name[Output_Variable];
  
  int FIRST_PLOT = 0;
  double i_PLOT  = 0.0;
  
  // C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S ( ... );
  // C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___C_O_N_T_O_U_R( ... ); 
  
  double W_GRID_MAX = 0.0;
  for(i=0; i<(No_of_POINTS_1 * No_of_POINTS_2); i++){
    W_GRID_MAX = MAX ( W_GRID[i], W_GRID_MAX );
  }  
  for(i=0; i<(No_of_POINTS_1 * No_of_POINTS_2); i++){
    if(W_GRID[i] > 20.0) W_GRID[i] = 20.0;
  }  
  
  C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S( Table.CPG,
							W_GRID, 
							FIRST_PLOT,
							Table.CPG->CPG_SCALE_W, 
							  Table.CPG->CPG_RANGE_W_0,
							Table.CPG->CPG_RANGE_W_1,
							i_PLOT );
#endif  
  
  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___F_R_E_E( &Space );

  free (W_GRID);
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif  

  printf("\nEnd of progam\n");
  return (0);
}





