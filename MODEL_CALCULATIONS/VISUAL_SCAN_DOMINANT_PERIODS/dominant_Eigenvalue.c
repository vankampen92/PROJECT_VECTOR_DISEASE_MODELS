#include <MODEL.h>

#define EPSILON 1.e-10

//#define DOMINANT_PERIOD_VERBOSE
double DOMINANT_EIGENVALUE ( Parameter_Table * P )
{

  double dominant_eigenvalue;

  float nr___x_min = P->nr___x_min;
  float nr___x_MAX = P->nr___x_MAX;

  int Status = D_O_M_I_N_A_N_T___E_I_G_E_N_V_A_L_U_E( P,
						      &dominant_eigenvalue,
						      nr___x_min,
						      nr___x_MAX );
  return( dominant_eigenvalue );
}

int D_O_M_I_N_A_N_T___E_I_G_E_N_V_A_L_U_E(  Parameter_Table * P,
					    double * value,
					    float xmin, float xmax )
{ 
  int M_bool, H_bool;
  gsl_vector * y_Sol;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3;
  int L, X, U, W, A; 
  int K;
  double w,y;
  double coherent_Number; 

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);
  
  y_Sol = gsl_vector_alloc(K+1);        gsl_vector_set_zero(y_Sol);
  
  ( * value ) = 0.0; coherent_Number = 0.0; 
 
  /* Filtering for stationary solutions where a non-zero level
     of mosquito population is maitained */
  M_bool = Feasibility_Condition_M(P);
  if (M_bool == 1){
    /* Mosquito self-sustained population */
    fixed_Points(P, y_Sol->data, EPSILON);
    w      = gsl_vector_get( y_Sol, W );
    y      = definition_OutPut_Variables(3, y_Sol->data, 0.0, P );
    H_bool = Feasibility_Condition_H( P, w, y ); 
    
    if( H_bool == 1 ) {
      /* Malaria Endemic Equilibrium */
      
#if defined DOMINANT_PERIOD_VERBOSE      
      gsl_vector_fprintf(stdout, y_Sol, "%g");
#endif

      /* BEGIN : Calculating EigenValues */
      float * l_re = vector(1, K+1);
      float * l_im = vector(1, K+1);
      
      E_I_G_E_N___V_A_L_U_E___C_A_L_C_U_L_A_T_I_O_N ( y_Sol->data,  K,W, P, l_re, l_im );  
      /*   END : Calculating Eigenvalues */ 
      
      /* If the DOMINANT_EIGENVALUE is passed to the compiler at compilation time,
	 then this function calculates only the dominant eigenvalue **/
      float D_re; float D_im;

      dominant_Eigenvalue( l_re, l_im, K+1, &D_re, &D_im);
	
      (* value) = D_re;	

      //(*dominant_Eigenvalue) = characteristic_Times__Coherence_No (l_re, l_im, K+1, 
      //                                                             &coherent_Number );

      free_vector(l_re, 1,K+1);
      free_vector(l_im, 1,K+1);
    }
  }
  
  gsl_vector_free(y_Sol);
  
  return (0);
}

