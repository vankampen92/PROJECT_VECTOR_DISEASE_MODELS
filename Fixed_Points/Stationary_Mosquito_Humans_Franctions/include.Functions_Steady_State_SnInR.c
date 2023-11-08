// #include "../Include/MODEL.h"
/* B E G I N :   Human submodel */
double Infectious_Human_asymptotic_Fraction(Parameter_Table *P)
{
  double y;
  // double M,B;
  // double Theta;
  //
  // Theta = (double)P->n_H * P->H_Gamma / (P->H_Delta + (double)P->n_H * P->H_Gamma);
  //
  // M = Total_Mosquito_Steady_State(P);
  // B = P->H_Beta = Beta_Function(P, M);
  // P->H_Recov = Queu_Function_Recovery(P, M, P->H_Recov_0, P->W_Recov);
  //
  // y = B * P->H_Delta * pow(Theta, (double)P->n_H) / ( (P->H_Recov + P->H_Delta )*(B + P->H_Delta) - P->H_Recov * B * pow(Theta, (double)P->n_H) );

  y = 1; /* upper boundary for effective fraction infected */

  return (y);
}

double Infectious_Human_Steady_State_Fraction(const double W, Parameter_Table *P)
{
  double y, w, H, a;
  double SIGMA; /* modifying parameter, equivalent to H_mM_c */
  double GAMMA1, GAMMA2, GAMMA3, ALPHA1, ALPHA2, ALPHA3, B1, B2, B3; /* Class specific derived parameters */
  double A1, A2, A3, G1, G2, G3; /* Auxiliary parameters */

  H = P->H; /* total human population */
  w = W/H; /* number of infected mosquitoes per human */

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

  y = (a*B1*w*(A1*G2*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w) + a*B2*w*(A2*A3*G3*(G2 + GAMMA1*SIGMA) - a*ALPHA3*B3*GAMMA3*(G2 + GAMMA1*SIGMA)*w +
          A3*(-(ALPHA2*G3*GAMMA2) + a*B3*(G2*G3 + GAMMA1*SIGMA*(G3 + GAMMA2*SIGMA))*w))))/
   (A1*G2*(G1 + a*B1*w)*(A2*A3*G3 + a*B3*(A3*G3 - ALPHA3*GAMMA3)*w) + a*w*(A2*A3*G3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w)) -
        a*B3*GAMMA3*w*(-(a*B1*B2*GAMMA1*GAMMA2*w) + ALPHA3*(B1*G2*GAMMA1 + B2*(G1*G2 + a*B1*(G2 + GAMMA1)*w))) +
        A3*(-(ALPHA2*B2*G3*GAMMA2*(G1 + a*B1*w)) + a*w*(B1*B3*G2*G3*GAMMA1 + B2*(B1*G3*GAMMA1*GAMMA2 + B3*(G1*G2*G3 + a*B1*(G2*G3 + GAMMA1*(G3 + GAMMA2))*w))))));

  return (y);
}
/* E N D :   Human submodel */
