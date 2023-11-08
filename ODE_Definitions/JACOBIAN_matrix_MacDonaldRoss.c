/* 
   JACOBIAN_matrix_MacDonaldRoss.c is a companion file of JAC_sys_MacDonaldRoss.c
   and it is characterized by the following features:
   
   Jacobian corresponding to the ODE system implemented in ODE_sys_MacDonaldRoss.c:
   
   Different possibilites to implement the dependence of the force of infection, 
   $\beta$, on the mosquito infectious population, y[W], through a #define BETA_DERIVATIVE
   
   The Jacobian does not have any explicity dependence on time.

   Notice that JACOBIAN_matrix_MacDonaldRoss.c could be compiled
   independently from JAC_sys_MacDonaldRoss.c, but not the other
   way around.
*/
#include <MODEL.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>


void evaluating_JACOBIAN_Matrix(gsl_matrix * m, const double *y, double t, int W, Parameter_Table  * P)
{
  int i,k;
  double EIR, Q_Recov_Deriv;
  double W_T;
  
  /* Setting the Jacobian matrix evaluated at (y[0], y[1]) */
    
  W_T = y[1]*P->H;
  /* where y[1] is the number of infectious mosquitoes per human */

  gsl_matrix_set_zero(m); 

  EIR = P->M_a * y[1];  /* EIR: Entomological inoculation rate */

  P->H_Recov = Queu_Function_Recovery(P, W_T, P->H_Recov_0, P->W_Recov);  

  Q_Recov_Deriv = Derivative_Queu_Function_Recovery(EIR, P->H_Recov_0, P->W_Recov);

  /* S row: Let dSdt be equal to F(), then the entries are defined 
     to be dFdS to dFdW */  
  
  gsl_matrix_set( m, 0,0, -( P->M_a*P->M_b* y[1] + P->Imm + P->H_Recov + P->H_Delta) );
  
  gsl_matrix_set( m, 0,1, P->M_a*P->M_b* (1.0 - y[0]) - Q_Recov_Deriv*P->M_a * y[0]);
  
  gsl_matrix_set( m, 1,0, P->M_a*P->M_c* (P->m - y[1]) );
  
  gsl_matrix_set( m, 1,1, -( P->M_a*P->M_c* y[0] + P->M_Delta) );

  /* End of setting the Jacobian matrix evaluated at (y[0], y[1]) */
}
