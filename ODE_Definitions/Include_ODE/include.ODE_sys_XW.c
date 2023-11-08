/* Applying time dependence to mosquito Parameters ...*/
  M_Fecundity = P->M_Fecundity; 

  M = P->m * P->H;
  
  dydt[X] = - P->M_a*P->M_c*f*y[X] - P->M_Delta*y[X] + M_Fecundity * M;              /* X   */
  
  dydt[W] =   P->M_a*P->M_c*f*y[X] - P->M_Delta*y[W];                                   /* W   */   
