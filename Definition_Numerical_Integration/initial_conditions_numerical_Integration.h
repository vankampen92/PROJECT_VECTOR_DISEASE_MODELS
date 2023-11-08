void I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___N_U_M_E_R_I_C_A_L___I_N_T_E_G_R_A_T_I_O_N( Parameter_Table * , double * );

void Human_Population_Initial_Condition_from_Parameter_Table(Parameter_Table * , double * );

void Human_Population_Random_Initial_Condition(Parameter_Table * P, double *Y); 

void R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S ( Parameter_Table * ,
								 int , int , int , int , int ,
								 int , int , int , int , int , int , /* allocate for SnInR model S1=>I3 */
								 int , int , int , int ,
								 int , int ,
							       double * );

void Human_Population_Random_Initial_Condition_from_Parameter_Table(Parameter_Table * , double * );
void Mosquito_Steady_State_Initial_Condition( Parameter_Table * P, double * Y );
void Human_Population_Random_Initial_Condition_Given_i__0( Parameter_Table * P, double * Y,
							   double y );
void R_E_S_C_A_L_I_N_G___I_N_I_T_I_A_L___C_O_N_D_I_T_I_O_N_S___G_I_V_E_N___y ( Parameter_Table * P,
									       int S, int E, int I, int R, int C,
												 int S1, int I1, int S2, int I2, int S3, int I3,
									       int L, int X, int U, int W,
									       int A, int K,
									       double * Y,
									       double y );
