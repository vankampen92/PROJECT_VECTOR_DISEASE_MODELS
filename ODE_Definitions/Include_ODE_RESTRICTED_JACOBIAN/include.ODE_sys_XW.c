/* Applying time dependence to mosquito Parameters ...*/
  M_Fecundity = P->M_Fecundity; 

  M = P->m * P->H;
  
/* dydt[X] = - P->M_a*P->M_c*f*y[X] - P->M_Delta*y[X] + M_Fecundity * M; */ /* X   */
  double y_X = M - y[W];

  dydt[W] =   P->M_a*P->M_c*f*y_X - P->M_Delta*y[W];   /* W   */   
