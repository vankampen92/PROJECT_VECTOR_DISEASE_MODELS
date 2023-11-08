#include "HEADERS.h"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                    HUMAN-VECTOR TRANSMITTED DISEASE DYNAMICS              */
/*	                                                                     */
/*                            David Alonso, 2011 (c)                         */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define HUMAN_CONSTANT_POPULATION

#define INTEGER_CODE_FOR_TIME_DIMENSION 0

#define MODEL_VARIABLES_MAXIMUM 5    /* Maximum no of MODEL (state) VARIABLES  --- this is unused?*/

#define MODEL_PARAMETERS_MAXIMUM 58  /* Maximum no of MODEL (input) PARAMETERS */

#define OUTPUT_VARIABLES_MAXIMUM 34  /* Maximum no of MODEL (output) VARIABLES */

typedef struct totalRateinfo
{
  double Total_Rate;
  double max_Probability;
}Stochastic_Rate;

#include "MODEL_RainTemp_STRUCT_DEF.h"

#include "MODEL_Time_Control_STRUCT_DEF.h"

#include "MODEL_Trend_Control_STRUCT_DEF.h"

#include "MODEL_Parameter_Space_STRUCT_DEF.h"

#include "MODEL_Parameter_Model_STRUCT_DEF.h"

#include "MODEL_Parameter_Table_STRUCT_DEF.h"

#include <Time_Control.h>

#include <./Definition_Parameter_Space/P_A_R_A_M_E_T_E_R___S_P_A_C_E.h>

#include <Parameter_Model.h>

/* Auxiliary Functions */
#include "main.H"
#include <assign.h>
#include <total_Humans.h>
#include <model_Variables_Code.h>
#include <definition_OutPut_Variables.h>
#include <superinfection_Functions.h>
#include <R_0.h>
#include <time_Oscillations_Parameter_Forcing.h>
#include <Input_Parameters_Output_Variables_fPRINT.h>
#include <Latex_Write_Parameter_Table.h>

#include <Fixed_Points/parameter_Simple_Scan.h>
#include <Fixed_Points/bifurcation_Diagram.h>
#include <Fixed_Points/fixed_Points.h>

#include <generic_Function_Parameter_Scan.h>
#include <generic_Subregion_Parameter_Space.h>
#include <generic_Random_Parameter_Space.h>
#include <generic_Random_Parameter_Space_Plus.h>

#include <./MODEL_CALCULATIONS/RANDOM_SCAN_COEXISTENCE_of_EQUILIBRIA/free_disease_stability.h>
#include <./MODEL_CALCULATIONS/VISUAL_SCAN_DOMINANT_PERIODS/dominant_Period_Coherent_Number.h>
#include <./MODEL_CALCULATIONS/VISUAL_SCAN_DYNAMICAL_REGIMS/dynamic_Regims.h>
#include <./MODEL_CALCULATIONS/VISUAL_SCAN_DYNAMICAL_REGIMS/coexistence_dynamic_Equilibria.h>
#include <./MODEL_CALCULATIONS/VISUAL_SCAN_PARAMETRIC_FUNCTION/R_0___Subdominant_Eigenvalue.h>
#include <./MODEL_CALCULATIONS/INPUT_OUTPUT_CORRELATION/correlation_Scan.h>
#include <eigen_Functions.h>
#include <Eigenvalue_Calculation.h>

#include <Definition_Numerical_Integration/deterministic_time_dynamics.h>
#include <Definition_Numerical_Integration/numerical_Integration_Driver.h>
#include <Definition_Numerical_Integration/initial_conditions_numerical_Integration.h>
#include <ODE_Definitions/ODE_Definitions.h>

#if defined APPLYING_TREND
#include <Trend_Control.h>
#endif

#if defined ERROR_FUNCTION
#include <Error_Function.h>
#endif

#if defined CPGPLOT_REPRESENTATION
/* Header file for Parameter Table dependent CPGPLOT plotting auxiliary functions */
#include <CPGPLOT_Parameter_Table/CPGPLOT___X_Y___Parameter_Table.h>
#endif
