/* S row: Let dSdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */  
  gsl_matrix_set(m, S,S, P->H_Birth - P->H_Delta - P->H_Beta);
  
  for(i=1; i<=P->n_H; i++)
    gsl_matrix_set(m, S,i, P->H_Birth); 

  gsl_matrix_set(m, S, I, P->H_Birth);
  gsl_matrix_set(m, S, R, P->H_Birth + P->H_Sigma);
  gsl_matrix_set(m, S, C, P->H_Birth + P->H_Rho);

  /* Zeros from (0,P->n_H+3+1) to (0,P->n_H+3+3+P->n_V-1) */
  gsl_matrix_set(m, S, W, -y[S]*BETA_DERIVATIVE + y[R]*P->M_a/H*Q_Sigma_Deriv);
  
  /* E_{1} row: Let dE_{1}dt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, E, S, P->H_Beta);
  gsl_matrix_set(m, E, E, -P->H_Delta -P->n_H*P->H_Gamma);
  
  gsl_matrix_set(m, E, W, y[S]*BETA_DERIVATIVE);

  /* From row E_{2} to row E_{n_H} */
  for(i=2; i<=P->n_H; i++){
    gsl_matrix_set(m, i, i-1, P->n_H*P->H_Gamma);
    gsl_matrix_set(m, i, i, -P->H_Delta-P->n_H*P->H_Gamma);
  }
  
  /* I row: Let dIdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, I, I-1, (1.-P->H_Xhi) * P->n_H*P->H_Gamma);
  gsl_matrix_set(m, I, I,  -P->H_Delta -P->H_Recov - P->H_Eta * P->H_Beta);
  gsl_matrix_set(m, I, C,   P->H_Nu);
  
  gsl_matrix_set(m, I, W,  -P->H_Eta*y[I]*BETA_DERIVATIVE -y[I]*P->M_a/H*Q_Recov_Deriv);
  
  /* R row: Let dRdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, R, I,  P->H_Recov);
  gsl_matrix_set(m, R, R, -P->H_Delta-P->H_Sigma);
  
  gsl_matrix_set(m, R, W,  P->M_a/H *(y[I]*Q_Recov_Deriv-y[R]*Q_Sigma_Deriv) );

  /* C row: Let dCdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, C, I-1, P->H_Xhi*P->n_H*P->H_Gamma );
  gsl_matrix_set(m, C, I,   P->H_Eta * P->H_Beta);
  gsl_matrix_set(m, C, C,  -P->H_Delta -P->H_Nu -P->H_Rho);
  
  gsl_matrix_set(m, C, W,   P->H_Eta*y[I]*BETA_DERIVATIVE);
