/* Notice that Parameter_Table Struct depends and relies
   on the correct previous defintion of the structures
   Time_Control, Parameter_Model, and Parameter_Space
*/
typedef struct Parameter_Tableinfo
{
  /* * * Stochastic Realizations * * */
#include "include.Stochastic_Realizations.global.h"

  /* * * Rain Temperature Driven Dynamics * * */
#include "include.global.RainTemp.h"
  RainTemp R_T;

#if defined APPLYING_TREND
#include "include.Trend_Control.global.h"
  Trend_Control * Tr;
#endif

  /* * * Time_Control * * * */
#include "include.Time_Control.global.h"
  Time_Control * T;

  /* * * Parameter_Model * * * */
#include "include.Parameter_Model.global.h"
  Parameter_Model * P;

#include "include.Initial_Conditions.global.h"

  /* * * Parameter_Space * * * */
  /* Input Model Parameters */
  // int MODEL_INPUT_PARAMETERS;      Already included from "include.Parameter_Model.global.h" above !!!//
  char ** Name_Parameters;            // Name_Parameters  : Name Model Input Parameters
  char ** Code_Parameters;
  char ** Symbol_Parameters;
  double * Default_Vector_Parameters;
  /* What follows defines a parameter sub-space within
     the whole parameter space
  */
  int * Index;
  double * Vector_Parameters;
#include <include.PARAMETER_SPACE.global.h>
  Parameter_Space * S;
  /* * * * * * * * * */

  /* Model Output Variables */
  // int MODEL_OUTPUT_VARIABLES;     Already included from "include.Parameter_Model.global.h" above !!!//
  char ** Variable_Name;              // Variable_Name   : Name Output Variables
  double * Default_Vector_Output_Variables;
  /* What follows defines a subset of output variables
     that will be saved, represented, etc
  */
  int SUB_OUTPUT_VARIABLES;
  int * IO_VARIABLE_LIST;
  double * Vector_Output_Variables;
  /* * * * * * * * * */

  /* Model Dynamic Variables */
  // int MODEL_STATE_VARIABLES;      Already included from "include.Parameter_Model.global.h" above !!!//
  char ** Model_Variable_Name;
  double * Vector_Model_Variables;
  double * Vector_Model_Variables_Time_0;
  double * Vector_Model_Variables_Stationarity;
  double ** Vector_Model_Variables_MultiStability;
  /*
     Evaluation of the largest (xmax) and the tiniest (xmin)
     numbers my machine can handle
  */
  float nr___x_min;
  float nr___x_MAX;

  /* * * C P G   P L O T * * */
#if defined CPGPLOT_REPRESENTATION
#include <include.CPG.global.h>
  Parameter_CPGPLOT * CPG;
#endif

}Parameter_Table;

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C( Parameter_Table * );

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( Parameter_Table * );

void values_HumanMos(Parameter_Table * );
void values_TempDependency(double Temp, Parameter_Table *);

void Resetting_Parameter_Combination( Parameter_Table * Table,
                                      double H_Delta, double H_Sigma_0, double H_Recov_0, int n_H, double Beta_e,
                                      double H_Rho, double H_Nu,
                                      double L_Devel, double L_Delta, double K_0,
                                      double M_a, double M_b, double M_c, double M_Delta,
                                      int n_V, double M_Gamma );

double Threshold_Intensity(Parameter_Table *P, double F_0);

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( Parameter_Table * );


void AssignLabel_to_OutPut_Variables(int j, char * Label, Parameter_Table *P);

double AssignStructValue_to_VectorEntry(int j, Parameter_Table *P);

void AssignVectorEntry_to_Structure(Parameter_Table *P, int j, double value);

void AssignLabel_to_Parameters(int j, char * Label, Parameter_Table *P);

void AssignCodes_to_Parameters(int j, char * Label, Parameter_Table *P);

void AssignLabel_to_Model_Variables(int j, char * Label, Parameter_Table *P);
