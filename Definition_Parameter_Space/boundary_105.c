#include <MODEL.h>

/*						\
 * Boundary_88 was derived from boundary_77.c
 * which was derived from boundary_66.c
 * 
 * Here, the ranges for the initial conditions
 * are less stringent. 
 * 
 * Boundary_66 was derived from boundary_55.c, 
 * but the time for thet outset of malaria
 * clinical symptomes is longer (1 to 3 weekd)
 * and the external force of infection is searched
 * in a slightly broader range:
 * 
 * boundary_55.c : (0, 0.000001)
 * boundary_66.c : (0, 0.000005)
 *  
 * In turn, boundary_55.c has been derived from 
 * boundary_44.c, with the following changes:
 *
 * The ranges of the 'initial condition' 
 * are further restricted in the direction of initial
 * number of susceptibles closer to the total
 * population.
 * 
 * The limits for the external force of infection
 * have also furtner narrowed down in agreement with
 * all previous explorations. 
 *
 * The limits of the difference between temperatures
 * outdoor indoor has been also narrowed down (0,3)
 * in agreeement with current literature.
 *
 * The limits controling the probability of the emergence
 * of a clinical case have been expanded: from (0,0.2)
 * to (0, 0.5).
\*/

void Boundary(int j, double *value_0, double *value_1)
{

  switch(j)
    {
      
    case 0:
      /* H */
      (*value_1) = 100000.; /* 20000 inhabitants  */
      (*value_0) = 50000.;  /* 500000 inhabitants */
              break;
    case 1:
	      /* H_Delta */
      (*value_1) = (0.06/365.0); /* 50 years */
      (*value_0) = (0.02/365.0); /* 20 years */
              break;
    case 2:
	      /*  H_Birth  */
      (*value_1) = (0.064/365.0); /* Maximum Birth Growth Rate observed in Kericho district */
      (*value_0) = (0.01/365.0);  /* Minimum Birth Growth Rate */     
	      break;
    case 3:
              /*  H_Sigma_0  */
      (*value_1) = (0.1);       
      (*value_0) = (0.000001);  //0.002
	      break;
    case 4:
	      /*  H_Recov_0  */
      (*value_1) = (0.05);
      (*value_0) = (0.000001);  //0.01    /* This is surrogate for value_0 = 0 */
	      break;
    case 5:
	      /*  n_H        */
      (*value_1) = 50;
      (*value_0) =  1;
	      break;
    case 6:
	      /*  H_Gamma    */
      (*value_1) =  (1.0/7.0);  /* 1 week  */
      (*value_0) =  (1.0/21.0); /* 3 weeks */
	      break;
    case 7:
	      /*  Imm      */
      (*value_1) =  (0.0001);
      (*value_0) =  (0.0);
	      break;
    case 8:
	      /*  H_Xhi      */
      (*value_1) = (0.5);
      (*value_0) = (0.0);
              break;
    case 9:
	      /*  H_Rho      */
      (*value_1) = (1.0);
      (*value_0) = (0.0);
	      break;
    case 10:
	      /*  H_Eta      */
      (*value_1) =  (1.0);
      (*value_0) =  (0.0);
	      break;
    case 11:
	      /*  H_Nu      */
      (*value_1) = (1.0);
      (*value_0) = (0.2);
	      break;
    case 12:
	      /*  M_a        */
      (*value_1) = (0.5);
      (*value_0) = (0.2);
	      break;
    case 13:
	      /*  M_b  */
      (*value_1) = (1.0);
      (*value_0) = (0.01);
              break;
    case 14:
	      /*  M_c  */
      (*value_1) = (1.0);
      (*value_0) = (0.0);
              break;
    case 15:
	      /*  M_Delta  */
      (*value_1) = (0.1);
      (*value_0) = (0.01);
              break;
    case 16:
	      /*  M_Delta_R  */
      (*value_1) = (0.1);
      (*value_0) = (0.01);
              break;
    case 17:
	      /*  M_Delta_PE  */
      (*value_1) = (0.1);
      (*value_0) = (0.01);
              break;	      
    case 18:
	      /*  M_Fecundity  */
      (*value_1) = (100.);
      (*value_0) =  (10.);
	      break;
    case 19:
             /*  M_NoEggs */
      (*value_1) = (100.) ;
      (*value_0) =   (0.0);
	      break;
    case 20:
	      /*  L_Devel  */
      (*value_1) = (0.2);
      (*value_0) = (0.01);
	      break;
    case 21:
	      /*  L_Delta_0  */
      (*value_1) = (0.5);
      (*value_0) = (0.01);
	      break;	      
    case 22:
	      /*  L_Delta_P   */
      (*value_1) =   (0.5);
      (*value_0) =   (0.01);
	      break;
    case 23:
              /*  L_Delta_R   *//* L_Delta = L_Delta_0(T) + L_Delta_P + L_Delta_R * H(Rain -<Rain>)              */
      (*value_1) =   (0.5);/*                        (H(x) = x if x>0, H(x) = 0, otherwise)            */
      (*value_0) =   (0.0);
	      break;
    case 24:
              /*  L_Delta_PE   */
      (*value_1) =   (0.5);                    
      (*value_0) =   (0.0);
	      break;
    case 25:
	      /*  K_0   */
      (*value_1) =  1.0e+05;  // 1.0E+06; //
      (*value_0) =  1.0e+02;  // 1.0E+04; //
	      break;
    case 26:
	      /*  K_Sigma  */
      printf("Error in paramater Space defintion occurred in boundary.c\n");exit(0) ;
              break;
    case 27:
	      /*  K_A  */
      (*value_1) =  3.0e+3; //(2) in Sirocco, 1.0e+2; //(1) 5.0e+3;  
      (*value_0) =  0.0; //(2) in Sirocco, 1.0e+0; //(1) 1.0e+1; 
	      break;
    case 28:
	      /*  K_p : Precipitation */
      (*value_1) =  10.0;  
      (*value_0) =  1.0;
	      break;
    case 29:
	      /*  K_E : Decaying rate */
      (*value_1) = 0.3; //0.1;    
      (*value_0) = 0.0; //0.01;
	      break;
    case 30:
	      /*  n_V = */
      (*value_1) = 50;
      (*value_0) =  1;
	      break;
    case 31:
	      /*  M_Gamma  */
      (*value_1) = (1.0/10.0);
      (*value_0) = (1.0/20.0);
              break;
    
    case 32:
	      /* Shift in temperature for adult mosquitoes */
      (*value_1) = (6.0);
      (*value_0) = (0.0);
              break;
    case 33:
	      /* Shift in temperature due to a different altitude */
      (*value_1) = (0.0);
      (*value_0) = (-2.0);
              break;
    case 34:	      
              /* External Influx of Adult Mosquitoes */
      (*value_1) = (0.001);
      (*value_0) = (0.0);

              break;
    case 35:
              /* Initial Fraction of Susceptible */
      (*value_1) = 1.0; 
      (*value_0) = (0.95);
            
	      break;
    case 36:
              /* Initial Fraction of Exposed */
      (*value_1) = (0.02);
      (*value_0) = (0.0); 
              
	      break;
    case 37:
              /* Initial Fraction of Infectious */
      (*value_1) = (0.02);
      (*value_0) = (0.0); 
              
	      break;
    case 38:
              /* Initial Fraction of cases */
      (*value_1) = (0.01);
      (*value_0) = (0.0);
            
              break;  
    case 39:
              /* Maturation Rate: Rain ---> Available Water  */
      (*value_1) = (1.0/1.0);  /* 7 days: 1.0/7.0 */
      (*value_0) = (1.0/120.0); /* 45 days: 1.0/45.0 */
            
              break; 
    case 40:
              /* Error Parameter_0  */
      (*value_1) = (1.0);  
      (*value_0) = (0.5); 
            
              break; 
    case 41:
              /* Error Parameter_1 */
      (*value_1) = ( 5.0 );  /* Overdisperion Parameter, 
				Psi_{BBK} \approx 4.46 */
      (*value_0) = ( 0.0 ); 
            
              break;    
    case 42:
              /* x: T_E = T_o + (1-x) * (T_i-T_o) */
      (*value_1) = ( 1.0 );  

      (*value_0) = ( 0.0 );
      
              break;
    case 43:
      /* M_c_1 */
      (*value_1) = ( 1.0 );  

      (*value_0) = ( 0.1 );
      
              break;
    case 44:
      /* M_c_2 */
      (*value_1) = ( 1.0 );  

      (*value_0) = ( 0.1 );
      
              break;
    case 45:
              /* Fraction of Exposed (2nd Class) */
      
      (*value_1) = (0.02);

      (*value_0) = (0.0);
      
              break;
    default:
      printf("...(in boundary.c) INVALID PARAMETER KEY (key = %d)\n", j);
      exit(0);
    }  
}	


