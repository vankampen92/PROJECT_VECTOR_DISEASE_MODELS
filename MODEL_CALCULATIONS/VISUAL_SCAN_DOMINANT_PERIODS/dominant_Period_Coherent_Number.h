double DOMINANT_EIGENVALUE ( Parameter_Table * P );

double COHERENCE_NUMBER ( Parameter_Table * P );

double DOMINANT_PERIOD ( Parameter_Table * P );

int D_O_M_I_N_A_N_T___E_I_G_E_N_V_A_L_U_E(  Parameter_Table * P,
					    double * dominant_Eigenvalue,
					    float xmin, float xmax );

int D_O_M_I_N_A_N_T___P_E_R_I_O_D___C_O_H_E_R_E_N_T___N_U_M_B_E_R(  Parameter_Table * P,
								    double * dominant_Period,
								    double * coherent_Number, 
								    float xmin, float xmax );

void E_I_G_E_N___V_A_L_U_E___C_A_L_C_U_L_A_T_I_O_N ( double * y_Sol,  int K, int W, Parameter_Table * P, 
						     float * l_re, float * l_im );

double Well_Defined_Matrix_Elements(float **mm, int N, float xmin, float xmax);
