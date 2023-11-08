#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#/*                                                                           */
#/*                           David Alonso, 2011 (c)                          */
#/*                                                                           */
#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
##############################################################################################################
PROJECT_DIR=${HOME}/VECTOR_DISEASE_MODELS/#################
C_NR=${PROJECT_DIR}/Library/C_NumRecip/####################
HEAD.H =${PROJECT_DIR}Include/MODEL.h######################
INCLUDE_DIR=${PROJECT_DIR}Include/#########################
CPGPLOT =${HOME}/CPGPLOT/##################################
EXTRA_LIBRARY_PATH=-L/usr/local/pgplot/####################
EXTRA_LIBRARY_PATH+=-L${CPGPLOT}library/################### 
EXTRA_LIBRARY_PATH+=-L${CPGPLOT}library_basic_UTL/######### 
EXTRA_LIBRARY_PATH+=-L${C_NR}##############################
EXTRA_INCLUDE_PATH=-I/usr/local/pgplot##################### See custumized ./bashrc file on ${HOME} directory. 
EXTRA_INCLUDE_PATH+=-I${INCLUDE_DIR}#######################  
EXTRA_INCLUDE_PATH+=-I${PROJECT_DIR}#######################
EXTRA_INCLUDE_PATH+=-I${CPGPLOT}###########################
EXTRA_INCLUDE_PATH+=-I${CPGPLOT}library/###################
EXTRA_INCLUDE_PATH+=-I${CPGPLOT}library_basic_UTL/#########
EXTRA_INCLUDE_PATH+=-I${C_NR}##############################
##############################################################################################################
## C O M P I L A T I O N   O P T I O N   C O N T R O L I N G   N U M E R I C A L   R E C I P E S 
NR=NUMERICAL_RECIPES###############################
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   P R O G R A M   O U T P U T 
V=NON_VERBOSE###################################### Possibilities: 'VERBOSE' / 'NON_VERBOSE'
FILE=FILE_REPRESENTATION###################### Possibilities: 'FILE_REPRESENTATION' / 'NON_FILE_REPRESENTATION'
CPG=CPGPLOT_REPRESENTATION############## Possibilities: 'CPGPLOT_REPRESENTATION' / 'NON_CPGPLOT_REPRESENTATION'
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   P A R A M E T E R   S P A C E ###############
TYPE_of_BOUNDARY=_101### '_102' /'_101' / '_104' /
TYPE_of_INDEX=_CR_19p#   '_PR_19p' / '_CR_19p' /  
##############################################################################################################
STOCHASTIC_DIR=${PROJECT_DIR}Definition_Stochastic_Dynamics/####
RANDOM_SEED=CURRENT_TIME_RDN_SEED####### 'CURRENT_TIME_RDN_SEED' / 'FILE_RND_SEED' 
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   S U P E R I N F E C T I O N #################
S=SUPERINFECTION######################## Possibilities: 'NON_SUPERINFECTION' / 'SUPERINFECTION' 
Q=NON_THRESHOLD######################### Possibilities: 'QUEU_FUNCTION_THRESHOLD' / 'NON_THRESHOLD' /
RECOVERY=SUPERINFECTION_RECOVERY######## Possibilities: 'NON_SUPERINFECTION_RECOVERY' / 'SUPERINFECTION_RECOVERY'
SIGMA=SUPERINFECTION_SIGMA############## Possibilities: 'NON_SUPERINFECTION_SIGMA' / 'SUPERINFECTION_SIGMA'
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   M O D E L   D E F I N I T I O N #############
M_MODEL=LXVnW#################### 'LXVnW' / 'XkVnW' / 'XVnW' / 'XW' / 
H_MODEL=CASES_1#################### 'SI' / 'SEnI' / 'CASES_1' / 'NO_CASES' /  'CASES_33' / 'MacDonaldRoss' /
ODE_MODEL=${H_MODEL}-${M_MODEL}#################### 
ODE_MODEL_DEF=${H_MODEL}${M_MODEL}#################
##############################################################################################################
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   J A C O B I A N   T Y P E   ################# 
JACOBIAN=ODE####################################### 'ODE' / 'ODE_RESTRICTED_JACOBIAN'
EXTRA_INCLUDE_PATH+=-I${ODE_DEF}Include_${JACOBIAN}/
##############################################################################################################
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   N U M E R I C A L   I N T E G R A T I O N  ##
##############################################################################################################
GC=GONO_INDOORS######################### Possibiliites: 'GONO_INDOORS' / 'GONO_x_VALUE'
TEMPERATURE_SHIFT=FIXED_T_SHIFT_TEMPERATURE### Possibilities: 'FIXED_T_SHIFT_TEMPERATURE' / 'T_SHIFT_TEMPERATURE' (see rainTemperature.c)
KLEIN=N_O_N___K_L_E_I_N################# Possibilities: 'K_L_E_I_N' / 'N_O_N___K_L_E_I_N'
RESISTANCE=NON_EVOLUTION_of_RESISTANCE###### Possibilities: If 'K_L_E_I_N' is defined, this flag can be 'EVOLUTION_of_RESISTANCE'.
ERROR=ERROR_FUNCTION#################### Possibilities: 'ERROR_FUNCTION' / 'NON_ERROR_FUNCTION' 
######################################## Otherwise, this flag should always be 'NON_EVOLUTION_of_RESISTANCE'
RAIN_DELAY=NON_WATER_MATURATION_DELAY### Possibilities: 'WATER_MATURATION_DELAY' / 'WITHOUT_RAIN_DELAY'
AILY=MONTH_TIME_INTEGRATION############# Options: 'DAILY_TIME_INTEGRATION' / 'MONTH_TIME_INTEGRATION'
TEMPERATURE=TRUE_TEMPERATURE############ 'TEMPERATURE_FILE' / 'TRUE_TEMPERATURE'
TREND=APPLYING_TREND#################### 'APPLYING_TREND' 
##############################################################################################################
ODE_DIR_GENERAL=${PROJECT_DIR}Definition_Numerical_Integration/#########
ODE_DIR=${PROJECT_DIR}Definition_Numerical_Integration/${H_MODEL}/#########
ODE_DEF=${PROJECT_DIR}ODE_Definitions/##########################
ODE_FIXED_POINTS=${PROJECT_DIR}Fixed_Points/####################
TYPE_NUMERICAL_INTEGRATION=GSL_RK4##############################
######################################## Possibilities: 
######################################## 'GSL_BSIMP' uses the Jacobian matrix which has to be provided in JAC_sys${SYS}.c.
######################################## 'GSL_RKF45' is a general purpose integrator.
######################################## 'GSL_BSIMP' and GSL_RKF45 uses adaptive steps.
######################################## 'GSL_RK4' does not uses adaptive steps 
## D E F I N I T I O N   N A M E   M A I N   P R O G R A M     #####################################
TYPE_of_MAIN=_1D_SCAN#################   ' _1D_SCAN'   /   '_2D_SCAN' 
## D E F I N I T I O N   N A M E   E X E C U T B L E   C O D E ###############################################
EXE=${ODE_MODEL}_${TYPE_of_MAIN}
## ${T}_${ODE_MODEL}_${I}_${AILY}_I${TYPE_of_INDEX}_B${TYPE_of_BOUNDARY}_${S}_${CPG}_${NUMERICAL_INTEGRATION}_${GC}_${TEMPERATURE_SHIFT}_${RESISTANCE}
##############################################################################################################
EXTERN=#Possibilities: void (to be locally executed) / -static (to be non-locally executed) # 
######################################## Possibilities: GA (locally executed) / GA_EXTERN (non-locally executed)
LDFLAGS+=-lm -lgsl -lgslcblas -lNumRec -lNRUTL -lda_cpgplot_XY_GRID_FILE -lda_cpgplot_BASIC ${EXTRA_LIBRARY_PATH}
CXXFLAGS+=${EXTRA_INCLUDE_PATH} -D${NR} -D${V} -D${CPG} -D${FILE} -D${Q} -D${S} -D${SIGMA} -D${RECOVERY} -D${RANDOM_SEED} -D${ERROR} -D${JACOBIAN} -D${M_MODEL} -D${H_MODEL} -D${ODE_MODEL_DEF} -D${TYPE_NUMERICAL_INTEGRATION} -D${TREND} -D${AILY} -D${TEMPERATURE} -D${TEMPERATURE_SHIFT} -D${KLEIN} -D${RAIN_DELAY} -D${GC} -D${RESISTANCE} -DHAVE_INLINE ${EXTERN} -g #-Wall 
##############################################################################################################
# either -g or some optimization opiton, for instance, -O3 
# This makefile uses full power of conditional compilation. There is a bunch of variables that control this and
# are passed as flags -D[NAME_of_the_VARIABLE] to the compiler during compilation 
##############################################################################################################
LIBS=-L/usr/lib -lX11
PGPLOT_LIB=-L/usr/lib -lpgplot -L/usr/lib -lpng
CPGPLOT_LIB=-L/usr/lib -lcpgplot -lpgplot -L/usr/lib -lpng
##############################################################################################################
OBJECTS = main${TYPE_of_MAIN}.o report.o argumentControl.o MODEL.o MODEL_SIMPLE.o correlation_1DScan.o correlation_2DScan.o Maximum_Lag_Correlation.o                                                                           \
	Parameter_Model.o Time_Control.o Trend_Control.o Parameter_Table.o  values_HumanMos.o threshold_Intensity.o definition_OutPut_Variables.o assignCode_to_Input_Parameters.o assignLabel_to_Input_Parameters.o assignLabel_to_Output_Variables.o assignLabel_to_Model_Variables.o assignTableStructValue_to_Vector.o assignVectorEntry_to_TableStructure.o Input_Parameters_Output_Variables_fPRINT.o Latex_assignLabel_to_Input_Parameters.o  Latex_Write_Parameter_Table.o                           \
	P_A_R_A_M_E_T_E_R___S_P_A_C_E.o index.Definition${TYPE_of_INDEX}.o boundary${TYPE_of_BOUNDARY}.o \
                                                                                                         \
	deterministic_time_dynamics.o numerical_Integration_Driver.o initial_conditions_numerical_Integration.o Human_Population_Initial_Condition_from_Parameter_Table.o JAC_sys_${ODE_MODEL}.o JACOBIAN_matrix_${ODE_MODEL}.o ODE_sys_${ODE_MODEL}.o  Human_Population_Random_Initial_Condition.o            \
	Functions_Steady_State_${ODE_MODEL}.o stable_Solution_${ODE_MODEL}.o fixed_Points.o fixed_Points_ALL.o intermediate_Root.o fixed_ALL_Points_Intersection.o y_W_diagramm.o fixed_Points_Intersection.o Stable_Solution_Partial_Mosquito.o Functions_Steady_State_Mosquito.o                                                                                                   \
	superinfection_Functions.o total_Humans.o model_Variables_Code_${JACOBIAN}.o R_0.o Error_Function.o \
	superinfection_Functions_Recovery.o superinfection_Functions_Sigma.o                             \
                                                                                                         \
	stat.o GSL_stat.o                                                                                \
	GSL_Discrete_Sampling.o GSL_Init_Random_Seed.o                                                   \
                                                                                                         \
	time_Oscillations_Parameter_Forcing.o                                                            \
	CPGPLOT___X_Y___Parameter_Table.o

# init_Rain_and_Temp.o temperature_dependent_param_values.o paramResponse_Curves.o rainTemperature.o rainTemp_TimeTransformation.o rainTemp_ParamAverages.o setting_proper_daily_time.o                       

CC=gcc##
FF=gfortran##

all: ${EXE} COMPILATION_OPTIONS

${EXE}:  	$(OBJECTS)   
		$(FF) -o ${EXE} $(OBJECTS) $(LDFLAGS) $(CXXFLAGS) $(CPGPLOT_LIB) $(LIBS)

# da__qag.o:	/home/dalonso/GSL_v1.12/gsl-1.12/integration/da__qag.c
#		${CC} -c /home/dalonso/GSL_v1.12/gsl-1.12/integration/da__qag.c $(CXXFLAGS)

# Main${TYPE_Of_MAIN} program functions: 
main${TYPE_of_MAIN}.o: main${TYPE_of_MAIN}.c ${HEAD.H} 
	$(CC) -c main${TYPE_of_MAIN}.c $(CXXFLAGS)

report.o: report.c ${HEAD.H}
	${CC} -c report.c $(CXXFLAGS)

argumentControl.o: argumentControl.c ${HEAD.H}
	${CC} -c argumentControl.c $(CXXFLAGS)

MODEL.o: MODEL.c ${HEAD.H} 
	$(CC) -c MODEL.c $(CXXFLAGS)

MODEL_SIMPLE.o: MODEL_SIMPLE.c ${HEAD.H} 
	$(CC) -c MODEL_SIMPLE.c $(CXXFLAGS)

correlation_1DScan.o: correlation_1DScan.c ${HEAD.H} 
	$(CC) -c correlation_1DScan.c $(CXXFLAGS)

correlation_2DScan.o: correlation_2DScan.c ${HEAD.H} 
	$(CC) -c correlation_2DScan.c $(CXXFLAGS)

Maximum_Lag_Correlation.o: Maximum_Lag_Correlation.c ${HEAD.H} 
	$(CC) -c Maximum_Lag_Correlation.c $(CXXFLAGS)

# Funcions controling main data structures (Parameter_Model, Time_Control, 
# Parameter_Table):
Parameter_Model.o: ${PROJECT_DIR}Parameter_Model.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Parameter_Model.c $(CXXFLAGS)

Time_Control.o: ${PROJECT_DIR}Time_Control.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Time_Control.c $(CXXFLAGS)

Trend_Control.o: ${PROJECT_DIR}Trend_Control.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Trend_Control.c $(CXXFLAGS)

Parameter_Table.o: ${PROJECT_DIR}Parameter_Table.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Parameter_Table.c $(CXXFLAGS)

values_HumanMos.o: ${PROJECT_DIR}values_HumanMos.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}values_HumanMos.c $(CXXFLAGS)

threshold_Intensity.o: ${PROJECT_DIR}threshold_Intensity.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}threshold_Intensity.c $(CXXFLAGS)

definition_OutPut_Variables.o: ${PROJECT_DIR}definition_OutPut_Variables.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}definition_OutPut_Variables.c ${CXXFLAGS}

assignLabel_to_Input_Parameters.o: ${PROJECT_DIR}assignLabel_to_Input_Parameters.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}assignLabel_to_Input_Parameters.c $(CXXFLAGS)

assignLabel_to_Model_Variables.o: ${PROJECT_DIR}assignLabel_to_Model_Variables.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}assignLabel_to_Model_Variables.c $(CXXFLAGS)

assignLabel_to_Output_Variables.o: ${PROJECT_DIR}assignLabel_to_Output_Variables.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}assignLabel_to_Output_Variables.c $(CXXFLAGS)

assignVectorEntry_to_TableStructure.o: ${PROJECT_DIR}assignVectorEntry_to_TableStructure.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}assignVectorEntry_to_TableStructure.c $(CXXFLAGS)

assignTableStructValue_to_Vector.o:	${PROJECT_DIR}/assignTableStructValue_to_Vector.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}/assignTableStructValue_to_Vector.c $(CXXFLAGS)

assignCode_to_Input_Parameters.o:	${PROJECT_DIR}/assignCode_to_Input_Parameters.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}/assignCode_to_Input_Parameters.c $(CXXFLAGS)

Latex_assignLabel_to_Input_Parameters.o: ${PROJECT_DIR}/Latex_assignLabel_to_Input_Parameters.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}/Latex_assignLabel_to_Input_Parameters.c  ${CXXFLAGS}

Latex_Write_Parameter_Table.o:	${PROJECT_DIR}/Latex_Write_Parameter_Table.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}/Latex_Write_Parameter_Table.c ${CXXFLAGS}

Input_Parameters_Output_Variables_fPRINT.o: ${PROJECT_DIR}Input_Parameters_Output_Variables_fPRINT.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Input_Parameters_Output_Variables_fPRINT.c $(CXXFLAGS)

# Functions to control the definition of a subspace from the whole parameter space
P_A_R_A_M_E_T_E_R___S_P_A_C_E.o: ${PROJECT_DIR}Definition_Parameter_Space/P_A_R_A_M_E_T_E_R___S_P_A_C_E.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/P_A_R_A_M_E_T_E_R___S_P_A_C_E.c $(CXXFLAGS)

boundary${TYPE_of_BOUNDARY}.o:   ${PROJECT_DIR}Definition_Parameter_Space/boundary${TYPE_of_BOUNDARY}.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/boundary${TYPE_of_BOUNDARY}.c $(CXXFLAGS)

index.Definition${TYPE_of_INDEX}.o: ${PROJECT_DIR}Definition_Parameter_Space/index.Definition${TYPE_of_INDEX}.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/index.Definition${TYPE_of_INDEX}.c $(CXXFLAGS)

# Functions controling numerical integration of the ODE system
deterministic_time_dynamics.o: ${ODE_DIR}deterministic_time_dynamics.c ${HEAD.H} 
	$(CC) -c ${ODE_DIR}deterministic_time_dynamics.c $(CXXFLAGS)

numerical_Integration_Driver.o: ${ODE_DIR_GENERAL}numerical_Integration_Driver.c ${HEAD.H} 
	$(CC) -c ${ODE_DIR_GENERAL}numerical_Integration_Driver.c $(CXXFLAGS)

initial_conditions_numerical_Integration.o: ${ODE_DIR}initial_conditions_numerical_Integration.c ${HEAD.H}
	${CC} -c ${ODE_DIR}initial_conditions_numerical_Integration.c $(CXXFLAGS)

Human_Population_Initial_Condition_from_Parameter_Table.o: ${ODE_DIR}Human_Population_Initial_Condition_from_Parameter_Table.c ${HEAD.H}
	${CC} -c ${ODE_DIR}Human_Population_Initial_Condition_from_Parameter_Table.c $(CXXFLAGS)

Human_Population_Random_Initial_Condition.o: ${ODE_DIR}Human_Population_Random_Initial_Condition.c ${HEAD.H}
	\${CC} -c ${ODE_DIR}Human_Population_Random_Initial_Condition.c $(CXXFLAGS)

JACOBIAN_matrix_${ODE_MODEL}.o: ${ODE_DEF}JACOBIAN_matrix_${ODE_MODEL}.c ${HEAD.H} 
	$(CC) -c ${ODE_DEF}JACOBIAN_matrix_${ODE_MODEL}.c $(CXXFLAGS)

JAC_sys_${ODE_MODEL}.o: ${ODE_DEF}JAC_sys_${ODE_MODEL}.c ${HEAD.H} 
	$(CC) -c ${ODE_DEF}JAC_sys_${ODE_MODEL}.c $(CXXFLAGS)

ODE_sys_${ODE_MODEL}.o: ${ODE_DEF}ODE_sys_${ODE_MODEL}.c ${HEAD.H} 
	$(CC) -c ${ODE_DEF}ODE_sys_${ODE_MODEL}.c $(CXXFLAGS)

# Functions to control graphical plots
CPGPLOT___X_Y___Parameter_Table.o: ${CPGPLOT}CPGPLOT_Parameter_Table/CPGPLOT___X_Y___Parameter_Table.c ${CPGPLOT}CPGPLOT_Parameter_Table/CPGPLOT___X_Y___Parameter_Table.h
	${CC} -c ${CPGPLOT}CPGPLOT_Parameter_Table/CPGPLOT___X_Y___Parameter_Table.c $(CXXFLAGS) 

# Auxiliary functions to specify model ODE definition 
total_Humans.o: ${PROJECT_DIR}total_Humans.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}total_Humans.c $(CXXFLAGS)

model_Variables_Code_${JACOBIAN}.o: ${PROJECT_DIR}model_Variables_Code_${JACOBIAN}.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}model_Variables_Code_${JACOBIAN}.c $(CXXFLAGS)

superinfection_Functions.o: ${PROJECT_DIR}superinfection_Functions.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}superinfection_Functions.c $(CXXFLAGS)

superinfection_Functions_Recovery.o: ${PROJECT_DIR}superinfection_Functions_Recovery.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}superinfection_Functions_Recovery.c $(CXXFLAGS)

superinfection_Functions_Sigma.o: ${PROJECT_DIR}superinfection_Functions_Sigma.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}superinfection_Functions_Sigma.c $(CXXFLAGS)

Error_Function.o: ${PROJECT_DIR}Error_Function.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Error_Function.c $(CXXFLAGS)

# R_0 related functions:
R_0.o: ${PROJECT_DIR}R_0.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}R_0.c $(CXXFLAGS)

# Funcions to calculate the fixed points of the ODE system
fixed_Points.o: ${ODE_FIXED_POINTS}fixed_Points.c ${HEAD.H} 
	$(CC) -c ${ODE_FIXED_POINTS}fixed_Points.c $(CXXFLAGS)

fixed_ALL_Points_Intersection.o: ${ODE_FIXED_POINTS}fixed_ALL_Points_Intersection.c ${HEAD.H} 
	$(CC) -c ${ODE_FIXED_POINTS}fixed_ALL_Points_Intersection.c $(CXXFLAGS)

fixed_Points_ALL.o: ${ODE_FIXED_POINTS}fixed_Points_ALL.c ${HEAD.H} 
	$(CC) -c ${ODE_FIXED_POINTS}fixed_Points_ALL.c $(CXXFLAGS)

intermediate_Root.o: ${ODE_FIXED_POINTS}intermediate_Root.c ${HEAD.H} 
	$(CC) -c ${ODE_FIXED_POINTS}intermediate_Root.c $(CXXFLAGS)

y_W_diagramm.o: ${ODE_FIXED_POINTS}y_W_diagramm.c ${HEAD.H} 
	$(CC) -c ${ODE_FIXED_POINTS}y_W_diagramm.c $(CXXFLAGS)

fixed_Points_Intersection.o: ${ODE_FIXED_POINTS}fixed_Points_Intersection.c ${HEAD.H} 
	$(CC) -c ${ODE_FIXED_POINTS}fixed_Points_Intersection.c $(CXXFLAGS)

stable_Solution_${ODE_MODEL}.o: ${ODE_FIXED_POINTS}stable_Solution_${ODE_MODEL}.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}stable_Solution_${ODE_MODEL}.c $(CXXFLAGS)

Stable_Solution_Partial_Mosquito.o: ${ODE_FIXED_POINTS}Stable_Solution_Partial_Mosquito.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}Stable_Solution_Partial_Mosquito.c $(CXXFLAGS)

Functions_Steady_State_Mosquito.o: ${ODE_FIXED_POINTS}Functions_Steady_State_Mosquito.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}Functions_Steady_State_Mosquito.c $(CXXFLAGS)

Functions_Steady_State_${ODE_MODEL}.o: ${ODE_FIXED_POINTS}Functions_Steady_State_${ODE_MODEL}.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}Functions_Steady_State_${ODE_MODEL}.c $(CXXFLAGS)

# Functions involved in controling time dependent dynamics 
time_Oscillations_Parameter_Forcing.o: ${PROJECT_DIR}time_Oscillations_Parameter_Forcing.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}time_Oscillations_Parameter_Forcing.c $(CXXFLAGS)

# Functions involved in controling Rain and Temperature time dependent dynamics 
setting_proper_daily_time.o: ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/setting_proper_daily_time.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/setting_proper_daily_time.c ${CXXFLAGS}

setting_processing_daily_time.o: ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/setting_processing_daily_time.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/setting_processing_daily_time.c ${CXXFLAGS}

init_Rain_and_Temp.o: ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/init_Rain_and_Temp.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/init_Rain_and_Temp.c $(CXXFLAGS)

rainTemperature.o: ../../rainTemperature.c ${HEAD.H}
	${CC} -c ../../rainTemperature.c $(CXXFLAGS)

temperature_dependent_param_values.o: ../../temperature_dependent_param_values.c ${HEAD.H}
	${CC} -c ../../temperature_dependent_param_values.c $(CXXFLAGS)

rainTemp_ParamAverages.o: ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/rainTemp_ParamAverages.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/rainTemp_ParamAverages.c $(CXXFLAGS)

rainTemp_TimeTransformation.o: ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/rainTemp_TimeTransformation.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/rainTemp_TimeTransformation.c $(CXXFLAGS)

Average_Seasonal_Cycle.o: ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/Average_Seasonal_Cycle.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Rain_Temperature_Dependency/Average_Seasonal_Cycle.c $(CXXFLAGS)

# Library of generic statistical functions and generic basic libraries to perform stochatic simulations  
stat.o:	${PROJECT_DIR}stat.c ${PROJECT_DIR}stat.h
	${CC} -c ${PROJECT_DIR}stat.c $(CXXFLAGS)

GSL_stat.o:	${PROJECT_DIR}GSL_stat.c ${PROJECT_DIR}stat.h
	${CC} -c ${PROJECT_DIR}GSL_stat.c $(CXXFLAGS)

GSL_Discrete_Sampling.o: ${PROJECT_DIR}GSL_Discrete_Sampling.c ${PROJECT_DIR}GSL_stat.h
	${CC} -c ${PROJECT_DIR}GSL_Discrete_Sampling.c $(CXXFLAGS)

GSL_Init_Random_Seed.o: ${PROJECT_DIR}GSL_Init_Random_Seed.c ${PROJECT_DIR}GSL_stat.h
	${CC} -c ${PROJECT_DIR}GSL_Init_Random_Seed.c $(CXXFLAGS)
#
clean:  
	rm -f *.o *~ core        
#
COMPILATION_OPTIONS:
	echo "Main model definition compilation options:" > ${EXE}_COMPILATION_OPTIONS.txt
	echo "${T}"                                    >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${ODE_MODEL}"                            >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${I}"                                    >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${AILY}"                                 >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "I${TYPE_of_INDEX}_B${TYPE_of_BOUNDARY}"  >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${S}"                                    >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${CPG}"                                  >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${TYPE_NUMERICAL_INTEGRATION}"           >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${GC}"                                   >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${TEMPERATURE_SHIFT}"                    >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${RESISTANCE}"                           >> ${EXE}_COMPILATION_OPTIONS.txt		
	echo "MAIN program: main${TYPE_of_MAIN}.c"    >> ${EXE}_COMPILATION_OPTIONS.txt         
	echo "---------------------------------------" >> ${EXE}_COMPILATION_OPTIONS.txt        
	echo "All compilation options as passed to the compiler through CXXFLAGS:" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${CXXFLAGS}"                             >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "---------------------------------------" >> ${EXE}_COMPILATION_OPTIONS.txt        
	echo "All linking options as passed to the linker through LDFLAGS, CPGPLOT_LIG and LIBS:" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "$(LDFLAGS) $(CPGPLOT_LIB) $(LIBS)"                                                  >> ${EXE}_COMPILATION_OPTIONS.txt

