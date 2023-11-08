#include <MODEL.h>

#define EPSILON 1.e-10

// #define DYNAMIC___VERBOSE
int CONDITION_on_FREE_DISEASE ( double (*FREE_DISEASE)(Parameter_Table *), 
				Parameter_Table * P )
{
  /* This function returns 1 when the free disease equilibrium is unstable
     but mosquito population is established. This means the system necessary
     evolves to an endemic state, where the disease is also established
  */
  int bool_UNSTABLE; 

  bool_UNSTABLE = 0;
 
  if ( 1.0 == FREE_DISEASE( P ) ) {			
    
    bool_UNSTABLE = 1;    

  }
 return( bool_UNSTABLE ); 
}

double F_R_E_E___D_I_S_E_A_S_E___S_T_A_B_I_L_I_T_Y (  Parameter_Table * P )
{ 
  /*  Possible return values: 
       
      1.0 ---> Disease Free Equilibrium (with viable Mosquito population) 
                is unstable. 
      2.0 ---> Disease Free Equilibrium (with viable Mosquito population) 
                is stable "stable node". 
      3.0 ---> Disease Free Equilibrium (with viable Mosquito population) 
               is stable "stable damped oscillations". 
      0.0 ---> Otherwise.
  */  
  double Type_of_Regim;
  int H_bool, M_bool;
  gsl_vector * y_Sol;
  float * l_re;
  float * l_im;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3;
  int L, X, U, W;
  int A; 
  int K;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);

  y_Sol = gsl_vector_alloc(K+1);    gsl_vector_set_zero(y_Sol);
  
  Type_of_Regim = 0.0;

  /* Filtering for stationary solutions where a non-zero level
     of mosquito population is maitained */
  M_bool = Feasibility_Condition_M(P);
  
  if (M_bool == 1){
    
      /* Disease Endemic (lower, but non-trivial) equilibrium */
#if defined DYNAMIC___VERBOSE      
      gsl_vector_fprintf(stdout, y_Sol, "%g");
      //Press_Key();
#endif
      /* BEGIN : Building Disease Free State */
      stable_Solution_Free_Disease(P, y_Sol->data);
      /*   END : ----------------------------*/

      /* BEGIN : Calculating EigenValues */
      l_re = vector(1, K+1);     set_to_value_float_1_N(l_re, K+1, 0.0); 
      l_im = vector(1, K+1);     set_to_value_float_1_N(l_im, K+1, 0.0); 
      
      E_I_G_E_N___V_A_L_U_E___C_A_L_C_U_L_A_T_I_O_N ( y_Sol->data,  
						      K, W, P, l_re, l_im );
      
      /*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#if defined ODE_RESTRICTED_JACOBIAN
      int Sub_Dominant = 0;
#else 
      int Sub_Dominant = 1;
#endif
      Type_of_Regim = Type_of_Stability_of_Equilibria( l_re, l_im, 
						       K+1, Sub_Dominant );
      
      /* Possibilities: if( Type_of_Regim == 1.0 )        */
      /* Unstable point                                   */
      /*                else if ( Type_of_Regim == 2.0 )  */ 
      /* Stable equilibrium "stable node"         */
      /*                else if ( Type_of_Regim == 3.0 )  */
      /* Stable quilibrium "damped oscillations" */ 
	  
      free_vector(l_re, 1,K+1);
      free_vector(l_im, 1,K+1);
  }
  
  gsl_vector_free(y_Sol);
  
  return (Type_of_Regim);
}

double F_R_E_E___D_I_S_E_A_S_E___S_T_A_B_I_L_I_T_Y___U_P_P_E_R___S_O_L ( Parameter_Table * P )
{ 
  /*  Possible return values: 
       
      1.0 ---> Disease Free Equilibrium (with viable Mosquito population) 
               is unstable. Therefore, there is at least one disease endemic stationary state 
      
      0.0 ---> Otherwise.
  */  
  double Type_of_Regim;
  int H_bool, M_bool;
  float * l_re;
  float * l_im;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3;
  int L, X, U, W;
  int A; 
  int K;
  
  double w,y;
  
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);
  
  Type_of_Regim = 0.0;

  /* Filtering for stationary solutions where a non-zero level
     of mosquito population is maitained */
  M_bool = Feasibility_Condition_M(P);
  
  if (M_bool == 1){
    
      W_y_fixed_Points_Upper(P, EPSILON, &w, &y);

      if (w > 0.0 && y > 0.0) {
	Type_of_Regim = 1.0;
	/* There is at least one endemic stationary stationary state */ 
      }
  }
  
  return (Type_of_Regim);
}

