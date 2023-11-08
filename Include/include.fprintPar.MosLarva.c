/* Mosquito (larva) parameters */

  fprintf(fp, "\n Mosquito (larva) parameters:\n");
  fprintf(fp, " Average development time (in days) ... ... ... ... ... ... ... ...> MALARIA -L0 %g\n", 1./L_Devel);  
  fprintf(fp, " Avarage life time (in days) (including all mortality riscs)... ...> MALARIA --- %g\n", 1./L_Delta);
  /* Seasonal forcing */
  fprintf(fp, " Average Larva carrying capacity... ... ... ... ... ... ... ... ...> MALARIA -L2 %g\n", K_0);

  fprintf(fp, " Stardard deviation around the average... ... ... ... ... . ... ...> MALARIA -L3 %g\n", K_Sigma);  
  fprintf(fp, " Period of seasonal fluctiations (in days)... ... ... ... . ... ...> MALARIA -L4 %g\n", K_Period);

  fprintf(fp, " Intensity of seasonal (annual) fluctuation (0 < f < 1).. . ... ...> MALARIA -L5 %g\n", K_Seasonal_Intensity);

  fprintf(fp, " Carrying capacity equivalent of daily input of water\n");
  fprintf(fp, " available for larval development ... .... . ... ... ... ... .. ...> MALARIA -L6 %g\n", K_A);
  fprintf(fp, " Typical daily rainfall retention for larval\n");
  fprintf(fp, " development ... .... ... ... ... ... ... .. ... .. .. .... ... ...> MALARIA -L7 %g\n", K_p); 
  fprintf(fp, " Decaying of carrying capacity (avaible water)\n");
  fprintf(fp, " through evaporation . ... ... ... ... ... ... ... ... ... ... ....> MALARIA -L8 %g\n", K_E);
  fprintf(fp, " Temperature induced larva mortality (day^{-1}) ... ... ... ... ...> MALARIA -L1 %g\n", L_Delta_0);
  fprintf(fp, " Predator and other random hazzards induced mortalities for the\n");
  fprintf(fp, " larval stage (day^{-1})... .. ... ...... ...... ...... ... ... ...> MALARIA -L9 %g\n", L_Delta_P);
  fprintf(fp, " Rain-induced larva mortality:\n"); 
  fprintf(fp, " Depending on the implementation, the L10 parameter has a different meaning,\n");
  fprintf(fp, " Always it means a positive contribution to larva mortality \n"); 
  fprintf(fp, " (either, if, for instance, there is a rainfall of 10.0 mm/day over the\n"); 
  fprintf(fp, " average rainfall intensity, then the increase it is 10 times L10, > MALARIA -L10 %g\n", L_Delta_R);
  fprintf(fp, " or, if rainfall is larger than certain percetile (L11), then\n");  
  fprintf(fp, " there is an increase of value L10)... ... ... ... ... ... ... ... > MALARIA -L10 %g\n", L_Delta_R);
  fprintf(fp, " Percentile value ... ... ... ... ... ... ... ... ... ... ... ... .> MALARIA -L11 %g\n", L_Delta_PE);
  fprintf(fp, " Maturation rate of rain water into water available for larvas... .> MALARIA -L12 %g\n", L_Delta_PE);
