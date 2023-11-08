#include <MODEL.h>

#define EPSILON 0.01

//#define DYNAMIC___VERBOSE

int CONDITION_on_R_0 ( double (*R___0)(Parameter_Table *), Parameter_Table * P )
{
  /* Output: 
     . bool_COEXISTENCE = 1 if R_0 is about 1, i.e., 
     
                  1 - EPSILON < R_0 < 1 + EPSILON 
     
     . bool_COEXISTENCE = 0 otherwise 
  */
  double R_0;

  int bool_R_0;

  bool_R_0 = 0;

  R_0 = R___0( P );

  if ( ( (1 - EPSILON) < R_0 ) && ( (1 + EPSILON) > R_0 ) ){
    
    bool_R_0 = 1;
    
  }
  
  return(bool_R_0);
}

double R_0___Subdominant_Eigenvalue (  Parameter_Table * P  )
{ 
   /* This function calculates R_0 as 

      R_0 = 1 + \lambda_0                                         (1)

      where \lambda_0 is the largest eigenvalue. Since our ODE system 
      is at constant population size, the largest eigenvalue when 
      the equilibrium is stable is always zero. In that case, a  
      positive subdominant eigen value determines instability, and R_0
      can be approximated throgh (1) by calculating its value for the 
      Jacobian matrix evaluated at the disease-free equilibrium 
    */
  double R_0;
  int M_bool;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3;
  int L, X, U, W;
  int A, K; 
  double w,y;
  double lambda_0;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);
    
  R_0 = 0.0;

  M_bool = Feasibility_Condition_M(P);
  if (M_bool == 1){
    /* Self-sustained Mosquito population */
    double * y_SOL = (double *)calloc( K+1, sizeof(double) ); 
    
    stable_Solution_Free_Disease( P,  y_SOL );

    float * l_re = vector(1, K+1);
    float * l_im = vector(1, K+1);
    E_I_G_E_N___V_A_L_U_E___C_A_L_C_U_L_A_T_I_O_N ( y_SOL,  K,W, P, l_re, l_im ); 
    
    lambda_0 =  subdominant_Eigenvalue( l_re, l_im, K+1 ); 
							       
    free_vector(l_re, 1,K+1);
    free_vector(l_im, 1,K+1);
    free(y_SOL);

    R_0 = 1.0 + lambda_0;
  }

  return (R_0);
}

