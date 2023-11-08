 /* S row: Let dSdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */ 
  /* 
  gsl_matrix_set(m, S, S, P->H_Birth - P->H_Delta - P->H_Beta);
  gsl_matrix_set(m, S, I, P->H_Birth + P->H_Recov);

  gsl_matrix_set(m, S, W, -y[S]*BETA_DERIVATIVE + y[I]*P->M_a/H*Q_Recov_Deriv);
  */
  /* I row: Let dIdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  double y_S = P->H - y[I]; 
  gsl_matrix_set(m, I, I,  -P->H_Beta -P->H_Delta -P->H_Recov);
  
  gsl_matrix_set(m, I, W,  y_S*BETA_DERIVATIVE - y[I]*P->M_a/H*Q_Recov_Deriv);




