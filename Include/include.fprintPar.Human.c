/* Human parameters */
  fprintf(fp, "\n Human parameters:\n");
  fprintf(fp, " Initial Force of Infection... ... ... ... ... ... ... ... > MALARIA -H0 %g\n", H_Beta);
  fprintf(fp, " Final Force of Infection (beta) . ... ... ... ... ... ... > MALARIA --- %g\n", P->H_Beta);
  fprintf(fp, " Birth rate (usually balancing deaths)... ... ... ... ...  > MALARIA -H1 %g\n",H_Birth);
  fprintf(fp, " Approx. average life time: ( in days)... ... ... ... ...  > MALARIA -H2 %g\n", 1./H_Delta);  
  fprintf(fp, " Average basic loss of immunity (in days)... ... ... ... . > MALARIA -H3 %g\n", 1./H_Sigma_0); 
  fprintf(fp, " Loss of immunity for current beta (in days) ... ... ... . > MALARIA --- %g\n", 1./P->H_Sigma);
  /* 5. years */
  fprintf(fp, " Average basic recovery time: (in days)... ... . ... ... . > MALARIA -H4 %g\n", 1./H_Recov_0);   
  /* 5. years */
  fprintf(fp, " Average recovery time for current beta (in days) .. ... . > MALARIA --- %g\n", 1./P->H_Recov);      
  /* less than a year */
  fprintf(fp, " Number of Human (incubating) Latent class... ... ... ...  > MALARIA -H5 %d\n", n_H);     /*  */
  fprintf(fp, " Malaria average incubating time (in days)... ... ... ...  > MALARIA -H6 %g\n", 1./H_Gamma); /* */
  fprintf(fp, " Per capita human infection rate per external cause... ... > MALARIA -H7 %g\n",
	  Imm);
