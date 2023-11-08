  fprintf(fp, "\n Mosquito (adult) parameters:\n");
  fprintf(fp, " Biting rate... ... ... ... ... ... ... ... ... ... ... ...  .. ... ..> MALARIA -M0 %g\n", M_a);
  fprintf(fp, " Infectivity for Humans when bitten by infectious mosquitoes... > MALARIA -M1 %g\n", M_b);
#if defined K_L_E_I_N
  fprintf(fp, " Infectivity for Mosquitoes when bitting infectius humans (I_1 or C). > MALARIA -M2 %g\n", M_c_1);  
  fprintf(fp, " Infectivity for Mosquitoes when bitting infectius humans.(I_2 or  I).> MALARIA -M2 %g\n", M_c_2);
#else
  fprintf(fp, " Infectivity for Mosquitoes when bitting infectius humans... ... ... .> MALARIA -M2 %g\n", M_c);
#endif
  fprintf(fp, " Average life time of mosqutoes (in days)... ... ... ... ... .... ... > MALARIA -M3 %g\n", 1./M_Delta);
  fprintf(fp, " Increase in Adult Mosquito Mortality if Rain > M5 ... ... ... .. ... > MALARIA -M4 %g\n", M_Delta_R);
  fprintf(fp, " Percentile value ... ... ... ... ... ... ... ... ... ... ... ... ... > MALARIA -M5 %g\n", M_Delta_PE);
  fprintf(fp, " Fecundity in larves per adult and day ... ... ... ... ... ... ... .  > MALARIA -M6 %g\n", M_Fecundity); 
  fprintf(fp, " Fecundity in No of Eggs per adult and day ... ... ... ... ... ... .. > MALARIA -M7 %g\n", M_NoEggs); 
  fprintf(fp, " Constant influx of adult mosquitoes from external sources ... ... .. > MALARIA -M8 %g\n", M_Imm);
  fprintf(fp, " Total number of mosquitoes per human (m = M/H) ... ... ... ... ... . > MALARIA -M9 %g\n", m);   

	    
