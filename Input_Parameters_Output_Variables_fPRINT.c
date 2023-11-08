#include "./Include/MODEL.h"

void fprintf_Input_Parameters(FILE * fp, Parameter_Table * P)
{
  int i,k;

  fprintf(fp, "Input Parameter:\t\t[-Input Code\tDefault Value]\n");
  fprintf(fp, "------------------------------------------------\n");

    for(i=0; i < P->SUB_MODEL_PARAMETERS; i++){
      k = P->Index[i];
      fprintf(fp, "%d: %s:\t[ %s\t%g]\n", 
	      k, P->Name_Parameters[k], P->Code_Parameters[k], P->Default_Vector_Parameters[k] );
    }
  
}

void fprintf_Output_Variables(FILE *fp, Parameter_Table * P)
{
  int i,k;

  fprintf(fp, "Represented Output Variables:\n");
  fprintf(fp, "-----------------------------\n");
  
    for(i=0; i<P->SUB_OUTPUT_VARIABLES; i++){
      k = P->IO_VARIABLE_LIST[i];
      fprintf(fp, "%d: Variable Name: %s\n", k, P->Variable_Name[k]);
    }

}

