#include "./Include/MODEL.h"

#if defined CPGPLOT_REPRESENTATION
#include <include.CPG.extern.h>
#endif
#include "./Include/include.Time_Control.extern.h"
#include "./Include/include.Type_Model.extern.h"
#include "./Include/include.Output_Variables.extern.h"
#include "./Include/include.Parameter_Model.extern.h"
#include "./Include/include.PARAMETER_SPACE.extern.h"
#include "./Include/include.Initial_Conditions.extern.h"

double Threshold_Intensity(Parameter_Table * P, double F_0)
{
  double W_0, y_0, W_1, y_1;
  double err_y, err_W;
  double EPSILON;
  
  EPSILON = 1.e-8;

  /* Initial Guess */
  y_0 = 2. * P->H_Delta;
  W_0 = F_0 * log(y_0/P->H_Delta);
  
  //printf("Rate... %g\t Error < %g\n", y_0, EPSILON);
  //printf("Intensity... %g\t Error < %g\n\n", W_0, EPSILON);
  
  do{
   
    y_1 = P->H_Delta + W_0;
    W_1 = F_0* log(y_1/P->H_Delta);
 
    err_y = fabs(y_0 - y_1);
    err_W = fabs(W_0 - W_1);
    
    W_0 = W_1;
    y_0 = y_1;
    
    //printf("Rate... %g\t Current absolute Error... %g\n", y_1, err_y);
    //printf("Threshold... %g\t Current absolute Error... %g\n\n", W_1, err_W);
    
  }
  while( (err_y > EPSILON) || (err_W > EPSILON) );

  /*
  double rate = W_1/(exp(W_1/F_0) - 1);
  printf(" Rate... %g\t Error < %g\n", y_0, EPSILON);
  printf(" Threshold in biting intensity... ... ... . %g\t Error < %g\n", W_0, EPSILON);
  printf(" Resulting rate at this biting intensity... %g (=H_Delta = %g)\n\n", rate, P->H_Delta);
  Press_Key();
  */
  return(W_0);
}

