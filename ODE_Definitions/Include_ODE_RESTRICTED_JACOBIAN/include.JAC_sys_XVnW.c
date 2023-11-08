  /* X row: Let dXdt be equal to F(), then the entries are defined 
     to dFdS to dFdW */
  /*
  for(i=E; i<=C; i++){
#if defined CASES_1
    if(i == I || i == C)
      gsl_matrix_set(m, X, i, - P->M_c*P->M_a*y[X]/H);
#else
    if(i == I)
    gsl_matrix_set(m, X, i, - P->M_c*P->M_a*y[X]/H);
#endif
    else
      gsl_matrix_set(m, X, i, 0.0);
  }
  gsl_matrix_set(m, X, X, P->M_Fecundity  -P->M_Delta - P->M_c*P->M_a* f /H);
  */
  
  /* V_{1} row: Let dV_{1}dt be equal to F(), then the entries are defined 
     to dFdS to dFdW */
  double y_U = 0.0;
  for (i=U; i<W; i++) y_U += y[U];
  double y_X = M - y_U - y[W];

  for(i=E; i<=C; i++){
#if defined CASES_1
    if(i == I || i == C)
      gsl_matrix_set(m, U, i, + P->M_c*P->M_a*y_X/H);
#else
    if(i == I)
      gsl_matrix_set(m, U, i, + P->M_c*P->M_a*y_X/H);
#endif
    else
      gsl_matrix_set(m, U, i, 0.0);
  }
  
  gsl_matrix_set(m, U, U, -P->M_Delta - P->n_V*P->M_Gamma);

  for(i=U+1; i<W; i++){
    gsl_matrix_set(m, U, i, -P->M_a*P->M_c*f);
  }

    gsl_matrix_set(m, U, W, -P->M_a*P->M_c*f );
  
  /* From row V_{2} to row V_{n_V} */
  for(i=U+1; i<W; i++){
    gsl_matrix_set(m, i, i-1, P->n_V*P->M_Gamma);
    gsl_matrix_set(m, i, i, -P->M_Delta-P->n_V*P->M_Gamma);
  }
  
  /* W row: Let dWdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  gsl_matrix_set(m, W, W-1, P->n_V*P->M_Gamma);
  gsl_matrix_set(m, W, W, -P->M_Delta);
