#include <MODEL.h>

void Index_Definition(int *Index, Parameter_Table *P)
{
  // Index[0]=1;   /*H_Delta   */
  Index[0]=12;   /* 12: Biting Rate   */
  Index[1]=4;   /* 4: H_Recov_0      */ 
  /* Last oportunity to modify the rest of parameters values 
     in Parameter struct, P */
}



