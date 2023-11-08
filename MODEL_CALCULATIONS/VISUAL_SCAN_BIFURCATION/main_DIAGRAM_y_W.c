/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
    This code animates the curve intersections that define the stationary points. The exemple below shows coexistence of two stable branches (bistability) along with an intermediate unstable one.

    Compilation:
        Read makefile carefully. The makefile can build different exe files depending on a range of options that define the functions
        to compile for each case. The script 'make_ALL.sh' is an exemple to build different exe files in one go.

        For a single example, type:

      	   1. ~S make M_MODEL=LXVnW H_MODEL=CASES_1 TYPE_of_MAIN=_DIAGRAM_y_W
           2. ~$ make M_MODEL=LXVnW H_MODEL=SnInR TYPE_of_MAIN=_DIAGRAM_y_W JACOBIAN=ODE

         Exectution Examples
         Make sure to clean bifurcation_Diagram_LOWER_SHEET*.dat files first!!!

           1. ~$ ./CASES_1-LXVnW_DIAGRAM_y_W -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 19 -S3 200 -S4 12 -S5 0.0 -S6 0.5 -n 1 -v0 3 -G0 1 -G1 1 -G2 0 -G3 0.1 -G4 0.5 -G5 0 -G6 0.0 -G7 1.0 -G8 0 -G9 1 -G10 1 -G11 3 -G12 1 -G27 1 -G28 20
           
           2. ~$ ./SnInR-LXVnW_DIAGRAM_y_W -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05   -S0 19 -S3 200 -S4 12 -S5 0.0 -S6 0.5 -n 1 -v0 3 -G0 1 -G1 1 -G2 0 -G3 0.1 -G4 0.5 -G5 0 -G6 0.0 -G7 200.0 -G8 0 -G9 1 -G10 1 -G11 3 -G12 1 -G27 1 -G28 20
           
           3. ~$ ./SnInR-LXVnW_DIAGRAM_y_W -Y0 18 -H2 0.000136986301369863 -H4 0.02 -H3 0.00273972602739726 -M1 0.7 -M2 0.5 -L2 100000 -N1 0.15 -N0 0.5 -N2 1 -N3 1 -S0 19 -S3 200 -S4 25 -S5 18.0 -S6 28.0 -n 1 -v0 3 -G0 1 -G1 1 -G2 0 -G3 0.1 -G4 0.5 -G5 0 -G6 0.0 -G7 200.0 -G8 0 -G9 1 -G10 1 -G11 3 -G12 1 -G27 1 -G28 20

     Solution A:

	   4. ~$ ./CASES_1-LXVnW_DIAGRAM_y_W -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 1.0E-10 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 19 -S3 100 -S4 12 -S5 0.0 -S6 0.5 -n 1 -v0 3 -G0 1 -G1 1 -G2 1 -G3 0.0 -G4 0.5 -G5 1 -G6 0.0 -G7 1.0 -G8 0 -G9 1 -G10 1 -G11 3 -G12 1 -G27 1 -G28 20 -G29 /XSERVE

	   5. ~$ ./CASES_1-LXVnW_DIAGRAM_y_W -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 19 -S3 200 -S4 12 -S5 0.0 -S6 0.5 -n 1 -v0 3 -G0 1 -G1 1 -G2 0 -G3 0.1 -G4 0.5 -G5 0 -G6 0.0 -G7 1.0 -G8 0 -G9 1 -G10 1 -G11 3 -G12 1 -G27 1 -G28 20 -G29 /XSERVE
*/
#include "../../Include/MODEL.h"

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

int main(int argc, char **argv)
{
  Parameter_Space Space;
  Parameter_Table Table;

  P_ARG = &Table;

#include "default.c"

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

  int No_of_POINTS_1    = No_of_POINTS;      // -S3 1000
  int Input_Parameter_1 = Input_Parameter;  // -S4 12 /* 12: a; 25: K_0; 4: H_Recov_0; 3: H_Sigma_0 */

   /* Extra default values */
   I_Time                =  100000;

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
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, CPG_DRIVER_NAME );
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif

  P_L_O_T_T_I_N_G___I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M( &Table,
								   I_Time,
								   No_of_POINTS_1,
								   Input_Parameter_1 );

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
