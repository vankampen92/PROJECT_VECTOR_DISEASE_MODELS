/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                             MALARIA ODE with "Gamma" DELAYS               */
/*                                                                           */
/*                         Recursive Calculation of Fixed Points             */
/*                                                                           */
/*                                 David Alonso, 2006 (c)                    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../Include/MODEL.h"
#include "extern.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>

void fixed_Points_ACC(Parameter_Table *P, double *y_Sol, double EPSILON, double T_obs)
{
  int A, E, I, W;
  double W_1, y_1;

  W  = P->n_H + P->n_V + 6; 
  I  = P->n_H + 1; 
  E = P->n_H; 
  A = W + 1;

  if (Feasibility_Condition_M(P) == 1) {

    W_y_fixed_Points_Lower(P, EPSILON, &W_1, &y_1);
    
    //W_y_fixed_Points(P, EPSILON, &W_1, &y_1);
    
    stable_Solution(y_1, W_1, P, y_Sol);
    y_Sol[A] = (P->H_Xhi*P->H_Gamma*P->n_H * y_Sol[E] + P->H_Eta*P->H_Beta * y_Sol[I])*T_obs;
  
  }
  else{
    
    W_1 = 0;
    stable_Solution_Free_Disease(P, y_Sol);
    y_Sol[A] = 0.0;
  }
 
}

