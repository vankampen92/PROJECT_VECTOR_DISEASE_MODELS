#include <MODEL.h>

int B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M___S_C_A_N( Parameter_Table *P, 
						     int No_of_POINTS_1, int Input_Parameter_1,
						     int No_of_POINTS_2, int Input_Parameter_2,
						     int No_of_Output_Variables, 
						     double EPSILON ) 
{
  double y_LOWER, y_INTER, y_UPPER;
  double Value, Value_0, Value_1;
  int i,j, k;
  int Output_Variable;

  /* This function calculates a bifurcation diagram for each Output Variable
     as given in the P->IO_VARIABLE_LIST[]. This is done by using as a bifurcation
     parameter Input_Parameter_1. 

     These bifurcation diagrams are then repeated by changing the value of a 2nd 
     Input_Parameter_2 in an outer loop:
 
       for (k=1; k<No_of_POINTS_2; k++) {
            ...
       }

     starting at line 54.

     Input parameters are labeled according to the input (model) parameters labels as
     appears in all the assing_[].c functions. 

     The output of the probram generates No_of_POINTS_2 different 1DIM graphics, each of 
     them containing 'No_of_Ouput_Variables' subplots. All of them are also saved in
     bifurcation_DIGRAM_[Number].dat type of files. 

     The key input parameter here is:
     
     . No_of_Output_Variables

     which means that repeated bifurcation diagrams are calculated, plotted (on the 
     same plot by using subplots), and saved for each output variable.
  */

  /* BEGIN : Allocating memory for saving data to plot a bifurcation  * * * * * * */
  /*         diagram for each variable  * * * * * * * * * * * * * * * * * * * * * */  
  double      *** y_SOL  = (double ***)malloc( No_of_Output_Variables * sizeof(double **) );
  for( i = 0; i < No_of_Output_Variables; i++){

    y_SOL[i] = (double **)malloc( 3 * sizeof(double *) );
 
    for( j = 0; j < 3; j++) {
      y_SOL[i][j] = (double *)malloc( No_of_POINTS_1 * sizeof(double) );
    }
  }
  	
  double       ** y_BIF  = (double  **)malloc( 3 * sizeof(double *) );
  for( j = 0; j < 3; j++) {
      y_BIF[j] = (double *)malloc( No_of_POINTS_1 * sizeof(double) );
  }
  double * x_Data  = (double *)malloc(No_of_POINTS_1 * sizeof(double) ); 
  /*   END : Allocating memory for saving dynamical data * * * * * */

  for( k = 0; k < No_of_POINTS_2; k++ ) {
  
    Boundary(Input_Parameter_2, &Value_0, &Value_1);
    Value = Value_0 + k * (Value_1 - Value_0)/(double)(No_of_POINTS_2 - 1);
    AssignVectorEntry_to_Structure(P, Input_Parameter_2, Value);
    
    Boundary(Input_Parameter_1, &Value_0, &Value_1);

    for( i = 0; i < No_of_Output_Variables; i++) {	   
      
      Output_Variable = P->IO_VARIABLE_LIST[i]; 

      for( j = 0; j < No_of_POINTS_1; j++ ){
	
	Value = Value_0 + j * (Value_1 - Value_0)/(double)(No_of_POINTS_1 - 1);
	AssignVectorEntry_to_Structure(P, Input_Parameter_1, Value);

#if defined LXVnW
        P->M_Fecundity = P->M_a * P->M_NoEggs;
#endif
#if defined XkVnW
        P->M_Fecundity = P->M_a * P->M_NoEggs;
#endif
#if defined XVnW
        /* Total mosquito population constant */
        P->M_Fecundity = P->M_Delta;
#endif
#if defined XW
        /* Total mosquito population constant */
        P->M_Fecundity = P->M_Delta;
#endif
	
	B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M( P, &y_LOWER, &y_INTER, &y_UPPER, Output_Variable, 
					       EPSILON );	
	
	x_Data[j] = Value;
	
	y_SOL[i][0][j] = y_LOWER; y_SOL[i][1][j] = y_INTER; y_SOL[i][2][j] = y_UPPER;
	
	y_BIF[0][j]    = y_LOWER;    y_BIF[1][j] = y_INTER;    y_BIF[2][j] = y_UPPER;
	
	printf(" y_LOWER = %g\ty_INTER = %g\ty_UPPER = %g\n", y_LOWER, y_INTER, y_UPPER);
      }
      
      /* BEGIN : Saving to File  */
      Saving_to_File_double_4Col("bifurcation_DIGRAM_", x_Data, y_BIF[0], y_BIF[1], y_BIF[2], No_of_POINTS_1, 100*k+Output_Variable); 
      /*   END : Saving to File */
    }
    
#if defined CPGPLOT_REPRESENTATION
    C_P_G___S_U_B___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M ( P, No_of_POINTS_1, 
									      x_Data, y_SOL, 
									      No_of_Output_Variables, 
									      Input_Parameter_1,
									      Input_Parameter_2);
#endif
  }
  
  /* BEGIN : Freeing previous allocated memory */
  for(i = 0; i < No_of_Output_Variables; i++) { 
    for( j = 0; j < 3; j++){ free (y_SOL[i][j]); }
    free (y_SOL[i]);
  }   
  free(y_SOL); 

  for( j = 0; j < 3; j++){ free (y_BIF[j]);}
  free (y_BIF);

  free(x_Data); 
  /*   END : End freeing allocated memory */

  return(0);
}

#if defined CPGPLOT_REPRESENTATION
void C_P_G___S_U_B___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M ( Parameter_Table * P, int NO_of_POINTS, 
      									       double * x_Data, double *** y_SOL, 
									       int No_of_Output_Variables, 
									       int Input_Parameter_1, 
									       int Input_Parameter_2)
{
  
  /* 
     CPG Representation: This function represents a bifurcation diagram for earch Output Variable
     as given in the P->IO_VARIABLE_LIST[], where the bifurcation parameter, represented in the x
     axis, is given as Input_Parameter_1. 
  */

  int i, k, SCALE_FIXED;
  char * p_Title;
  char * Number   = (char *)malloc( sizeof(char) * 50 );
  char ** Y_label = (char **)malloc( sizeof(char *) * No_of_Output_Variables );
  char * X_label; 
  char * Title_In = (char *)malloc( sizeof(char) * 500 );
    
  /*********************************************************************/
  
  X_label   = P->Name_Parameters[Input_Parameter_1]; 
 
  for(i=0; i < No_of_Output_Variables; i++){
    
    k = P->IO_VARIABLE_LIST[i]; 
    
    Y_label[i]  = (char *)malloc( sizeof(char) * 500 );
    
    Y_label[i]  = P->Variable_Name[k];

    //printf("Y_label : %s\t P->Out_Var_List[i] = %d\t i = %d\n", P->Output_Var_Name[k], k, i);
    //Press_Key();
  }
  /*********************************************************************/
  
  for (i = 0; i < No_of_Output_Variables; i++) {
 
    Title_In[0] = '\0';
    p_Title = strcat( Title_In, Y_label[i] );
    p_Title = strcat( Title_In, " --- ");
    p_Title = strcat( Title_In, P->Name_Parameters[Input_Parameter_2]);
    p_Title = strcat( Title_In, "  =  ");
    
    double Value = AssignStructValue_to_VectorEntry( Input_Parameter_2, P );

    doubletochar( Value, Number );
    p_Title = strcat( Title_In, Number);

    //SCALE_FIXED  = 0;
    C_P_G___2d___X_Y_n___P_L_O_T_T_I_N_G ( NO_of_POINTS, 3, x_Data, y_SOL[i], 
					   X_label, Y_label[i], Title_In );
  }
    

  free (Title_In); free (Y_label); free (Number);
} 
#endif
