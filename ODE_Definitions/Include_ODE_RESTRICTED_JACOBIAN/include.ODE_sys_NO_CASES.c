
  P->H_Beta = Beta_Function(P, y[W]);  
  P->H_Sigma = Queu_Function_Sigma(P, y[W], P->H_Sigma_0, P->W_Sigma);
  P->H_Recov = Queu_Function_Recovery(P, y[W], P->H_Recov_0, P->W_Recov);

  /* dydt[S] = -P->H_Beta*y[S] + P->H_Birth*H -P->H_Delta*y[S] 
     + P->H_Sigma*y[R];            *//* S   */
  
  double y_E = 0.0;
  for (i=E; i<I; i++) y_E += y[i];  
  double y_S = P->H - y_E - y[I] - y[R]; 

  dydt[E] = + P->H_Beta*y_S - P->n_H*P->H_Gamma*y[E] - P->H_Delta*y[E];                  /* E_1 */
  for(i=1+E; i < I; i++){                                                               /* E_n */
    dydt[i] = P->n_H*P->H_Gamma*y[i-1] - P->n_H*P->H_Gamma*y[i] - P->H_Delta*y[i];
  }    
  
  dydt[I] =   P->n_H*P->H_Gamma*y[I-1] - P->H_Recov*y[I] - P->H_Delta*y[I];                 /* I   */                          

  dydt[R] = P->H_Recov * y[I] - P->H_Sigma * y[R] - P->H_Delta*y[R];                      /* R   */

