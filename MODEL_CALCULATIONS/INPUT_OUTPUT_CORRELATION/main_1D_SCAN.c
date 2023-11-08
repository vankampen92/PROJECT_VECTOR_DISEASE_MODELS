/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/*
   This function calculates the correlation between externally-driven fluctuations
   in model variables and the external fluctuations themselves for a number of
   mosquito-human models of malaria transmision.

   This code needs the CPG variable to be CPGPLOT_REPRESENTATION at compilation
   time (even though non graphic output may be given).

   Since the dynamics of transmision introduces delays, these corralation is
   calculated as the maximum correlation between fluctuation input (temporally
   fluctuating model parameter) and the fluctuating response in a model variable
   over incrasing lags. This code can calculate this at any point within the parameter
   space. In particular, this code calculates this correlation along a transect
   between an intial and a final value of a given model parameter.

   Compilation:

   . ~$ make TYPE_of_MAIN=_1D_SCAN CPG=CPGPLOT_REPRESENTATION

   Exectution:
   Note: This forcese carrying capacity only when TYPE_of_TIME_DEPENDENCE = 1 (see ./Definition_Numerical_Integration/CASES_1/deterministic_time_dynamics.c and Time_Control structure) and the output variable corresponding to code 30 (-v0 30) will be also the carrying capacity (see ./definition_OutPut_Variables.c) provided -TP 25 -TY 0. Usually these two things have to coincide at compilation time.

   Alternatively, the code can be built to force biting rate (a) only TYPE_of_TIME_DEPENDENCE = 2 and the output variable corresponding to code 30 (-v0 30) corresponds to also the biting rate provided -TP 12 -TY 0. These two input parameters indicate TYPE_of_TREND (-TY 0) and the label of the model parameter that has been forced (-TP 12).

   . ~$ ./CASES_1-LXVnW__1D_SCAN -G0 1 -G1 3 -G5 0 -G6 0.0 -G7 1.0 -S0 19 -S3 100 -S4 25 -S5 10000.0 -S6 100000.0 -n 3 -v0 30 -v1 3 -v2 21 -t0 1441 -t1 0.0 -t2 10800    -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 1 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2    -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4   -P0 1 -P1 0.083  -TP 12 -TY 0 -t4 2 -Xn 1 -L5 0.5

   When forcing a, biting rate, and scanning the mean biting rate (problematic call):
   . ~$ ./CASES_1-LXVnW__1D_SCAN  -G0 1 -G1 3 -G5 0 -G6 0.0 -G7 1.0 -S0 19 -S3 50 -S4 12 -S5 0.2 -S6 0.4 -n 3 -v0 30 -v1 3 -v2 21 -t0 1441 -t1 1441 -t2 10800  -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 1 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2  -M0 0.25 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4   -P0 10 -P1 0.08 -TP 12 -TY 0 -t4 2 -Xn 1 -L5 0.5

   When forcing K_0 and scannig the mean value of K_0:
   . ~$ ./CASES_1-LXVnW__1D_SCAN -G0 1 -G1 3 -G5 0 -G6 0.0 -G7 1.0 -S0 19 -S3 100 -S4 25 -S5 10000.0 -S6 100000.0 -n 3 -v0 30 -v1 3 -v2 21 -t0 1441 -t1 0.0 -t2 10800    -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 1 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2    -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4   -P0 1 -P1 0.083  -TP 25 -TY 0 -t4 1 -Xn 1 -L5 0.5

   When forcing temperatute at different level of the carrying capacity:
   . ~$ ./CASES_1-LXVnW__1D_SCAN -G0 1 -G1 3 -G5 0 -G6 0.0 -G7 1.0 -S0 19 -S3 100 -S4 25 -S5 10000.0 -S6 100000.0 -n 3 -v0 30 -v1 3 -v2 21 -t0 1441 -t1 0.0 -t2 10800    -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 1 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2    -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4   -P0 1 -P1 0.083  -TP 51 -TY 0 -t4 4 -Xn 1 -L5 0.5

   When forcing temperature at different levels of average temperature:
   . ~$ ./CASES_1-LXVnW__1D_SCAN -G0 1 -G1 3 -G5 0 -G6 0.0 -G7 1.0 -S0 19 -S3 100 -S4 51 -S5 18.0 -S6 25.0 -n 3 -v0 30 -v1 3 -v2 21 -t0 1441 -t1 0.0 -t2 10800    -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 1 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2    -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4   -P0 1 -P1 0.083  -TP 51 -TY 0 -t4 4 -Xn 1 -L5 0.5

   . Input arguments controling graphic output: -G5 0 -G6 0.0 -G7 1.0 -G0 1 -G1 3

   . Input arguments controling the exploration of parameter space scanning: -S0 19 -S3 100 -S4 12 -S5 0.1 -S6 0.3
     Note: -S0 19 should match the dimension of the index vector (see index_Definition_[n].c)
           -S4 Input Parmater to explore from a initial to a final value.
	   [-S3 -S5 -S6] define the exploration (number of points, min and max values, see below)

   . Input arguments controling what correlation will be calulated: -n 3 -v0 30 -v1 3 -v2 21
     -n   3: Number of output variables. This code requires n to be 3. If this number if lower
             the probram crashes. There should be at least room allocated for three output
	     variables.
     -v0 30: This should be always 30. This is important (see definition_OutPut_Variables.c).
             This label defines the parameter to be considered output variable. See function
             double definition_OutPut_Variables(int j, double * y, const double t, Parameter_Table * P).
             from definition_OutPut_Variables.c. Let this variable be X.
     -v1 3:  3 is the key for the fraction of infectious humans. This can be changed from
             command line argument. Let this variable be Y.

     This code saves two two-column files (scan_CORRELATION_0.dat and scan_COVARIANCE_0.dat)
     with the correlation (covariance) between X and Y, Corr(X,Y), as the input parameter defined
     in -S4 increases from -S5 to -S6:
                                               Input_Paramter_Value  Corr(X,Y)
                                                                ...  ...

   . Other important input arguments are:

     -TP 12  Label for the forced parameter that will be shown as an output variable. This works in conjuntion with the choice of one of the output variables being '30', as in the example above (-n 3 -v0 30 -v1 3).
     -TY 0   Label TREND_TYPE from Trend_Control structure (see Trend_Control.c) to control the time dependence used to force model parameters (0 means that this is effectively controled by the function 'void Update_Time_Dependence ( int TYPE_of_TIME_DEPENDENCE, double Time_Current, Parameter_Table * Table)', defined in deterministic_time_dynamics.c ). Other forms to force model parameters is when they depend on time dependent variables, such as temperature, measured at different time intervals.
     -t4 2   This define TYPE_of_TIME_DEPENDENCE from Time_Control structure to control the type of forcing in
               'void Update_Time_Dependence ( int TYPE_of_TIME_DEPENDENCE, double Time_Current, Parameter_Table * Table)'
     -Xn 0   Input Argument Controling Initial Conditions from Initial Conditions set:
               . 0 :  Initial Conditions from Time Table Structure (default) or command line argument.
               . 1 :  Initial Conditions at Random
               . 2 :  Initial Conditions at stationary state
               . 3 :  Initial Conditions at disease-free equlibrium

   . Parameters related to the definition of the sinusoidal periodic forcing:

     -L3 K_Sigma
     -L4 K_Period
     -L5 K_Seasonal_Intensitty
   . Sinusoidal periodic forcing takes always the form: 

        value(t) = Mean_Value * ( 1.0 + Seasonal_Intensity * sin(2.0 * M_PI*t / Period) )

  (see time_Oscillations_Parameter_Forcing.c, where K_Sigma is not yet implemented)

   . Defaulf values are:
     . K_Period is about 1 year
     . K_Seasonal_Intensity is just a litte lower than 1.0

   . Mean values for forcing parameters are given as input parameters through the correspoding keys. For instance, -L2 30000 will mean then Mean_Value for the carrying capacity will be 30000. Parameters depending on temperature are setup to the their corresponding values through

  void values_TempDependency(double Temp, Parameter_Table * P)

  as the Parameter_Table is uploaded (see Parameter_Table.c and values_HumanMos.c.)

   . Input arguments controling the numerical integration: -t0 1441 -t1 0.0 -t2 10800 -t4 4

     -t0 1441 No of discrete points in numerical integration from time -t1 [0.0] to time -t2 [10800]
     -t4 4 TYPE_of_TIME_DEPENDENCE parameter

   . Set of input arguments defining ODE system (model parameters):

    -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05

   . Notice that this parameters may be changed to make them congruent with a given temperature
   when uploading the Parameter_Table at the beginning of code execution if the funcion:
      values_TempDependency(T->Temp, T);
   is called right after
      void values_HumanMos(P);
*/

int C_O_R_R_E_L_A_T_I_O_N___S_I_M_P_L_E___S_C_A_N( Parameter_Table * ,
						   int ,
						   int ,
						   double ,
						   double );
int main(int argc, char **argv)
{
  Parameter_Space Space;
  Parameter_Table Table;
  Time_Control Time;

  P_ARG = &Table;

#include "default.c"

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

#if defined CASES_33
  K_Mean_Value         = K_p;
#else
  K_Mean_Value         = K_0;
#endif
  M_a_Mean_Value       = M_a;

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  P_A_R_A_M_E_T_E_R___S_P_A_C_E___A_L_L_O_C( &Space, &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___U_P_L_O_A_D( &Space, &Table, A_n, A_d);
  printf(" Parameter_Space structure has been correctly allocated and initiated\n");

#if defined APPLYING_TREND
  printf(" Trend_Control structure will be allocated: \n");
  Trend_Control * Tr = (Trend_Control *)malloc( 1 * sizeof(Trend_Control) );
  T_R_E_N_D___C_O_N_T_R_O_L___U_P_L_O_A_D( Tr, &Table);
  //S_E_T_U_P___T_R_E_N_D___T_R_I_A_N_G_L_E (Tr, &Time, Input_Parameter );
  //S_E_T_U_P___T_R_E_N_D___F_R_E_E___T_R_I_A_N_G_L_E (Tr, &Time, Input_Parameter );
  printf(" Trend_Control structure has been correctly allocated and initiated\n");
  Table.Tr = Tr;
#endif

  /* If the dynamics is temperature/rainful driven, the corresponding
     data structure should be also allocated and initiated here
     (at least, after initiating Parameter_Table structure)
  */
  /* */
  printf(" Time_Control structure will be allocated: \n");
  printf(" %d output variables of length %d points will be allocated\n", SUB_OUTPUT_VARIABLES, I_Time);
  T_I_M_E___C_O_N_T_R_O_L___A_L_L_O_C( &Time, &Table, I_Time);
  T_I_M_E___C_O_N_T_R_O_L___U_P_L_O_A_D( &Time, &Table, I_Time);
  printf(" Time_Control structure has been correctly allocated and initiated\n");

#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, "/XSERVE" );
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif

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

  int Input_Parameter = Space.Input_Parameter;
  int Status = C_O_R_R_E_L_A_T_I_O_N___S_I_M_P_L_E___S_C_A_N( &Table,
							      Space.No_of_POINTS,
							      Space.Input_Parameter,
							      Space.Value_0,
							      Space.Value_1 );

  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
  T_I_M_E___C_O_N_T_R_O_L___F_R_E_E( &Time, &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___F_R_E_E( &Space );
#if defined APPLYING_TREND
  T_R_E_N_D___C_O_N_T_R_O_L___F_R_E_E( Tr );
#endif
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif

  printf("\nEnd of progam\n");
  return (0);
}
