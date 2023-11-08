/* 
 * This auxiliar initialization of rainfall and temperature time series uses a
 * slight different parameter set than simply init_Rain_and_Temp.c alone.
 * The novel point here is to be able to introduce mortality due to wash
 * out (excess of rain) in the adult mosquito population. In the
 * previous simpler vertions of this project there was only 
 * rainfall-induced mortalitly for the larva population.
 *
 * In any case, the initialization of the R_T data structure must be used along 
 * with a related function for the parameter time dependence. This function is 
 * stored in a corresponding rainTemperature_...c file.
 *
 * It should be always called according to the prototype definition:
 *
 *         void rainTemp_Parameters(ParamSet *P , double t)
 */
#include "../Include/MODEL.h"

#define PRINT_OUT

void init_Rain_and_Temperature_AUX(Parameter_Table *P, char *F_1, int NO_of_POINTS)
{
  /* 
     Percentile calculation from the data in F_1 file, which is usually a rainfall time
     series. NO_of_POINTS is the lenght of this time series.
     
     This auxiliary function should be called always after the data structure has
     been correctly initilized through a init_Rain_and_Temperature() previous call.
  */ 
  int i_Index, i;
  double R, R_que_R; 

  P->R_T.Rain_PerCen = dvector(0, NO_of_POINTS-1);  
  gsl_vector * Rain = gsl_vector_alloc(NO_of_POINTS);
  gsl_permutation * p       = gsl_permutation_alloc(NO_of_POINTS);

  /* Reading from files */
  Reading_from_File_double_TwoCol(F_1, P->R_T.Time, Rain->data, NO_of_POINTS);
     
#if defined PRINT_OUT
  printf("Data file:\n");
  printf("... ... ... %s\n", F_1);
#endif
  
  gsl_sort_vector_index(p, Rain);
  
  for(i=0; i<NO_of_POINTS; i++){

    i_Index = gsl_permutation_get(p, i);

    R = (double)i/(double)NO_of_POINTS;
  
    P->R_T.Rain_PerCen[i_Index] = R;
  }

#if defined PRINT_OUT
  for(i=0; i<NO_of_POINTS; i++){

    i_Index = gsl_permutation_get(p, i);

    R = gsl_vector_get(Rain, i);
   
    R_que_R = gsl_vector_get(Rain, i_Index);
    
    printf("%g\t %g\t %g\t %g\t %d %g\n", P->R_T.Time[i], R, P->R_T.Rain[i], P->R_T.Rain_PerCen[i], i_Index, R_que_R);

  }
#endif
 
#if defined PRINT_OUT
  printf(" Saving percentile vector from time series data read from %s...\n", F_1);
  printf(" in file perCent_Rain.dat\n");
  Press_Key();
#endif
  
  Saving_to_File_double("perCent_Rain", P->R_T.Time, P->R_T.Rain_PerCen, NO_of_POINTS, 0);

  gsl_vector_free(Rain); 
  gsl_permutation_free(p);
}

void free_Rain_and_Temperature_AUX(Parameter_Table *P)
{
  free_dvector(P->R_T.Rain_PerCen, 0, P->R_T.No - 1);
}
