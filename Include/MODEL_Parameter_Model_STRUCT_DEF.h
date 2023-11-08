typedef struct Parameter_Modelinfo
{
  /* * * Model Parameters  * * */
#include <include.Parameter_Model.global.h>

  /* * * Initial Conditions  * */
#include <include.Initial_Conditions.global.h>
  
#if defined APPLYING_TREND
  /* * * Defining trend type * */
#include <include.Trend_Control.global.h> 
#endif
  /* * * Defining Rain Temperature Structure for Rain Temperature time dependent dynamics */
#include <include.global.RainTemp.h>
  
  /* * * * Rain and Temperature input file to read */  
#include <include.global.FileToRead.h>


#if defined CPGPLOT_REPRESENTATION 
  Parameter_CPGPLOT * CPG;
#endif


}Parameter_Model;

