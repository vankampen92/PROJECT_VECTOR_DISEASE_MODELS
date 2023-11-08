#include "../Include/MODEL.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>

#define LOWER_EQUILIBRIUM

void Fixed_Points_Lower_or_Upper(Parameter_Table *P, double *y_Sol, double EPSILON, int LU)
{
  /* This function search for the fixed point either from below (when LU = 0) or from 
     above (when LU = 1) */
  
  double W_1, y_1;
  
  if (Feasibility_Condition_M(P) == 1) {

    if (LU == 0) { 
      W_y_fixed_Points_Lower(P, EPSILON, &W_1, &y_1);
    }
    else {
      W_y_fixed_Points_Upper(P, EPSILON, &W_1, &y_1);
    }
    
    stable_Solution(y_1, W_1, P, y_Sol);
  }

  else
    stable_Solution_Free_Disease(P, y_Sol); 
}
