#include <MODEL.h>

#define EPSILON (1.0e-8)           /* Accuracy of the iterative process to find 
				      the stationary solution */

void I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N( Parameter_Table * P, 
										      double * y_INI )
{
  int i;
  int I, W;

         I = 0; /* Fraction of infectious humans     */
         W = 1; /* Fraction of infectious mosquitoes */

#if defined INITIAL_CONDITION
         Human_Population_Initial_Condition_from_Parameter_Table(P, y_INI);  
         y_INI[W] = P->m__i;
#else
         fixed_Points(P, y_INI, EPSILON);
	 for( i = 0; i < P->MODEL_STATE_VARIABLES; i++ ) P->Vector_Model_Variables_Stationarity[i] = y_INI[i] ;
#endif
   
  if(P->TREND_TYPE > 0){
    init_Trend(P); /* Fixed time dependent trends in parameter values 
		      This function updates paremeter structure according to 
		      a predefined trend */
  } 
}
