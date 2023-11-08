#include <MODEL.h>

void Index_Definition(int *Index, Parameter_Table *P)
{
  // Index[0]=1;   /*H_Delta   */
  Index[0]=4;   /* H_Recov_0   */
  Index[1]=25;  /* 25: K_0: Larva Carrying Capaicty   */ 
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
  
  Index[16]=3; /* H_Sigma_0 */

  Index[17]=30; /* n_V /Plasmodium/       */

  Index[18]=31; /* M_Gamma /Plasmodium/   */

  /* Last oportunity to modify the rest of parameters values 
     in Parameter struct, P */
}



