/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

/* This code calculate dominant periods and coherence numbers for a number 
   of human-mosquito models of malaria transmission.

   Compilation:
   
   . ~$ make TYPE_of_INDEX=_PR_19p TYPE_of_MAIN=_DOMINANT_COHERENCE

   Execution:

   . ~$ ./NO_CASES-LXVnW-ODE_RESTRICTED_JACOBIAN -S0 19 -n 4 -G0 2 -G1 2
*/

gsl_rng * r; /* Global generator defined in main.c */

int main(int argc, char **argv)
{
  int i;
  Parameter_Space Space;
  Parameter_Table Table;
  
  P_ARG = &Table;

#include "default.c"    
  
  //int Input_Parameter_2 = 28; /* K_p */
  int Output_Variable   = 3;  /* Fraction of Infectious Humans */
  I_Time                =  500;

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

#if defined EIGENVALUE
	printf(" EIGENVALUE has been defined. The dominant eigenvalue raw value is given instead of\n     \
	one over this value (dominant period, in year units). The coherence number is put artificially\n  \
	to zero\n");
	Press_Key();
#endif

  /* BEGIN: Solution A: Extra default values: Parameters that produce cycles around 6 to 10 years.*/
  /* Solution A ----------------------------------------------------------------------------------*/
  // -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1    -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4   -P0 1 -P1 0.05
  Resetting_Parameter_Combination( &Table, 
                                      1.4E-4, 6.7E-4, 6.3E-3, 1, 0.00001,
                                      0.2, 0.1, 
                                      6.7E-2, 0.5, 3.0E4, 
                                      0.3, 0.5, 0.2, 0.04, 
                                      1, 0.05 );

  /* BEGIN : Writing Latex Table Solution A */
  write_Parameter_Table___RANGES___VALUES___LATEX ( "Latex_Parameter_Table_Solution_A.tex", 
						    "TYPE_of_BOUNDARY", 
						    &Table, Space.P_MAX->data, 
						    Space.P_min->data, Space.nPar );  
  /*   END : End writing         */
  int No_of_POINTS_1    = 500;
  int Input_Parameter_1 = 12;   assert (I_Time == No_of_POINTS_1);   /* (a, 12)  */
  int No_of_POINTS_2    = 500;
  int Input_Parameter_2 = 25;   /* (K_0, 25) (H_Gamma, 6) (H_nu, 11) (H_Recov_0, 4)*/
  Parameter_Scan_2D_GRID_SHADES( &Table, 
				 No_of_POINTS_1, Input_Parameter_1,
				 No_of_POINTS_2, Input_Parameter_2,
				 //DOMINANT_EIGENVALUE,	
				 DOMINANT_PERIOD,	
	 			 "Dominant_Period_Solution_A__K0__Boundary_102.dat" );

  Resetting_Parameter_Combination( &Table, 
                                      1.4E-4, 6.7E-4, 6.3E-3, 1, 0.00001,
                                      0.2, 0.1, 
                                      6.7E-2, 0.5, 3.0E4, 
                                      0.3, 0.5, 0.2, 0.04, 
                                      1, 0.05 );

  Parameter_Scan_2D_GRID_SHADES( &Table, 
				 No_of_POINTS_1, Input_Parameter_1,
				 No_of_POINTS_2, Input_Parameter_2,
				 COHERENCE_NUMBER, 
				 "Coherence_Number_Solution_A__K0__Boundary_102.dat" );
  /*   END: Solution A --------------------------------------------------------------------------*/

  /* BEGIN: Solution B: Extra default values: Parameters that produce cycles around 3 to 4 years.*/
  No_of_POINTS_1    = 500;
  Input_Parameter_1 = 12;   assert (I_Time == No_of_POINTS_1);   /* (a, 12)  */
  No_of_POINTS_2    = 500;
  Input_Parameter_2 = 25;   /* (K_0, 25) (H_Gamma, 6) (H_nu, 11) (H_Recov_0, 4)*/
  /* Solution B ---------------------------------------------------------------------------------*/
  // -H2 7.0E-5 -H3 3.0E-3 -H4 9.0E-3 -H5 5 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2    -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4   -P0 10 -P1 0.083 
  Resetting_Parameter_Combination( &Table, 
                                     1.4E-4, 3.0E-3, 9.0E-3, 5, 0.00001,
                                     0.2, 0.2, 
                                     6.7E-2, 0.5, 4.0E4, 
                                     0.3, 0.8, 0.2, 0.06, 
                                     10, 0.083 );  
  /* BEGIN : Writing Latex Table Solution B */
  write_Parameter_Table___RANGES___VALUES___LATEX ( "Latex_Parameter_Table_Solution_B.tex", 
						    "TYPE_of_BOUNDARY", 
						    &Table, Space.P_MAX->data, 
						    Space.P_min->data, Space.nPar );  
  /*   END : End writing         */
  Parameter_Scan_2D_GRID_SHADES( &Table, 
				 No_of_POINTS_1, Input_Parameter_1,
				 No_of_POINTS_2, Input_Parameter_2,
				 //DOMINANT_EIGENVALUE, 
				 DOMINANT_PERIOD, 
	                         "Dominant_Period_Solution_B__K0__Boundary_102.dat" );
  
  Resetting_Parameter_Combination( &Table, 
                                     1.4E-4, 3.0E-3, 9.0E-3, 5, 0.00001,
                                     0.2, 0.2, 
                                     6.7E-2, 0.5, 4.0E4, 
                                     0.3, 0.8, 0.2, 0.06, 
                                     10, 0.083 );  
  
  Parameter_Scan_2D_GRID_SHADES( &Table, 
				 No_of_POINTS_1, Input_Parameter_1,
				 No_of_POINTS_2, Input_Parameter_2,
				 COHERENCE_NUMBER,
				 "Coherence_Number_Solution_B__K0__Boundary_102.dat" );
  /*   END : Solution B ------------------------------------------------------------------------*/

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





