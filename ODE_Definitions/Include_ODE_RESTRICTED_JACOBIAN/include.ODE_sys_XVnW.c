/* Applying time dependence to mosquito Parameters ...*/
  M_Fecundity = P->M_Fecundity; 
  K_0         = P->K_0;

  M = P->m * P->H;
  
/* dydt[X] = - P->M_a*P->M_c*f*y[X] - P->M_Delta*y[X] + M_Fecundity * M; *//* X   */
  
  double y_U = 0.0;
  for (i=U; i<W; i++) y_U += y[U];
  double y_X = M - y_U - y[W];

  dydt[U] = P->M_a*P->M_c*f*y_X- P->M_Delta*y[U] - P->n_V*P->M_Gamma*y[U];          /* V_1 */   
  for(i=U+1; i < W; i++){                                                            /* V_n */
    dydt[i] = + P->n_V*P->M_Gamma*y[i-1] - P->M_Delta*y[i] - P->n_V*P->M_Gamma*y[i]; 
  }

  dydt[W] =  P->n_V*P->M_Gamma*y[W-1] - P->M_Delta*y[W];                             /* W   */ 
