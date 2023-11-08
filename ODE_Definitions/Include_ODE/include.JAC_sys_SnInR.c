 /* S1 row: Let dS1dt be equal to F(), then the entries are defined
     to be dFdS1 to dFdW */
  gsl_matrix_set(m, S1, S1, P->H_Birth - P->H_Delta - P->H_Beta);

  for(i=1; i<=6; i++) /* I2 ==> R columns */
    gsl_matrix_set(m, S1, i, P->H_Birth);

  gsl_matrix_set(m, S1, S2, P->H_Birth + P->H_Sigma);

  /* Zeros from L ==> V columns */
  gsl_matrix_set(m, S1, W, -y[S1]*P->M_a*P->M_b/H);

  /* I1 row: Let dI1dt be equal to F(), then the entries are defined
     to be dFdS1 to dFdW */
  gsl_matrix_set(m, I1, S1, P->H_Beta);
  gsl_matrix_set(m, I1, I1, -P->H_Delta -P->H_Recov);
  gsl_matrix_set(m, I1, W, y[S1]*P->M_a*P->M_b/H);

  /* S2 row: Let dS2dt be equal to F(), then the entries are defined
      to be dFdS1 to dFdW */
  gsl_matrix_set(m, S2, I1, P->H_Recov);
  gsl_matrix_set(m, S2, S2, -P->H_Delta - P->H_mBeta*P->H_Beta - P->H_Sigma);
  gsl_matrix_set(m, S2, S3, P->H_mSigma*P->H_Sigma);
   /* Zeros from L ==> V columns */
  gsl_matrix_set(m, S2, W, -y[S2]*P->H_mBeta*P->M_a*P->M_b/H);

  /* I2 row: Let dI2dt be equal to F(), then the entries are defined
     to be dFdS1 to dFdW */
  gsl_matrix_set(m, I2, S2, P->H_mBeta*P->H_Beta);
  gsl_matrix_set(m, I2, I2, -P->H_Delta -P->H_mRecov*P->H_Recov);
  gsl_matrix_set(m, I2, W, y[S2]*P->H_mBeta*P->M_a*P->M_b/H);

  /* S3 row: Let dS3dt be equal to F(), then the entries are defined
      to be dFdS1 to dFdW */
  gsl_matrix_set(m, S3, I2, P->H_mRecov*P->H_Recov);
  gsl_matrix_set(m, S3, S3, -P->H_Delta - pow(P->H_mBeta,2)*P->H_Beta - P->H_mSigma*P->H_Sigma);
  gsl_matrix_set(m, S3, R, pow(P->H_mSigma,2)*P->H_Sigma);
   /* Zeros from L ==> V columns */
  gsl_matrix_set(m, S3, W, -y[S3]*pow(P->H_mBeta,2)*P->M_a*P->M_b/H);

  /* I2 row: Let dI1dt be equal to F(), then the entries are defined
     to be dFdS1 to dFdW */
  gsl_matrix_set(m, I3, S3, pow(P->H_mBeta,2)*P->H_Beta);
  gsl_matrix_set(m, I3, I3, -P->H_Delta - pow(P->H_mRecov,2)*P->H_Recov);
  gsl_matrix_set(m, I3, W, y[S3]*pow(P->H_mBeta,2)*P->M_a*P->M_b/H);

  /* R row: Let dRdt be equal to F(), then the entries are defined
      to be dFdS1 to dFdW */
  gsl_matrix_set(m, R, I3, pow(P->H_mRecov,2)*P->H_Recov);
  gsl_matrix_set(m, R, R, -P->H_Delta - pow(P->H_mSigma,2)*P->H_Sigma);
