
  P->H_Beta = Beta_Function(P, y[W]);  
  P->H_Recov = Queu_Function_Recovery(P, y[W], P->H_Recov_0, P->W_Recov);

  dydt[S] = -P->H_Beta*y[S] + P->H_Birth*H -P->H_Delta*y[S] + P->H_Recov*y[I];         /* S   */

  dydt[E] = + P->H_Beta*y[S] - P->n_H*P->H_Gamma*y[E] - P->H_Delta*y[E];                      /* E_1 */
  for(i=2; i<=P->n_H; i++){                                                                   /* E_n */
    dydt[i] = P->n_H*P->H_Gamma*y[i-1] - P->n_H*P->H_Gamma*y[i] - P->H_Delta*y[i];
  }    
  
  dydt[I] =   P->n_H*P->H_Gamma*y[I-1] - P->H_Recov*y[I] - P->H_Delta*y[I];         
