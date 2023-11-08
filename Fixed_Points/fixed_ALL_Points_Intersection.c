#include "../Include/MODEL.h"

#define No_of_POINTS_ACCURACY 10000

void F_I_X_E_D___A_L_L___P_O_I_N_T_S( Parameter_Table * P, 
				      double * y_SOL_Lower, 
				      double * y_SOL_Inter, 
				      double * y_SOL_Upper, 
				      double Epsi )
{
  int N = No_of_POINTS_ACCURACY;
  
  double * x_Data = (double *)calloc( N, sizeof(double) );
  double ** y     = (double **)calloc( 2, sizeof(double) );
  y[0]            = (double *)calloc( N, sizeof(double) );
  y[1]            = (double *)calloc( N, sizeof(double) );

  double x = I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M( P, N, x_Data, y[0], y[1] );

  // printf("Upper Fixed Point:\n");
  fixed_Point_Upper(P, y_SOL_Upper, Epsi);
  
  fixed_Points_Intersection( P, y_SOL_Lower, y_SOL_Upper, y_SOL_Inter, 
			     x_Data, y, N );
 
  free (x_Data); free (y[0]); free (y[1]); free(y); 
}
