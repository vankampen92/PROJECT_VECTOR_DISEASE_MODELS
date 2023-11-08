/* Applying time dependence to mosquito Parameters ...*/
  M_Fecundity = P->M_Fecundity; 
  K_0         = P->K_0;

  M = 0.;
  for(i=X; i<= W; i++) M += y[i];
   
  dydt[X] = - P->M_a*P->M_c*f*y[X] - P->M_Delta*y[X] + M_Fecundity *M* (1 - M/K_0);  /* X   */
  
  dydt[U] = P->M_a*P->M_c*f*y[X]- P->M_Delta*y[U] - P->n_V*P->M_Gamma*y[U];          /* V_1 */   
  for(i=U+1; i < W; i++){                                                            /* V_n */
    dydt[i] = + P->n_V*P->M_Gamma*y[i-1] - P->M_Delta*y[i] - P->n_V*P->M_Gamma*y[i]; 
  }

  dydt[W] =  P->n_V*P->M_Gamma*y[W-1] - P->M_Delta*y[W];                             /* W   */ 
