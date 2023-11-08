/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code calculates ODE model temporal evolution for a range of human-mosquito models

   Compilation:

   . ~$ make M_MODEL=LXVnW H_MODEL=CASES_1

   Execution (with time dependence):

   . ~$ ./CASES_1-LXVnW -S0 19 -n 2 -v0 3 -v1 30  -G0 1 -G1 2 -Xn 0 -t0 200 -t1 0.0 -t2 5000.0  -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1 -M0 0.4 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -TP 12 -TY 0 -t4 2

   Execution (without time dependence -t4 0):

   . ~$ ./CASES_1-LXVnW -S0 19 -n 2 -v0 3 -v1 30  -G0 1 -G1 2 -Xn 0 -t0 1000 -t1 0.0 -t2 10000.0  -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1 -M0 0.4 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -t4 0

   Important parameters controling the type of time dependencies are:

     # -TP 12  Label for the force parameter that will be shown as an output variable. This works in conjuntion with the choice
               of one of the output variables being '30', as in the example above (-n 2 -v0 3 -v1 30).
     # -TY 0   Label TREND_TYPE from Trend_Control structure (see Trend_Control.c) to control the time dependence used to force
               model parameters (0 means that this is effectively controled by the function:
               'void Update_Time_Dependence ( int TYPE_of_TIME_DEPENDENCE, double Time_Current, Parameter_Table * Table)'
               defined in deterministic_time_dynamics.c ). Other forms to force model parameters is when they depend on time
               dependent variables, such as temperature, measured at different time intervals.
     # -t4 2   This define TYPE_of_TIME_DEPENDENCE from Time_Control structure to control the type of forcing in
               'void Update_Time_Dependence ( int TYPE_of_TIME_DEPENDENCE, double Time_Current, Parameter_Table * Table)'
     # -Xn 0   Input Argument Controling Initial Conditions (TYPE_of_INITIAL_CONDITION) from Initial Conditions set:
               . 0 :  Initial Conditions from Time Table Structure (default) or command line argument.
               . 1 :  Initial Conditions at Random
               . 2 :  Initial Conditions at stationary state
               . 3 :  Initial Conditions at disease-free equlibrium

  Parameters related to the definition of the sinusoidal periodic forcing:

     # -L3 K_Sigma
     # -L4 K_Period
     # -L5 K_Seasonal_Intensitty

  Sinusoidal periodic forcing takes always the form:

        value = Mean_Value * ( 1.0 + Seasonal_Intensity * sin(2.0 * M_PI*t / Period) )

  (see time_Oscillations_Parameter_Forcing.c, where K_Sigma is not yet implemented)

  Defaulf values are:
     . K_Period is about 1 year
     . K_Seasonal_Intensity is just a litte lower than 1.0

  Mean values for forcing parameters are given as input parameters through the correspoding keys. For instance, -L2 30000 will mean then Mean_Value for the carrying capacity will be 30000. Parameters depending on temperature are setup the their corresponding values through

  void values_TempDependency(double Temp, Parameter_Table * P)

  as the Parameter_Table is uploaded (see Parameter_Table.c and values_HumanMos.c.

  Examples of Tempereture-driven oscilations (Seasonal Intensity = 0.3, <T> = 25.0)
     . ~$ ./CASES_1-LXVnW -S0 19 -n 2 -v0 3 -v1 30  -G0 1 -G1 2 -Xn 2 -t0 400 -t1 0.00 -t2 10000.0  -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1 -M0 0.4 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -Y0 25.0 -TP 51 -TY 0 -t4 4 -L5 0.3

     . ~$ ./SnInR-LXVnW -S0 19 -n 2 -v0 3 -v1 30  -G0 1 -G1 2 -Xn 2 -t0 500 -t1 0.00 -t2 12000.0  -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1 -M0 0.4 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -Y0 25.0 -TP 51 -TY 0 -t4 4 -L5 0.3
*/

int main(int argc, char **argv)
{
  int i;
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
  Table.T = &Time;

#if defined APPLYING_TREND
  printf(" Trend_Control structure will be allocated: \n");
  Tr = (Trend_Control *)malloc( 1 * sizeof(Trend_Control) );
  T_R_E_N_D___C_O_N_T_R_O_L___U_P_L_O_A_D( Tr, &Table);
  int Input_Parameter = Tr->Tr_Input_Parameter;
  //S_E_T_U_P___T_R_E_N_D___T_R_I_A_N_G_L_E (Tr, &Time, Input_Parameter );
  //S_E_T_U_P___T_R_E_N_D___F_R_E_E___T_R_I_A_N_G_L_E (Tr, &Time, Input_Parameter );
  printf(" Trend_Control structure has been correctly allocated and initiated\n");
  Table.Tr = Tr;
#endif

#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, "/XSERVE" );
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif

#include <gsl_random_number_Setup.c>
#if defined VERBOSE
  /* BEGIN: Checking Random Number Generator Setup */
  for(i=0; i<10; i++){
    printf( "f(%d)=%g, ", i, gsl_rng_uniform(r) );
    printf( "f_GAUS(%d)=%g\n", i, gsl_ran_gaussian(r, 1.0) );
  }
  printf("\n");//Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif

  /* BEGIN : Writing Latex Table */
  write_Parameter_Table___RANGES___VALUES___LATEX ( "Latex_Parameter_Table.tex",
                                                    "TYPE_of_BOUNDARY",
						    &Table,
						    Space.P_MAX->data,
						    Space.P_min->data, Space.nPar );
  /*   END : End writing         */
  //Press_Key();
  if (TYPE_of_INITIAL_CONDITION == 1)
    for( i=0; i<100; i++ ) M_O_D_E_L( &Table );
  else
    M_O_D_E_L( &Table );

  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif
  T_I_M_E___C_O_N_T_R_O_L___F_R_E_E( &Time, &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___F_R_E_E( &Space );
#if defined APPLYING_TREND
  T_R_E_N_D___C_O_N_T_R_O_L___F_R_E_E( Tr );
#endif
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}
