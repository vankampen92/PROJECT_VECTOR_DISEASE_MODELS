/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

/* This code evaluates a parametric function for differents sweepings of the 
   parameter space for a number of human-mosquito models of malaria transmission.
   Parameter ranges are defined the boundary_*.c file. Parameters to scan 
   are defined in the index_Definition_*.c files

   The parametric function is generically defined by the funciton:
   
   void definition_Scan_Function( Parameter_Table * )

   from definition_OutPut_Variables.c file. 

   The input arguments in the example below:

   -n 1 -v0 19

   tell there will be only one output variable (-n 1) and the function to 
   scan is the one defined by key 19 in the function (-v0 19): 
   
   double definition_OutPut_Variables(int, double *, const double, Parameter_Table *)

   from definition_OutPut_Variables.c file. This key corresponds to R_0. 

   Compilation (see make_ALL_examples.sh)
   
   . ~$ make TYPE_of_INDEX=_Hu_4p TYPE_of_MAIN=_SUBPLOTS M_MODEL=LXVnW H_MODEL=CASES_1
   
   Execution: 
   
   . ~$ ./CASES_1-LXVnW_Hu_4p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2 

   . ~$ ./CASES_1-LXVnW_Ca_4p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2 

   . ~$ ./CASES_1-LXVnW_Mo_4p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2 

   . ~$ ./CASES_1-LXVnW_Pa_4p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2 
*/

gsl_rng * r; /* Global generator defined in main.c */

float * customized_contour_levels( Parameter_CPGPLOT * C )
{
    int i;

    /* for (i=0; i < C->NC; i++) { */
    /*   clevels[i] = 1.0; */
    /* } */
    /* Two contour levels */
    C->NC = 5;

    float * clevels = (float *)calloc( C->NC, sizeof(float) );
 
    clevels[0] = 1.0;
    clevels[1] = 2.0;
    clevels[2] = 3.0;
    clevels[3] = 4.0;
    clevels[4] = 5.0;
    
    return(clevels);
}

int main(int argc, char **argv)
{
  int i;
  Parameter_Space Space;
  Parameter_Table Table;
  P_ARG = &Table;        /* see global.h */

  int Input_Parameter_2;
  
  int No_of_POINTS_1    = 500;
  int No_of_POINTS_2    = 500;
    
  int Input_Parameter_1 = 12;       /* 12 ---> Biting rate */ 

  // int Input_Parameter_1 = 25;    /* 25 ---> Carrying capacity         */

  /* 22 ---> L_Delta (Lavae Mortality) */
  /* 20 ---> L_Devel                   */ 
  /* 15 ---> M_Delta (Adult Mortality) */
  /*  8 ---> H_Xhi   (E ----> either C or I with Probability H_Xhi and 1-H_Xhi, respectively) */
  /*  9 ---> H_Rho   (C ----> S, at a rate H_Rho)        */ 
  /* 10 ---> H_Eta   (I ----> C, at a rate H_Eta * Beta) */
  /* 11 ---> H_Nu    (C ----> I, at a rate H_Nu)         */
  
#include "default.c"    
  /* Extra default values */
  I_Time                =  No_of_POINTS_1;

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  P_A_R_A_M_E_T_E_R___S_P_A_C_E___A_L_L_O_C( &Space, &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___U_P_L_O_A_D( &Space, &Table, A_n, A_d);
  printf(" Parameter_Space structure has been correctly allocated and initiated\n");

#include <gsl_random_number_Setup.c>
#if defined VERBOSE
  /* BEGIN: Checking Random Number Generator Setup */
  for(i=0; i<10; i++){
    printf( "f(%d)=%g, ", i, gsl_rng_uniform(r) );
    printf( "f_GAUS(%d)=%g\n", i, gsl_ran_gaussian(r, 1.0) );
  }
  printf("\n");Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif

#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, "?" );
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif  
 
  for(i=0; i  <  Table.SUB_MODEL_PARAMETERS; i++){
    
    values_HumanMos(&Table);  /* Resetting default parameter values */

    Input_Parameter_2 = Table.S->I[i];     

    double * W_GRID = (double *)malloc( No_of_POINTS_1 * No_of_POINTS_2 * sizeof(double) );
    
    int Status =  G_E_N_E_R_I_C___F_U_N_C_T_I_O_N___P_A_R_A_M_E_T_E_R___S_C_A_N( &Table, 
										 No_of_POINTS_1, Input_Parameter_1,
										 No_of_POINTS_2, Input_Parameter_2,
										 definition_Scan_Function,
										 //R_0___Subdominant_Eigenvalue,
										 W_GRID, "R_0.dat" );
#if defined CPGPLOT_REPRESENTATION
    /* BEGIN : 2D GRID cpgplot representation */
    /*********************************************************************/
    Table.CPG->X_label   = Table.Name_Parameters[Input_Parameter_1]; 
    Table.CPG->Y_label   = Table.Name_Parameters[Input_Parameter_2]; 
    /*********************************************************************/
    Boundary(Input_Parameter_1, &Value_0, &Value_1);
    Table.CPG->ORIGIN_X    = Value_0;
    Table.CPG->X_Dimension = (Value_1 - Value_0);
    
    Boundary(Input_Parameter_2, &Value_0, &Value_1);
    Table.CPG->ORIGIN_Y = Value_0;
    Table.CPG->Y_Dimension = (Value_1 - Value_0);
    
    Table.CPG->x_GRID  = No_of_POINTS_1; 
    Table.CPG->y_GRID  = No_of_POINTS_2;
    
    int Output_Variable  = Table.IO_VARIABLE_LIST[0];
    Table.CPG->W_label   = Table.Variable_Name[Output_Variable];
    
    int FIRST_PLOT = 0;
    double i_PLOT  = 0.0;
    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S( Table.CPG,
							  W_GRID, 
							  FIRST_PLOT,
							  Table.CPG->CPG_SCALE_W, 
							  Table.CPG->CPG_RANGE_W_0,
							  Table.CPG->CPG_RANGE_W_1,
							  i_PLOT );
    Press_Key();
    FIRST_PLOT = 1;
    Table.CPG->AUTOMATIC_CONTOUR = 0;
    /* If AUTOMATIC_CONTOUR is 0, the user should customized contours through
       the function customized_contour_levels(...);
    */
    Table.CPG->contour_level = customized_contour_levels ( Table.CPG );
    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___C_O_N_T_O_U_R( Table.CPG,
							    W_GRID, 
							    FIRST_PLOT,
							    Table.CPG->CPG_SCALE_W, 
							    Table.CPG->CPG_RANGE_W_0,
							    Table.CPG->CPG_RANGE_W_1,
							    i_PLOT ); 
#endif
    free (W_GRID);
  }
  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  P_A_R_A_M_E_T_E_R___S_P_A_C_E___F_R_E_E( &Space );	
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif  

  printf("\nEnd of progam\n");
  return (0);
}





