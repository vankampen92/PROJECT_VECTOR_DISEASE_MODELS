  /* X row: Let dXdt be equal to F(), then the entries are defined 
     to dFdS to dFdW */
  for(i=S; i<=C; i++){
#if defined CASES_1
    if(i == I || i == C)
      gsl_matrix_set(m, X, i, P->M_c*P->M_a*y[X]*f/H_2 - P->M_c*P->M_a*y[X]/H);
#else
    if(i == I )
      gsl_matrix_set(m, X, i, P->M_c*P->M_a*y[X]*f/H_2 - P->M_c*P->M_a*y[X]/H);
#endif
    else
      gsl_matrix_set(m, X, i, P->M_c*P->M_a*y[X]*f/H_2);
  }  

  gsl_matrix_set(m, X, X, P->M_Fecundity  -P->M_Delta - P->M_c*P->M_a* f /H);
  
  /* W row: Let dWdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */
  for(i=S; i<=C; i++){
#if defined CASES_1
    if(i == I || i == C)
      gsl_matrix_set(m, W, i, -P->M_c*P->M_a*y[X]* f /H_2 + P->M_c*P->M_a*y[X]/H);
#else
   if(i == I )
     gsl_matrix_set(m, W, i, -P->M_c*P->M_a*y[X]* f /H_2 + P->M_c*P->M_a*y[X]/H);
#endif
    else
      gsl_matrix_set(m, W, i, -P->M_c*P->M_a*y[X]* f /H_2);
  }
  
  gsl_matrix_set(m, W, X, P->M_c*P->M_a* f );
  gsl_matrix_set(m, W, W, -P->M_Delta);
