/* Applying time dependence to mosquito Parameters ...*/
  M_Fecundity = P->M_Fecundity; 
  L_Devel     = P->L_Devel;
  K_0         = P->K_0;

  M = 0.;
  for(i=X; i<= W; i++) M += y[i];
  
  dydt[L] = M_Fecundity *M* (1 - y[L]/K_0) - P->L_Delta*y[L] - L_Devel*y[L];    /* L   */ 
  
  dydt[X] = - P->M_a*P->M_c*f*y[X] - P->M_Delta*y[X] + L_Devel*y[L];  /* X */
  
  dydt[U] = P->M_a*P->M_c*f*y[X]- P->M_Delta*y[U] - P->n_V*P->M_Gamma*y[U];                                                               /* V_1 */   
  for(i=U+1; i < W; i++){                                    /* V_n */
    dydt[i] = + P->n_V*P->M_Gamma*y[i-1] - P->M_Delta*y[i] - P->n_V*P->M_Gamma*y[i]; 
  }

  dydt[W] =  P->n_V*P->M_Gamma*y[W-1] - P->M_Delta*y[W];     /* W   */ 
