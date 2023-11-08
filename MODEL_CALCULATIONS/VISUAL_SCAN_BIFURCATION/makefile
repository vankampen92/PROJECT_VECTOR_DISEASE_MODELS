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
##############################################################################################################
## C O M P I L A T I O N   O P T I O N   C O N T R O L I N G   N U M E R I C A L   R E C I P E S 
NR=NUMERICAL_RECIPES#############################
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   P R O G R A M   O U T P U T 
V=NON_VERBOSE########################### Possibilities: 'VERBOSE' / 'NON_VERBOSE'
CPG=CPGPLOT_REPRESENTATION############## Possibilities: 'CPGPLOT_REPRESENTATION' / 'NON_CPGPLOT_REPRESENTATION'
FILE=FILE_REPRESENTATION################ Possibilities: 'FILE_REPRESENTATION'  / ' NON_FILE_REPRESENTATION'
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   P A R A M E T E R   S P A C E ###############
TYPE_of_BOUNDARY=_101### '_101' / '_102'
TYPE_of_INDEX=_PR_19p#   '_09_22p' / '_08_21p' / '08_18p' / 
##############################################################################################################
STOCHASTIC_DIR=${PROJECT_DIR}Definition_Stochastic_Dynamics/####
RANDOM_SEED=CURRENT_TIME_RDN_SEED####### 'CURRENT_TIME_RDN_SEED' / 'FILE_RND_SIDE' 
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   S U P E R I N F E C T I O N #################
S=SUPERINFECTION######################## Possibilities: 'NON_SUPERINFECTION' / 'SUPERINFECTION' 
Q=NON_THRESHOLD######################### Possibilities: 'QUEU_FUNCTION_THRESHOLD' / 'NON_THRESHOLD' /
RECOVERY=SUPERINFECTION_RECOVERY######## Possibilities: 'NON_SUPERINFECTION_RECOVERY' / 'SUPERINFECTION_RECOVERY'
SIGMA=SUPERINFECTION_SIGMA############## Possibilities: 'NON_SUPERINFECTION_SIGMA' / 'SUPERINFECTION_SIGMA'
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   N U M E R I C A L   I N T E G R A T I O N  ##
ODE_DEF=${PROJECT_DIR}ODE_Definitions/##########################
ODE_FIXED_POINTS=${PROJECT_DIR}Fixed_Points/####################
ERROR=ERROR_FUNCTION#################### Possibilities: 'ERROR_FUNCTION' / 'NON_ERROR_FUNCTION'
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   M O D E L   D E F I N I T I O N #############
M_MODEL=XW#################### 'LXVnW' / 'XkVnW' / 'XVnW' / 'XW' / 
H_MODEL=SI#################### 'SI' / 'SEnI' / 'CASES_1' / 'NO_CASES' /  'CASES_33' / 'MacDonaldRoss' /
ODE_MODEL=${H_MODEL}-${M_MODEL}#################### 
ODE_MODEL_DEF=${H_MODEL}${M_MODEL}#################
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   J A C O B I A N   T Y P E   ################# 
JACOBIAN=ODE_RESTRICTED_JACOBIAN# 'ODE' / 'ODE_RESTRICTED_JACOBIAN'
EXTRA_INCLUDE_PATH+=-I${ODE_DEF}Include_${JACOBIAN}/
##############################################################################################################
EXTERN=#Possibilities: void (to be locally executed) / -static (to be non-locally executed) # 
######################################## Possibilities: GA (locally executed) / GA_EXTERN (non-locally executed)
LDFLAGS+=-lm -lgsl -lgslcblas -lNumRec -lNRUTL -lda_cpgplot_XY_GRID_FILE -lda_cpgplot_BASIC ${EXTRA_LIBRARY_PATH}
CXXFLAGS+=${EXTRA_INCLUDE_PATH} -D${NR} -D${V} -D${CPG} -D${FILE} -D${Q} -D${S} -D${SIGMA} -D${RECOVERY} -D${RANDOM_SEED} -D${ERROR} -D${JACOBIAN} -D${M_MODEL} -D${H_MODEL} -D${ODE_MODEL_DEF} -DHAVE_INLINE ${EXTERN} -g #-Wall 
##############################################################################################################
# either -g or some optimization opiton, for instance, -O3 
# This makefile uses full power of conditional compilation. There is a bunch of variables that control this and
# are passed as flags -D[NAME_of_the_VARIABLE] to the compiler during compilation 
##############################################################################################################
LIBS=-L/usr/lib -lX11
PGPLOT_LIB=-L/usr/lib -lpgplot -L/usr/lib -lpng
CPGPLOT_LIB=-L/usr/lib -lcpgplot -lpgplot -L/usr/lib -lpng
##############################################################################################################
TYPE_of_MAIN=##### [void] / '_SIMPLE' / '_DIAGRAM_y_W' / '_SIMPLE_TWO'
TYPE_of_BIFURCATION=_Intersection### / '_ALL' / '_Intersection' /
## D E F I N I T I O N   N A M E   E X E C U T B L E   C O D E ###############################################
EXE=${ODE_MODEL}${TYPE_of_MAIN}
##############################################################################################################
## ${T}_${ODE_MODEL}_${I}_${AILY}_I${TYPE_of_INDEX}_B${TYPE_of_BOUNDARY}_${S}_${CPG}_${NUMERICAL_INTEGRATION}_${GC}_${TEMPERATURE_SHIFT}_${RESISTANCE}
##############################################################################################################
OBJECTS = main${TYPE_of_MAIN}.o report.o argumentControl.o     \
	Parameter_Table.o  assignCode_to_Input_Parameters.o assignLabel_to_Input_Parameters.o assignLabel_to_Output_Variables.o assignLabel_to_Model_Variables.o assignTableStructValue_to_Vector.o assignVectorEntry_to_TableStructure.o Input_Parameters_Output_Variables_fPRINT.o definition_OutPut_Variables.o R_0.o Error_Function.o                                                                                                                                        \
	values_HumanMos.o total_Humans.o superinfection_Functions.o superinfection_Functions_Recovery.o superinfection_Functions_Sigma.o threshold_Intensity.o model_Variables_Code_${JACOBIAN}.o                                                                                                                                          \
	P_A_R_A_M_E_T_E_R___S_P_A_C_E.o index.Definition${TYPE_of_INDEX}.o boundary${TYPE_of_BOUNDARY}.o         \
	JAC_sys_${ODE_MODEL}.o JACOBIAN_matrix_${ODE_MODEL}.o ODE_sys_${ODE_MODEL}.o                             \
	Functions_Steady_State_${ODE_MODEL}.o stable_Solution_${ODE_MODEL}.o Functions_Steady_State_Mosquito.o Stable_Solution_Partial_Mosquito.o                                                    \
	fixed_Points.o fixed_Points_ALL.o intermediate_Root.o fixed_Points_Intersection.o                        \
	GSL_stat.o stat.o                                      \
	GSL_Discrete_Sampling.o GSL_Init_Random_Seed.o         \
	C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M.o bifurcation_Diagram${TYPE_of_BIFURCATION}.o bifurcation_Diagram_Parameter_Scan.o bifurcation_Diagram_Simple_Scan.o Separating_and_Saving_Bifurcation_Branches.o y_W_diagramm.o  
#stat.o                                       
CC=gcc##
FF=gfortran##

all: ${EXE} COMPILATION_OPTIONS

${EXE}:  	$(OBJECTS)   
		$(FF) -o ${EXE} $(OBJECTS) $(LDFLAGS) $(CXXFLAGS) $(CPGPLOT_LIB) $(LIBS)

# Main program functions: 
main${TYPE_of_MAIN}.o: main${TYPE_of_MAIN}.c ${HEAD.H} 
	$(CC) -c main${TYPE_of_MAIN}.c $(CXXFLAGS)

report.o: report.c ${HEAD.H}
	${CC} -c report.c $(CXXFLAGS)

argumentControl.o: argumentControl.c ${HEAD.H}
	${CC} -c argumentControl.c $(CXXFLAGS)

MODEL.o: MODEL.c ${HEAD.H} 
	$(CC) -c MODEL.c $(CXXFLAGS)

Maximum_Lag_Correlation.o: Maximum_Lag_Correlation.c ${HEAD.H} 
	$(CC) -c Maximum_Lag_Correlation.c $(CXXFLAGS)

# Funcions controling main data structures (Parameter_Model, Time_Control, 
# Parameter_Table):
Parameter_Model.o: ${PROJECT_DIR}Parameter_Model.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Parameter_Model.c $(CXXFLAGS)

Time_Control.o: ${PROJECT_DIR}Time_Control.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Time_Control.c $(CXXFLAGS)

Parameter_Table.o: ${PROJECT_DIR}Parameter_Table.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Parameter_Table.c $(CXXFLAGS)

values_HumanMos.o: ${PROJECT_DIR}values_HumanMos.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}values_HumanMos.c $(CXXFLAGS)

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

assignTableStructValue_to_Vector.o:	${PROJECT_DIR}assignTableStructValue_to_Vector.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}$/assignTableStructValue_to_Vector.c $(CXXFLAGS)

assignCode_to_Input_Parameters.o:	${PROJECT_DIR}assignCode_to_Input_Parameters.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}$/assignCode_to_Input_Parameters.c $(CXXFLAGS)

Input_Parameters_Output_Variables_fPRINT.o: ${PROJECT_DIR}Input_Parameters_Output_Variables_fPRINT.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Input_Parameters_Output_Variables_fPRINT.c $(CXXFLAGS)

# Functions to control the definition of a subspace from the whole parameter space
P_A_R_A_M_E_T_E_R___S_P_A_C_E.o: ${PROJECT_DIR}Definition_Parameter_Space/P_A_R_A_M_E_T_E_R___S_P_A_C_E.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/P_A_R_A_M_E_T_E_R___S_P_A_C_E.c $(CXXFLAGS)

boundary${TYPE_of_BOUNDARY}.o:   ${PROJECT_DIR}Definition_Parameter_Space/boundary${TYPE_of_BOUNDARY}.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/boundary${TYPE_of_BOUNDARY}.c $(CXXFLAGS)

index.Definition${TYPE_of_INDEX}.o: ${PROJECT_DIR}Definition_Parameter_Space/index.Definition${TYPE_of_INDEX}.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}Definition_Parameter_Space/index.Definition${TYPE_of_INDEX}.c $(CXXFLAGS)

# Functions to control graphical plots
CPG_Drawing_X_Y_Drivers.o:	${PROJECT_DIR}CPG_Drawing_X_Y_Drivers.c ${CPGPLOT}cpgplot_UTL.h
	${CC} -c ${PROJECT_DIR}CPG_Drawing_X_Y_Drivers.c $(CXXFLAGS) 

# Functions controling numerical integration of the ODE system
JACOBIAN_matrix_${ODE_MODEL}.o: ${ODE_DEF}JACOBIAN_matrix_${ODE_MODEL}.c ${HEAD.H} 
	$(CC) -c ${ODE_DEF}JACOBIAN_matrix_${ODE_MODEL}.c $(CXXFLAGS)

JAC_sys_${ODE_MODEL}.o: ${ODE_DEF}JAC_sys_${ODE_MODEL}.c ${HEAD.H} 
	$(CC) -c ${ODE_DEF}JAC_sys_${ODE_MODEL}.c $(CXXFLAGS)

ODE_sys_${ODE_MODEL}.o: ${ODE_DEF}ODE_sys_${ODE_MODEL}.c ${HEAD.H} 
	$(CC) -c ${ODE_DEF}ODE_sys_${ODE_MODEL}.c $(CXXFLAGS)

# Auxiliary functions to specify model ODE definition 
total_Humans.o: ${PROJECT_DIR}total_Humans.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}total_Humans.c $(CXXFLAGS)

model_Variables_Code_${JACOBIAN}.o: ${PROJECT_DIR}model_Variables_Code_${JACOBIAN}.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}model_Variables_Code_${JACOBIAN}.c $(CXXFLAGS)

threshold_Intensity.o: ${PROJECT_DIR}threshold_Intensity.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}threshold_Intensity.c $(CXXFLAGS)

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

fixed_Points_ALL.o: ${ODE_FIXED_POINTS}fixed_Points_ALL.c ${HEAD.H} 
	$(CC) -c ${ODE_FIXED_POINTS}fixed_Points_ALL.c $(CXXFLAGS)

fixed_Points_Intersection.o: ${ODE_FIXED_POINTS}fixed_Points_Intersection.c ${HEAD.H} 
	$(CC) -c ${ODE_FIXED_POINTS}fixed_Points_Intersection.c $(CXXFLAGS)

intermediate_Root.o:  ${ODE_FIXED_POINTS}intermediate_Root.c ${HEAD.H}
	${CC} -c  ${ODE_FIXED_POINTS}intermediate_Root.c $(CXXFLAGS)

stable_Solution_${ODE_MODEL}.o: ${ODE_FIXED_POINTS}stable_Solution_${ODE_MODEL}.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}stable_Solution_${ODE_MODEL}.c $(CXXFLAGS)

Functions_Steady_State_Mosquito.o: ${ODE_FIXED_POINTS}Functions_Steady_State_Mosquito.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}Functions_Steady_State_Mosquito.c $(CXXFLAGS)

Functions_Steady_State_${ODE_MODEL}.o: ${ODE_FIXED_POINTS}Functions_Steady_State_${ODE_MODEL}.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}Functions_Steady_State_${ODE_MODEL}.c $(CXXFLAGS)

Stable_Solution_Partial_Mosquito.o: ${ODE_FIXED_POINTS}Stable_Solution_Partial_Mosquito.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}Stable_Solution_Partial_Mosquito.c $(CXXFLAGS)

# Library of generic statistical functions and generic basic libraries to perform stochatic simulations  
stat.o:	${PROJECT_DIR}stat.c ${PROJECT_DIR}stat.h
	${CC} -c ${PROJECT_DIR}stat.c $(CXXFLAGS)

GSL_stat.o:	${PROJECT_DIR}GSL_stat.c ${PROJECT_DIR}stat.h
	${CC} -c ${PROJECT_DIR}GSL_stat.c $(CXXFLAGS)

GSL_Discrete_Sampling.o: ${PROJECT_DIR}GSL_Discrete_Sampling.c ${PROJECT_DIR}GSL_stat.h
	${CC} -c ${PROJECT_DIR}GSL_Discrete_Sampling.c $(CXXFLAGS)

GSL_Init_Random_Seed.o: ${PROJECT_DIR}GSL_Init_Random_Seed.c ${PROJECT_DIR}GSL_stat.h
	${CC} -c ${PROJECT_DIR}GSL_Init_Random_Seed.c $(CXXFLAGS)

# Bifurcation diagram functions
bifurcation_Diagram${TYPE_of_BIFURCATION}.o: ${ODE_FIXED_POINTS}bifurcation_Diagram${TYPE_of_BIFURCATION}.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}bifurcation_Diagram${TYPE_of_BIFURCATION}.c $(CXXFLAGS)

bifurcation_Diagram_Scan.o: ${ODE_FIXED_POINTS}bifurcation_Diagram_Scan.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}bifurcation_Diagram_Scan.c $(CXXFLAGS)

bifurcation_Diagram_Parameter_Scan.o: ${ODE_FIXED_POINTS}bifurcation_Diagram_Parameter_Scan.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}bifurcation_Diagram_Parameter_Scan.c $(CXXFLAGS)

bifurcation_Diagram_Simple_Scan.o: ${ODE_FIXED_POINTS}bifurcation_Diagram_Simple_Scan.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}bifurcation_Diagram_Simple_Scan.c $(CXXFLAGS)

C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M.o: ${ODE_FIXED_POINTS}C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}C_P_G___P_L_O_T_T_I_N_G___B_I_F_U_R_C_A_T_I_O_N___D_I_A_G_R_A_M.c $(CXXFLAGS)

Separating_and_Saving_Bifurcation_Branches.o: ${ODE_FIXED_POINTS}Separating_and_Saving_Bifurcation_Branches.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}Separating_and_Saving_Bifurcation_Branches.c $(CXXFLAGS)

y_W_diagramm.o: ${ODE_FIXED_POINTS}y_W_diagramm.c ${HEAD.H}
	${CC} -c ${ODE_FIXED_POINTS}y_W_diagramm.c $(CXXFLAGS)
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
	echo "Type of bifurcationnn code: ${TYPE_of_BIFURCATION}"        >> ${EXE}_COMPILATION_OPTIONS.txt	
	echo "Main Progam: main${TYPE_of_MAIN}"        >> ${EXE}_COMPILATION_OPTIONS.txt	
	echo "---------------------------------------" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "All compilation options as passed to the compiler through CXXFLAGS:" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${CXXFLAGS}"                             >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "---------------------------------------" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "All linking options as passed to the compiler through LDFLAGS:" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${LDFLAGS}"                             >> ${EXE}_COMPILATION_OPTIONS.txt
