#include <MODEL.h>

#define EPSILON 1.e-10

//#define DYNAMIC___VERBOSE

int CONDITION_on_COEXISTENCE ( double (*COEXISTENCE)(Parameter_Table *), Parameter_Table * P )
{
  /* bool_COEXISTENCE = 1 if the condition on coexistence is fulfilled.
     bool_COEXISTENCE = 0 otherwise 
  */

  int bool_COEXISTENCE;

  bool_COEXISTENCE = 0;

  if ( 1.0 == COEXISTENCE(P) ){
    
    bool_COEXISTENCE = 1;
    
  }
  
  return(bool_COEXISTENCE);
}

double C_O_E_X_I_S_T_E_N_C_E___D_Y_N_A_M_I_C___E_Q_U_I_L_I_B_R_I_A (  Parameter_Table * P  )
{ 
   /* This function detects whether current parameter set in Parameter_Table P allows
      for coexistence of non-trivial, endemic stable equilibria. 
      Type of Dynamic Regims: 
       0 ---> Non-coexistence of dynamic equilibria.
       1 ---> Coexistence of dynamic equilibria.
    */
  double Type_of_Regim;
  int H_bool, M_bool;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3;
  int L, X, U, W;
  int A, K; 
  double w,y;
  double W_u, W_l, y_u, y_l;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);
    
  double * y_SOL_Lower = (double *)calloc( K+1, sizeof(double) ); 
  double * y_SOL_Upper = (double *)calloc( K+1, sizeof(double) );  
  double * y_SOL_Inter = (double *)calloc( K+1, sizeof(double) );   

  Type_of_Regim = 0.0;

  /* Filtering for stationary solutions where a non-zero level
     of mosquito population is maitained */
  M_bool = Feasibility_Condition_M(P);
  
  if (M_bool == 0){
    /* Mosquito free Equilibrium */
    Type_of_Regim = 0.0;
  }
  else{
    /* Mosquito self-sustained population: 
       Possibility of malaria infection. 
       Possibility of coexistence of endemic equilibria. 
    */
    fixed_Points_All( P, y_SOL_Lower, y_SOL_Upper, y_SOL_Inter, 
		      EPSILON );
    
    W_l      = y_SOL_Lower[W];
    y_l      = definition_OutPut_Variables(3, y_SOL_Lower, 0.0, P );
    
    /* Assessing disease establishment: R_0 > 0 */
    H_bool = Feasibility_Condition_H( P, W_l, y_l );  
    
    if( H_bool == 1 ) { 
      /* Disease Endemic (lower, but non-trivial) equilibrium */
      
      W_u      = y_SOL_Upper[W];
      y_u      = definition_OutPut_Variables(3, y_SOL_Upper, 0.0, P );
      
      if (fabs(W_u - W_l) > 1000.0 * EPSILON || fabs(y_u - y_l) > 1000.0 * EPSILON){
	
	Type_of_Regim = 1.0;	
      }
    }
  }

  free(y_SOL_Lower);
  free(y_SOL_Inter);
  free(y_SOL_Upper);
  
  return (Type_of_Regim);
}

