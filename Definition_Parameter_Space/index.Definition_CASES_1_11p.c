#include <MODEL.h>

// Parameter Space defined by Human related parameters 

void Index_Definition(int *Index, Parameter_Table *P)
{
  Index[0]=1;    /* H_Delta              */
  Index[1]=3;    /* H_Sigma_0            */
  Index[2]=4;    /* H_Recov_0            */ 
  Index[3]=5;    /* n_H  /Homo sapines/  */
  Index[4]=6;    /* H_Gamma              */
  Index[5]=7;    /* External Immigration */
  Index[6]=13;   /* M_b                  */

  Index[7]=8;    /* H_Xhi       */ 
  Index[8]=9;    /* H_Rho       */
  Index[9]=10;   /* H_Eta       */
  Index[10]=11;  /* H_Nu        */
}



