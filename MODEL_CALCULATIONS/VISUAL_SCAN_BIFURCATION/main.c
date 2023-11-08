/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

/*
  This code calculates 3D bifurcation diagram by scanning the control variable in two dimensions 
  being the response variable the third dimension.

  Compilation:
        Read makefile carefully. The makefile can build different exe files depending on a range of options that define the functions
        to compile for each case. The script 'make_ALL.sh' is an exemple to build different exe files in one go.        

  For a single example, type:

	. ~S make M_MODEL=LXVnW H_MODEL=CASES_1

	This should generate the exe file 'CASES_1-LXVnW'. Make sure you are compiling this current main file (main.c), this is, you should make sure you see the follwing line in the makefile:
	TYPE_of_MAIN=##### [void] / '_SIMPLE' / '_DIAGRAM_y_W' / '_SIMPLE_TWO'

   Execution Examples. Scanning the plane (a, K_0) in 1st example and (K_0, a) in the 2nd.  
   Make sure to clean *.dat files first!!!
   Example 1 (Compiled with Input_Parameter_1 = 12 on line of code right after argument_Control(...)):
        . ~$ rm *.dat
        . ~$ ./CASES_1-LXVnW -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05   -S0 19 -S3 200 -S4 25 -n 1 -v0 3 -G0 1 -G1 2 -G2 1 -G3 0.1 -G4 0.5 -G5 1 -G6 0.0 -G7 1.0 -G8 0 -G9 1 -G10 1 -G11 3 -G12 1 -G27 1 -G28 20
        . ~$ rm *.dat
   
   Example 2 (Compiled with Input_Parameter_1 = 25 on line of code right after argument_Control(...)):
        . ~$ rm *.dat
        . ~$ ./CASES_1-LXVnW -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05   -S0 19 -S3 200 -S4 12 -n 1 -v0 3 -G0 1 -G1 2 -G2 1 -G3 100.0 -G4 1.0E+05 -G5 1 -G6 0.0 -G7 1.0 -G8 0 -G9 1 -G10 1 -G11 3 -G12 1 -G27 1 -G28 20
        . ~$ rm *.dat

   Execution Examples. Scanning the plane (T, K_0) in 3rd example and (K_0, T) in the 4th.  
   Example 3 (Compiled with Input_Parameter_1 = 51 on line of code right after argument_Control(...)):
        . ~$ rm *.dat
        . ~$ ./CASES_1-LXVnW -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05   -S0 19 -S3 200 -S4 25 -n 1 -v0 3 -G0 1 -G1 2 -G2 1 -G3 16 -G4 32.0 -G5 1 -G6 0.0 -G7 1.0 -G8 0 -G9 1 -G10 1 -G11 3 -G12 1 -G27 1 -G28 20
        . ~$ rm *.dat

   Example 4 (Compiled with Input_Parameter_1 = 25 on line of code right after argument_Control(...)):
        . ~$ rm *.dat
        . ~$ ./CASES_1-LXVnW -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05   -S0 19 -S3 200 -S4 51 -n 1 -v0 3 -G0 1 -G1 2 -G2 1 -G3 10000.0 -G4 1.0E+05 -G5 1 -G6 0.0 -G7 1.0 -G8 0 -G9 1 -G10 1 -G11 3 -G12 1 -G27 1 -G28 20
        . ~$ rm *.dat

	Note: -G3 x0 -G4 x1, where (x0, x1) defines the interval on the x axis to plot.   
*/

gsl_rng * r; /* Global generator defined in main.c */

int main(int argc, char **argv)
{
  Parameter_Space Space;
  Parameter_Table Table;
  //Time_Control Time;

  P_ARG = &Table;

#include "default.c"

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);
  /* Extra default values */

   int No_of_POINTS_2    = 200; 
   int Input_Parameter_2 = Input_Parameter;  // -S4 [Input_Parameter]
   int No_of_POINTS_1    = No_of_POINTS;     // -S3 n (from 200 to 400 works fine)
   int Input_Parameter_1 = 12;               // 

   I_Time                =  No_of_POINTS_1;

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
  int Output_Variable   = Table.IO_VARIABLE_LIST[0]; /* 21: EIR; 3: Fraction of Infectious Humans */

  double Epsilon = 1.0E-4;
  int Status = B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M___P_A_R_A_M_E_T_E_R___S_C_A_N( &Table,
										    No_of_POINTS_1,
										    Input_Parameter_1,
										    No_of_POINTS_2,
										    Input_Parameter_2,
										    Output_Variable,
										    Epsilon );
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
