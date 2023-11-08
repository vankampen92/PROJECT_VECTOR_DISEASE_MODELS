/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                                    MALARIA MODELS                         */
/*                                                                           */
/*                         Intersection Calculation of Fixed Points          */
/*                                                                           */
/*                                 David Alonso, 2006 (c)                    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../Include/MODEL.h"

double S_I_G_N___of___a___N_U_M_B_E_R (double y_D)
{
      double s;
      if( y_D > 0.0 )      s = 1.0;
      else if (y_D == 0.0) s = 0.0;
      else                 s = -1.0;
      return (s);
}

int fixed_Points_Intersection(Parameter_Table * P,
			       double *y_Sol_Lower, double *y_Sol_Upper, double *y_Sol_Inter,
			       double *x_Data, double **y, int N )
{
  int Lower_Root, Intermediate_Root, Upper_Root;
  int i;
  double W_l, y_l;
  double W_i, y_i;
  double W_u, y_u;
  double w, y_D, y_M, y_H;
  double s_0, s_1;

  int S, E, I, R, C, S1, I1, S2, I2, S3, I3, L, X, U, W, A, K;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P,
					    &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,
					    &L, &X, &U, &W, &A,
					    &K );
    for(i = 0; i<=W; i++){
        y_Sol_Inter[i] = y_Sol_Upper[i];
	y_Sol_Lower[i] = y_Sol_Upper[i];
    }

    W_u= y_Sol_Upper[W];

    w  = x_Data[0];
    y_M = y[0][0];
    y_H = y[1][0];

    y_D = y_H - y_M;
    s_0 = S_I_G_N___of___a___N_U_M_B_E_R (y_D);

    Lower_Root = 0; Intermediate_Root = 0; Upper_Root = 0;
    i = 1;
    while ( w < W_u && i < N ) {
      // assert(i < N);

      w  = x_Data[i];
      y_M = y[0][i];
      y_H = y[1][i];

      y_D = y_H - y_M;
      s_1 = S_I_G_N___of___a___N_U_M_B_E_R (y_D);

      //printf(" s_0 = %g\t\t s_1 = %g\n", s_0, s_1);

      if( s_1 * s_0 == -1.0 || s_1 * s_0 == 0.0 ) {
	if (Lower_Root == 0) {
	  /* Change of sign has occurred */
	  /* The lower root is:          */
	  W_l = x_Data[i-1];
	  y_l = y[0][i-1];
	  Lower_Root = 1;
	  stable_Solution(y_l, W_l, P, y_Sol_Lower);
	  // printf("Lower root found!\n");
	}
	else if (Intermediate_Root == 0) {
	  W_i = x_Data[i-1];
	  y_i = y[0][i-1];
	  Intermediate_Root = 1;
	  stable_Solution(y_i, W_i, P, y_Sol_Inter);
	  // printf("Intermediate root found!\n");
	}
	else if (Upper_Root == 0 ) {
	  W_u = x_Data[i-1];
	  y_u = y[0][i-1];
	  Upper_Root = 1;
	  stable_Solution(y_u, W_u, P, y_Sol_Upper);
	  // printf("Upper root found!\n");
	}
	else {
	  printf(" All roots have been found\n");
	  printf(" Mysterious extra change of sign has occurred\n");
	  printf(" The program will exit.");
	  exit(0);
	}
      }

      s_0 = s_1;
      i++;
      //w   = x_Data[i++];
    }

    if( Intermediate_Root == 1 && Upper_Root == 0 ){
     for(i = 0; i<=W; i++){
	y_Sol_Upper[i] = y_Sol_Inter[i];
	y_Sol_Inter[i] = y_Sol_Lower[i];
     }
     /* There is, in fact, only a lower and upper root */
     Lower_Root        = 1;
     Intermediate_Root = 0;
     Upper_Root        = 1;
    }

    return( Intermediate_Root );
}
