/*
   Features:  
   1. Model of MacDonald and Ross (possibility of superinfection)

*/

#include <MODEL.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

int 
function (double t, const double y[], double dydt[],
	  void *params)
{
  int i,k;
  Parameter_Table * P = (Parameter_Table *)params; 
  
  double M;  /* Total mosquito population for certain mosquito life-history parameters
	      *	that usually depend on environmental conditions of rain and temperature.
              *	(see Functions_Steady_State_Mosquito.c)
	      */
  M = Total_Mosquito_Steady_State(  P  );

  double W = y[1]*P->H;  /* . W: Total number of infectious mosquitoes */
  
  P->m = M/P->H;         /* . m: Total number of mosquitoes per human */
 
  P->H_Recov = Queu_Function_Recovery(P, W, P->H_Recov_0, P->W_Recov);  
  /* where y[1] is the number of infectious mosquitoes per human */

  /* Fraction of infectious humans */
  dydt[0] = (P->M_a * P->M_b * y[1] + P->Imm ) * (1.0 - y[0]) - P->H_Recov * y[0] - P->H_Delta * y[0];
  /* Number of infectious mosquitoes per human */
  dydt[1] = P->M_a * P->M_c * y[0] * (P->m - y[1]) - P->M_Delta * y[1];

  return GSL_SUCCESS;
}
