#include <MODEL.h>

void Index_Definition(int *Index, Parameter_Table *P)
{
  Index[0]=1;    /* 1: H_Delta              */
  Index[1]=4;    /* 4: H_Recov_0            */
  Index[2]=7;    /* 7: External Immigration */
  Index[3]=13;   /* 13: M_b                 */

  Index[4]=12;     /* M_a                  */
  Index[5]=15;     /* M_Delta              */
  Index[6]=14;     /* M_c                  */
  Index[7]=46;     /* m = M/H              */
}
