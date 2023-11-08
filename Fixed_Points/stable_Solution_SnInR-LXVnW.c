#include "../Include/MODEL.h"

void stable_Solution(double y, double W, Parameter_Table *P, double *Y)
{
  /*
     This function returns the values of the different population fractions
     (mosquitoes and humans) at equilibrium
  */
  int i;
  double Rho;
  double S1,I1,S2,I2,S3,I3,R;
  double L,X,V_1;
  double M, H;        /* total mosquito (M) and human (H) population sizes */
  double g, g_M;
  double w, a;        /*number of mosquitoes per human (w), biting rate (a) */
  double SIGMA;       /* modifying parameter, equivalent to H_mM_c */
  double GAMMA1, GAMMA2, GAMMA3, ALPHA1, ALPHA2, ALPHA3, B1, B2, B3; /* Class specific derived parameters */
  double A1, A2, A3, G1, G2, G3; /* Auxiliary paremeters */


  int S_; int E_; int I_; int R_; int C_; int S1_; int I1_; int S2_; int I2_; int S3_; int I3_;
  int L_; int X_; int U_; int W_; int A_;
  int K_;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P,
					    &S_, &E_, &I_, &R_, &C_, &S1_, &I1_, &S2_, &I2_, &S3_, &I3_,
					    &L_, &X_, &U_, &W_, &A_,
					    &K_);


  H = P->H;                             /* Total Human Population */
  w = W/H;                              /* number of infected mosquitoes per human */

  /* Defining parameters for curve equation.
  This expression comes from the Mathematica file "/{MEBT}/Code/Mathematica/calcSS_vs3i3r.nb" */
  a = P->M_a; /* biting rate */
  SIGMA = P->H_mM_c; /* modifier of human infectivity */
  GAMMA1 = P->H_Recov_0;
  GAMMA2 = P->H_mRecov*P->H_Recov_0;
  GAMMA3 = pow(P->H_mRecov,2)*P->H_Recov_0;
  ALPHA1 = P->H_Sigma_0;
  ALPHA2 = P->H_mSigma*P->H_Sigma_0;
  ALPHA3 = pow(P->H_mSigma,2)*P->H_Sigma_0;
  B1 = P->M_b;
  B2 = P->H_mBeta*P->M_b;
  B3 = pow(P->H_mBeta,2)*P->M_b;

  A1 = ALPHA1 + P->H_Delta;
  A2 = ALPHA2 + P->H_Delta;
  A3 = ALPHA3 + P->H_Delta;
  G1 = GAMMA1 + P->H_Delta;
  G2 = GAMMA2 + P->H_Delta;
  G3 = GAMMA3 + P->H_Delta;

  /* Stable values: Humans*/                                   /* S1 ==> R   */
  S1 = (G1*(a*B2*w*(A2*A3*G2*G3 - A3*ALPHA2*G3*GAMMA2 + a*A3*B3*G2*G3*w - a*ALPHA3*B3*G2*GAMMA3*w) + A1*G2*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w)))/
   (A1*G2*(G1 + a*B1*w)*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w) + a*w*(A2*A3*G3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w)) -
        a*B3*GAMMA3*w*(-(a*B1*B2*GAMMA1*GAMMA2*w) + ALPHA3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w))) +
        A3*(-(ALPHA2*B2*G3*GAMMA2*(G1 + a*B1*w)) + a*w*(B1*B3*G2*G3*GAMMA1 + B2*(B1*G3*GAMMA1*GAMMA2 + B3*(G1*G2*G3 + a*B1*(G2*G3 + GAMMA1*(G3 + GAMMA2))*w))))));

  I1 = (a*B1*w*(a*B2*w*(A2*A3*G2*G3 - A3*ALPHA2*G3*GAMMA2 + a*A3*B3*G2*G3*w - a*ALPHA3*B3*G2*GAMMA3*w) + A1*G2*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w)))/
   (A1*G2*(G1 + a*B1*w)*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w) + a*w*(A2*A3*G3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w)) -
        a*B3*GAMMA3*w*(-(a*B1*B2*GAMMA1*GAMMA2*w) + ALPHA3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w))) +
        A3*(-(ALPHA2*B2*G3*GAMMA2*(G1 + a*B1*w)) + a*w*(B1*B3*G2*G3*GAMMA1 + B2*(B1*G3*GAMMA1*GAMMA2 + B3*(G1*G2*G3 + a*B1*(G2*G3 + GAMMA1*(G3 + GAMMA2))*w))))));

  S2 = (a*B1*G2*GAMMA1*w*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w))/
   (A1*G2*(G1 + a*B1*w)*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w) + a*w*(A2*A3*G3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w)) -
        a*B3*GAMMA3*w*(-(a*B1*B2*GAMMA1*GAMMA2*w) + ALPHA3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w))) +
        A3*(-(ALPHA2*B2*G3*GAMMA2*(G1 + a*B1*w)) + a*w*(B1*B3*G2*G3*GAMMA1 + B2*(B1*G3*GAMMA1*GAMMA2 + B3*(G1*G2*G3 + a*B1*(G2*G3 + GAMMA1*(G3 + GAMMA2))*w))))));

  I2 = (pow(a,2)*B1*B2*GAMMA1*pow(w,2)*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w))/
   (A1*G2*(G1 + a*B1*w)*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w) + a*w*(A2*A3*G3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w)) -
        a*B3*GAMMA3*w*(-(a*B1*B2*GAMMA1*GAMMA2*w) + ALPHA3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w))) +
        A3*(-(ALPHA2*B2*G3*GAMMA2*(G1 + a*B1*w)) + a*w*(B1*B3*G2*G3*GAMMA1 + B2*(B1*G3*GAMMA1*GAMMA2 + B3*(G1*G2*G3 + a*B1*(G2*G3 + GAMMA1*(G3 + GAMMA2))*w))))));

  S3 = (pow(a,2)*A3*B1*B2*G3*GAMMA1*GAMMA2*pow(w,2))/
   (A1*G2*(G1 + a*B1*w)*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w) + a*w*(A2*A3*G3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w)) -
        a*B3*GAMMA3*w*(-(a*B1*B2*GAMMA1*GAMMA2*w) + ALPHA3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w))) +
        A3*(-(ALPHA2*B2*G3*GAMMA2*(G1 + a*B1*w)) + a*w*(B1*B3*G2*G3*GAMMA1 + B2*(B1*G3*GAMMA1*GAMMA2 + B3*(G1*G2*G3 + a*B1*(G2*G3 + GAMMA1*(G3 + GAMMA2))*w))))));

  I3 = (pow(a,3)*A3*B1*B2*B3*GAMMA1*GAMMA2*pow(w,3))/
   (A1*G2*(G1 + a*B1*w)*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w) + a*w*(A2*A3*G3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w)) -
        a*B3*GAMMA3*w*(-(a*B1*B2*GAMMA1*GAMMA2*w) + ALPHA3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w))) +
        A3*(-(ALPHA2*B2*G3*GAMMA2*(G1 + a*B1*w)) + a*w*(B1*B3*G2*G3*GAMMA1 + B2*(B1*G3*GAMMA1*GAMMA2 + B3*(G1*G2*G3 + a*B1*(G2*G3 + GAMMA1*(G3 + GAMMA2))*w))))));

  R = (pow(a,3)*B1*B2*B3*GAMMA1*GAMMA2*GAMMA3*pow(w,3))/
   (A1*G2*(G1 + a*B1*w)*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w) + a*w*(A2*A3*G3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w)) -
        a*B3*GAMMA3*w*(-(a*B1*B2*GAMMA1*GAMMA2*w) + ALPHA3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w))) +
        A3*(-(ALPHA2*B2*G3*GAMMA2*(G1 + a*B1*w)) + a*w*(B1*B3*G2*G3*GAMMA1 + B2*(B1*G3*GAMMA1*GAMMA2 + B3*(G1*G2*G3 + a*B1*(G2*G3 + GAMMA1*(G3 + GAMMA2))*w))))));


  Y[S1_] = S1 *H; 
  Y[I1_] = I1 *H; 
  Y[S2_] = S2 *H; 
  Y[I2_] = I2 *H; 
  Y[S3_] = S3 *H; 
  Y[I3_] = I3 *H;
  Y[R_]  = R  *H; 


  /* Stable values: Mosquitoes */
  M = Total_Mosquito_Steady_State(P);   /* Total Mosquito Population */
  g_M = P->n_V * P->M_Gamma /(P->n_V * P->M_Gamma + P->M_Delta);

  Stable_Solution_Partial_Mosquito_Larva( P, M, g_M,
					  y, W,
					  L_, W_, Y );
}

void stable_Solution_Free_Disease(Parameter_Table *P, double *Y)
{
  int i,S,E,I,R,C,S1,I1,S2,I2,S3,I3,L,X,U,W;
  int K,A;

  double M;
  /*    L a b e l s      */
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P,
					    &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,
					    &L, &X, &U, &W,
					    &A, &K);

  /* Human */

  Y[S1] = P->H;
  Y[I1] = 0.0;
  Y[S2] = 0.0;
  Y[I2] = 0.0;
  Y[S3] = 0.0;
  Y[I3] = 0.0;
  Y[R] = 0.0;

  /* Mosquito */

   M = Total_Mosquito_Steady_State(P);

   Stable_Solution_Partial_Mosquito_Larva_Free_Disease (P, M,
							L, W, Y );
}

/*-----------------EVERYTHING AFTER THIS IS UNNECESSARY?-------------------*/

/* The next three functions were compiled separately in stable_Solution_Free_Disease_Non_Cases.c */
int Feasibility_Condition_H(Parameter_Table *P, double W, double y)
{

  int Y;

  if ( (W > 0.0) && (y > 0.0) && (y < 1.0) ){
    Y=1;
  }
  else{
    Y=0;
  }

  return(Y);
}
