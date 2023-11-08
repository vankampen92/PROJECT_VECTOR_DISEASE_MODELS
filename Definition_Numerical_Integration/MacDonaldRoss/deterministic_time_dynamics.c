#include <MODEL.h>

/* 
   This driver produces the temporal evolution of a ODE 
   system. Sampling times are defined in Time structure 
   when this data structure is setup from scratch 
   at the main program.
   PGPLOTing is also possible at running time.

   This function calls the gsl-based ODE driver:

   int numerical_Integration_Driver( Parameter_Table * Table, int i, double * Time_Current );

   which is a generic common function which is always called 
   for any implemented particular model 
*/ 

void D_E_T_E_R_M_I_N_I_S_T_I_C___T_I_M_E___D_Y_N_A_M_I_C_S( Parameter_Table * Table )
{
  /* This function perform one stochastic realization (i-th),
     sample the system at times stored in Time->Time_Vector[],
     and save a file corresponding to this i-th stochastic
     realization. 
  */
  int i; int State; 

  FILE *FP; char file[50];
  int j, k, kk;
  int TIMES;
  Time_Control * Time;
  double Time_Current, value;

  Time         = Table->T;
  TIMES        = Table->T->I_Time;
  
    /* Each stochastic realization will be saved in a different file */
  file[0]='\0';  fitxer(file, "ODE_output", 0, ".dat"); FP = fopen(file, "w");
  
  /* BEGIN : Initial Conditions */
  int MODEL_STATE_VARIABLES = 2;    /* MacDonald and Ross Model */ 
  Table->MODEL_STATE_VARIABLES = MODEL_STATE_VARIABLES;

  /* BEGIN: Names for model state variables */
  // Table->Model_Variable_Name = (char **)malloc( MODEL_STATE_VARIABLES * sizeof(char *) );
  // for (i=0; i < MODEL_STATE_VARIABLES; i++){
  //    Table->Model_Variable_Name[i] = (char *)malloc( 100 * sizeof(char) );
  //    AssignLabel_to_Model_Variables(i, Table->Model_Variable_Name[i], Table);
  // }
  /*   END: Names for model state variables */

  Table->Vector_Model_Variables = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );
  Table->Vector_Model_Variables_Stationarity = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );  
  
  I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N( Table, 
										   Table->Vector_Model_Variables );
#if defined CPGPLOT_REPRESENTATION
  Table->CPG->x_Time[0]      = Time->Time_Vector[0];
#endif
  for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
    kk = Table->IO_VARIABLE_LIST[k]; 
    value = definition_OutPut_Variables(kk, Table->Vector_Model_Variables, Time->Time_Vector[0], Table);
#if defined CPGPLOT_REPRESENTATION
    Table->CPG->y_Time[k][0] = value;
#endif
    Table->Vector_Output_Variables[k] = value;
  }
  /*   END : Initial Conditions */
  
  Time_Current = Time->Time_Vector[0];
  
#if defined VERBOSE
    printf("t=%g", Time_Current); 
    for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
      printf("\ty[%d]=%g", k,Table->Vector_Output_Variables[k]); 
    }
    printf("\n");
#endif

    fprintf(FP,"%g", Time_Current); 
    for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
      fprintf(FP,"\t%g", Table->Vector_Output_Variables[k]);
    }
    fprintf(FP,"\n");
    printf(" Initiating Numerical Integration\n"); 

  for( j = 1; j < TIMES; j++ ) {
    /* This loop advances the system sequentially from 
       intitial time 0 to 1st time , ...,  from time (j-1) to j, and so on. 
       Note: When the system is frozen (FROZEN_SYSTEM = 1), then
       this loop does not advance the system any more 
    */
      State = numerical_Integration_Driver( Table, j, &Time_Current );
    
      if (State != GSL_SUCCESS) break;
    
#if defined CPGPLOT_REPRESENTATION
      Table->CPG->x_Time[j] = Time_Current;
#endif
      for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
	kk = Table->IO_VARIABLE_LIST[k]; 
	value = definition_OutPut_Variables(kk, Table->Vector_Model_Variables, Time_Current, Table);
#if defined CPGPLOT_REPRESENTATION      
	Table->CPG->y_Time[k][j] = value;
#endif  
	Table->Vector_Output_Variables[k] = value;
      }
      
#if defined CPGPLOT_REPRESENTATION    
      C_P_G___S_U_B___P_L_O_T_T_I_N_G ( Table, j, Table->CPG->x_Time, Table->CPG->y_Time );
#endif
      /* BEGIN : Writing a costumized file ... */
      fprintf(FP,"%g", Time_Current); 
      for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
	fprintf(FP,"\t%g", Table->Vector_Output_Variables[k]);
      }
      fprintf(FP,"\n");
#if defined VERBOSE
      printf("t=%g", Time_Current); 
      for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
	printf("\ty[%d]=%g", k,Table->Vector_Output_Variables[k]); 
      }
      printf("\n"); Press_Key();
#endif
      /*   END: Writing costumized file        */
  }/* go further to the next time            */
  fclose(FP);

  if (State != GSL_SUCCESS) printf(" Numerical integration failed at the %dth time\n", j);
  
  free( Table->Vector_Model_Variables );
  free( Table->Vector_Model_Variables_Stationarity );

  // for (i=0; i < MODEL_STATE_VARIABLES; i++){
  //   free (Table->Model_Variable_Name[i]);
  // }
  // free (Table->Model_Variable_Name);
}
