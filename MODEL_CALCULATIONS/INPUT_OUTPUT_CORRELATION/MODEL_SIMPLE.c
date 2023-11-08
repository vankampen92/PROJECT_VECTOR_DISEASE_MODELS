#include "../../Include/MODEL.h"

/*
    D E T E R M I N I S T I C   T I M E   D Y N A M I C S 
*/
#define EPSILON 1.0E-8

int M_O_D_E_L___S_I_M_P_L_E ( Parameter_Table * Table )
{
  int S; int E; int I; int R; int C; int S1; int I1; int S2; int I2; int S3; int I3;
  int L; int X; int U; int W;
  int A;
  int K;

  int Time_Dependence;
  double corr;
  int i,j,k, n;
  int I_Time, no_Patch;
  int Bad_Times;
  Parameter_Model * P;  

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
	
  I_Time    = Table->T->I_Time;

  P = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (Table, P);
  Table->P  = P;
  printf(" Parameter_Model structure has been correctly allocated and initiated\n");

  /* B E G I N : -------------------------------------------------------------------------------*/
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
       for (k=0; k < Table->MODEL_STATE_VARIABLES; k++)		\
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
  /*     E N D : -------------------------------------------------------------------------------*/

  printf("Entering Determinisitic Time Dynamics...\n");
  //Press_Key();
  
  D_E_T_E_R_M_I_N_I_S_T_I_C___T_I_M_E___D_Y_N_A_M_I_C_S( Table ) ;
  
  free( Table->Vector_Model_Variables_Time_0);
  free( Table->Vector_Model_Variables );
  free( Table->Vector_Model_Variables_MultiStability[0] );
  free( Table->Vector_Model_Variables_MultiStability[1] );
  free( Table->Vector_Model_Variables_MultiStability[2] );
  free( Table->Vector_Model_Variables_Stationarity );
  free ( P );

  return(0);
}



  
