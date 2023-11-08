
  P->H_Beta = Beta_Function(P, y[W]);  
  P->H_Recov = Queu_Function_Recovery(P, y[W], P->H_Recov_0, P->W_Recov);

 /* dydt[S] = -P->H_Beta*y[S] + P->H_Birth*H -P->H_Delta*y[S] + P->H_Recov*y[I];         *//* S   */
    
  double y_S = P->H - y[I]; 

  dydt[I] =  P->H_Beta*y_S - P->H_Recov*y[I] - P->H_Delta*y[I];                /* I   */

  
