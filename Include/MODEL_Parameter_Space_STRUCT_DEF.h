typedef struct Parameter_Space_info
{
  gsl_vector * P_MAX;         /* Max and Min for each parameter */
  gsl_vector * P_min;     
  int * I;
  gsl_vector * Accuracy;      /* Different accuracy for each searcheable parameter */
  int nPar;

#include <include.PARAMETER_SPACE.global.h>

#if defined PARAMETRIC_CONFIGURATIONS
  int No_Parametric_Configurations;
  double ** Parametric_Configuration;
#endif
}Parameter_Space;

/* void Boundary(int j, double *value_0, double *value_1); */

/* void Index_Definition(int * Index, Parameter_Table * T); */

/* void P_A_R_A_M_E_T_E_R___S_P_A_C_E___A_L_L_O_C( Parameter_Space *S, Parameter_Table * T); */

/* void P_A_R_A_M_E_T_E_R___S_P_A_C_E___U_P_L_O_A_D( Parameter_Space * S, Parameter_Table * T,  */
/* 						  double A_n, double A_d ); */

/* void P_A_R_A_M_E_T_E_R___S_P_A_C_E___F_R_E_E( Parameter_Space * S ); */
