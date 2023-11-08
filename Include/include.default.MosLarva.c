  /* Mosquito (larva) parameters */
  /* Average values Proc. Roy. Soc. London B paper, Alonso Etal 2010 */
  /* L_Devel   = 0.0345; */
  /* L_Delta_P = 0.08; */
  /* K_0       = 1.698E+05;             /\* Average Larva carrying capacity K_0 = K_A*K_p/K_E *\/ */
 
  L_Devel = 1/(15.);           /* Average development time: 15 days */
  L_Delta = 1/(2.);              /* Avarage life time 2 days */
  L_Delta_0 = 1/(2.0);               /* By default, no temperature effect */
  L_Delta_P = 0.0;             /* By default, no predator effect on larva mortality */ 
  L_Delta_R = 0.0;
  L_Delta_PE = 1.0;              /* If Rain is heavier that the L_Delta_PE percentile, there is
				    an increment in larva mortality due to 'wash-out' */
/* Seasonal forcing */
  K_A     = 100.;                /* Carrying capacity equivalent of suitable water */ 
  K_p     = 10.0;                /* Daily average rain mm per day */
  K_E     = 0.01;
  K_0     = 1.0E+05;             /* Average Larva carrying capacity K_0 = K_A*K_p/K_E */
  K_Maturation = 1.0/15.0;       /* Average time water takes into
				    mature into water available for
				    mosquitoes: about 15 days */ 
  K_Sigma  = 1.0;               /* Stardard deviation around the average */ 
  K_Period = 360.;              /* 12 moths times 30 day is 360, the 
				   length of a synthetic year */
//K_Seasonal_Intensity = 1.0;
//K_Seasonal_Intensity = 0.8;
//K_Seasonal_Intensity = 0.9;
  K_Seasonal_Intensity = 0.95;

#if defined CASES_33  
  K_Mean_Value         = K_p;
#else
  K_Mean_Value         = K_0;
#endif

/* Consistently, K_0 = P->K_A*P->K_p/P->K_E */
