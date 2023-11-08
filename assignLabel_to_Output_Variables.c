#include "./Include/MODEL.h"

void output_Var_Name(char * Label, char * Title_In);

//#if defined APPLYING_TREND 
#include <include.Trend_Control.extern.h>
//#endif

void AssignLabel_to_OutPut_Variables(int j, char * Label, Parameter_Table * P)
{
  /* See
     
     ./GA_Stable_v2.0.0/TimeSeries_1st_GENE_SHIFT/no_of_variable_to_save.c
     
     to find a long defintion for the same output variables.
     Output variable names and labels in that file and here should be
     always in total agreement.
  */
  
  switch(j)
    {
    case INTEGER_CODE_FOR_TIME_DIMENSION:
    
              output_Var_Name(Label, " T I M E ");
  
	      ;
	      break;
    case 1:   /* Total Mosquito Population */
              output_Var_Name(Label, " [M] : A d u l t   M o s q u i t o  P o p u l a t i o n");

              ; 
	      break;
    case 2:   /* Accumulated malaria clinical cases */
              output_Var_Name(Label, " C A S E S ");
	       
              ; 
	      break;
    case 3:   /* Fraction of infectious humans: [ (I+C)/H ] */
#if defined CASES_33
	      output_Var_Name(Label, " [ y___H   =   ( I + C ) / H ]");
#else 
#if defined CASES_1
	      output_Var_Name(Label, " [ y___H   =   ( I + C ) / H ]");
#else 
	      output_Var_Name(Label, " [ y___H   =   I / H ]");
#endif
#endif      
	      ; 
	      break;
    case 4:   
              output_Var_Name(Label, " [ m  =  M / H ] : N o   o f   M o s q u i t o e s   p e r   h u m a n ");
      
	      ; 
	      break;
    case 5:
	      output_Var_Name(Label, " [ w___H  =   W / H ]");
      
	      ; 
	      break;
    case 6:
	      output_Var_Name(Label, " [ B E T A ]   F O R C E   o f   I N F E C C I O N");
      
	      ; 
	      break;
    case 7:
	      output_Var_Name(Label, " [ B e t a___I ] F O R C E   o f   I N F E C C I O N ( i m m i g r a t i o n ) ");
            
	      ; 
	      break;
    case 8:
	      output_Var_Name(Label, " [ B e t a___L ] F O R C E   o f   I N F E C C I O N ( l o c a l ) ");
     
	      ; 
	      break;
    case 9:
              output_Var_Name(Label, " ( B e t a___L )/ ( B e t a__I  +  B e t a___L ) ");
              ; 
	      break;
    case 10:
	      output_Var_Name(Label, "  B e t a___I /( B e t a__I  +  B e t a___L )");
      
	      ; 
	      break;
    case 11:
	      output_Var_Name(Label, " B e t a___L  / B e t a___I ");
      
	      ; 
	      break;
    case 12:
	      output_Var_Name(Label, " w___M  =   W / M ");
       
	      ; 
	      break;
    case 13:
	      output_Var_Name(Label, " T E M P E R A T U R E ");
      
	      ; 
	      break;
    case 14:
	      output_Var_Name(Label, " R A I N F A L L ");
      
	      ; 
	      break;
    case 15:
	      output_Var_Name(Label, " C A R R Y I N G  C A P A C I T Y ");
      
	      ; 
	      break;
    case 16:
      //output_Var_Name(Label, " F r a c t i o n   o f   s u s c e p t i b l e s   [ s  =  S / H ] ");
	      output_Var_Name(Label, " [ s  =  S / H ] ");
              ;
              break;
    case 17:
              output_Var_Name(Label, " D y n a m i c   V e c t o r i a l   C a p a c i t y ");
                                  ;
              break;
    case 18:
              output_Var_Name(Label, " S t a t i c   V e c t o r i a l   C a p a c i t y ");
                                  ;
              break;
    case 19:
              output_Var_Name(Label, " R__0 ");
                                  ;
              break;
    case 20:
              output_Var_Name(Label, " (R__0)^2 ");
                                  ;
              break;
    case 21:
              output_Var_Name(Label, " E I R ( y e a r ^{-1} )");
                                  ;
              break;
    case 22:
              output_Var_Name(Label, " A__0 ( y e a r ) ");
                                  ;
              break;
    case 23:
              output_Var_Name(Label, " T___I_n_f_e_c_t_i_o_u_s ( m o n t h )");
                                  ;
              break;
    case 24:
              output_Var_Name(Label, " T___I_m_m_u_n_i_t_y ( m o n t h )");
                                  ;
              break;
    case 25:
              output_Var_Name(Label, " M a l a r i a  I n c i d e n c e (per 100,000)");
                                  ;
              break;
    case 26:   /* Accumulated malaria clinical cases */
              output_Var_Name(Label, " C A S E S (with noise)");

              ;
              break;
    case 27:   /* Accumulated malaria clinical cases */
              output_Var_Name(Label, " E X P E C T E D   N o  of  C A S E S (error model)");

              ;
              break;
    case 28:   /* Accumulated malaria clinical cases */
              output_Var_Name(Label, " S T R A I N   T Y P E   F A V O R E D ");

              ;
              break;
    case 29:   /* Accumulated malaria clinical cases */
              output_Var_Name(Label, " T H R E S H O L D   V A L U E :  S T R A I N   E V O L U T I O N");

              ;
              break;
//#if defined APPLYING_TREND
    case 30:
	AssignLabel_to_Parameters( Tr_Input_Parameter, Label, P );

	printf(" Applying Trend to Parameter %s no: %d\n" , Label, Tr_Input_Parameter);
	//printf(" Press any key\n");
	//getchar(); // Press_Key();

        char * p = strcat( Label, "   [ Trend Value ]" );

              // output_Var_Name(Label, " [ H_Rho ]:  R E C O V E R Y   R A T E   T H R O U G H   T R E A T M E N T");
        ;
              break;
//#endif
    case 31:   /* Accumulated malaria clinical cases */
              output_Var_Name(Label, " [ e ]:  T R E A T M E N T   E F F I C I E N C Y  [ e ]");

              ;
              break;
    case 32:   /* Accumulated malaria clinical cases */
              output_Var_Name(Label, " [ H ]:  T O T A L   H U M A N   P O P U L A T I O N");

              ;
              break;
    case 33:   /* Accumulated malaria clinical cases */
              output_Var_Name(Label, " [ L ]:  R A I N F A L L   ( m m   p e r   d a y )");

              ;
              break;
    default:
      printf(".... INVALID OUTPUT VARIABLE KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Output_Variables(stdout, P);
      exit(0);
    }
}

void output_Var_Name(char * Label, char * Title_In)
{
  char * p;

  Label[0] = '\0';
  p = strcat( Label, Title_In );

}
