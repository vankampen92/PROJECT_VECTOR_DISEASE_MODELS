#include <MODEL.h>

#include <include.extern.par.POPULATION.h>

#define EPSILON (1.0e-8)           /* Accuracy of the iterative process to find
				      the stationary solution */

void I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N( Parameter_Table * P,
										      double * y_INI )
{
  int i, S, E, E_1, E_2, I, R, C, S1, I1, S2, I2, S3, I3, W, A, K_W, K;
  int L, X, U;
  double C_obs;

  P->H = (double)POPULATION;
  //printf(" In  I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N (...) "); getchar();
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P,  &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  &L, &X, &U, &W, &A, &K);

#if defined INITIAL_CONDITION
  // Human_Population_Initial_Condition_from_Parameter_Table(P, y_INI);
  // printf(" Before Human_Population_Random_Initial_Condition_from_Parameter_Table (...)"); getchar();
  Human_Population_Random_Initial_Condition_from_Parameter_Table(P, y_INI);
  // printf(" After Human_Population_Random_Initial_Condition_from_Parameter_Table (...)"); getchar();
  /* BEGIN : Stationary Mosquito population at a given level of human
     infection.  This level is fixed by the fraction y = (C + I)/H */
  // printf(" Before Mosquito_Steady_State_Initial_Condition(...)"); getchar();
  Mosquito_Steady_State_Initial_Condition( P, y_INI );
  /*   END : Stationary Mosquito Population */
#else

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  #if defined RANDOM_INITIAL_CONDITION

     #if defined ODE_RESTRICTED_JACOBIAN
       if( P->TYPE_of_MODEL == 44 ){
	 y_INI[0] =  P->i__0;  /* Total number of infectious humans   */
	 y_INI[1] =  P->m__i;  /* Total number of infected mosquitoes */
       }
       else {
	 double i___0 = P->i__0;
	 #if defined BASIN_SCAN
	        i___0 = P->i__0 / P->H;
	 #endif
	 #if defined RANDOM_SCAN
	        i___0 = P->i__0 / P->H;
	 #endif
	 Human_Population_Random_Initial_Condition_Given_i__0( P, y_INI,
							       i___0 );

	 y_INI[W] = P->m__i;  /* Total number of infected mosquitoes */
       }
     #else
         double i___0 = P->i__0 / P->H;
	 Human_Population_Random_Initial_Condition_Given_i__0( P, y_INI,
							       i___0 );

	 y_INI[W] = P->m__i;  /* Total number of infected mosquitoes */
     #endif
  #else

     fixed_Points(P, y_INI, EPSILON);
     for( i = 0; i < P->MODEL_STATE_VARIABLES; i++ )
       P->Vector_Model_Variables_Stationarity[i] = y_INI[i] ;

  #endif

#endif

#if defined CASES_33
  /* BEGIN : Carrying Capacity: Stationary Value */
  /* K   */ /* dydt[K] =  P->K_A * P->K_p - P->K_E * y[K];*/ /* K   */
  y_INI[K] = P->K_A * P->K_p / P->K_E;
  P->Vector_Model_Variables_Stationarity[K] = y_INI[K];
  /*  END                      */
#endif
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
#if defined CASES_33
  y = (Y[C]+Y[I])/P->H;
#endif

#if defined CASES_1
  y = (Y[C]+Y[I])/P->H;
#else
  y = Y[I]/P->H;
#endif

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
