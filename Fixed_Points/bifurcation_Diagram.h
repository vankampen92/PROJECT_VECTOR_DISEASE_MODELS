int B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M___S_I_M_P_L_E___S_C_A_N( Parameter_Table *P, 
								   int No_of_POINTS, 
								   int Output_Variable, 
								   int Input_Parameter, 
								   double EPSILON );

int B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M___S_C_A_N( Parameter_Table *P,
						     int No_of_POINTS_1, int Input_Parameter_1,
						     int No_of_POINTS_2, int Input_Parameter_2,
						     int No_of_Output_Variables, 
						     double EPSILON );

int B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M___P_A_R_A_M_E_T_E_R___S_C_A_N( Parameter_Table * P, 
									 int No_of_POINTS_1, int Input_Parameter_1,
									 int No_of_POINTS_2, int Input_Parameter_2,
									 int Output_Variable, 
									 double EPSILON );

void B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M(Parameter_Table * P, double * y_0, double * y_1, double * y_2, 
					   int variable_code, double Epsi);

void Saving_Bifurcation_Files( char * Bifurcation,
			       int Bifurcation_Parameter, 
			       double * x_LOWER, double * y_LOWER, int No_of_POINTS_LOWER,
			       double * x_INTER, double * y_INTER, int No_of_POINTS_INTER,
			       double * x_UPPER, double * y_UPPER, int No_of_POINTS_UPPER,
			       int Output_Variable );

int Determining_Intermediate_Branch ( double Epsilon, 
				      double y_LOWER, double y_INTER, double y_UPPER );


void Separating_Bifurcation_Branches ( double Epsilon,
				       double * x_Data,
				       double * y_LOWER, double * y_INTER, double * y_UPPER,
				       int No_of_POINTS, 				    
				       double * x_Lower, double * y_Lower, int * N_Lower, 
				       double * x_Inter, double * y_Inter, int * N_Inter, 
				       double * x_Upper, double * y_Upper, int * N_Upper);

#if defined  CPGPLOT_REPRESENTATION
void C_P_G___S_U_B___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M ( Parameter_Table * P, int NO_of_POINTS, 
      									       double * x_Data, double *** y_SOL, 
									       int No_of_Output_Variables, 
									       int Input_Parameter_1, 
									       int Input_Parameter_2);

void I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M___S_I_N_G_L_E___P_L_O_T ( Parameter_Table * P,
                                                                             int N, double * x_Data, double ** y,
                                                                             char * Title_In );

void C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_E_P_R_E_C_A_T_E_D (Parameter_Table * P, 
									    int NO_of_POINTS,
									    double * x_Data,
									    double ** y_SOL, 
									    int Output_Variable, 
									    int Input_Parameter_1, 
									    int Input_Parameter_2);

void C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M (Parameter_Table * P, 
								      double * x_Lower,
								      double * y_Lower,
								      int N_Lower,
								      double * x_Inter,
								      double * y_Inter,
								      int N_Inter,
								      double * x_Upper,
								      double * y_Upper,
								      int N_Upper,
								      int Output_Variable, 
								      int Input_Parameter_1, 
								      int Input_Parameter_2); 
#endif
