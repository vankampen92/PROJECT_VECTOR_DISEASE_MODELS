#include <include.default.POPULATION.c>

#include <include.default.Human.c>
#include <include.default.Cases.c>
#include <include.default.SnInR.c>

#include <include.default.MosAdult.c>
#include <include.default.MosLarva.c>
#include <include.default.Plasmodium.c>

#include <include.default.Temperature.c>

#include <include.Type_Model.default.c>

#if defined ERROR_FUNCTION
#include <include.default.Error_Function.c>
#endif

#include <include.default.EnvParControl.c>

MODEL_OUTPUT_VARIABLES = OUTPUT_VARIABLES_MAXIMUM;   /* Actual no of MODEL (output) VARIABLES */
MODEL_INPUT_PARAMETERS = MODEL_PARAMETERS_MAXIMUM;  /* Actual no of MODEL (input) PARAMETERS */
MODEL_STATE_VARIABLES  = MODEL_VARIABLES_MAXIMUM;  /* Actual no of MODEL (state) VARIABLES  */
