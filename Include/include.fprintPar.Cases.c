/* Human parameters to deal with clinical malaria */

	 fprintf(fp, " \nMODEL PARAMETERS CONTROLING CASES:\n");
         fprintf(fp, " Probability (Xhi) of giving rise to a clinical case when bitten as a susceptible ... ...  > MALARIA -C0 %g\n", H_Xhi);
         fprintf(fp, " Rate of clearing clinical malaria (with treatment) ... ... ... ... ... ... ... ... ... .. > MALARIA -C1 %g\n", H_Rho);
         fprintf(fp, " Probability (Eta) of giving rise to a clinical case when bitten once already infected ... > MALARIA -C2 %g\n", H_Eta);
         fprintf(fp, " Rate of clearing clinical malaria (without treatment)... ... ... ... ... ... ... ... ...  > MALARIA -C3 %g\n", H_Nu);
	 fprintf(fp, "\n"); 
	      

