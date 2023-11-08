/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                                    MALARIA MODELS                         */
/*                                                                           */
/*                         Recursive Calculation of Fixed Points             */
/*                                                                           */
/*                                 David Alonso, 2006 (c)                    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../Include/MODEL.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>

void fixed_Points_All(Parameter_Table * P, double *y_Sol_Lower, double *y_Sol_Upper, double *y_Sol_Inter,
		      double EPSILON)
{
  int i;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3, L, X, U, W, A, K;
  double W_l, y_l;
  double W_u, y_u;
  double w, y_C, y_I;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P,
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,
					   &L, &X, &U, &W, &A,
					   &K);

  if (Feasibility_Condition_M(P) == 1) {

    printf("Lower Fixed Point...\n");
    fixed_Point_Lower(P, y_Sol_Lower, EPSILON);

    printf("Upper Fixed Point...\n");
    fixed_Point_Upper(P, y_Sol_Upper, EPSILON);

    printf("Intermediate Fixed Points...\n");

    w = y_Sol_Lower[W];
    W_l = w;
    w = y_Sol_Upper[W];
    W_u = w;

    if (P->TYPE_of_MODEL >= 11 && P->TYPE_of_MODEL <= 14 ){
      y_C = y_Sol_Lower[C];
      y_I = y_Sol_Lower[I];
      y_l = (y_C + y_I)/P->H;

      y_C = y_Sol_Upper[C];
      y_I = y_Sol_Upper[I];
      y_u = (y_C + y_I)/P->H;
    }
    else if (P->TYPE_of_MODEL >= 21 && P->TYPE_of_MODEL <= 24 ){
      y_I = y_Sol_Lower[I];
      y_l = y_I;

      y_I = y_Sol_Upper[I];
      y_u = y_I;
    }
    else if (P->TYPE_of_MODEL >= 31 && P->TYPE_of_MODEL <= 34 ){
      y_I = y_Sol_Lower[I];
      y_l = y_I;

      y_I = y_Sol_Upper[I];
      y_u = y_I;
    }
    else if (P->TYPE_of_MODEL >= 41 && P->TYPE_of_MODEL <= 44 ){
      y_I = y_Sol_Lower[I];
      y_l = (y_I)/P->H;

      y_I = y_Sol_Upper[I];
      y_u = (y_I)/P->H;
    }
    else if (P->TYPE_of_MODEL >= 51 && P->TYPE_of_MODEL <= 54 ){ /* SnInR models */
      y_I = y_Sol_Lower[I1]+P->H_mM_c*y_Sol_Lower[I2]+pow(P->H_mM_c,2)*y_Sol_Lower[I2];
      y_l = (y_I)/P->H; /* fraction of effective infectious humans (on lower branch) */

      y_I = y_Sol_Upper[I1]+P->H_mM_c*y_Sol_Upper[I2]+pow(P->H_mM_c,2)*y_Sol_Upper[I2];
      y_u = (y_I)/P->H;
    }
    else {
      printf(" Error in fixed_Points_ALL.c. The variable TYPE_of_MODEL is taking an out-of-range value\n");
      printf(" TYPE_of_MODEL = %d. Only 11, 12, 13, 14,  21, 22, 23, 24,  31, 32, 33, 34,  41, 42, 43, 44, and 51 are permitted values\n", P->TYPE_of_MODEL);
      exit(0);
    }

    printf(" Difference between lower and upper solution (1000.0 * EPSILON = %g)...\n", 1000.0 * EPSILON);
    printf(" Infectious mosquitoes:         Lower: %g\tUpper: %g\tDifference: %g\n", W_l, W_u, fabs(W_l - W_u));
    printf(" Fraction of infectious humans: Lower: %g\tUpper: %g\tDifference: %g\n", y_l, y_u, fabs(y_l - y_u));

    if (fabs(W_u - W_l) > 1000.0 * EPSILON || fabs(y_u - y_l) > 1000.0 * EPSILON){

      fixed_Point_Intermediate(P, W_l,W_u, y_l,y_u, y_Sol_Inter, EPSILON);

    }
    else{
      for(i = 0; i<=W; i++){
	y_Sol_Inter[i] = y_Sol_Lower[i];
      }
    }
  }

  else{

    /* All three solutions are actually the same (free disease equilibrium) */
    printf("Free-disease equilibrium (non-viable mosquito population)\n");
    stable_Solution_Free_Disease(P, y_Sol_Lower);
    stable_Solution_Free_Disease(P, y_Sol_Inter);
    stable_Solution_Free_Disease(P, y_Sol_Upper);

  }
}

void fixed_Point_Lower(Parameter_Table *P, double *y_Sol, double EPSILON)
{
  double W, y;

  W_y_fixed_Points_Lower(P, EPSILON, &W, &y);

  stable_Solution(y, W, P, y_Sol);

}

void fixed_Point_Upper(Parameter_Table *P, double *y_Sol, double EPSILON)
{
  double W, y;

  W_y_fixed_Points_Upper(P, EPSILON, &W, &y);

  stable_Solution(y, W, P, y_Sol);

}

void fixed_Point_Intermediate(Parameter_Table *P,
			      double W_l,double W_u, double y_l,double y_u,
			      double *y_Sol, double EPSILON)
{
  double W, y;

  W_y_fixed_Points_Intermediate(P, W_l,W_u, y_l,y_u,
				EPSILON, &W, &y);

  stable_Solution(y, W, P, y_Sol);

}

void W_y_fixed_Points_Intermediate(Parameter_Table *P,
				   double W_l,double W_u, double y_l,double y_u,
				   double EPSILON, double *W, double *y)
{
  double y_1, W_1;
  double y_0, W_0;
  int No_Count;

  /* Upper Solution */
  (*W) = W_u;
  (*y) = y_u;

  No_Count = 0;

  y_1 = y_u - EPSILON;
  W_1 = Infectious_Mosquito_Steady_State(y_1, P);

  y_0 = y_l + EPSILON;
  W_0 = Infectious_Mosquito_Steady_State(y_0, P);

  /* The pairs (W_1, y_1) and (W_0, y_0) are my first guesses */
  /* In fact, I am taking W_0, W_1 to bracket the intermediate
     root that will be my result (*W)
  */
  (*W) = intermediateRoot_Malaria (P, W_0, W_1);

  (*y) = Infectious_Human_Steady_State_Fraction((*W), P);
}

double y_Function (const double W, void *params)
{
  double y, y_H, y_M;
  Parameter_Table *P;

  P = (Parameter_Table *) params;

  y_M = Inverted_Mosquito_Steady_State(W,P);
  y_H = Infectious_Human_Steady_State_Fraction(W,P);

  y = y_H - y_M;

  return(y);
}
