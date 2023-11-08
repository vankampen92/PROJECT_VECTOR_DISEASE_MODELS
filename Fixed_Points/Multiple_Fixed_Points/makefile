#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#/*                                                                           */
#/*                                  SIC_MALARIA                              */
#/*                                                                           */
#/*                             David Alonso, 2005 (c)                        */
#/*                                                                           */
#/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
##############################################################################################################
## C O M P I L A T I O N   O P T I O N S   C O N T R O L I N G   J A C O B I A N   T Y P E   ################# 
JACOBIAN=ODE# 'ODE' / 'ODE_RESTRICTED_JACOBIAN'
EXTRA_INCLUDE_PATH+=-I${ODE_DEF}Include_${JACOBIAN}/
##############################################################################################################
########### Two possibilities:  'CASES_1'  / 'MacDonaldRoss' ####
Q=NON_THRESHOLD################ Possibilities: 'QUEU_FUNCTION_THRESHOLD' / 'NON_THRESHOLD' / #
S=SUPERINFECTION######################### Possibilities: 'NON_SUPERINFECTION' / 'SUPERINFECTION'
V=NON_VERBOSE###################################### Possibilities: 'VERBOSE' / 'NON_VERBOSE'
#
LDFLAGS+=-lm -lgsl -lgslcblas -lNumRec -lNRUTL ${EXTRA_LIBRARY_PATH}
CXXFLAGS+=${EXTRA_INCLUDE_PATH} -D${ODE_MODEL_DEF} -D${JACOBIAN} -D${M_MODEL} -D${H_MODEL} -D${NR} -D${V} -D${S} -D${Q} -g #-Wall  
OBJECTS = stat.o argumentControl.o report.o main.o                                                             \
	values_HumanMos.o total_Humans.o superinfection_Functions.o threshold_Intensity.o superinfection_Functions_Recovery.o superinfection_Functions_Sigma.o model_Variables_Code_${JACOBIAN}.o \
	fixed_Points.o fixed_Points_ALL.o intermediate_Root.o y_W_diagramm.o                                   \
	Functions_Steady_State_${ODE_MODEL}.o Functions_Steady_State_Mosquito.o stable_Solution_${ODE_MODEL}.o \
	Stable_Solution_Partial_Mosquito.o                                                                     \
	ODE_sys_${ODE_MODEL}.o JAC_sys_${ODE_MODEL}.o JACOBIAN_matrix_${ODE_MODEL}.o                           \
	assignLabel_to_Model_Variables.o
CC=gcc

EXE = ${ODE_MODEL}

all: ${EXE}

${EXE}:  	$(OBJECTS) COMPILATION_OPTIONS
		$(CC) -o ${EXE} $(OBJECTS) $(LDFLAGS) $(CXXFLAGS)  

stat.o:	${PROJECT_DIR}stat.c ${PROJECT_DIR}stat.h
	${CC} -c ${PROJECT_DIR}stat.c $(CXXFLAGS)

main.o: main.c ${HEAD.H} 
	$(CC) -c main.c $(CXXFLAGS)

argumentControl.o: argumentControl.c ${HEAD.H}
	${CC} -c argumentControl.c $(CXXFLAGS)

report.o: report.c ${HEAD.H}
	${CC} -c report.c $(CXXFLAGS)

values_HumanMos.o: ${PROJECT_DIR}values_HumanMos.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}values_HumanMos.c $(CXXFLAGS)

superinfection_Functions.o: ${PROJECT_DIR}superinfection_Functions.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}superinfection_Functions.c $(CXXFLAGS)

threshold_Intensity.o: ${PROJECT_DIR}threshold_Intensity.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}threshold_Intensity.c $(CXXFLAGS)

total_Humans.o: ${PROJECT_DIR}total_Humans.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}total_Humans.c $(CXXFLAGS)

model_Variables_Code_${JACOBIAN}.o: ${PROJECT_DIR}model_Variables_Code_${JACOBIAN}.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}model_Variables_Code_${JACOBIAN}.c $(CXXFLAGS)

superinfection_Functions_Recovery.o: ${PROJECT_DIR}superinfection_Functions_Recovery.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}superinfection_Functions_Recovery.c $(CXXFLAGS)

superinfection_Functions_Sigma.o: ${PROJECT_DIR}superinfection_Functions_Sigma.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}superinfection_Functions_Sigma.c $(CXXFLAGS)

fixed_Points.o: ../fixed_Points.c ${HEAD.H}
	${CC} -c ../fixed_Points.c $(CXXFLAGS)

fixed_Points_ALL.o: ../fixed_Points_ALL.c ${HEAD.H}
	${CC} -c ../fixed_Points_ALL.c $(CXXFLAGS)

intermediate_Root.o: ../intermediate_Root.c ${HEAD.H}
	${CC} -c ../intermediate_Root.c $(CXXFLAGS)

y_W_diagramm.o: ../y_W_diagramm.c ${HEAD.H}
	${CC} -c ../y_W_diagramm.c $(CXXFLAGS)

stable_Solution_${ODE_MODEL}.o: ../stable_Solution_${ODE_MODEL}.c ${HEAD.H}
	${CC} -c ../stable_Solution_${ODE_MODEL}.c $(CXXFLAGS)

Functions_Steady_State_Mosquito.o: ../Functions_Steady_State_Mosquito.c ${HEAD.H}
	${CC} -c ../Functions_Steady_State_Mosquito.c $(CXXFLAGS)

Functions_Steady_State_${ODE_MODEL}.o: ../Functions_Steady_State_${ODE_MODEL}.c ${HEAD.H}
	${CC} -c ../Functions_Steady_State_${ODE_MODEL}.c $(CXXFLAGS)

Stable_Solution_Partial_Mosquito.o: ../Stable_Solution_Partial_Mosquito.c ${HEAD.H}
	${CC} -c ../Stable_Solution_Partial_Mosquito.c $(CXXFLAGS)

ODE_sys_${ODE_MODEL}.o: ${ODE_DEF}/ODE_sys_${ODE_MODEL}.c ${HEAD.H}
	${CC} -c ${ODE_DEF}/ODE_sys_${ODE_MODEL}.c $(CXXFLAGS)

JAC_sys_${ODE_MODEL}.o: ${ODE_DEF}/JAC_sys_${ODE_MODEL}.c ${HEAD.H}
	${CC} -c ${ODE_DEF}/JAC_sys_${ODE_MODEL}.c $(CXXFLAGS)

JACOBIAN_matrix_${ODE_MODEL}.o: ${ODE_DEF}/JACOBIAN_matrix_${ODE_MODEL}.c ${HEAD.H}
	${CC} -c ${ODE_DEF}/JACOBIAN_matrix_${ODE_MODEL}.c $(CXXFLAGS)

assignLabel_to_Model_Variables.o: ${PROJECT_DIR}/assignLabel_to_Model_Variables.c ${HEAD.H}
	${CC} -c ${PROJECT_DIR}/assignLabel_to_Model_Variables.c ${CXXFLAGS}

clean:  
	rm -f *.o *~ core         

COMPILATION_OPTIONS:
	echo "Main model definition compilation options:" > ${EXE}_COMPILATION_OPTIONS.txt
	echo "${ODE_MODEL}"                            >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${S}"                                    >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${Q}"                                    >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "All compilation options as passed to the compiler through CXXFLAGS:" >> ${EXE}_COMPILATION_OPTIONS.txt
	echo "${CXXFLAGS}"                             >> ${EXE}_COMPILATION_OPTIONS.txt





