void write_Parameter_Table___RANGES___VALUES___LATEX ( char * table_Param, char * parameter_Space_Code, Parameter_Table * P,
                                                         double * Par_MAX, double * Par_min, int no_Par );

void write_Param_Table_PARAMETER_RANGES___LATEX ( char * table_Param, char * parameter_Space_Code, Parameter_Table *P, 
						  double * Par_MAX, double * Par_min, int no_Par );

void write_Param_Table_AVE_STD___LATEX( char * table_Param, Parameter_Table *P, 
					double * Par_AVE, double * Par_STD, int no_Par );

void write_Param_Table_AVE_CI___LATEX( char * table_Param, Parameter_Table *P, 
				       double * Par_AVE, double ** Confidence_Interval, int no_Par );

void write_Param_Table_Default_Values( char * table_Param, Parameter_Table * P, 
				       int no_Par );

void write_Param_Table(Parameter_Table *P);
