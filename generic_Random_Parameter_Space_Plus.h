double G_E_N_E_R_I_C___R_A_N_D_O_M___P_A_R_A_M_E_T_E_R___S_P_A_C_E____P_L_U_S ( Parameter_Table * P, 
										int Realizations,
										double (* GENERIC_FUNCTION) (Parameter_Table *),
										int (* CONDITION_on_GENERIC_FUNCTION) ( double (*)(Parameter_Table *), 
															Parameter_Table * ), 
										double ** X);
