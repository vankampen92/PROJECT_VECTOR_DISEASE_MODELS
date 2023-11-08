int G_E_N_E_R_I_C___F_U_N_C_T_I_O_N___P_A_R_A_M_E_T_E_R___S_C_A_N( Parameter_Table * P, 
								   int No_of_POINTS_1, int Input_Parameter_1,
								   int No_of_POINTS_2, int Input_Parameter_2,
								   double (* GENERIC_FUNCTION) (Parameter_Table *),
								   double * W_GRID, char * Output_File );
#if defined CPGPLOT_REPRESENTATION
void C_P_G___P_L_O_T_T_I_N_G___S_C_A_N ( Parameter_Table * P, 
					 int NO_of_POINTS, double * x_Data, double * y_SOL, 
					 int Input_Parameter_1, 
					 int Input_Parameter_2 );

void Parameter_Scan_2D_GRID_SHADES( Parameter_Table * Table, int No_of_POINTS_1, int Input_Parameter_1, 
				    int No_of_POINTS_2, int Input_Parameter_2, 
				    double (* GENERIC_FUNCTION) (Parameter_Table *), 
				    char * Output_File_Data );
#endif
