/* Human class parameters for SnInR model */
fprintf(fp, " \nMODEL PARAMETERS CONTROLING CLASSES:\n");
  fprintf(fp, " Modifier on rate of loss of immunity ... ... ... ... ...  > MALARIA -Z0 %g\n", H_mSigma;
  fprintf(fp, " Modifier on rate of recovery from infection ... ... ... . > MALARIA -Z1 %g\n", H_mRecov;
  fprintf(fp, " Modifier on susceptibility of humans ... ... ... ... ...  > MALARIA -Z2 %g\n", H_mBeta;
  fprintf(fp, " Modifier on infectiousness of humans ... ... ... ... ...  > MALARIA -Z3 %g\n", H_mM_c);
fprintf(fp, "\n");
