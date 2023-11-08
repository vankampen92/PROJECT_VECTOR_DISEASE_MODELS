void ArgumentControl(int argc, char **argv);

void Parameters_from_Command_Line(FILE *fp, Parameter_Table *P);

void Parameters_ModelReport(char *File, Parameter_Table *P);

int M_O_D_E_L( Parameter_Table * Table );

int M_O_D_E_L___S_I_M_P_L_E ( Parameter_Table * Table );

int B_A_S_I_N___o_f___A_T_T_R_A_C_T_I_O_N ( int , Parameter_Table *, 
					    int , double * , double * ,
					    int , double * , double * ,
					    int , 
					    double *, 
					    int * , int *  );


