#include "../../Include/MODEL.h"

#define EPSILON 1.0E-10

extern gsl_rng * r;

int M_O_D_E_L( Parameter_Table * Table )
{
  int S; int E; int I; int R; int C; int S1; int I1; int S2; int I2; int S3; int I3;  
  int L; int X; int U; int W; 
  int A; 
  int K;
  double x; 

  int i,j,k, n;
  int I_Time, no_Patch;
  int Bad_Times;
  Parameter_Model * P;  

  I_Time    = Table->T->I_Time;

#if defined LXVnW
        Table->M_Fecundity = Table->M_a * Table->M_NoEggs;
#endif
#if defined XkVnW
        Table->M_Fecundity = Table->M_a * Table->M_NoEggs;
#endif
#if defined XVnW
        /* Total mosquito population constant */
        Table->M_Fecundity = Table->M_Delta;
#endif
#if defined XW
        /* Total mosquito population constant */
        Table->M_Fecundity = Table->M_Delta;
#endif

  P = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (Table, P);
  Table->P  = P;
  printf(" Parameter_Model structure has been correctly allocated and initiated\n");

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
  /* Code definitions and dimension of the state model variables */
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (Table, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  &L, &X, &U, &W, &A, &K);
  
  int MODEL_STATE_VARIABLES = K+1; 
  Table->MODEL_STATE_VARIABLES = MODEL_STATE_VARIABLES;
  /* BEGIN: Names for model state variables */
  // Table->Model_Variable_Name = (char **)malloc( MODEL_STATE_VARIABLES * sizeof(char *) );
  // for (i=0; i < MODEL_STATE_VARIABLES; i++){
  //    Table->Model_Variable_Name[i] = (char *)malloc( 100 * sizeof(char) );
  //    AssignLabel_to_Model_Variables(i, Table->Model_Variable_Name[i], Table);
  // }
  /*   END: Names for model state variables */
  Table->Vector_Model_Variables_Time_0 = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );
  Table->Vector_Model_Variables = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );
  Table->Vector_Model_Variables_Stationarity = (double *)calloc( MODEL_STATE_VARIABLES, 
								 sizeof(double) ); 
  Table->Vector_Model_Variables_MultiStability[0] = (double *)calloc( MODEL_STATE_VARIABLES, 
								   sizeof(double) ); 
  Table->Vector_Model_Variables_MultiStability[1] = (double *)calloc( MODEL_STATE_VARIABLES, 
								   sizeof(double) ); 
  Table->Vector_Model_Variables_MultiStability[2] = (double *)calloc( MODEL_STATE_VARIABLES, 
								   sizeof(double) ); 
     /* B E G I N : Calculation of Stationary Points */
       F_I_X_E_D___A_L_L___P_O_I_N_T_S( Table, 
					Table->Vector_Model_Variables_MultiStability[0],
					Table->Vector_Model_Variables_MultiStability[1], 
					Table->Vector_Model_Variables_MultiStability[2], 
					EPSILON );
       
       printf("Lower Fixed Point (model variables):\t");
       for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) \
	 printf("y_LOWER[%d] = %g\t", k, Table->Vector_Model_Variables_MultiStability[0][k]);
       printf("\n");
       printf("Inter Fixed Point (model variables):\t");
       for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) 
 	printf("y_INTER[%d] = %g\t", k, Table->Vector_Model_Variables_MultiStability[1][k]);
       printf("\n");
       printf("Upper Fixed Point (model variables):\t");
       for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) 
	 printf("y_UPPER[%d] = %g\t", k, Table->Vector_Model_Variables_MultiStability[2][k]);
       printf("\n");
     /*    E N D : --------------------------------- */

#if defined TIME_DEPENDENCE 
  printf(" Entering deterministic dynamics. Parameter time dependencies will be\n");
  printf(" activated according to command line/default values \n");
  printf(" TYPE_of_TIME_DEPENDENCE = %d\n", Table->TYPE_of_TIME_DEPENDENCE );
  // Table->K_Mean_Value   = AssignStructValue_to_VectorEntry(Table->Tr->Tr_Input_Parameter, Table);
  // Table->M_a_Mean_Value = AssignStructValue_to_VectorEntry(Table->Tr->Tr_Input_Parameter, Table);  
#else
  printf(" Entering deterministic dynamics. Parameter time dependencies will be\n");
  printf(" de-activated. No time dependencies.\n");
  assert (P->TYPE_of_TIME_DEPENDENCE == 0);
#endif
  
  D_E_T_E_R_M_I_N_I_S_T_I_C___T_I_M_E___D_Y_N_A_M_I_C_S( Table ) ;				    

#if defined CPGPLOT_REPRESENTATION 
  /* Notice that j = TIMES now, as expected, since the program is just out
     from the loop:
        for( j = 1; j < TIMES; j++ ) { ... }
  */
  // C_P_G___S_U_B___P_L_O_T_T_I_N_G ( Table, j, Table->CPG->x_Time, Table->CPG->y_Time );
  //  Parameter Table dependent costumized plotting is defined in ~/CPGPLOT/CPGPLOT_Parameter_Table/ files
  int TIMES           = Table->T->I_Time;
  int Input_Parameter = 25; /* The value of this model parameter appears in the title */
  C_P_G___S_U_B___P_L_O_T_T_I_N_G___C_U_S_T_O_M_I_Z_E_D___T_I_T_L_E ( Table, 
								      TIMES, 
								      Table->CPG->x_Time, 
								      Table->CPG->y_Time,  
								      Input_Parameter );
  /* B E G I N : P h a s e   d i a g r a m  ------------------------------------------*/
  /* int DEVICE_NUMBER = cpgopen("/XSERVE");                                          */
  /* if (DEVICE_NUMBER <= 0 ) {                                                       */
  /*   printf(" Graphic device cannot be opened\n");                                  */
  /*   exit(1);                                                                       */
  /* }                                                                                */
  /* cpgsubp(1, 1); /\* Subdivision of the window in panels.                          */
  /* 		    Automatic writing on consecutive panels                           */
  /* 		    in CPG__PANEL__X  x  CPG__PANEL__Y grid                           */
  /* 		 *\/                                                                  */
  /* if ( Table->CPG->CPG_SCALE_Y == 1 ) {                                            */
  /*   double H = (double)Table->POPULATION;                                          */
  /*   double w = Infectious_Mosquito_Steady_State( 1.0, Table )/H;                   */
  /*   Table->CPG->CPG_RANGE_X_0 = 0.0;                                               */
  /*   Table->CPG->CPG_RANGE_X_1 = w;                                                 */
  /* }                                                                                */
  /* C_P_G___P_H_A_S_E____D_I_A_G_R_A_M ( Table, 1, 0,                                */
  /* 				       TIMES, Table->CPG->y_Time );                   */
  /*     E N D : ---------------------------------------------------------------------*/
#endif
  free( Table->Vector_Model_Variables_Time_0);
  free( Table->Vector_Model_Variables );
  free( Table->Vector_Model_Variables_MultiStability[0] );
  free( Table->Vector_Model_Variables_MultiStability[1] );
  free( Table->Vector_Model_Variables_MultiStability[2] );
  free( Table->Vector_Model_Variables_Stationarity );

  free ( P );
  return(0);
}


  

  
