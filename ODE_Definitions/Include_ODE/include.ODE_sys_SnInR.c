
  P->H_Beta = Beta_Function(P, y[W]); /* Force of infection */
  P->H_Recov = P->H_Recov_0; /* Recovery from infection -- Queu_Function_Recovery(P, y[W], P->H_Recov_0, P->W_Recov); */
  P->H_Sigma = P->H_Sigma_0; /* Loss of immunity */

  dydt[S1] = P->H_Birth*H -P->H_Beta*y[S1] -P->H_Delta*y[S1] + P->H_Sigma*y[S2];                                     /* S1   */
  dydt[I1] = P->H_Beta*y[S1] -P->H_Recov*y[I1] - P->H_Delta*y[I1];                                                  /* I1   */
  dydt[S2] = P->H_Recov*y[I1] -P->H_mBeta*P->H_Beta*y[S2] -P->H_Sigma*y[S2] -P->H_Delta*y[S2] + P->H_mSigma*P->H_Sigma*y[S3];                                            /* S2   */
  dydt[I2] = P->H_mBeta*P->H_Beta*y[S2] - P->H_mRecov*P->H_Recov*y[I2] - P->H_Delta*y[I2];                           /* I2   */
  dydt[S3] = P->H_mRecov*P->H_Recov*y[I2] -pow(P->H_mBeta,2)*P->H_Beta*y[S3] -P->H_mSigma*P->H_Sigma*y[S3] -P->H_Delta*y[S3] + pow(P->H_mSigma,2)*P->H_Sigma*y[R];   /* S3   */
  dydt[I3] = pow(P->H_mBeta,2)*P->H_Beta*y[S3]- pow(P->H_mRecov,2)*P->H_Recov*y[I3] - P->H_Delta*y[I3];          /* I3   */
  dydt[R]  = pow(P->H_mRecov,2)*P->H_Recov*y[I3] - pow(P->H_mSigma,2)*P->H_Sigma*y[R] - P->H_Delta*y[R];         /* R    */
