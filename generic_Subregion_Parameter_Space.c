#include <MODEL.h>

int G_E_N_E_R_I_C___S_U_B_R_E_G_I_O_N___P_A_R_A_M_E_T_E_R___S_P_A_C_E( Parameter_Table * P, 
								       int No_of_POINTS_1, int Input_Parameter_1,
								       int No_of_POINTS_2, int Input_Parameter_2,
								       double (* GENERIC_FUNCTION) (Parameter_Table *),
	                                                               int (* CONDITION_on_GENERIC_FUNCTION) ( double (*)(Parameter_Table *),  Parameter_Table * ), 
								       double * X, double  * Y, 
                                                                       int * No_of_POINTS )
{
  double Value, Value_0, Value_1;
  int j,k,  n;
  double y_Data, x_Data;
  
  /* This function calculates a subregion of the parameter space where
     certain condition is fulfilled. This condition involved the evaluation
     of a GENERIC_FUNCTON which depends on model parameters (Parameter_Table).
 
     This is done by scanning the parameter space defined by Input_Parameter_1 
     and Input_Parameter_2. The boundaries of the parameter domain under study 
     are defined in the corresponding  boundary_[TYPE_of_BOUNDARY].c file. 
     They can only be changed through changing that file and re-compiling again.

     Input parameters are labeled according to the input (model) parameters 
     labels as appear in all the assign_[].c functions. 

     The output of the probram generates two arrays X[] and Y[] containing the
     coordinates delimiting the subregion found. These are also saved in a 
     two-column (x,y) file called generic_subregion_parameter_space.dat. A 
     complementary 4-column (i,j,x,y) file containing the same information, 
     generic_subregion_parameter_space__i_j_x_y.dat, is also saved for representation 
     and checking purposes. 
  */
  
  FILE * fp = fopen ( "generic_subregion_parameter_space__i_j_x_y.dat", "w" );  
  n = 0; 
  for( k = 0; k < No_of_POINTS_2; k++ ) {
  
    Boundary(Input_Parameter_2, &Value_0, &Value_1);
    
    Value = Value_0 + k * (Value_1 - Value_0)/(double)(No_of_POINTS_2 - 1);
    y_Data = Value;

    AssignVectorEntry_to_Structure(P, Input_Parameter_2, Value);
    
    Boundary(Input_Parameter_1, &Value_0, &Value_1);

      for( j = 0; j < No_of_POINTS_1; j++ ){
	
	Value = Value_0 + j * (Value_1 - Value_0)/(double)(No_of_POINTS_1 - 1);
	x_Data = Value;

	AssignVectorEntry_to_Structure(P, Input_Parameter_1, Value);

	// assert(Input_Parameter_1 == 1 || Input_Parameter_1 == 2);
	// assert(Input_Parameter_2 == 1 || Input_Parameter_2 == 2);
	
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
	
	if( CONDITION_on_GENERIC_FUNCTION ( GENERIC_FUNCTION, P ) == 1 ){
	  X[n]    = x_Data;   Y[n] = y_Data;
	  n++;
#if defined VERBOSE	
	  printf(" x = %g\ty = %g\n", x_Data, y_Data );
#endif 
	  fprintf(fp, "%d\t%d\t%g\t%g\n", j,k, x_Data, y_Data);
	}
      }
  }
  fclose(fp);
  /* BEGIN : Saving to File  */
  FILE * fp_0 = fopen ( "generic_subregion_parameter_space.dat", "w" );  
  for( k = 0; k < n; k++ ) fprintf(fp_0, "%g\t%g\n", X[k], Y[k]);
  fclose(fp_0); ;
  /*   END : Saving to File */  
 
  ( * No_of_POINTS ) =  n; 

  return(0);
}

