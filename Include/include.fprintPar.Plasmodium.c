/* Plasmodium parameters */
  fprintf(fp, "\n Plasmodioum related parameters:\n");
  fprintf(fp, " Numer of mosquito latent classes (incubating Plasmodium)... > MALARIA -P0 %d\n", n_V);  /* */
  fprintf(fp, " Average time for Plasmodium to develop... ... ... ... ... . > MALARIA -P1 %g\n", 1./M_Gamma);     
  Plasmodium_Sigma = 1./ sqrt((double)n_V) / M_Gamma; 
  fprintf(fp, " Standard deviation around the average... ... ... ... ... .. > MALARIA -P2 %g\n", Plasmodium_Sigma);
