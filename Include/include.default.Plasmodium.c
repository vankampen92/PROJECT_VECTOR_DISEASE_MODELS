 /* Plasmodium parameters */
  /* Average values Proc. Roy. Soc. London B paper, Alonso Etal 2010 */
  /* n_V = 9;               /\* Mosquito Latent class: those incubating malaria *\/ */
  /* M_Gamma = 0.066;    /\* 1/M_Gamma is the average time for Plasmodium to develop *\/    */
  n_V = 1;               /* Mosquito Latent class: those incubating malaria */
  M_Gamma = 1./(12.);    /* 1/M_Gamma is the average time for Plasmodium to develop */   
  Plasmodium_Sigma = 1./ sqrt((double)n_V) / M_Gamma;
  Plasmodium_Devel = M_Gamma;
