  /* Mosquito (adult) parameters */
  /* Average values Proc. Roy. Soc. London B paper, Alonso Etal 2010 */
  /* M_a = 0.34;  /\* T = 23.4 = T_o + 5.0 *\/ */
  /* M_b = 0.649;    */
  /* M_c = 0.365; */
  /* M_Delta = 0.1;  */
  M_a = 0.3;  M_a_Mean_Value = 0.3;
  M_b = 0.5;
 // M_c = 0.01;
  M_c = 0.2;
  M_c_1 = 0.5;
  M_c_2 = 0.8;
  M_Delta = 1./(25.);    /* Average life time of mosqutoes (approx 20 days)      */
  M_Delta_R = 0.0;       /* Increment in adult mortality due to rain (wash-out)  */
  M_Delta_PE = 1.0;      /* If Rain is heavier that the L_Delta_PE percentile, there is
			    an increment in adult mortality due to 'wash-out'    */
  //M_Fecundity = 100.;  /* 100 larves per adult and day                         */
  M_NoEggs      = 66.0;	 /* Backup value: 66.0 */

  m             = 1.5;   /* No of total mosquitoes per human   */  
/* Since we have a BITING RATE DRIVEN FECUNDITY, we prescribe: */   
  M_Fecundity = M_a * M_NoEggs;

#if defined LXVnW
	M_Fecundity = M_a * M_NoEggs;
#endif
#if defined XkVnW
	M_Fecundity = M_a * M_NoEggs;
#endif 
#if defined XVnW
        /* Total mosquito population constant */
	M_Fecundity = M_Delta;
#endif 
#if defined XW
	/* Total mosquito population constant */
	M_Fecundity = M_Delta;
#endif  

  M_Imm = 0.0;           /* 0.0001; *//* External influx of non-local adult mosquitoes from 
				       * surrounding areas 
				       */	
