/* Human parameters */
//POPULATION = 50000; (see include.default.POPULATION.c)
  H          = (double)POPULATION;
  H_Beta    = 0.;
  H_Birth   = 1./(365.*20.);
  H_Delta   = 1./(365.*20.); /* Average life time: 20. years */
  H_Sigma_0 = 1./(5.*300.);  /* Basic loss of immunity: 5. years */
  H_Recov_0 = 1./300.;       /* Recovery times from infection: less than a year */
  n_H       = 1;             /* Human Latent class: humans incubating malaria */
 // H_Gamma   = 1./12.;      /* 1/H_Gamma is the average latent time, 12 days */
  H_Gamma   = 0.05;          /* 1/H_Gamma is the average latent time, 12 days */
  Imm       = 0.00001;
  Human_Growing_Population = 0.0;
  
/* Average values Proc. Roy. Soc. London B paper, Alonso Etal 2010 */
  /* H_Sigma_0 = 0.0805;       /\* Basic loss of immunity: 5. years *\/ */
  /* H_Recov_0 = 0.0055;       /\* Recovery times from infection: less than a year *\/ */
  /* n_H       = 3;            /\* Human Latent class: humans incubating malaria *\/ */
  /* H_Gamma   = 0.0486;       /\* 1/H_Gamma is the average latent time, 12 days *\/ */
  /* Imm       = 2.57E-5;      /\* External Force of Infection *\/ */
