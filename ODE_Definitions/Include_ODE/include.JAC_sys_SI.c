 /* S row: Let dSdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */  
  gsl_matrix_set(m, S, S, P->H_Birth - P->H_Delta - P->H_Beta);
  gsl_matrix_set(m, S, I, P->H_Birth + P->H_Recov);

  /* Zeros from (0,P->n_H+3+1) to (0,P->n_H+3+3+P->n_V-1) */
  gsl_matrix_set(m, S, W, -y[S]*BETA_DERIVATIVE + y[I]*P->M_a/H*Q_Recov_Deriv);
  
  /* I row: Let dIdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, I, S,   P->H_Beta);
  gsl_matrix_set(m, I, I,  -P->H_Delta -P->H_Recov);
  
  gsl_matrix_set(m, I, W,  y[S]*BETA_DERIVATIVE - y[I]*P->M_a/H*Q_Recov_Deriv);




