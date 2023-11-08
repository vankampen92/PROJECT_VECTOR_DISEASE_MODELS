
/* L row: Let dLdt be equal to F(), then the entries are defined
     to dFdS to dFdW */
  gsl_matrix_set(m, L, L, -P->M_Fecundity*M/P->K_0 - P->L_Delta- P->L_Devel);
  for(i=X; i<= W; i++)
    gsl_matrix_set(m, L, i, P->M_Fecundity*(1.-y[L]/P->K_0));

/* X row: Let dXdt be equal to F(), then the entries are defined
     to dFdS to dFdW */

  /* X row : human columns */
  for(i=S; i<=C; i++){
    #if defined SnInR
      if(i == I1) {
        gsl_matrix_set(m, X, i, - P->M_c*P->M_a*y[X]/H);
      }
      else if (i == I2) {
        gsl_matrix_set(m, X, i, - P->H_mM_c*P->M_c*P->M_a*y[X]/H);
      }
      else if (i == I3) {
        gsl_matrix_set(m, X, i, - pow(P->H_mM_c,2)*P->M_c*P->M_a*y[X]/H);
      }
      else {
        /* dF/dS1, ... dF/dR = 0 */
      }
    #endif


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

  /* X row : Mosquito columns */
  gsl_matrix_set(m, X, L, P->L_Devel);
  gsl_matrix_set(m, X, X, -P->M_Delta - P->M_c*P->M_a* f /H);

/* V_{1} row: Let dV_{1}dt be equal to F(), then the entries are defined
     to dFdS to dFdW */

  /* V_{1} row : Human columns */
  for(i=S; i<=C; i++){
    #if defined SnInR
      if(i == I1) {
        gsl_matrix_set(m, U, i,  P->M_c*P->M_a*y[X]/H);
      }
      else if (i == I2) {
        gsl_matrix_set(m, U, i,  P->H_mM_c*P->M_c*P->M_a*y[X]/H);
      }
      else if (i == I3) {
        gsl_matrix_set(m, U, i,  pow(P->H_mM_c,2)*P->M_c*P->M_a*y[X]/H);
      }
      else {
        /* dF/dS1, ... dF/dR = 0 */
      }
    #endif

    #if defined CASES_1
      if(i == I || i == C)
        gsl_matrix_set(m, U, i, -P->M_c*P->M_a*y[X]* f /H_2 + P->M_c*P->M_a*y[X]/H);
    #else
      if(i == I )
        gsl_matrix_set(m, X, i, P->M_c*P->M_a*y[X]*f/H_2 - P->M_c*P->M_a*y[X]/H);
    #endif
      else
        gsl_matrix_set(m, U, i, -P->M_c*P->M_a*y[X]* f /H_2);
  }

  /* V_{1} row: Mosquito columns */
  gsl_matrix_set(m, U, X, P->M_c*P->M_a* f /H);
  gsl_matrix_set(m, U, U, -P->M_Delta - P->n_V*P->M_Gamma);

/* From row V_{2} to row V_{n_V} */
  for(i=U+1; i<W; i++){
    gsl_matrix_set(m, i, i-1, P->n_V*P->M_Gamma);
    gsl_matrix_set(m, i, i, -P->M_Delta-P->n_V*P->M_Gamma);
  }

/* W row: Let dWdt be equal to F(), then the entries are defined
     to be dFdS to dFdW */

  /* W row: Mosquito Columns */
  gsl_matrix_set(m, W, W-1, P->n_V*P->M_Gamma);
  gsl_matrix_set(m, W, W, -P->M_Delta);
