#include "../Include/MODEL.h"

void Stable_Solution_Partial_Mosquito_Larva (Parameter_Table * P, double M, double g_M, 
					     double y, double w,
					     int L, int W, double * Y )
  {   
     int i,j;
     double X, V_1; 

      Y[L]   = P->M_Delta / P->L_Devel * M;                                           /* L   */  
                            
      X = Y[L+1]   = P->M_Delta /(P->M_c * P->M_a * y + P->M_Delta) * M;              /* X   */
  
      if( g_M > 0 ) {
        V_1 = Y[L+2] = P->M_c * P->M_a * y / (P->n_V * P->M_Gamma + P->M_Delta) * X;  /* V_1 */    

  	for(i=L+3; i < W; i++){                                                       /* V_n */  /* n=2, ..., n_V */
    	 	j = (i-(L+2));                                                        /* V_j */
    		Y[i] = pow(g_M, (double)(j)) * V_1; 
        }
      }
      else {
        assert( L+2 == W);
      }     
      
      Y[W] = w;                                                                       /* W   */
  }          

void Stable_Solution_Partial_Mosquito_Larva_Free_Disease (Parameter_Table * P,  
							  double M, int L, int W, double * Y )
  {
    int i;

    Y[L]  = P->M_Delta / P->L_Devel * M;     /* L   */ 
  
    Y[L+1]  = M;                             /* X   */
  
    Y[L+2]  = 0.0;                           /* V_1 */    
    for(i=L+3; i < W; i++){                  /* V_n */
      Y[i] = 0.0; 
    }
  
    Y[W] = 0.0;                              /* W   */
  }

void Stable_Solution_Partial_Mosquito_Constant_Population (Parameter_Table * P, 
							   double M, double g_M, 
							   double y, double w,
							   int X, int W, double * Y )
  {   
     int i,j;
     double x, V_1; 

  int S_; int E_; int I_; int R_; int C_; int S1_; int I1_; int S2_; int I2_; int S3_; int I3_;  	
  int L_; int X_; int U_; int W_; int A_; 	
  int K_;
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P, 
					    &S_, &E_, &I_, &R_, &C_, &S1_, &I1_, &S2_, &I2_, &S3_, &I3_,  
					    &L_, &X_, &U_, &W_, &A_, 
					    &K_);

  assert( W == W_ );
  assert( X == X_ );	 

#if defined ODE
     x = Y[X]   = P->M_Delta /(P->M_c * P->M_a * y + P->M_Delta) * M;              /* X   */
#endif
#if defined ODE_RESTRICTED_JACOBIAN
     x = P->M_Delta /(P->M_c * P->M_a * y + P->M_Delta) * M;              /* X   */
#endif    
     	 
#if defined XW
     assert( g_M == 0.0 );
#endif 
 
      if( g_M > 0 ) {
        V_1 = Y[U_] = P->M_c * P->M_a * y / (P->n_V * P->M_Gamma + P->M_Delta) * x;  /* V_1 */    

  	for(i=1+U_; i < W; i++){                               /* V_n */  /* n=2, ..., n_V */
    	 	j = i - U_;                                                         /* V_j */
    		Y[i] = pow(g_M, (double)(j)) * V_1; 
        }
      }
      else {
#if defined ODE
        assert( X+1 == W);
#endif
#if defined ODE_RESTRICTED_JACOBIAN
	assert( X  == W );
#endif
      }     
      
      Y[W] = w;                                                                       /* W   */
  }          

void Stable_Solution_Partial_Mosquito_Constant_Population_Free_Disease (Parameter_Table *P, 
									double M, 
									int X, int W, 
									double * Y )
{
    int i;

    int S_; int E_; int I_; int R_; int C_; int S1_; int I1_; int S2_; int I2_; int S3_; int I3_;
    int L_; int X_; int U_; int W_; int A_;
    int K_;
    M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P,
                                            &S_, &E_, &I_, &R_, &C_, &S1_, &I1_, &S2_, &I2_, &S3_, &I3_,
                                            &L_, &X_, &U_, &W_, &A_,
                                            &K_);
  assert( W == W_ );
  assert( X == X_ );

#if defined ODE
    Y[X]  = M;                             /* X   */
#endif
  
    Y[U_]  = 0.0;                           /* V_1 */    
    for(i = 1+U_; i < W; i++){                  /* V_n */
      Y[i] = 0.0; 
    }
  
    Y[W] = 0.0;                              /* W   */
}

