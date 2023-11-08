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

  Index[0]=25;   
  Index[1]=25;   
  Index[2]=25;   
  Index[3]=25;   

  Index[4]=1;   /*H_Delta   */
  Index[5]=3;   /* H_Sigma_0 */
  Index[6]=4;   /* H_Recov_0   */
  Index[7]=5;   /* n_H  /Homo sapines   */
  Index[8]=6;   /* H_Gamma     */
  Index[9]=7;   /* External Immigration */

  Index[10]=8;   /* H_Xhi       */ 
  Index[11]=9;   /* H_Rho       */
  Index[12]=10;  /* H_Eta       */
  Index[13]=11;  /* H_Nu        */

  Index[14]=12;  /* M_a         */
  Index[15]=13;  /* M_b         */
  Index[16]=14;  /* M_c         */ 

  Index[17]=15;  /* M_Delta   */       
  Index[18]=19;  /* N_Eggs that recruit into the larval state */ 
  Index[19]=20;  /* L_Devel         */
  Index[20]=22;  /* L_Delta_P       */
  Index[21]=25;  /* K_0: Larva Carrying Capaicty   */ 

  Index[22]=30;  /* n_V /Plasmodium/       */
  Index[23]=31;  /* M_Gamma /Plasmodium/   */

  /* Last oportunity to modify the rest of parameters values 
     in Parameter struct, P */
}



