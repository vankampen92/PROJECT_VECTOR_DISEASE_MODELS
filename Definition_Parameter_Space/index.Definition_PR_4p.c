#include <MODEL.h>

void Index_Definition(int *Index, Parameter_Table *P)
{
  // Index[0]=1;   /*H_Delta   */
  Index[0]=25;   /* 25: K_0: Larva Carrying Capaicty   */
  Index[1]=15;   /* 15: Mosquito Mortality */
  Index[2]=22;   /* 22: Larva Mortality    */
  Index[3]=20;   /* 20: Larva Development  */
  /* Last oportunity to modify the rest of parameters values 
     in Parameter struct, P */
}



