#include "../Include/MODEL.h"

#define No_of_POINTS_ACCURACY 50000

// void B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M___I_N_T_E_R_S_E_C_T_I_O_N( Parameter_Table * P, 
// 								      double * y_0, 
// 								      double * y_1, 
//								      double * y_2, 
//								      int variable_code,
//								      double Epsi )

void B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M( Parameter_Table * P, 
					    double * y_0, 
					    double * y_1, 
					    double * y_2, 
					    int variable_code,
					    double Epsi )
{
  
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3, L, X, U, W, A, K;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);
  int N = No_of_POINTS_ACCURACY;
  
  double * x_Data = (double *)calloc( N, sizeof(double) );
  double ** y     = (double **)calloc( 2, sizeof(double) );
  y[0]            = (double *)calloc( N, sizeof(double) );
  y[1]            = (double *)calloc( N, sizeof(double) );

  double x = I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M( P, N, x_Data, y[0], y[1] );
  /*
  char * p_DUMMY = strcat( Title_In, "  I n t e r s e c t i o n:  ");
         p_DUMMY = strcat( Title_In, P->Name_Parameters[Input_Parameter] );
	 p_DUMMY = strcat( Title_In, "  =  ");
	 doubletochar( Value, Number );
	 p_DUMMY = strcat( Title_In, Number);
  */
  //I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M___S_I_N_G_L_E___P_L_O_T ( P, N, x_Data, y, 
  //   									  "C u r v e   I n t e r s e c t i o n s" );
  //Press_Key();
   
  double * y_SOL_Lower = (double *)calloc( K+1, sizeof(double) ); 
  double * y_SOL_Upper = (double *)calloc( K+1, sizeof(double) );  
  double * y_SOL_Inter = (double *)calloc( K+1, sizeof(double) );  

  printf("Upper Fixed Point:\n");
  fixed_Point_Upper(P, y_SOL_Upper, Epsi);
  
  fixed_Points_Intersection( P, y_SOL_Lower, y_SOL_Upper, y_SOL_Inter, 
			     x_Data, y, N );
 
  double y__0 = definition_OutPut_Variables(variable_code, y_SOL_Lower, 0.0, P);
  double y__1 = definition_OutPut_Variables(variable_code, y_SOL_Inter, 0.0, P);
  double y__2 = definition_OutPut_Variables(variable_code, y_SOL_Upper, 0.0, P);


  *y_0 = y__0; *y_1 = y__1; *y_2 = y__2;

  free (x_Data); free (y[0]); free (y[1]); free(y); 
  free( y_SOL_Lower ); free( y_SOL_Inter ); free( y_SOL_Upper );   
}
