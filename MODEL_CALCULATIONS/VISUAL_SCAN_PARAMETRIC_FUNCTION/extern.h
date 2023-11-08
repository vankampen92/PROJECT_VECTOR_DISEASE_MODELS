#if defined CPGPLOT_REPRESENTATION 
#include <include.CPG.extern.h>
#if defined FILE_REPRESENTATION
#include <include.FILES_to_READ.extern.h>
#endif

#endif
#include <include.Output_Variables.extern.h>
#include <include.Parameter_Model.extern.h>
#include <include.PARAMETER_SPACE.extern.h>
#include <include.Stochastic_Realizations.extern.h>
#include <include.Time_Control.extern.h>

#include <include.Initial_Conditions.extern.h>

/* * * Defining Rain Temperature Structure for Rain Temperature time dependent dynamics */
#include <include.extern.RainTemp.h>
  
  /* * * * Rain and Temperature input files to read */  
#include <include.extern.FileToRead.h>

extern Parameter_Table * P_ARG;
