#include <MODEL.h>

/* This 08 option has been derived from 
   index.Definition_07.c by making T_SHIFT
   equal to a fixed value and searching 
   for an x parameter, which measure the 
   fraction of time an adult mosquito 
   spends around house temperatures. The 
   possibility of a randomly elected initial
   conditions for the human population is
   keet as it was in the index.Definition_07_21p
   option. 
*/

void Index_Definition(int *Index, Parameter_Table *P)
{
  Index[0]=8;   /* H_Xhi       */ 
  Index[1]=9;   /* H_Rho       */
  Index[2]=10;  /* H_Eta       */
  Index[3]=11;  /* H_Nu        */
}



