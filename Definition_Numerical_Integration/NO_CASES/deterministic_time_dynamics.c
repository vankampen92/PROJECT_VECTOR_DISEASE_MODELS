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
void Update_Time_Dependence ( int Time_Dependence, double Time_Current, Parameter_Table * Table)
{
        if (Time_Dependence == 1 ){
        /* ... or sinusoidal (of any possible kind of) forcing in some parameters */
        //M_Fecundity = Fecundity_Mosquito_00(t, P); 
        //L_Devel     = L_Devel_Mosquito(t, P); 
#if defined CASES_33
        Table->K_p        = K_p_Precipitation(Time_Current, Table);
#else
        Table->K_0        = K_Mosquito(Time_Current, Table);
#endif
        }
        else if (Time_Dependence == 2) {
#if defined CASES_33
        Table->K_p          = K_p_Precipitation(Time_Current, Table);
#else
        Table->K_0          = Table->K_Mean_Value;

        Table->M_a          = Sinusoidal_Oscillation(Time_Current,
                                                 Table->K_Seasonal_Intensity,
                                                 Table->M_a_Mean_Value,
                                                 0.0,
                                                 Table->K_Period);
        Table->M_Fecundity  = Table->M_a * Table->M_NoEggs;
#endif
        }
        else if (Time_Dependence == 3) {
#if defined CASES_33
        Table->K_p        = K_p_Precipitation(Time_Current, Table);
#else
        Table->K_0          = K_Mosquito(Time_Current, Table);

        Table->M_a          = Sinusoidal_Oscillation(Time_Current,
                                                 Table->K_Seasonal_Intensity,
                                                 Table->M_a_Mean_Value,
                                                 0.0,
                                                 Table->K_Period);
        Table->M_Fecundity  = Table->M_a * Table->M_NoEggs;
#endif
        } 
        else { 
#if defined VERBOSE
	printf(" No sinusoidal forcing! ");
        printf(" Time_Dependence = %d\n", Time_Dependence);
        printf(" HUMANS: birth rate = %g\t death rate = %g\n", Table->H_Birth, Table->H_Delta);  
	printf(" Total human population = %g\n", Table->H);
#endif
        }
} 

void D_E_T_E_R_M_I_N_I_S_T_I_C___T_I_M_E___D_Y_N_A_M_I_C_S( Parameter_Table * Table, 
							    int Time_Dependence )
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
  
  /* Each stochastic realization may be saved in a different file */
  file[0]='\0';  fitxer(file, "ODE_output_", 0, ".dat"); FP = fopen(file, "w");
  
  /* BEGIN : Initial Conditions * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
  // printf(" Before I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N (...)\n"); 
     I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N( Table, 
										      Table->Vector_Model_Variables );  
  // printf(" After I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N (...). Initial Conditions:  "); 
#if defined CASES_33
     /* A is the label of accumulated cases between sampling points */
     Table->Vector_Model_Variables[A] = 0.0;
#endif 
     for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) { 
       // printf("y[%d] = %g\t", k, Table->Vector_Model_Variables[k]);
       Table->Vector_Model_Variables_Time_0[k] = Table->Vector_Model_Variables[k];
     }
     // printf("\n");
     // Press_Key();
  
     Time_Current = Time->Time_Vector[0];
     Update_Time_Dependence (Time_Dependence, Time_Current, Table );

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
  
#if defined APPLYING_TREND
  A_P_P_L_Y_I_N_G___T_R_E_N_D( Table, Time_Current );
#endif

#if defined VERBOSE
    printf("t=%g", Time_Current); 
    for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
      printf("\ty[%d]=%g", k,Table->Vector_Output_Variables[k]); 
    }
    printf("\n");
#endif

    //fprintf(FP,"%g", Time_Current); 
    fprintf(FP,"%g", Time_Current/360.0); 
    for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
      fprintf(FP,"\t%g", Table->Vector_Output_Variables[k]);
    }
    fprintf(FP,"\n");

    //printf(" Initiating Numerical Integration\n"); 
  for( j = 1; j < TIMES; j++ ) {
    /* This loop advances the system sequentially from 
       intitial time 0 to 1st time , ...,  from time (j-1) to j, and so on. 
       Note: When the system is frozen (FROZEN_SYSTEM = 1), then
       this loop does not advance the system any more 
    */
#if defined CASES_33
      Table->Vector_Model_Variables[A] = 0.0;
#endif 
      Update_Time_Dependence (Time_Dependence, Time_Current, Table );
#if defined APPLYING_TREND
      A_P_P_L_Y_I_N_G___T_R_E_N_D(  Table, Time_Current );
#endif 
      State = numerical_Integration_Driver( Table, j, &Time_Current );
      
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
      /*   END: Writing costumized file        */

#if defined VERBOSE
      printf("t=%g", Time_Current); 
      for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
	printf("\ty[%d]=%g", k,Table->Vector_Output_Variables[k]); 
      }
      printf("\n"); Press_Key();
#endif
      //Press_Key();
  }/* ------> go further to the next time step */
  fclose(FP);

  if (State != GSL_SUCCESS) printf(" Numerical integration failed at the %dth time\n", j);
  // for (i=0; i < MODEL_STATE_VARIABLES; i++){
  //   free (Table->Model_Variable_Name[i]);
  // }
  // free (Table->Model_Variable_Name);
}

