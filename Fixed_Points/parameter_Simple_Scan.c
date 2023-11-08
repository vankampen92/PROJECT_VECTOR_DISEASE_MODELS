#include <MODEL.h>

int P_A_R_A_M_E_T_E_R___S_I_M_P_L_E___S_C_A_N( Parameter_Table * P, 
					       int No_of_POINTS, 
					       int Output_Variable, 
					       int Input_Parameter ) 
{
  double Value, Value_0, Value_1;
  int i,j, k;
  
  /* This function scan one parameter between its min value and MAX value in 
     boundary_[BOUNDARY_TYPE].c evaluating, for each value, a function that
     depends on model parameters, while all the other parameters are
     kept constant.
    
     The function to scan is defined in definition_Output_Variables.c.
 
     Input parameter is the label of any given input (model) parameters from
     the list appearing in all the assing_[].c functions.

     A file named: "scan_OUTPUT_VARIABLE_[Output_Variable].dat" is saved. 
  */
  if( Output_Variable != 19 && Output_Variable != 20 ) {
    printf(" Wrong Output Variable!!!\n");
    printf("   if( Output_Variable != 19 && Output_Variable != 20 ) { \n");
    printf("   The program will exit!\n");
    exit(0);
  }
  /* BEGIN : Allocating memory for saving data * * * * * * * * * * * * */
  double * y_SOL;
  
  double * y_BIF  = (double  *)malloc( No_of_POINTS * sizeof(double) );
  
  double * x_Data  = (double *)malloc(No_of_POINTS * sizeof(double) ); 
  /*   END : Allocating memory for saving dynamical data * * * * * */

  Boundary(Input_Parameter, &Value_0, &Value_1);
    
  for( j = 0; j < No_of_POINTS; j++ ){
      
    Value = Value_0 + j * (Value_1 - Value_0)/(double)(No_of_POINTS - 1);
    
    AssignVectorEntry_to_Structure(P, Input_Parameter, Value);
    P->M_Fecundity = P->M_a * P->M_NoEggs;

    x_Data[j] = Value;
    
    y_BIF[j]  = definition_OutPut_Variables(Output_Variable, y_SOL, 0.0, P);
    
    printf(" y_Value = %g\n", y_BIF[j]);
  }
    
    /* BEGIN : Saving to File  */
  Saving_to_File_double("scan_OUTPUT_VARIABLE_", x_Data, y_BIF, No_of_POINTS, Output_Variable); 
    /*   END : Saving to File */
 
  /* BEGIN : Freeing previous allocated memory */
  free (y_BIF);

  free(x_Data); 
  /*   END : End freeing allocated memory */

  return(0);
}

