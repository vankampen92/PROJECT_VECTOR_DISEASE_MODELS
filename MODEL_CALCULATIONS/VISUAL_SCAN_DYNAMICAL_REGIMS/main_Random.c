/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2017 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

/* This code produces 2D plots through scanning a parameter subspace defined by 
   two labels corresponding two model parameters (Input_Parameter_1 and Input_Parameter_2) 
   in order to determine different dynamic regimes of the model under study. 

   Compilation:
   (see makefile)
   ~$: make TYPE_of_MAIN=_Random
   
   Exectution example:
   1. ~$: ./SUPERINFECTION_CASES_1-LXVnW_PR_2p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05  -S0 2 -n 1 -v0 3 -G0 1 -G1 1 -G13 1 -G14 "Parameter\(2748)space\(2748)exploration:\(2748)dynamical\(2748)regims"

                                               -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 

   (-S0 2 is the dimension of the vector containing the indeces of the parameters to explore. Usually the exe file subfix '_PR_Np' indicates that the index vector is N-Dim, this is, 
   a N-Dim subparameter space will be explrored. In this example, N =2) 
    
   2. ~$: ./SUPERINFECTION_CASES_1-LXVnW_PR_2p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05  -S0 2 -n 1 -v0 3 -G0 1 -G1 1 -G13 1 -G14 "Parameter\(2748)space\(2748)exploration:\(2748)dynamical\(2748)regims"

   3. ~$: ./SUPERINFECTION_CASES_1-LXVnW_PR_19p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4   -P0 1 -P1 0.05   -S0 19 -n 2 -v0 3 -G0 1 -G1 2 -G13 1 -G14 "\(2748)"
*/

gsl_rng * r; /* Global generator defined in main.c */

int main(int argc, char **argv)
{
  int i;
  Parameter_Space Space;
  Parameter_Table Table;
  P_ARG = &Table;

  int Input_Parameter_1, Input_Parameter_2; 
  int No_of_POINTS_1    = 400; 
  int No_of_POINTS_2    = 400;

  /* A No_of_POINTS_1 x No_of_POINTS_2 rectangular grid will be 
     used to dicretize the parameter subspace */
 
#include "default.c"    
  /* Extra default values */
  I_Time                =  No_of_POINTS_1;

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  P_A_R_A_M_E_T_E_R___S_P_A_C_E___A_L_L_O_C( &Space, &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___U_P_L_O_A_D( &Space, &Table, A_n, A_d);
  printf(" Parameter_Space structure has been correctly allocated and initiated\n");

  Input_Parameter_1 = Table.S->I[0]; // i.e, Biting rate 
  Input_Parameter_2 = Table.S->I[1]; // i.e, Carrying capacity, r_0  

#include <gsl_random_number_Setup.c>
#if defined VERBOSE
  /* BEGIN: Checking Random Number Generator Setup */
  for(i=0; i<10; i++){
    printf( "f(%d)=%g, ", i, gsl_rng_uniform(r) );
    printf( "f_GAUS(%d)=%g\n", i, gsl_ran_gaussian(r, 1.0) );
  }
  printf("\n"); // Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif

#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, "?" );
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif
  /* 
     BEGIN : Evaluation of the largest (xmax) and the tiniest (xmin) 
     numbers my machine can handle 
  */
  float xmin, xmax;
  Calculation_of_Local_Machine_MAX_min_allowed_float_numbers (&xmin, &xmax);
  
  printf("My largest useable float value without causing overflow is %f\n", xmax);
  printf("My tiniest useable float value without causing overflow is %f\n", xmin);
  Table.nr___x_min = xmin;
  Table.nr___x_MAX = xmax;
  // printf(" Press any key to continue...\n"); getchar();
  /*   END : Evaluation of xmax and ymin number causing overflow */
 
  int Status;   
  double Immigration_Default = Table.Imm;
    // Table.Imm          = 0.0;
    /* Note: It is important to calculate dynamic regims with External Force of Infection
       (Imm) equal to zero. This enables the code to capture the disease-free region (with
       a viable mosquito population) in the parameter space.
    */
  double * W_GRID = (double *)calloc( No_of_POINTS_1 * No_of_POINTS_2, sizeof(double) );
  Status =  G_E_N_E_R_I_C___F_U_N_C_T_I_O_N___P_A_R_A_M_E_T_E_R___S_C_A_N( &Table, 
									   No_of_POINTS_1, Input_Parameter_1, 
									   No_of_POINTS_2, Input_Parameter_2,
									   DYNAMIC_REGIM, 
									   W_GRID, 
									   "Dynamic_Regims.dat" ); 
    /* The scan function DYNAMIC_REGIM returns a double value between 0 and 4 (stored in array W_GRID). 
       Possible return values: 
       0 ---> Disease Free Equilibrium (Mosquito Free Equilibrium)
       1 ---> Disease Free Equilibrium (with viable Mosquito population) R_0 < 1
       2 ---> Disease Endemic Equilibrium (node stable)
       3 ---> Disease Endemic Equilibrium (damped oscillations) 
       4 ---> Unstable local equilibrium 
       If there is coexistence, unless stated, we characterize the properties of the lower
       equilibrium
    */
    /* Note: The intermediate stationary point that should be calculated in 
       case of coexistence of stationary points fails to be calculated
       when the external force of infection is equated to zero (Imm = 0.0)
       This problem has been corrected by compiling and calling fixed_Points_Intermediate.c 
       instead of using fixed_Points_ALL.c
    */
  printf("\n Coexistence of Stationary States Calculation...\n");
  values_HumanMos(&Table);  /* Resetting default parameter values */
  Table.Imm          = Immigration_Default;
  int Total_POINTS;
  double * X = (double *)calloc( 40000, sizeof(double) );
  double * Y = (double *)calloc( 40000, sizeof(double) );
  
  Status =  G_E_N_E_R_I_C___R_A_N_D_O_M___P_A_R_A_M_E_T_E_R___S_P_A_C_E( &Table, 
									 40000,
									 C_O_E_X_I_S_T_E_N_C_E___D_Y_N_A_M_I_C___E_Q_U_I_L_I_B_R_I_A,
									 CONDITION_on_COEXISTENCE, 
									 X, Y );
  Total_POINTS = Status; 
  Saving_to_File_double( "Stable_Coexistence_Shaded_Area_", X, Y, Total_POINTS, 0 );   
  
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
  
  int FIRST_PLOT = 0;
  double i_PLOT  = 0.0;
  int no_of_COLORS = 5;
  double * COLOR_STATES = (double *)calloc( no_of_COLORS, sizeof(double) );
  COLOR_STATES[0] = 1.0; 
  COLOR_STATES[1] = 3.0; COLOR_STATES[2] = 2.0; COLOR_STATES[3] = 8.0; COLOR_STATES[4] = 5.0;
  /* Dynamic Regims: 
     Color_Index 1 will be for the first dynamic regim (Mosquito free Equilibrium), color 2 for the
     2nd and so on, as follows:
     From dynamic regim state 0 to 4 ---> Dynamic Regim
     --------------------------------------------------
     0 ---> Disease Free Equilibriu (non-viable mosquito population)   
     1 ---> Disease Free Equilibrium (viable mosquito population with R_0 < 1, node stable)
     2 ---> Disease Endemic Equilibrium (viable mosquito population with R_0 > 1, node stable) 
     3 ---> Disease Endemic Equilibrium (viable mosquito population iwth R_0 > 1, damped oscillations)
     4 ---> Unstable local equilibrium.
     
     If there is coexistence, unless stated, we characterize the properties of the lower
     equilibrium
  */
  C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___R_E_C_T_A_N_G_L_E_S( Table.CPG,
								W_GRID, 
								FIRST_PLOT,
								no_of_COLORS, 
								COLOR_STATES,
								i_PLOT );
  FIRST_PLOT = 1;
  C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_U_B_R_E_G_I_O_N ( Table.CPG, 
							       FIRST_PLOT, 
							       X, Y, Total_POINTS );
  free (COLOR_STATES);
 
  color_Index =    1;   type_of_Line =   2;   type_of_Width =  6;  type_of_Symbol = 4;

  i = 0; 
  if ( i == 0 )
    C_P_G___P_L_O_T_T_I_N_G___E_X_T_R_A___L_I_N_E (0.15, 6.3E-3, 0.45, 6.3E-3, 
						   color_Index,
						   type_of_Line,
						   type_of_Width,
						   type_of_Symbol);
  else{ 
    C_P_G___P_L_O_T_T_I_N_G___E_X_T_R_A___L_I_N_E (0.15, 3.0E4, 0.45, 3.0E4, 
						   color_Index,
						   type_of_Line,
						   type_of_Width,
						   type_of_Symbol);
    C_P_G___P_L_O_T_T_I_N_G___E_X_T_R_A___L_I_N_E (0.2, 2.0E4, 0.2, 8.0E4, 
						   color_Index,
						   type_of_Line,
						   type_of_Width,
						   type_of_Symbol);
  }
#endif  
  
  free(X); free(Y); free (W_GRID); 
  
  /* BEGIN : Writing Latex Table */
  values_HumanMos(&Table);  /* Resetting default parameter values */
  write_Parameter_Table___RANGES___VALUES___LATEX ( "Latex_Parameter_Table.tex", "Definition Parameter Space", 
						    &Table, Space.P_MAX->data, Space.P_min->data, Space.nPar );  
  /*   END : End writing         */	
  // printf(" Press any key to continue...\n"); getchar();
  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___F_R_E_E( &Space );
  
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif  
  
  printf("\nEnd of progam\n");
  return (0);
}





