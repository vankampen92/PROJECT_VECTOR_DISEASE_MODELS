#if defined CPGPLOT_REPRESENTATION 

#include <include.CPG.global.h>

#if defined FILE_REPRESENTATION
#include <include.FILES_to_READ.global.h>
#endif

#endif

#if defined APPLYING_TREND
#include <include.Trend_Control.global.h>
#endif

#include <include.Output_Variables.global.h>
#include <include.PARAMETER_SPACE.global.h>
#include <include.Stochastic_Realizations.global.h>
#include <include.Time_Control.global.h>

#include <include.Parameter_Model.global.h>

/* * * Definiting initial conditions */
#include <include.Initial_Conditions.global.h>

/* * * Defining Rain Temperature Structure for Rain Temperature time dependent dynamics */
#include <include.global.RainTemp.h>
  
  /* * * * Rain and Temperature input files to read */  
#include <include.global.FileToRead.h>

Parameter_Table * P_ARG;

#if defined ERROR_FUNCTION
int MY_ERROR_HANDLER = 0;
#endif
