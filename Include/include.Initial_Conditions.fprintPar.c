/* Initial Conditions parameters */
  fprintf(fp, " I N I T I A L   C O N D I T I O N S :\n");
  fprintf(fp, " Type of Initial Conditions: .. ... . ... ... .. > MALARIA -Xn %d\n",
	  TYPE_of_INITIAL_CONDITION);  
  fprintf(fp, " Initial fraction of Susceptibles .. ... . ... ..> MALARIA -X0 %g\n", s__0);
  fprintf(fp, " Initial fraction of Exposed ... ... ... ... ... > MALARIA -X1 %g\n", e__0);
  fprintf(fp, " Initial fraction of Infectives .. ... ... ... ..> MALARIA -X2 %g\n", i__0);
  fprintf(fp, " Initial fraction of Recovered ...  .. ... ... ..> MALARIA -X3  %g\n",r__0);
  fprintf(fp, " Initial fraction of Cases ... ... .. ... . ... .> MALARIA -X4 %g\n", c__0);
#if defined K_L_E_I_N
  fprintf(fp, " Initial fraction of Exposed (2nd class) ... ....> MALARIA -X4  %g\n", e__2);
#endif

#if defined SnInR
  fprintf(fp, " Initial fraction of Susceptibles (S1).. ... . ... ...> MALARIA -X71 %g\n", s1__0);
  fprintf(fp, " Initial fraction of Infectives (I1) .. ... ... ... ..> MALARIA -X72 %g\n", i1__0);
  fprintf(fp, " Initial fraction of Susceptibles (S2).. ... . ... ...> MALARIA -X73 %g\n", s2__0);
  fprintf(fp, " Initial fraction of Infectives (I2) .. ... ... ... ..> MALARIA -X74 %g\n", i2__0);
  fprintf(fp, " Initial fraction of Susceptibles (S3).. ... . ... ...> MALARIA -X75 %g\n", s3__0);
  fprintf(fp, " Initial fraction of Infectives (I3) .. ... ... ... ..> MALARIA -X76 %g\n", i3__0);
#endif
