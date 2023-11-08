#include <MODEL.h>

#define EPSILON 1.e-7

#if defined VERBOSE
#define DOMINANT_PERIOD_VERBOSE
#endif 

double COHERENCE_NUMBER ( Parameter_Table * P )
{

  double dominant_period;
  double coherence_number;

  float nr___x_min = P->nr___x_min;
  float nr___x_MAX = P->nr___x_MAX;

  int Status = D_O_M_I_N_A_N_T___P_E_R_I_O_D___C_O_H_E_R_E_N_T___N_U_M_B_E_R( P,
                                                                              &dominant_period,
                                                                              &coherence_number,
                                                                              nr___x_min,
                                                                              nr___x_MAX );
  int LABEL  = 0;
  if (LABEL == 1)
     return( dominant_period );
  else
     return( coherence_number );
}


double DOMINANT_PERIOD ( Parameter_Table * P )
{
 
  double dominant_period;
  double coherence_number;

  float nr___x_min = P->nr___x_min;
  float nr___x_MAX = P->nr___x_MAX;
  
  int Status = D_O_M_I_N_A_N_T___P_E_R_I_O_D___C_O_H_E_R_E_N_T___N_U_M_B_E_R( P,			
									      &dominant_period,
									      &coherence_number,
									      nr___x_min,
									      nr___x_MAX );
  int LABEL  = 1;
  if (LABEL == 1) 
     return( dominant_period );
  else  
     return( coherence_number ); 
}

int D_O_M_I_N_A_N_T___P_E_R_I_O_D___C_O_H_E_R_E_N_T___N_U_M_B_E_R(  Parameter_Table * P,
								    double * dominant_Period,
								    double * coherent_Number, 
								    float xmin, float xmax )
{ 
  int M_bool, H_bool;
  gsl_vector * y_Sol;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3;
  int L, X, U, W, A; 
  int K;
  double w,y;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);
  
  y_Sol = gsl_vector_alloc(K+1);        gsl_vector_set_zero(y_Sol);
  
  ( * dominant_Period ) = 0.0; ( * coherent_Number ) = 0.0; 
 
  /* Filtering for stationary solutions where a non-zero level
     of mosquito population is maitained */
  M_bool = Feasibility_Condition_M(P);

  if (M_bool == 1){
    /* Mosquito self-sustained population */
    fixed_Points(P, y_Sol->data, EPSILON);

#if defined DOMINANT_PERIOD_VERBOSE
    /* Malaria Endemic Equilibrium */
    gsl_vector_fprintf(stdout, y_Sol, "%g");
#endif
    w      = gsl_vector_get( y_Sol, W );
    y      = definition_OutPut_Variables(3, y_Sol->data, 0.0, P );
    
    H_bool = Feasibility_Condition_H( P, w, y ); 
    
    if( H_bool == 1 ) {
      /* BEGIN : Calculating EigenValues */
      float * l_re = vector(1, K+1);
      float * l_im = vector(1, K+1);
      
      E_I_G_E_N___V_A_L_U_E___C_A_L_C_U_L_A_T_I_O_N ( y_Sol->data,  K,W, P, l_re, l_im );  
      /*   END : Calculating Eigenvalues */ 

      /* If the DOMINANT_PERIOD is passed to the compiler at compilation time,
	 then this function calculates both the dominant period in years and 
	 the coherent number */

#if defined ODE_RESTRICTED_JACOBIAN
      int Sub_Dominant = 0;
#else
      int Sub_Dominant = 1;
#endif
      (*dominant_Period) = Dominant_Period__Coherence_Number (l_re, l_im, K+1, 
      							      coherent_Number, Sub_Dominant );
    
      free_vector(l_re, 1,K+1);
      free_vector(l_im, 1,K+1);
    }
  }

  if( M_bool == 0 ) printf("M=0 "); // Non-feasible Mosquito Popualtion
  if( H_bool == 0 ) printf("H=0 "); // Disease Free Equilibrium

  
  gsl_vector_free(y_Sol);
  
  return (0);
}

