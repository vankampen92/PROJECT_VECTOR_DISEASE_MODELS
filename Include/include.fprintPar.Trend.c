 fprintf(fp, " \n Parameters Controling Trends\n");

 fprintf(fp, " Trend Type ... ... ... ... ... ... ... ... ... ... ... . > MALARIA -TY %d\n", TREND_TYPE);
 fprintf(fp, "   0. Trend Type = 0 TRIANGULAR TREND\n");
 fprintf(fp, "   1. Trend Type = 1 LINEAR TREND\n\n");
 
 fprintf(fp, " The initial starting time of the trend  ... ... . > MALARIA -T0 %g\n", Tr_Time_0); 
 fprintf(fp, " The final time of the trend . ... ... .... .... . > MALARIA -T1 %g\n", Tr_Time_1);
 fprintf(fp, " The intermediate value of time ... ... .. ... ... > MALARIA -Ti %g\n\n", Tr_value_0);
 
 fprintf(fp, " The initial value of the parameter... ... ... . > MALARIA -TI %g\n", Tr_value_0); 
 fprintf(fp, " The final value of the parameter ... ... .... . > MALARIA -TF %g\n", Tr_value_1);
 fprintf(fp, " The intermediate value of parameter ... ... ... > MALARIA -TM %g\n\n", Tr_value_i);
 
 
 fprintf(fp, " Trend Discretization (no of jumps) ... ... ... ... ... ..> MALARIA -TJ %d\n", 
	Tr_No_of_Jumps);

 fprintf(fp, " Input model parameter key ... ... . ... ... ... ... ... ..> MALARIA -TP %d\n", 
	Tr_Input_Parameter);
