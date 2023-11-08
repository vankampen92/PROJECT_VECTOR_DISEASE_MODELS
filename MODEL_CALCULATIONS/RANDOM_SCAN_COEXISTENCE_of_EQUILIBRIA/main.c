/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code explores the model parameter space to estimate the frequency 
   in wich certain function that depends on parameter values fullfils 
   certain condition. 

   It this case, the condition is defined by the boolean function 
   
   CONDITION_on_COEXISTENCE(...)
   
   that takes 1 when a give parameter set allows for coexistence of
   stable equilibria (bi-stability), and 0 otherwise. 
   (see file coexistence_dynamic_Equilibria.c)

   The basic idea follows stochastic integration where we simply count
   the times a randomly selected parameter set, within a
   defined region of the parameter space, happens to produce  
   bi-stability in the model under stuty. Then we diveded that
   number by the total number of trials to obtain a relative frequency
   or relative volume of the parameter space where conditions for
   bi-stability are met. This can be done for models of increasing 
   complexity. Models are defined at compilation time and 
   correspond to different human-mosquito coupled models.

   Compilation (example):
   
   . ~$ make TYPE_of_INDEX=_CASES_1_11p TYPE_of_BOUNDARY=_101 H_MODEL=CASES_1 M_MODEL=LXVnW
   
   You should heck that you have this line of code in the  makefile: 
   TYPE_of_MAIN=################# Options '[void]' / '_ENDEMIC_COEXISTENCE'
   so that you compile actually this file (main.c)

   Execution (example): 

   . ~$ ./SUPERINFECTION_LXVnW_CASES_1_11p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.2 -M1 0.5 -M2 0.2 -M3 0.04 -L0 0.067 -L1 0.5 -L2 3.0E4 -P0 1 -P1 0.05 -R0 10000 -S0 11 -n 1 -v0 3 -G0 3 -G1 3
*/ 

int main(int argc, char **argv)
{
  int i;
  Parameter_Space Space;
  Parameter_Table Table;
  
  P_ARG = &Table;

#include "default.c"    
  /* Extra default values */

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
  
  /* Note: The intermediate stationary point that should be calculated in 
           case of coexistence of stationary points fails to be calculated
	   when the external force of infection is equated to zero (Imm = 0.0)
	   This problem has been corrected by compiling and calling 
	   fixed_Points_Intermediate.c instead of using fixed_Points_ALL.c
  */
  printf("\n Coexistence of Stationary States Calculation...\n");
  double * X = (double *)calloc( Realizations, sizeof(double) );
  double * Y = (double *)calloc( Realizations, sizeof(double) );
  
  double F, Ave_F, Var_F;
  Var_F = Ave_F = 0.0;
  printf(" Repetitions (from i=0 to 99): ");
  for (i=0; i < 100; i++) {
    
    F =  G_E_N_E_R_I_C___R_A_N_D_O_M___P_A_R_A_M_E_T_E_R___S_P_A_C_E( &Table, 
								      Realizations,
								      C_O_E_X_I_S_T_E_N_C_E___D_Y_N_A_M_I_C___E_Q_U_I_L_I_B_R_I_A,
								      CONDITION_on_COEXISTENCE,
								      X, Y ); 
    Ave_F += F/(double)Realizations;
    Var_F += F/(double)Realizations * F/(double)Realizations;

    printf("[Area(%d)= %g] ", i, F/(double)Realizations);
  }  
  printf("\n");
  Ave_F = Ave_F/(double)100;
  Var_F = Var_F/(double)100;
  Var_F = sqrt(Var_F - Ave_F*Ave_F);
  
  FILE * fp = fopen("Results_Coexistence_100.dat", "w");
  fprintf(fp, "%g\t%g\n", Ave_F, Var_F);
  printf(   "Area = %g\tSTD = %g\n", Ave_F, Var_F);
  fclose(fp);
  
  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
  free(X); free(Y); 

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___F_R_E_E( &Space );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */
  printf("\nEnd of progam\n");
  return (0);
}





