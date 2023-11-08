/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

/* This code explores the model parameter space to estimate the frequency 
   in wich certain function that depends on parameter values fullfils 
   certain condition. 

   It this case, the condition is defined by the boolean function 
   
   CONDITION_on_FREE_COEXISTENCE(...)
   
   that takes 1 when a given parameter set allows for at least one 
   disease endemic stationary state coexistence (with viable Mosquito 
   population), this is the full disease-free equilibrium is unstable. 
   
   Then, within the points fullfiling this first condition, an additional 
   condition is required: coexistence of stable equilibria (bi-stability)
   (see file free_disease_Stability.c).

   Then, the times both conditions are met is divided by the total number 
   of times the first condition is met. This estimates the fraction of 
   parameter space where bistability is found given the existence of 
   at least on equilibrium and a mosquito viable population. 
   (see:
   double F_R_E_E___D_I_S_E_A_S_E___S_T_A_B_I_L_I_T_Y___U_P_P_E_R___S_O_L ( Parameter_Table * ); 
   from free_disease_Stability.c)

   Other calculations are possible, for instance, using 
   double F_R_E_E___D_I_S_E_A_S_E___S_T_A_B_I_L_I_T_Y (  Parameter_Table * ); 
   instead, but the option explained above is more efficient. 

   Again the basic idea follows stochastic integration where we simply count
   the times a randomly selected parameter set, within a
   defined region of the parameter space, happens to produce  
   bi-stability in the model under stuty. Then we diveded that
   number by the total number of trials to obtain a relative frequency
   or relative volume of the parameter space where conditions for
   bi-stability are met. This can be done for models of increasing 
   complexity. Models are defined at compilation time and 
   correspond to different human-mosquito coupled models.

   Compilation (example):
   
   . ~$ make TYPE_of_INDEX=_CASES_1_11p TYPE_of_BOUNDARY=_101 H_MODEL=CASES_1 M_MODEL=LXVnW TYPE_of_MAIN=_ENDEMIC_COEXISTENCE
   
   Execution (example): 

   . ~$ ./SUPERINFECTION_LXVnW_CASES_1_11p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.2 -M1 0.5 -M2 0.2 -M3 0.04 -L0 0.067 -L1 0.5 -L2 3.0E4 -P0 1 -P1 0.05 -R0 10000 -S0 11 -n 1 -v0 3 -G0 3 -G1 3
*/

gsl_rng * r; /* Global generator defined in main.c */

#define No_of_REPETITIONS 3

int main(int argc, char **argv)
{
  int i, j, k, kk, n, n_Bool, n_0, n_1;
  
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
  double ** X_0 = (double **)calloc( Realizations, sizeof(double *) );
  for (i=0; i < Realizations; i++) {
    X_0[i] = (double *)calloc( SUB_MODEL_PARAMETERS, sizeof(double) );
  }
  double ** X_1 = (double **)calloc( Realizations, sizeof(double *) );
  for (i=0; i < Realizations; i++) {
    X_1[i] = (double *)calloc( SUB_MODEL_PARAMETERS, sizeof(double) );
  }
    
  double F, Ave_F, Var_F; 
  double Ave_n, Var_n;
  Var_F = Ave_F = 0.0;
  Var_n = Ave_n = 0.0;
  printf(" Repetitions (from i=0 to 99): ");
  for (i=0; i < No_of_REPETITIONS; i++) {
    
    /* F =  G_E_N_E_R_I_C___R_A_N_D_O_M___P_A_R_A_M_E_T_E_R___S_P_A_C_E____P_L_U_S ( &Table, Realizations,                       */
    /* 										  F_R_E_E___D_I_S_E_A_S_E___S_T_A_B_I_L_I_T_Y,   */
    /* 										  CONDITION_on_FREE_DISEASE,                     */
    /* 										  X );                                           */

    F =  G_E_N_E_R_I_C___R_A_N_D_O_M___P_A_R_A_M_E_T_E_R___S_P_A_C_E____P_L_U_S ( &Table, Realizations, 
					   F_R_E_E___D_I_S_E_A_S_E___S_T_A_B_I_L_I_T_Y___U_P_P_E_R___S_O_L,  
										  CONDITION_on_FREE_DISEASE, 
										  Space.Parametric_Configuration );

    Ave_F += F/(double)Realizations;
    Var_F += F/(double)Realizations * F/(double)Realizations;

    printf("[Area Endemic(%d)= %g] ", i, F/(double)Realizations);

    n = 0; n_Bool = 0; n_0 = 0; n_1 = 0;
    for (j = 0; j< (int)F; j++){
      for (k=0; k < Table.S->nPar; k++){
	kk = Table.S->I[k];
	AssignVectorEntry_to_Structure(&Table, kk, Space.Parametric_Configuration[j][k]);
	if (kk == 1) Table.H_Birth = Table.H_Delta;
	if (kk == 2) Table.H_Delta = Table.H_Birth;
      }
#if defined LXVnW
      Table.M_Fecundity = Table.M_a * Table.M_NoEggs;
#endif
#if defined XkVnW
      Table.M_Fecundity = Table.M_a * Table.M_NoEggs;
#endif
#if defined XVnW
      /* Total mosquito population constant */
      Table.M_Fecundity = Table.M_Delta;
#endif
#if defined XW
      /* Total mosquito population constant */
      Table.M_Fecundity = Table.M_Delta;
#endif
      
      n_Bool = CONDITION_on_COEXISTENCE (C_O_E_X_I_S_T_E_N_C_E___D_Y_N_A_M_I_C___E_Q_U_I_L_I_B_R_I_A, &Table );
 
      if ( n_Bool == 0 ) {
	for (k=0; k< Table.S->nPar; k++) { X_0[n_0][k] = Space.Parametric_Configuration[j][k]; }
	n_0++;
      }
      else if (n_Bool == 1 ) {
	for (k=0; k< Table.S->nPar; k++) { X_1[n_1][k] = Space.Parametric_Configuration[j][k]; }
	n_1++;
      }
      else {
	printf(" Error from main_ENDEMIC_COEXISTENCE.c: n_Bool = %d\n", n_Bool);
	printf(" n_Bool should be either 0 or 1. The program will exit\n");
	exit(0);
      }
      
      
      n += n_Bool;    
    }
    
    assert(n == n_1);

    if( F > 0.0 ) {
      Ave_n += (double)n/F;
      Var_n += (double)n/F * (double)n/F;
    }
  }
  
  printf("\n");
  Ave_F = Ave_F/(double)No_of_REPETITIONS;
  Var_F = Var_F/(double)No_of_REPETITIONS;
  Var_F = sqrt(Var_F - Ave_F*Ave_F);
  
  Ave_n = Ave_n/(double)No_of_REPETITIONS;
  Var_n = Var_n/(double)No_of_REPETITIONS;
  Var_n = sqrt(Var_n - Ave_n*Ave_n);
  
  FILE * fp = fopen("Results_Coexistence_No_of_REPETITIONS.dat", "w");
  fprintf(fp, "%g\t%g\n", Ave_F, Var_F);
  fprintf(fp, "%g\t%g\n", Ave_n, Var_n);
  printf(   "Area where disease free equilibrium is unstable with established mosquito local popualtion,\n");
  printf(   "i. e., there is a endemic state: A = %g\tSTD = %g\n", Ave_F, Var_F);
  printf(   "Area where there is coexistence of equilibria (given the disease free equilibrium is unstable,\n");
  printf(   "i. e., R_0 > 1 and there is a established mosquito local population): A = %g\tSTD = %g\n", Ave_n, Var_n);
  fclose(fp);
   
#if defined CPGPLOT_REPRESENTATION
  P_L_O_T_T_I_N_G___P_A_R_A_M_E_T_R_I_C___C_O_N_F_I_G_U_R_A_T_I_O_N_S ( &Table, 
									&Space,
									X_0, n_0, 
									X_1, n_1 );
#endif  

  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
  for(i=0; i<Realizations; i++) { free (X_0[i]);  free(X_1[i]); }
  free(X_0); free(X_1); 
  
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___F_R_E_E( &Space );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */
  printf("\nEnd of progam\n");
  return (0);
}





