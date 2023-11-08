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
  // Index[0]=1;   /*H_Delta   */
  Index[0]=3;   /* H_Sigma_0   */
  Index[1]=4;   /* H_Recov_0   */ 
  Index[2]=5;   /* n_H  /Homo sapines   */
  Index[3]=6;   /* H_Gamma     */
  Index[4]=7;   /* External Immigration */

  Index[5]=8;   /* H_Xhi       */ 
  Index[6]=9;   /* H_Rho       */
  Index[7]=10;  /* H_Eta       */
  Index[8]=11;  /* H_Nu        */

  Index[9]=12;  /* M_a         */
  Index[10]=13; /* M_b         */
  Index[11]=14; /* M_c        */ 

  Index[12]=15; /* M_Delta   */       
  Index[13]=19; /* N_Eggs that recruit into the larval state */ 
  Index[14]=20; /* L_Devel         */
  Index[15]=21; /* L_Delta_0       */
  
  Index[16]=28; /* K_p: Precipitation */

  Index[17]=30; /* n_V /Plasmodium/       */

  Index[18]=31; /* M_Gamma /Plasmodium/   */

  /* Last oportunity to modify the rest of parameters values 
     in Parameter struct, P */
}



