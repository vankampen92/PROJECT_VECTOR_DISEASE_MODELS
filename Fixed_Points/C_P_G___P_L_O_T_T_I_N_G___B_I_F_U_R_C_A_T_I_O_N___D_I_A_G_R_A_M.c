#include <MODEL.h>

#if defined CPGPLOT_REPRESENTATION
void C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M (Parameter_Table * P, 
								      double * x_Lower,
								      double * y_Lower, int N_Lower,
								      double * x_Inter,
								      double * y_Inter, int N_Inter,
								      double * x_Upper,
								      double * y_Upper, int N_Upper,
								      int Output_Variable, 
								      int Input_Parameter_1, 
								      int Input_Parameter_2)
{
  /* 
     CPG Representation: This function represents a bifurcation diagram for Output Variable, 
     where the bifurcation parameter, represented in the x axis, is given as Input_Parameter. 
  */

  int i, SCALE_FIXED;
  char * p_Title;
  char * Y_label;
  char * X_label; 
  char * Title_In = (char *)malloc( sizeof(char) * 500 );
  char * Number   = (char *)malloc( sizeof(char) * 50  );
  /*********************************************************************/
  X_label   = P->Name_Parameters[Input_Parameter_1]; 
  Y_label   = P->Variable_Name[Output_Variable];
  /*********************************************************************/
  
  Title_In[0] = '\0';
  // p_Title = strcat( Title_In, "  B i f u r c a t i o n:  ");
  p_Title = strcat( Title_In, Y_label );
  p_Title = strcat( Title_In, "    ( ");
  p_Title = strcat( Title_In, P->Name_Parameters[Input_Parameter_2] );
  p_Title = strcat( Title_In, "  =  ");
  
  double Value = AssignStructValue_to_VectorEntry( Input_Parameter_2, P );
  // doubletochar( Value, Number );
  sprintf(Number, "%g", Value);

  p_Title = strcat( Title_In, Number);
  p_Title = strcat( Title_In, " )  ");

  int SAME = 0;
  P->CPG->type_of_Line = 1;
  P->CPG->type_of_Width = 8;
  P->CPG->color_Index = 3;
  P->CPG->type_of_Symbol = 1;
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( P->CPG , SAME,
							N_Lower, x_Lower, y_Lower, 
							X_label, Y_label, Title_In, 
							P->CPG->CPG_SCALE_X, P->CPG->CPG_SCALE_Y);
  SAME = 1;
  P->CPG->type_of_Line = 4;
  P->CPG->type_of_Width = 6;
  P->CPG->color_Index = 5;
  P->CPG->type_of_Symbol = 1;
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( P->CPG , SAME,
							N_Inter, x_Inter, y_Inter, 
							X_label, Y_label, Title_In, 
							P->CPG->CPG_SCALE_X, P->CPG->CPG_SCALE_Y);
  SAME = 1;
  P->CPG->type_of_Line = 1;
  P->CPG->type_of_Width = 8;
  P->CPG->color_Index = 2;
  P->CPG->type_of_Symbol = 1;
  CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( P->CPG , SAME,
							N_Upper, x_Upper, y_Upper, 
							X_label, Y_label, Title_In, 
							P->CPG->CPG_SCALE_X, P->CPG->CPG_SCALE_Y);
  
  free (Title_In); free (Number);
} 

void C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_E_P_R_E_C_A_T_E_D ( Parameter_Table * P, 
									     int NO_of_POINTS,
									     double * x_Data,
									     double ** y_SOL, 
									     int Output_Variable, 
									     int Input_Parameter_1, 
									     int Input_Parameter_2)
{
  /* 
     CPG Representation: This function represents a bifurcation diagram for Output Variable, 
     where the bifurcation parameter, represented in the x axis, is given as Input_Parameter. 
  */

  int i, SCALE_FIXED;
  char * p_Title;
  char * Y_label;
  char * X_label; 
  char * Title_In = (char *)malloc( sizeof(char) * 500 );
  char * Number   = (char *)malloc( sizeof(char) * 50  );
  /*********************************************************************/
  X_label   = P->Name_Parameters[Input_Parameter_1]; 
  Y_label   = P->Variable_Name[Output_Variable];
  /*********************************************************************/
  
  Title_In[0] = '\0';
  // p_Title = strcat( Title_In, "  B i f u r c a t i o n:  ");
  p_Title = strcat( Title_In, Y_label );
  p_Title = strcat( Title_In, "    ( ");
  p_Title = strcat( Title_In, P->Name_Parameters[Input_Parameter_2] );
  p_Title = strcat( Title_In, "  =  ");
  
  double Value = AssignStructValue_to_VectorEntry( Input_Parameter_2, P );
  // doubletochar( Value, Number );
  sprintf(Number, "%g", Value);

  p_Title = strcat( Title_In, Number);
  p_Title = strcat( Title_In, " )  ");
  
  //SCALE_FIXED  = 0;
  CPGPLOT___X_Y_n___P_L_O_T_T_I_N_G ( P->CPG , NO_of_POINTS, 3, x_Data, y_SOL, 
				      X_label, Y_label, Title_In, 
				      P->CPG->CPG_SCALE_X, P->CPG->CPG_SCALE_Y);
  
  free (Title_In); free (Number);
} 
#endif
