#include "../../Include/MODEL.h"

#include "extern.h"
extern int HELP_INPUT_ARGUMENTS;

void Parameters_from_Command_Line(FILE *fp, Parameter_Table *P)
{

  fprintf_Input_Parameters(fp, P);

#include "../../Include/include.Output_Variables.fprintPar.c"

#if defined CPGPLOT_REPRESENTATION
#include <include.CPG.fprintPar.c>
#endif

#if defined FILE_REPRESENTATION
fprintf_Input_Parameter_FILE( fp, P->CPG->CPG_File );
#endif 	

#if defined APPLYING_TREND
#include <include.fprintPar.Trend.c>
#endif

#include <include.fprintPar.POPULATION.c>
#include <include.fprintPar.Human.c>
#include <include.fprintPar.Cases.c>

#include <include.fprintPar.MosAdult.c>
#include <include.fprintPar.MosLarva.c>
#include <include.fprintPar.Plasmodium.c>

#include <include.Initial_Conditions.fprintPar.c>

#include <include.fprintPar.EnvParControl.c>

#if defined ERROR_FUNCTION
#include <include.fprintPar.Error_Function.c>
#endif

#include <include.fprintPar.FileToRead.c>
#include <include.fprintPar.RainTemp.c>
}

void Parameters_ModelReport(char *File, Parameter_Table *P)
{
  FILE *fp;
  Parameters_from_Command_Line(stdout, P);  
  fp = fopen(File, "w");
  Parameters_from_Command_Line(fp, P);
  fclose(fp);
}
