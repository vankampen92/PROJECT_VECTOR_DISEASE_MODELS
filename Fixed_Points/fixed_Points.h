//Type of stability of Fixed points (according to eigenvalues)
#include "Type_of_Stability_of_Equilibria.h"
#include "Dominant_Period__Coherence_Number.h"
#include "Stable_Solution_Partial_Mosquito.h"

//Looking for void in file ./stable_Solution_CASES_33.c...
double q_Function(Parameter_Table *P);
double z_Function(Parameter_Table *P);
int Feasibility_Condition_H(Parameter_Table *P, double W, double y);
void stable_Solution(double y, double W, Parameter_Table *P, double *Y);
void stable_Solution_Free_Disease(Parameter_Table *P, double *Y);
void Human_Population_Initial_Conidition_from_Parameter_Table(Parameter_Table *P, double *Y);
//
//Looking for void in file ./intermediate_Root.c...
double intermediateRoot_Malaria (Parameter_Table *P, double x_lo, double x_hi);
//
//Looking for void in file ./Functions_Steady_State.c...
double Infectious_Human_asymptotic_Fraction(Parameter_Table *P);
double Infectious_Human_Steady_State_Fraction(const double W, Parameter_Table *P);
double Infectious_Mosquito_Steady_State(const double y, Parameter_Table *P);
double Inverted_Mosquito_Steady_State(const double W, Parameter_Table *P);

//Looking for void in file ./y_W_diagramm.c...
void y_W_diagramm(int k, Parameter_Table *P);
double I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M( Parameter_Table *P, int No, 
						      double *x_Data, double *y_1, double *y_2 );
void P_L_O_T_T_I_N_G___I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M( Parameter_Table * P, 
								      int N, 
								      int No_of_POINTS,
								      int Input_Parameter );
// 
//Looking for void in file ./fixed_Points.c...
void fixed_Points(Parameter_Table *P, double *y_Sol, double EPSILON);
double C_fixed_Points(Parameter_Table *P, double EPSILON);
void W_y_fixed_Points_Upper(Parameter_Table *P, double EPSILON, double *W, double *y);
void W_y_fixed_Points_Lower(Parameter_Table *P, double EPSILON, double *W, double *y);
void fixed_Points_Testing(Parameter_Table *P, double *y_Sol, double EPSILON);
// ... ... ... ...  
//Looking for void in file ./Functions_Steady_State_Mosquito.c...
double Total_Mosquito_Dynamic_State(Parameter_Table *P, double *y);
double Total_Mosquito_Steady_State(Parameter_Table *P);
int Feasibility_Condition_M(Parameter_Table *P);
double Total_Larva_Stable_State(Parameter_Table *P);
void Mosquito_Steady_State(const double y_C, const double y_I, double * Y, Parameter_Table * P);
// ... ... ... ...  
// In file ./fixed_Points_Intersection.c
int fixed_Points_Intersection(Parameter_Table * P,
                               double *y_Sol_Lower, double *y_Sol_Upper, double *y_Sol_Inter,
                               double *x_Data, double **y, int N );
// In file ./fixed_ALL_Points_Intersection.c
void F_I_X_E_D___A_L_L___P_O_I_N_T_S( Parameter_Table * P, 
				      double * y_SOL_Lower, 
				      double * y_SOL_Inter, 
				      double * y_SOL_Upper, 
				      double Epsi );
//Looking for void in file ./fixed_Points_ALL.c...
void fixed_Points_All(Parameter_Table *P, double *y_Sol_Lower, double *y_Sol_Upper, double *y_Sol_Inter, double EPSILON);
void fixed_Point_Lower(Parameter_Table *P, double *y_Sol, double EPSILON);
void fixed_Point_Upper(Parameter_Table *P, double *y_Sol, double EPSILON);
void fixed_Point_Intermediate( Parameter_Table * P, 
			       double W_l,double W_u, double y_l,double y_u,
			       double *y_Sol, double EPSILON);
void W_y_fixed_Points_Intermediate( Parameter_Table * P, 
				    double W_l,double W_u, double y_l,double y_u,
				    double EPSILON, double *W, double *y);
double y_Function (const double W, void *params);
// ... ... ... ...  
//Looking for void in file ./Multiple_Fixed_Points/main_Cases.c...
void checking_Solution(Parameter_Table *, double *);
// ... ... ... ...  
//Looking for void in file ./mosquito_Stable_Population.c...
double mosquito_Stable_Population(Parameter_Table *P);
double larva_Stable_Population(Parameter_Table *P);
// ... ... ... ...  
//Looking for void in file ./bifurcation_Diagram.c...
void B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M(Parameter_Table * P, double * y_0, double * y_1, double * y_2, 
					   int variable_code, double Epsi);
// ... ... ... ...  
//Looking for void in file ./fixed_Points_ACC.c...
void fixed_Points_ACC(Parameter_Table *P, double *y_Sol, double EPSILON, double T_obs);
