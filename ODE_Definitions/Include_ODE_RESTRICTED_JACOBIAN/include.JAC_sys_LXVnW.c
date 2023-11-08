  /* L row: Let dLdt be equal to F(), then the entries are defined 
     to dFdS to dFdW */
  gsl_matrix_set(m, L, L, -P->M_Fecundity*M/P->K_0 - P->L_Delta- P->L_Devel);
  for(i=X; i<= W; i++) 
    gsl_matrix_set(m, L, i, P->M_Fecundity*(1.-y[L]/P->K_0));
  
  /* X row: Let dXdt be equal to F(), then the entries are defined 
     to dFdS to dFdW */
  for(i=E; i<=C; i++){
#if defined CASES_1
    if(i == I || i == C)
      gsl_matrix_set(m, X, i, - P->M_c*P->M_a*y[X]/H);
#else
    if(i == I )
      gsl_matrix_set(m, X, i, - P->M_c*P->M_a*y[X]/H);
#endif
    else
      gsl_matrix_set(m, X, i, 0.0);
  }
  gsl_matrix_set(m, X, L, P->L_Devel);
  gsl_matrix_set(m, X, X, -P->M_Delta - P->M_c*P->M_a* f /H);
  
  /* V_{1} row: Let dV_{1}dt be equal to F(), then the entries are defined 
     to dFdS to dFdW */
  for(i=E; i<=C; i++){
#if defined CASES_1
    if(i == I || i == C)
      gsl_matrix_set(m, U, i, + P->M_c*P->M_a*y[X]/H);
#else
    if(i == I )
      gsl_matrix_set(m, X, i, + P->M_c*P->M_a*y[X]/H);
#endif
    else
      gsl_matrix_set(m, U, i, 0.0);
  }
  gsl_matrix_set(m, U, X, P->M_c*P->M_a* f /H);
  gsl_matrix_set(m, U, U, -P->M_Delta - P->n_V*P->M_Gamma);

  /* From row V_{2} to row V_{n_V} */
  for(i=U+1; i<W; i++){
    gsl_matrix_set(m, i, i-1, P->n_V*P->M_Gamma);
    gsl_matrix_set(m, i, i, -P->M_Delta-P->n_V*P->M_Gamma);
  }
  
  /* W row: Let dWdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, W, W-1, P->n_V*P->M_Gamma);
  gsl_matrix_set(m, W, W, -P->M_Delta);
