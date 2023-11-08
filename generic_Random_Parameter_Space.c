#include <MODEL.h>

extern gsl_rng * r;

double G_E_N_E_R_I_C___R_A_N_D_O_M___P_A_R_A_M_E_T_E_R___S_P_A_C_E( Parameter_Table * P, 
								    int Realizations,
								    double (* GENERIC_FUNCTION) (Parameter_Table *),
								    int (* CONDITION_on_GENERIC_FUNCTION) ( double (*)(Parameter_Table *),  Parameter_Table * ), 
								    double * X, double  * Y )
{
  double Frequency;
  double Value, Value_0, Value_1;
  int i,j, k,  n;
  double y_Data, x_Data;
  
  /* This function estimates the area of a subregion of the parameter space where
     certain condition is fulfilled. This condition involved the evaluation
     of a GENERIC_FUNCTON which depends on model parameters (Parameter_Table).
 
     This is done by random sampling the parameter space defined by the 
     Parameter Space Structure, in particular, index.Definitiion(...) and
     boundary(...) functions. The boundaries of the parameter domain under study 
     are defined in the corresponding  boundary_[TYPE_of_BOUNDARY].c file. 
     They can only be changed through changing that file and re-compiling again.

     The output of the probram generates two arrays X[] and Y[] containing the
     coordinates defining the subregion found. 
  */
  
  n = 0; 
  for( k = 0; k < Realizations; k++ ) {
  
    /* B E G I N : Defining a point/parameter set within Parameter Space */
    for (i=0; i < P->S->nPar; i++){
      
      j = P->S->I[i];
      
      Boundary(j, &Value_0, &Value_1);
      
      Value = Value_1 - gsl_rng_uniform(r) *  (Value_1 - Value_0);
      
      AssignVectorEntry_to_Structure(P, j, Value);

      if (j == 1) P->H_Birth = P->H_Delta;
      if (j == 2) P->H_Delta = P->H_Birth;

      if (P->S->nPar == 2) {
	if (i == 0) x_Data = Value;
	if (i == 1) y_Data = Value;
      }
    }
    
#if defined LXVnW
        P->M_Fecundity = P->M_a * P->M_NoEggs;
#endif
#if defined XkVnW
        P->M_Fecundity = P->M_a * P->M_NoEggs;
#endif
#if defined XVnW
        /* Total mosquito population constant */
        P->M_Fecundity = P->M_Delta;
#endif
#if defined XW
        /* Total mosquito population constant */
        P->M_Fecundity = P->M_Delta;
#endif
    /*     E N D : Defining a point/parameter set within Parameter Space */
	
    if( CONDITION_on_GENERIC_FUNCTION ( GENERIC_FUNCTION, P ) == 1 ){
      if (P->S->nPar == 2) {
       X[n]    = x_Data;   Y[n] = y_Data;
      }
#if defined VERBOSE	
       printf(" x = %g\ty = %g\n", x_Data, y_Data );
#endif 
      n++;
    }   
  }

  Frequency =  (double)n; 

  return( Frequency );
}

