#include "../Include/MODEL.h"

void B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M(Parameter_Table * P, 
					   double * y_0, double * y_1, double * y_2, 
					   int variable_code, double Epsi)
	
{
  int i;
  double H_0, H_1, H_2;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3, L, X, U, W, A, K;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);
    
  double * y_SOL_Lower = (double *)calloc( K+1, sizeof(double) ); 
  double * y_SOL_Upper = (double *)calloc( K+1, sizeof(double) );  
  double * y_SOL_Inter = (double *)calloc( K+1, sizeof(double) );   

  fixed_Points_All( P, y_SOL_Lower, y_SOL_Upper, y_SOL_Inter, 
		    Epsi );
  
  H_0 = total_Humans(y_SOL_Lower, P);
  H_1 = total_Humans(y_SOL_Inter, P);
  H_2 = total_Humans(y_SOL_Upper, P);
  
  printf("Total Humans: H_0 = %g\tH_1 = %g\tH_2 = %g\n", H_0, H_1, H_2);
  printf(" Variable Code... %d\t", variable_code);
  fprintf___variable(variable_code, stdout);

  if( H_0 > 50001.0 || H_1 > 50001.0 || H_2 == 50000.1){
    printf(" Stationary state violates total population. Fractions will\n");
    printf(" be greater than 1.\n");
    Press_Key();
  }

  double y__0 = definition_OutPut_Variables(variable_code, y_SOL_Lower, 0.0, P);
  double y__1 = definition_OutPut_Variables(variable_code, y_SOL_Inter, 0.0, P);
  double y__2 = definition_OutPut_Variables(variable_code, y_SOL_Upper, 0.0, P);

  *y_0 = y__0; *y_1 = y__1; *y_2 = y__2;
  
  printf(" y_LOWER = %g\ty_INTER = %g\ty_UPPER = %g\n", *y_0, *y_1, *y_2);
#if defined VERBOSE
  Press_Key();
#endif
  free( y_SOL_Lower ); free( y_SOL_Inter ); free( y_SOL_Upper );   
}
