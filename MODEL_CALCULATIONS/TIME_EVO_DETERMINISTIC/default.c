#if defined CPGPLOT_REPRESENTATION 
#include <include.CPG.default.c>

#if defined FILE_REPRESENTATION
#include <include.FILES_to_READ.default.c>
#endif

#endif

#if defined APPLYING_TREND
#include <include.Trend_Control.default.c>
#endif

#include <include.Output_Variables.default.c>
#include <include.Parameter_Model.default.c>
#include <include.PARAMETER_SPACE.default.c>
#include <include.Stochastic_Realizations.default.c>
#include <include.Time_Control.default.c>

#include <include.Initial_Conditions.default.c>

#include <include.default.FileToRead.c>
#include <include.default.RainTemp.c>
