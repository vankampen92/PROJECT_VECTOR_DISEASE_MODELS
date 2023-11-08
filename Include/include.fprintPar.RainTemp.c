/* Rain and Temperature time series related parameters */
	    
fprintf(fp, " \n Time dependent parameters (Rain and Temperature) controling some mosquito parameters:\n");
fprintf(fp, " Number of time-dependent parameters (total length of rain and temperature time series)... ... ... ...> MALARIA -R0 %d\n", 
	 NO_of_POINTS);
fprintf(fp, " Time increment between rain and temperature data points ... ... ... ... ... ... ... ... ... ... .... > MALARIA -R1 %g\n", 
	 T_INCREMENT);
fprintf(fp, " Number of points defining the anual cycle, usually 12 months ..... ... ... ... ... ... ... ... ... ..> MALARIA -R2 %d\n", 
	NO_of_POINTS_AVE);
fprintf(fp, " Shift in temperature to mimic a difference between the effective temperature affecting adult mosquitoes\n");
fprintf(fp, " and environmental true temperture controling larval development ... ... ... ... ... ... ... ... ...  > MALARIA -R3 %g\n", 
	TEMP__SHIFT);
fprintf(fp, " Shift in temperature to mimic a change in altitude in the location temperature the data come from ...> MALARIA -R4 %g\n", 
	T_ELEVATION);
fprintf(fp, " Initial year at which time calculations should start (usually, but not always is 1970.0) ... ... ....> MALARIA -R5 %g\n", 
	INITIAL_YEAR);
fprintf(fp, " Fraction of time adult mosquitoes spent on average experiencing and outdoor (lower) temperature ... .> MALARIA -R6 %g\n",
	x);
