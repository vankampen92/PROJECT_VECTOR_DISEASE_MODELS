 /* S row: Let dSdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */  
  /* gsl_matrix_set(m, S,S, P->H_Birth - P->H_Delta - P->H_Beta);
  
  for(i=1; i<=P->n_H; i++)
    gsl_matrix_set(m, S,i, P->H_Birth); 

  gsl_matrix_set(m, S, I, P->H_Birth + P->H_Recov);

  
  gsl_matrix_set(m, S, W, -y[S]*BETA_DERIVATIVE + y[I]*P->M_a/H*Q_Recov_Deriv);
  */
  /* E_{1} row: Let dE_{1}dt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  double y_E = 0.0;
  for (i=E; i<I; i++) y_E += y[i];  
  double y_S = P->H - y_E - y[I];

  gsl_matrix_set(m, E, E, -P->H_Beta -P->H_Delta -P->n_H*P->H_Gamma);
  for(i=E+1; i <= I; i++){  
    gsl_matrix_set(m, E, i, -P->H_Beta);
  } 
  gsl_matrix_set(m, E, W, y_S*BETA_DERIVATIVE);

  /* From row E_{2} to row E_{n_H} */
  for(i=E+1; i < I; i++){
    gsl_matrix_set(m, i, i-1, P->n_H*P->H_Gamma);
    gsl_matrix_set(m, i, i, -P->H_Delta-P->n_H*P->H_Gamma);
  }
  
  /* I row: Let dIdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, I, I-1, P->n_H*P->H_Gamma);
  gsl_matrix_set(m, I, I,  -P->H_Delta -P->H_Recov);
  gsl_matrix_set(m, I, W,  -y[I]*P->M_a/H*Q_Recov_Deriv);
