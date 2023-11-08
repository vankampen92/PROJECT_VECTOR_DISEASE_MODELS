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
void Update_Time_Dependence ( int TYPE_of_TIME_DEPENDENCE,
			      double Time_Current, Parameter_Table * Table)
{
  /* Time dependence is some parameters through "Sinusoidal Periodic Forcing":

        value = Mean_Value * ( 1.0 + Seasonal_Intensity * sin(2.0 * M_PI*t / Period) ) 

  */
  if (TYPE_of_TIME_DEPENDENCE == 1 ){
        /* ... or sinusoidal (of any possible kind of) forcing in some parameters */
	  Table->K_0        = K_Mosquito(Time_Current, Table);
  }
  else if (TYPE_of_TIME_DEPENDENCE == 2) {
	  Table->M_a          = Sinusoidal_Oscillation(Time_Current,
						       Table->K_Seasonal_Intensity,
						       Table->M_a_Mean_Value,
						       Table->K_Sigma,
						       Table->K_Period);
	  Table->M_Fecundity  = Table->M_a * Table->M_NoEggs;
  }
  else if (TYPE_of_TIME_DEPENDENCE == 3) {
	  Table->K_0          = K_Mosquito(Time_Current, Table);

	  Table->M_a          = Sinusoidal_Oscillation(Time_Current,
						       Table->K_Seasonal_Intensity,
						       Table->M_a_Mean_Value,
						       Table->K_Sigma,
						       Table->K_Period);
	  Table->M_Fecundity  = Table->M_a * Table->M_NoEggs;
  }
  else if (TYPE_of_TIME_DEPENDENCE == 4) {
	  Table->Temp         = Sinusoidal_Oscillation(Time_Current,
						       Table->K_Seasonal_Intensity,
						       Table->Temp_Mean_Value,
						       Table->K_Sigma,
						       Table->K_Period);
	  values_TempDependency(Table->Temp, Table);
  } 
  else { 
	  printf(" No time dependence! ");
	  printf(" TYPE_of_TIME_DEPENDENCE = %d\n", TYPE_of_TIME_DEPENDENCE);
	  printf(" Range of Permited Values {1, 2, 3, 4}\n"); 
	  printf(" HUMANS: birth rate = %g\t death rate = %g\n", Table->H_Birth, Table->H_Delta);  
	  printf(" Total human population = %g\n", Table->H);
	  exit(0); 
  }
} 

void D_E_T_E_R_M_I_N_I_S_T_I_C___T_I_M_E___D_Y_N_A_M_I_C_S( Parameter_Table * Table )
{
  /* This function perform one stochastic realization (i-th),
     sample the system at times stored in Time->Time_Vector[],
     and save a file corresponding to this i-th stochastic
     realization. 

     This function makes two essential calls:

     1. I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N (...),
     which sets up initial conditions. In turn, this function, depending on the input parameter
     TYPE_of_INITIAL_CONDITION, sets up initial consitions in one way or another, by calling 
     the functions: 
     . Human_Population_Initial_Condition_from_Parameter_Table(P, y_INI);
     . Human_Population_Random_Initial_Condition(P, y_INI);
     . Mosquito_Steady_State_Initial_Condition( P, y_INI );
     . fixed_Points(P, y_INI, EPSILON);
     . stable_Solution_Free_Disease(P, y_INI);
     
     2. numerical_Integration_Driver(...), which performs the actual numerical integration

     In addition, it depends on calling the following functions:
     . A_P_P_L_Y_I_N_G___T_R_E_N_D (...), which, in turn, calls Update_Time_Dependence(...), 
     which performs the update of parameter table depending on the value of the input parameter 
     TYPE_of_TIME_DEPENDENCE
     . definition_OutPut_Variables(...)
  */
  int i; int State; 
  
  FILE *FP; char file[50];
  int j, k, kk;
  int TIMES;
  Time_Control * Time;
  double Time_Current, value;

  Time         = Table->T;
  TIMES        = Table->T->I_Time;
  
  /* Each stochastic realization may be saved in a different file */
  file[0]='\0';  fitxer(file, "ODE_output_", 0, ".dat"); FP = fopen(file, "w");
  
  /* BEGIN : Initial Conditions * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
  // printf(" Before I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N (...)\n"); 
  I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N( Table, 
										      Table->Vector_Model_Variables );  
  // printf(" After I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N (...). Initial Conditions:  "); 

  for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) { 
       // printf("y[%d] = %g\t", k, Table->Vector_Model_Variables[k]);
    Table->Vector_Model_Variables_Time_0[k] = Table->Vector_Model_Variables[k];
  }
     // printf("\n");
     // Press_Key();

  Time_Current = Time->Time_Vector[0];
     
  if (Table->TYPE_of_TIME_DEPENDENCE > 0) {
    /* Update_Time_Dependence (Table->TYPE_of_TIME_DEPENDENCE, Time_Current, Table ); */
    A_P_P_L_Y_I_N_G___T_R_E_N_D( Table, Time_Current );
  }
     
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
  /*   END : Initial Conditions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  
#if defined VERBOSE
  printf("t=%g", Time_Current); 
  for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
    printf("\ty[%d]=%g", k,Table->Vector_Output_Variables[k]); 
  }
  printf("\n");
#endif

  /* BEGIN : Writing a costumized file ... */
    //fprintf(FP,"%g", Time_Current); 
  fprintf(FP,"%g", Time_Current/360.0); 
  for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
    fprintf(FP,"\t%g", Table->Vector_Output_Variables[k]);
  }
  fprintf(FP,"\n");
  /*   END: Writing costumized file        */
  
    //printf(" Initiating Numerical Integration\n"); 
  for( j = 1; j < TIMES; j++ ) {
    /* This loop advances the system sequentially from 
       intitial time 0 to 1st time , ...,  from time (j-1) to j, and so on. 
       Note: When the system is frozen (FROZEN_SYSTEM = 1), then
       this loop does not advance the system any more 
    */
    if (Table->TYPE_of_TIME_DEPENDENCE > 0) {
      /* Update_Time_Dependence (Table->TYPE_of_TIME_DEPENDENCE, Time_Current, Table ); */
      A_P_P_L_Y_I_N_G___T_R_E_N_D( Table, Time_Current );
    }
/*-------------------------------------------------------------------*/      
/* B E G I N : 
 *     CENTRAL POINT HERE: Numerical Integration up to the next time 
 */
    State = numerical_Integration_Driver( Table, j, &Time_Current );
/*     E N D 
/*-------------------------------------------------------------------*/            
 
    if (State != GSL_SUCCESS) break;
    
#if defined CPGPLOT_REPRESENTATION
    Table->CPG->x_Time[j] = Time_Current;
#endif
    for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
      kk = Table->IO_VARIABLE_LIST[k]; 
      value = definition_OutPut_Variables(kk, Table->Vector_Model_Variables, 
					  Time_Current, Table);
#if defined CPGPLOT_REPRESENTATION      
      Table->CPG->y_Time[k][j] = value;
#endif  
      Table->Vector_Output_Variables[k] = value;
    }
#if defined CPGPLOT_REPRESENTATION
      /* This should be only activated in case we want to animate ODE time evolution by 
	 representing the solution as time progresses                                       */
      // C_P_G___S_U_B___P_L_O_T_T_I_N_G ( Table, j, Table->CPG->x_Time, Table->CPG->y_Time );
      // C_P_G___P_H_A_S_E____D_I_A_G_R_A_M ( Table, 0, 1, j,  
      //                                      Table->CPG->y_Time );
#endif
    /* BEGIN : Writing a costumized file ... */
    fprintf(FP,"%g", Time_Current/360.0); 
      //fprintf(FP,"%g", Time_Current); 
    for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
      fprintf(FP,"\t%g", Table->Vector_Output_Variables[k]);
    }
    fprintf(FP,"\n");

    printf("t=%g\n", Time_Current); 
    char * Label = (char *)calloc( 20, sizeof(char) );
    for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) {
      AssignLabel_to_Model_Variables(k, Label, Table);
      printf("y[%s] = %g\n", Label, Table->Vector_Model_Variables[k]);
    }
    printf("\n");
    free(Label);
    /*   END: Writing costumized file        */

#if defined VERBOSE
      printf("t = %g\n", Current_Time); 
      for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
	printf("\ty[%d]=%g", k,Table->Vector_Output_Variables[k]); 
      }
      printf("\n"); Press_Key();
#endif
      //Press_Key();
  }/* ------> go further to the next time step */
  fclose(FP);

  if (State != GSL_SUCCESS) printf(" Numerical integration failed at the %dth time\n", j);
}
