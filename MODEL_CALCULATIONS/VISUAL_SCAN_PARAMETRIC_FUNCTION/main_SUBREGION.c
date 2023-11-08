/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code scans a parametric function for a number of human-mosquito models 
   of malaria transmission. Parameter ranges are defined in boundary_*.c file. 
   Parameters to scan are defined in the index_Definition_*.c files

   The parametric function is generically defined by the funciton:
   
   void definition_Scan_Function( Parameter_Table * )

   from definition_OutPut_Variables.c file. 

   The input arguments in the example below:

   -n 1 -v0 19

   tell there will be only one output variable (-n 1) and the function to 
   scan is the one defined by key 19 in the function (-v0 19): 
   
   double definition_OutPut_Variables(int, double *, const double, Parameter_Table *)

   from definition_OutPut_Variables.c file. This key corresponds to R_0. 
   
   This function also plots the region of the explored parameter space where certain 
   condition on the function scanned (in this case R_0) is met, for instance, 
   1 - eps < R_0 < 1 + eps (see R_0___Subdominant_Eigenvalue.c)
   
   Compilation:
   
   . ~$ make TYPE_of_INDEX=_R0_2p M_MODEL=LXVnW H_MODEL=CASES_1 TYPE_of_MAIN=_SUBREGION JACOBIAN=ODE

   . ~$ make TYPE_of_INDEX=_Hu_4p M_MODEL=LXVnW H_MODEL=CASES_1 TYPE_of_MAIN=_SUBREGION JACOBIAN=ODE
   
   Execution: 
                                                      
   . ~$ ./CASES_1-LXVnW_R0_2p -H7 0.0 -L2 4.0E4 -M1 0.8 -M2 0.2 -M3 0.06 -H3 3.0E-3 -H4 9.0E-3 -H6 0.05 -H5 5 -C3 0.2 -P0 10 -P1 0.083 -S0 2 -n 1 -v0 19 -G0 1 -G1 1

   . $ ./CASES_1-LXVnW_Hu_4p  -H7 0.0 -L2 3.0E4 -M2 0.1 -M3 0.06 -H4 2.6E-3 -H6 0.05 -H5 5 -C3 0.1 -P0 5 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 1 -G1 1                     
*/

int main(int argc, char **argv)
{
  Parameter_Space Space;
  Parameter_Table Table;
  //Time_Control Time;
  
  P_ARG = &Table;

#include "default.c"    
  /* Extra default values */
  int No_of_POINTS_1    = 500;
  int Input_Parameter_1 = 12; /* 12 ---> Biting rate */ 
  int No_of_POINTS_2    = 500;
  int Input_Parameter_2 = 25; /* 25 ---> Carrying capacity         */
                              /* 22 ---> L_Delta (Lavae Mortality) */
 	                      /* 20 ---> L_Devel                   */ 
                              /* 15 ---> M_Delta (Adult Mortality) */
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
  int i;
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

  double Epsilon = 1.0E-08;
  double * W_GRID = (double *)malloc( No_of_POINTS_1 * No_of_POINTS_2 * sizeof(double) );
  int Status =  G_E_N_E_R_I_C___F_U_N_C_T_I_O_N___P_A_R_A_M_E_T_E_R___S_C_A_N( &Table, 
									       No_of_POINTS_1, Input_Parameter_1,
									       No_of_POINTS_2, Input_Parameter_2,
									       //definition_Scan_Function,
									       R_0___Subdominant_Eigenvalue,
 									       W_GRID,
									       "R_0.dat" );
  // printf(" H_Eta = %g\n", Table.H_Eta); 
  // Press_Key();
  values_HumanMos(&Table);  /* Resetting default parameter values */
  int Total_POINTS;
  double * X = (double *)calloc( No_of_POINTS_1 * No_of_POINTS_2, sizeof(double) );
  double * Y = (double *)calloc( No_of_POINTS_1 * No_of_POINTS_2, sizeof(double) );
  Status =  G_E_N_E_R_I_C___S_U_B_R_E_G_I_O_N___P_A_R_A_M_E_T_E_R___S_P_A_C_E( &Table, 
									       No_of_POINTS_1, Input_Parameter_1,
									       No_of_POINTS_2, Input_Parameter_2,
									       //definition_Scan_Function,
									       R_0___Subdominant_Eigenvalue,
									       CONDITION_on_R_0, 
									       X, Y, 
									       &Total_POINTS );

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

    int Output_Variable  = Table.IO_VARIABLE_LIST[0];
    Table.CPG->W_label   = Table.Variable_Name[Output_Variable];

    int FIRST_PLOT = 0;
    double i_PLOT  = 0.0;
    
    // C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S ( ... );
    // C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___C_O_N_T_O_U_R( ... ); 
    
    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S( Table.CPG,
							  W_GRID, 
							  FIRST_PLOT,
							  Table.CPG->CPG_SCALE_W, 
							  Table.CPG->CPG_RANGE_W_0,
							  Table.CPG->CPG_RANGE_W_1,
							  i_PLOT );
    FIRST_PLOT = 1;
    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_U_B_R_E_G_I_O_N ( Table.CPG, 
								 FIRST_PLOT, 
								 X, Y, Total_POINTS );
#endif  	
  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
  free(X); free(Y);  
  // free (Tr);
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





