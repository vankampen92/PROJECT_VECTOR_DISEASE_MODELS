#include "../../Include/MODEL.h" 
/* Global Shared parameters main Program <---> ArgumentControl() */

#include "extern.h"

extern int HELP_INPUT_ARGUMENTS;

void ArgumentControl(int argc, char **argv)
{
  int argcount, skip;
  
  for(argcount=1; argcount<argc; argcount+=skip)
    {
      if(argv[argcount][0] == '-')
	{
	  skip = 1;
	  switch(argv[argcount][1])
	    {

#if defined CPGPLOT_REPRESENTATION 
#include <include.CPG.argumentControl.c>
#endif

#if defined APPLYING_TREND
#include <include.Trend_Control.argumentControl.c>
#endif

#include <include.Output_Variables.argumentControl.c>
#include <include.Parameter_Model.argumentControl.c>
#include <include.PARAMETER_SPACE.argumentControl.c>
#include <include.Stochastic_Realizations.argumentControl.c>
#include <include.Time_Control.argumentControl.c>

#include <include.Initial_Conditions.argumentControl.c>

#include <include.argumentControl.FileToRead.c>
#include <include.argumentControl.RainTemp.c>

  	    default:
	      printf("**invalid command line argument >%c< \n",
		     argv[argcount][1]);
	    case 'h':
	      
	      P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C( P_ARG );
	      P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( P_ARG );
	      Parameters_from_Command_Line(stdout, P_ARG);

	      printf("\n"); 
	      printf(" As an example,\n"); 
	      printf("        >> [PROGRAM_NAME] -n2 -v0 1 -v1 2 -B0 2\n\n");

	      P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( P_ARG );
	      exit(0);   
	    }
	}
      else
	{
	  printf("**invalid command line flag >%c<\n",argv[argcount][0]);
	  printf("try -h for help.\n");
	  exit(0);
	}
    }
}	




