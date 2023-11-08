#include <MODEL.h>

#include <include.extern.par.POPULATION.h>

#define EPSILON (1.0e-8)           /* Accuracy of the iterative process to find 
				      the stationary solution */

#ifndef VERBOSE
#define STAT_BOOL_VERBOSE 0
#else
#define STAT_BOOL_VERBOSE 1
#endif

void I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N( Parameter_Table * P, 
										      double * y_INI )
{
  int i, S, E, E_1, E_2, I, R, C, S1, I1, S2, I2, S3, I3, W, A, K_W, K;
  int L, X, U;
  double C_obs;
  
  P->H = (double)POPULATION;
  //printf(" In  I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N (...) "); getchar();
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P,
	      &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  &L, &X, &U, &W, &A, &K);
  
  if(P->TYPE_of_INITIAL_CONDITION == 0) {
    Print_Press_Key (STAT_BOOL_VERBOSE, 0, 
	  "Initial Conditions are defined from command line or by default values\n");
    
    Human_Population_Initial_Condition_from_Parameter_Table(P, y_INI);
    
    Print(STAT_BOOL_VERBOSE, " Before Mosquito_Steady_State_Initial_Condition(...)");
    /* BEGIN : Stationary Mosquito population at a given level of human
               infection.  This level is fixed by the fraction y = (C + I)/H */
    Mosquito_Steady_State_Initial_Condition( P, y_INI ); 
    /*   END : Stationary Mosquito Population */
  }
  else if (P->TYPE_of_INITIAL_CONDITION == 1) {
    Print_Press_Key (STAT_BOOL_VERBOSE, 0, 
	  "Random Initial Conditions are defined within some boundary values\n");
    // Human_Population_Random_Initial_Condition_Given_i__0( P, y_INI, i___0 );
    Human_Population_Random_Initial_Condition( P, y_INI);
    Mosquito_Steady_State_Initial_Condition( P, y_INI );
  }
  else if (P->TYPE_of_INITIAL_CONDITION == 2) {
    Print_Press_Key (STAT_BOOL_VERBOSE, 0, 
	  "Initial Conditions are defined as the fixed points of the system\n");
    fixed_Points(P, y_INI, EPSILON);  /* Calculating Lower/Single point... 
				       * (see fixed_Points.c) 
				       */
    for( i = 0; i < P->MODEL_STATE_VARIABLES; i++ ) 
       P->Vector_Model_Variables_Stationarity[i] = y_INI[i] ;
  }
  else if (P->TYPE_of_INITIAL_CONDITION == 3) {
    Print_Press_Key (STAT_BOOL_VERBOSE, 0, 
	  "Initial Conditions are defined as the disease-free equilibrium\n");
    stable_Solution_Free_Disease(P, y_INI);
    
  }
  else {
    printf(" Attention: Initial Condition Value is undefined:\n");
    printf(" Allows values are 0, 1, 3, and 3, but TYPE_of_INITIAL_CONDITION = %d\n",
	   P->TYPE_of_INITIAL_CONDITION );
    exit(0); 
  }    
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

}

void Mosquito_Steady_State_Initial_Condition( Parameter_Table * P, double * Y )
{
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3;
  int L, X, U, W;
  int A, K; 
  double y, w;
                                           
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (   P,
                                              &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,
                                              &L, &X, &U, &W, 
					      &A, &K );

  y = (Y[C]+Y[I])/P->H;

  
  w = Infectious_Mosquito_Steady_State( y, P );

  double M = Total_Mosquito_Steady_State( P );

  double g_M = P->n_V * P->M_Gamma /(P->n_V * P->M_Gamma + P->M_Delta);

#if defined LXVnW  
  Stable_Solution_Partial_Mosquito_Larva ( P, M, g_M,
					   y, w,
					   L, W, Y );
#else
  Stable_Solution_Partial_Mosquito_Constant_Population ( P,
                                                         M, g_M,
							 y, w,
							 X, W, Y );
#endif
}
							 
  
  
  
