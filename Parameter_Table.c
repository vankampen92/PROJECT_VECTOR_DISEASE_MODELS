#include "./Include/MODEL.h"

#if defined CPGPLOT_REPRESENTATION
#include <include.CPG.extern.h>
#endif
#include "./Include/include.Time_Control.extern.h"
#include "./Include/include.Output_Variables.extern.h"
#include "./Include/include.Parameter_Model.extern.h"
#include "./Include/include.PARAMETER_SPACE.extern.h"
#include "./Include/include.Initial_Conditions.extern.h"
#include "./Include/include.Stochastic_Realizations.extern.h"

#if defined APPLYING_TREND
#include "./Include/include.Trend_Control.extern.h"
#endif

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C( Parameter_Table *T )
{
  int i;

  /* Model parameters are all input parameters defining and controling
     model dynamics (both through simulation and mathematically, in case
     the model has a mathematical description such as a system of ODEs)
  */
  T->Code_Parameters = (char **)malloc( MODEL_INPUT_PARAMETERS * sizeof(char *) );
  for (i=0; i<MODEL_INPUT_PARAMETERS; i++){
    T->Code_Parameters[i] = (char *)malloc( 100 * sizeof(char) );
  }
  T->Name_Parameters = (char **)malloc( MODEL_INPUT_PARAMETERS * sizeof(char *) );
  for (i=0; i<MODEL_INPUT_PARAMETERS; i++){
    T->Name_Parameters[i] = (char *)malloc( 100 * sizeof(char) );
  }
  T->Default_Vector_Parameters = (double *)malloc( MODEL_INPUT_PARAMETERS * sizeof(double) );

  T->Index = (int *)malloc( SUB_MODEL_PARAMETERS * sizeof(int) );
  T->Vector_Parameters = (double *)malloc( SUB_MODEL_PARAMETERS * sizeof(double) );

  /* Output Variables are any measure of the state model variables of any function of
     these at any given time */
  T->Variable_Name = (char **)malloc( MODEL_OUTPUT_VARIABLES * sizeof(char *) );
  for (i=0; i<MODEL_OUTPUT_VARIABLES; i++){
    T->Variable_Name[i] = (char *)malloc( 100 * sizeof(char) );
  }
  T->Default_Vector_Output_Variables = (double *)malloc( MODEL_OUTPUT_VARIABLES * sizeof(double) );

  T->IO_VARIABLE_LIST = (int *)malloc( SUB_OUTPUT_VARIABLES * sizeof(int) );
  T->Vector_Output_Variables = (double *)malloc( SUB_OUTPUT_VARIABLES * sizeof(double) );

  T->Vector_Model_Variables_MultiStability =(double **)calloc( 3, sizeof(double *) );

  /* Model Variables represent only the state model variables, i.e., the set of variables
     completely defining the state of the system at any given time. Model Variables can be,
     of course, also output variables. They can be defined as output variables
     whose definition can be found at Definition_Output_Variables.c */

  /* Some implementations of this code require to alloc memmory according to
     a number of state variables that can change dynamically. In that case, this
     6 lines of code should be commented out. Notice alse the corresponding lines
     in void P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( Parameter_Table * T )

     For most calculations, I opted for allocating this part of the data structure
     only if needed (see ./MODEL_CALCULATIONS/TIME_EVO_DETERMINISTIC/MODEL.c) regardless
     the number of MODEL STATE VARIABLES changing or not during execution. Essentially,
     the numerical integration of a system of ODEs relies on T->Vector_Model_Variables.
     Therefore, a driver, usaully called void MODEL(Parameter_Table *), is in charge
     of doing this allocation previous to calling the numerical integration function,
     and deallocating this memmory right after.
  */
  // T->Model_Variable_Name = (char **)malloc( MODEL_STATE_VARIABLES * sizeof(char *) );
  // for (i=0; i<MODEL_STATE_VARIABLES; i++){
  //   T->Model_Variable_Name[i] = (char *)malloc( 100 * sizeof(char) );
  // }
  // T->Vector_Model_Variables = (double *)malloc( MODEL_STATE_VARIABLES * sizeof(double) );
  // T->Vector_Model_Variables_Time_0 = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) ); 
  // T->Vector_Model_Variables_Stationarity = (double *)malloc( MODEL_STATE_VARIABLES * sizeof(double) );
}

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( Parameter_Table * T )
{
  int i;

  /* * * Stochastic Realizations Upload * * */
  T->DISCARTING_EXTINCTIONS = DISCARTING_EXTINCTIONS;
  T->Realizations           = Realizations;
  /* * * Rain Temperature Upload * * */
  /* * * * * * * * * * * * * * * * * */
  
#if defined APPLYING_TREND
  /* Trend Control Upload */
  T->Tr_No_of_Jumps = Tr_No_of_Jumps;
  T->Tr_value_0     = Tr_value_0;
  T->Tr_value_1     = Tr_value_1;
  T->Tr_value_i     = Tr_value_i;
  T->Tr_Time_0      = Tr_Time_0;
  T->Tr_Time_1      = Tr_Time_1;
  T->Tr_Time_i      = Tr_Time_i;
  T->Tr_Input_Parameter = Tr_Input_Parameter;
  T->TREND_TYPE         = TREND_TYPE;
#endif

  /* Time Control Upload */
  T->I_Time = I_Time;
  T->Time_0 = Time_0;
  T->Time_1 = Time_1;
  T->Time_Scale_Unit = Time_Scale_Unit;;
  T->TYPE_of_TIME_DEPENDENCE = TYPE_of_TIME_DEPENDENCE;
  T->EPSILON         = EPSILON;

  /* Parameter Model Upload */
  values_HumanMos(T);

  /* Calculate temperature dependent parameters & update table */
  // values_TempDependency(T->Temp, T);
  /*                        */

  /* Initial Conditions Upload */
  T->TYPE_of_INITIAL_CONDITION = TYPE_of_INITIAL_CONDITION; 
  T->s__0 = s__0; /* Susceptible fraction */
  T->e__0 = e__0; /* Total fraction of exposed */
  T->e__2 = e__2; /* Total fraction of exposed (in the R class, of Klein etal's model */
  T->i__0 = i__0; /* Infectious fraction */
  T->r__0 = r__0; /* Fraction of recovered */
  T->c__0 = c__0; /* Cases fraction */

  T->s1__0 = s1__0; /* Fractions for classes (SnInR models) */
  T->i1__0 = i1__0;
  T->s2__0 = s2__0;
  T->i2__0 = i2__0;
  T->s3__0 = s3__0;
  T->i3__0 = i3__0;
  /* Parameters Defining Initial Conditions for Mosquitoes */
  T->l__0 = l__0;
  T->m__0 = m__0;
  T->m__i = m__i; /* Total fraction of infected mosquitoes */
  
  /* Parameter Space Upload: PARAMETER SPACE   */
  /* Total number of actual input paramters */
  T->SUB_MODEL_PARAMETERS = SUB_MODEL_PARAMETERS;
  T->A_n = A_n;
  T->A_d = A_d;
  T->No_of_POINTS    = No_of_POINTS;
  T->Input_Parameter = Input_Parameter;
  T->Value_0         = Value_0;
  T->Value_1         = Value_1;
  /* Total number of potential input paramters */
  T->MODEL_INPUT_PARAMETERS = MODEL_INPUT_PARAMETERS;

  /* Total number of actual model output variables */
  T->SUB_OUTPUT_VARIABLES   = SUB_OUTPUT_VARIABLES;
  /* Total number of potential model output variables */
  T->MODEL_OUTPUT_VARIABLES = MODEL_OUTPUT_VARIABLES;

  /* Total number of potential state variables */
  T->MODEL_STATE_VARIABLES  = MODEL_STATE_VARIABLES;

  /* Type of Model upload  */
  T->TYPE_of_MODEL        = TYPE_of_MODEL;

#if defined CASES_1
  T->TYPE_of_MODEL        = 11;
#endif
#if defined CASES_1LXVnW
  T->TYPE_of_MODEL        = 11;
#endif
#if defined CASES_1XkVnW
  T->TYPE_of_MODEL        = 12;
#endif
#if defined CASES_1XVnW
  T->TYPE_of_MODEL        = 13;
#endif
#if defined CASES_1XW
  T->TYPE_of_MODEL        = 14;
#endif

#if defined NO_CASES
  T->TYPE_of_MODEL        = 21;
#endif
#if defined NO_CASESLXVnW
  T->TYPE_of_MODEL        = 21;
#endif
#if defined NO_CASESXkVnW
  T->TYPE_of_MODEL        = 22;
#endif
#if defined NO_CASESXVnW
  T->TYPE_of_MODEL        = 23;
#endif
#if defined NO_CASESXW
  T->TYPE_of_MODEL        = 24;
#endif

#if defined SEnI
  T->TYPE_of_MODEL        = 31;
#endif
#if defined SEnILXVnW
  T->TYPE_of_MODEL        = 31;
#endif
#if defined SEnIXkVnW
  T->TYPE_of_MODEL        = 32;
#endif
#if defined SEnIXVnW
  T->TYPE_of_MODEL        = 33;
#endif
#if defined SEnIXW
  T->TYPE_of_MODEL        = 34;
#endif

#if defined SI
  T->TYPE_of_MODEL        = 41;
#endif
#if defined SILXVnW
  T->TYPE_of_MODEL        = 41;
#endif
#if defined SIXkVnW
  T->TYPE_of_MODEL        = 42;
#endif
#if defined SIXVnW
  T->TYPE_of_MODEL        = 43;
#endif
#if defined SIXW
  T->TYPE_of_MODEL        = 44;
#endif

#if defined SnInR
  T->TYPE_of_MODEL        = 51;
#endif
#if defined SnInRLXVnW
  T->TYPE_of_MODEL        = 51;
#endif
#if defined SnInRXkVnW /* None of these following SnInR models are unpacked anywhere else yet */
  T->TYPE_of_MODEL        = 52;
#endif
#if defined SnInRint
  T->TYPE_of_MODEL        = 53;
#endif
#if defined SnInRXW
  T->TYPE_of_MODEL        = 54;
#endif

#if defined MacDonaldRoss
  T->TYPE_of_MODEL        = 2;
#endif

#if defined CASES_33
  T->TYPE_of_MODEL        = 0;
#endif

  T->Growth_Function_Type = Growth_Function_Type;
  
  /* BEGIN: Parameter default values into vector structure */
  for(i = 0; i<MODEL_INPUT_PARAMETERS; i++){
    T->Default_Vector_Parameters[i] = AssignStructValue_to_VectorEntry(i, T);
  }
  /*   END: Parameter default values into vector structure */

  /* BEGIN: Names and codes for model parameters */
  for(i = 0; i<MODEL_INPUT_PARAMETERS; i++){
    AssignLabel_to_Parameters(i, T->Name_Parameters[i], T);
    AssignCodes_to_Parameters(i, T->Code_Parameters[i], T);
  }
  /*   END: Names and codes for model parameter  */

  /* BEGIN: Names for output variables           */
  for(i = 0; i<MODEL_OUTPUT_VARIABLES; i++){
    AssignLabel_to_OutPut_Variables(i, T->Variable_Name[i], T);
  }
  /*   END: Names for output variables */

  /* BEGIN: Default model input parameters */
  i=0;
  while (i < SUB_MODEL_PARAMETERS) {
    T->Index[i] = i;
    i++;
  }
  // This assignation will be overwritten when Parameter_Space structure is setup
  /*  END: Default model input parameters */

  /* BEGIN: Default model input parameters */
  if ( 0 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[0] = variable_0;
  if ( 1 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[1] = variable_1;
  if ( 2 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[2] = variable_2;
  if ( 3 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[3] = variable_3;
  if ( 4 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[4] = variable_4;
  if ( 5 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[5] = variable_5;
  if ( 6 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[6] = variable_6;
  if ( 7 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[7] = variable_7;
  if ( 8 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[8] = variable_8;
  if ( 9 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[9] = variable_9;
  if ( 10 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[10] = variable_10;
  if ( 11 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[11] = variable_11;
  if ( 12 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[12] = variable_12;
  if ( 13 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[13] = variable_13;
  if ( 14 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[14] = variable_14;
  if ( 15 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[15] = variable_15;
  if ( 16 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[16] = variable_16;
  if ( 17 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[17] = variable_17;
  if ( 18 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[18] = variable_18;
  if ( 19 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[19] = variable_19;
  if ( 20 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[20] = variable_20;
  if ( 21 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[21] = variable_21;
  if ( 22 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[22] = variable_22;
  if ( 23 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[23] = variable_23;
  if ( 24 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[24] = variable_24;
  if ( 25 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[25] = variable_25;
  if ( 26 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[26] = variable_26;
  if ( 27 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[27] = variable_27;
  if ( 28 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[28] = variable_28;
  if ( 29 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[29] = variable_29;
  if ( 30 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[30] = variable_30;
  if ( 31 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[31] = variable_31;
  if ( 32 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[32] = variable_32;
  if ( 33 < SUB_OUTPUT_VARIABLES ) T->IO_VARIABLE_LIST[33] = variable_33;
  /*   END: Output variable current actual values into IO_VARIABLE_LIST vector */

  /* Some implementations of this code require to alloc memmory according to
     a number of state variables that can change dynamically. In that case, this
     3 lines of code should be commented out. Notice alse the corresponding lines
     in the function below:
     void P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( Parameter_Table * T )
     Only if the number of dynamic state model variables never cange during execution,
     these lines of code make sense here
  */
  /* Initial Conditions: MODEL STATE VARIABLES */
  // for (i=0; i < MODEL_STATE_VARIABLES; i++){
  //    AssignLabel_to_Model_Variables(i, Table->Model_Variable_Name[i], Table);
  // }
}

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( Parameter_Table * T )
{
  int i;

  for (i=0; i < T->MODEL_INPUT_PARAMETERS; i++){
    free( T->Code_Parameters[i] );
  }
  free(T->Code_Parameters);

  for (i=0; i < T->MODEL_INPUT_PARAMETERS; i++){
    free( T->Name_Parameters[i] );
  }
  free(T->Name_Parameters);
  free(T->Default_Vector_Parameters);

  free(T->Index);
  free(T->Vector_Parameters);

  for (i=0; i < T->MODEL_OUTPUT_VARIABLES; i++){
    free(T->Variable_Name[i]);
  }
  free(T->Variable_Name);
  free(T->Default_Vector_Output_Variables);

  /* Some implementations of this code require to alloc memmory according to
     a number of model variables that can change dynamically.

     For most calculations,  I opted for allocating/de-allocating this part of
     the data structure only if needed
     (see, for instance, ./MODEL_CALCULATIONS/TIME_EVO_DETERMINISTIC/MODEL.c)
     regardless the number of MODEL STATE VARIABLES changing or not during execution.
  */

  // for (i=0; i<MODEL_STATE_VARIABLES; i++){
  //   free(T->Model_Variable_Name[i]);
  // }
  // free(T->Model_Variable_Name);
  // free( T->Vector_Model_Variables );
  // free( T->Vector_Model_Variables_Stationarity );
  // free( T->Vector_Model_Variables_MultiStability[0] );
  // free( T->Vector_Model_Variables_MultiStability[1] );
  // free( T->Vector_Model_Variables_MultiStability[2] );
  // free( T->Vector_Model_Variables_Time_0 );
  
  free(T->Vector_Model_Variables_MultiStability);

  free(T->IO_VARIABLE_LIST);
  free(T->Vector_Output_Variables);
}
