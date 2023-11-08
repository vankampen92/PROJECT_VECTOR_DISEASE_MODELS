#include <MODEL.h>

#define EPSILON 1.e-10

//#define DYNAMIC___VERBOSE

double DYNAMIC_REGIM ( Parameter_Table * P )
{
 
  double Type_of_Regim;

  float nr___x_min = P->nr___x_min;
  float nr___x_MAX = P->nr___x_MAX;
  
  int Status = T_Y_P_E___O_F___D_Y_N_A_M_I_C___E_Q_U_I_L_I_B_R_I_A ( P,			
								     nr___x_min,
								     nr___x_MAX );
  Type_of_Regim = (double)Status;

  printf("%s", ".");
  return( Type_of_Regim ); 
}

int T_Y_P_E___O_F___D_Y_N_A_M_I_C___E_Q_U_I_L_I_B_R_I_A (  Parameter_Table * P,	
							   float xmin, float xmax)
{ 
   /* Dynamic Regims (possible return values): 
       0 ---> Disease Free Equilibrium (Mosquito Free Equilibrium)
       1 ---> Disease Free Equilibrium (with viable Mosquito population) R_0 < 1
       2 ---> Disease Endemic Equilibrium (node stable)
       3 ---> Disease Endemic Equilibrium (damped oscillations) 
       4 ---> Unstable local equilibrium 
       If there is coexistence, unless stated, we characterize the properties of the lower
       equilibrium
    */
  int LABEL;
  int Type_of_Regim;
  int H_bool, M_bool;
  gsl_vector * y_Sol;
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
  
  y_Sol = gsl_vector_alloc(K+1);        gsl_vector_set_zero(y_Sol);
  
  Type_of_Regim = 0;

  /* Filtering for stationary solutions where a non-zero level
     of mosquito population is maitained */
  
  M_bool = Feasibility_Condition_M(P);
  if (M_bool == 0){
    /* Mosquito free Equilibrium */
    Type_of_Regim = 0;
  }
  else{
    /* Mosquito self-sustained population 
       Possibility of malaria infection. Disease free equilibrium or not
       can be also assessed by R_0 the calculation. 
    */
    fixed_Points(P, y_Sol->data, EPSILON);
    w      = gsl_vector_get( y_Sol, W );
    y      = definition_OutPut_Variables(3, y_Sol->data, 0.0, P );
    H_bool = Feasibility_Condition_H( P, w, y );  /* See stable_Solution_[MODEL].c */

    if( H_bool == 0 ) {
      /* Disease Free Equilibrium,  R_0 < 1 */
      Type_of_Regim = 1;
    }
    else { 
      /* Disease Endemic (lower, but non-trivial) equilibrium */
#if defined DYNAMIC___VERBOSE      
      gsl_vector_fprintf(stdout, y_Sol, "%g");
#endif

      /* BEGIN : Calculating EigenValues */
      l_re = vector(1, K+1);     set_to_value_float_1_N(l_re, K+1, 0.0); 
      l_im = vector(1, K+1);     set_to_value_float_1_N(l_im, K+1, 0.0); 
      
      E_I_G_E_N___V_A_L_U_E___C_A_L_C_U_L_A_T_I_O_N ( y_Sol->data,  K, W, P, l_re, l_im );
      
      /*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#if defined ODE_RESTRICTED_JACOBIAN
      int Sub_Dominant = 0;
#else 
      int Sub_Dominant = 1;
#endif
      y = Type_of_Stability_of_Equilibria( l_re, l_im, K+1, Sub_Dominant );

      if( y == 1.0 ) {
	      /* Unstable point  */
	      Type_of_Regim = 4;
	      printf(" Unstable endemic equilibrium\n");
	      printf(" This is not expected here, since the lower endemic\n");
	      printf(" equilibrium calculated here is always a stable point\n");
	      printf(" when it exist.\n");
	      //exit(0);
      }
      else if ( y == 2.0 ) {
	      /* Stable endemic equilibrium (with one neutral mode) 
		 present "stable node" type of stability 
	      */
	      Type_of_Regim = 2;
      }
      else if ( y == 3.0 ) {
	      /* Stable endemic equilibrium (with one neutral mode) 
		 presenting "damped oscillations" type of stability 
	      */
	      Type_of_Regim = 3;
      }
      else {
	      printf(" Options in Type_of_Stability_of_Equilibria(...) should be: 1, 2, 3\n");
	      printf(" However, they seem to be ill-defined --- y = %g\n    (error message from file: dynamic_Regims.c)\n", y);
	      exit(0);
      } 
	  
      free_vector(l_re, 1,K+1);
      free_vector(l_im, 1,K+1);
    }
  }
  
  gsl_vector_free(y_Sol);
  
  return (Type_of_Regim);
}

