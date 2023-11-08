/* Human parameters */
  fprintf(fp, "\n"); 
  fprintf(fp, " Number of environmental-dependent parameters ... .> MALARIA -Z %d\n", no_Func);
 if(no_Func == 8) {
   fprintf(fp, " Activation Pattern ... ... ... ... ... ... . ... .> I[%d, %d, %d, %d, %d, %d, %d, %d]\n",
	   I0, I1, I2, I3, I4, I5, I6, I7);
 }
 else if (no_Func == 9) {
   fprintf(fp, " Activation Pattern ... ... ... ... ... ... . ... .> I[%d, %d, %d, %d, %d, %d, %d, %d, %d]\n",
	   I0, I1, I2, I3, I4, I5, I6, I7, I8);
 }
 else{
   fprintf(fp, " Activation Patter has %d entries (not shown here)\n", no_Func);
   fprintf(fp, " Activation Pattern ... ... ... ... ... ... . ... .> I[%d, ..., %d]\n", I0, I19);
 }
 

