/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../../Include/MODEL.h"

#include "global.h"

/* This code calculate dominant periods for differents sweeps of the parameter
   space for a number of human-mosquito models of malaria transmission.
   Parameter ranges are defined the boundary_*.c file. Parameters to scan 
   are defined in the index_Definition_*.c files

   When drawing extra contour lines, please see function
   
   float * customized_contour_levels( Parameter_CPGPLOT * C )
   
   at the end of this file.

   Compilation (see make_ALL_examples.sh)
   
   . ~$ make TYPE_of_INDEX=_Hu_4p TYPE_of_MAIN=_SUBPLOTS M_MODEL=LXVnW H_MODEL=CASES_1 JACOBIAN=ODE_RESTRICTED_JACOBIAN
   . ~$ make TYPE_of_INDEX=_PR_1p TYPE_of_MAIN=_SUBPLOTS M_MODEL=LXVnW H_MODEL=CASES_1 JACOBIAN=ODE_RESTRICTED_JACOBIAN
   
   Execution: 
   
   . ~$ ./CASES_1-LXVnW-ODE_RESTRICTED_JACOBIAN_Hu_4p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2 

   . ~$ ./CASES_1-LXVnW-ODE_RESTRICTED_JACOBIAN_Ca_4p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2 

   . ~$ ./CASES_1-LXVnW-ODE_RESTRICTED_JACOBIAN_Mo_4p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2 

   . ~$ ./CASES_1-LXVnW-ODE_RESTRICTED_JACOBIAN_Pa_4p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2 

   Execution (solution A):                                                       
   . ~$ ./CASES_1-LXVnW-ODE_RESTRICTED_JACOBIAN_PR_1p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -S0 1 -n 1 -v0 19 -G0 1 -G1 1 -G14 T\\d\\fs0\\fn\\u

   Execution (solution B):
   . $ ./CASES_1-LXVnW-ODE_RESTRICTED_JACOBIAN_PR_1p  -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 5 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2  -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 8.0E3  -P0 10 -P1 0.083 -S0 1 -n 1 -v0 19 -G0 1 -G1 1 -G14 T\\d\\fs0\\fn\\u
   
*/

gsl_rng * r; /* Global generator defined in main.c */

float * customized_contour_levels( Parameter_CPGPLOT * C );

int main(int argc, char **argv)
{
  int i,j,k,n;
  Parameter_Space Space;
  Parameter_Table Table;
  P_ARG = &Table;

  int No_of_POINTS_1    = 400;
  int Input_Parameter_1 = 12; /* 12 ---> Biting rate       */ 
  int No_of_POINTS_2    = 400;
  int Input_Parameter_2 = 25; /* 25 ---> Carrying capacity */
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
  printf("\n"); //Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif

#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, "?" );
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif

  /* BEGIN : Evaluation of the largest (xmax) and the tiniest (xmin) 
     numbers my machine can handle 
  */
  float xmin, xmax;
  Calculation_of_Local_Machine_MAX_min_allowed_float_numbers (&xmin, &xmax);
  
  printf("My largest useable value without causing overflow is %f\n", xmax);
  printf("My tiniest useable value without causing overflow is %f\n", xmin);
  Table.nr___x_min = xmin;
  Table.nr___x_MAX = xmax;
  /*   END : Evaluation of xmax and ymin number causing overflow */

  for(k=0; k  <  Table.SUB_MODEL_PARAMETERS; k++){
    
    values_HumanMos(&Table);  /* Resetting default parameter values */

    Input_Parameter_2 = Table.S->I[k];     
    double * W_GRID = (double *)malloc( No_of_POINTS_1 * No_of_POINTS_2 * sizeof(double) );
    int Status =  G_E_N_E_R_I_C___F_U_N_C_T_I_O_N___P_A_R_A_M_E_T_E_R___S_C_A_N( &Table, 
										 No_of_POINTS_1, Input_Parameter_1,
										 No_of_POINTS_2, Input_Parameter_2,
										 DOMINANT_PERIOD,
										 W_GRID,
										 "Dominant_Period_1.dat");
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
    
  
    int FIRST_PLOT = 0;
    double i_PLOT  = 0.0;
   
    double W_GRID_MAX = 0.0;
    for(i=0; i<(No_of_POINTS_1 * No_of_POINTS_2); i++){
      if( W_GRID[i] > xmax ) W_GRID[i] = xmax; 
      W_GRID_MAX = MAX ( W_GRID[i], W_GRID_MAX );
    }

    printf("\n Maximum z value to plot: W_GRID_MAX = %g\n", W_GRID_MAX); 
    printf("If it is greater than 20.0, it will be reset to 20\n");
    
    for(i=0; i<(No_of_POINTS_1 * No_of_POINTS_2); i++) {
       if(W_GRID[i] > 20.0) W_GRID[i] = 20.0;
    }
    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S( Table.CPG,
							  W_GRID, 
							  FIRST_PLOT,
							  Table.CPG->CPG_SCALE_W, 
							  Table.CPG->CPG_RANGE_W_0,
							  Table.CPG->CPG_RANGE_W_1,
							  i_PLOT );

    double * W_GRID_BIS = (double *)calloc( No_of_POINTS_1 * No_of_POINTS_2, sizeof(double) );
    Status =  G_E_N_E_R_I_C___F_U_N_C_T_I_O_N___P_A_R_A_M_E_T_E_R___S_C_A_N( &Table, 
									     No_of_POINTS_1,
									     Input_Parameter_1, 
									     No_of_POINTS_2,
									     Input_Parameter_2,
									     DYNAMIC_REGIM, 
									     W_GRID_BIS, 
									     "Dynamic_Regims.dat" );
    /* The scan function DYNAMIC_REGIM returns a double value between 0 and 4 
       (stored in array W_GRID_BIS). 
       Possible return values: 
       0 ---> Disease Free Equilibrium (Mosquito Free Equilibrium)
       1 ---> Disease Free Equilibrium (with viable Mosquito population) R_0 < 1
       2 ---> Disease Endemic Equilibrium (node stable)
       3 ---> Disease Endemic Equilibrium (damped oscillations) 
       4 ---> Unstable local equilibrium 
       If there is coexistence, unless stated, we characterize the properties of the lower
       equilibrium
    */
    double Value, x_Data, y_Data; 
    int Total_POINTS;
    double * X = (double *)calloc( No_of_POINTS_1*No_of_POINTS_2, sizeof(double) );
    double * Y = (double *)calloc( No_of_POINTS_1*No_of_POINTS_2, sizeof(double) );
    Total_POINTS = 0;
    n = 0; 
    for( j = 0; j < No_of_POINTS_2; j++ ) {
  
      Boundary(Input_Parameter_2, &Value_0, &Value_1);
      Value = Value_0 + j * (Value_1 - Value_0)/(double)(No_of_POINTS_2 - 1);
      y_Data = Value;

      Boundary(Input_Parameter_1, &Value_0, &Value_1);
      for( i = 0; i < No_of_POINTS_1; i++ ){
	
	Value = Value_0 + i * (Value_1 - Value_0)/(double)(No_of_POINTS_1 - 1);
	x_Data = Value;

	if( W_GRID_BIS[n] < 1.1 && W_GRID_BIS[n] > 0.99) {
	  X[Total_POINTS] = x_Data;
	  Y[Total_POINTS] = y_Data;
	  // printf(" (a = %g, K_0 = %g)\t W_GRID_BIS[%d] = %g\n",
	  //	 X[Total_POINTS], Y[Total_POINTS], y_Data, n, W_GRID_BIS[n]);  
	  // printf(" (a = %g, K_0 = %g)\t W_GRID_BIS[%d] = %g\n", x_Data, y_Data, n, W_GRID_BIS[n]);  
	  Total_POINTS++;
	}

	n++; 
      }
    }
    
    Table.CPG->color_Index = 3; /* Green (corresponding to disease-free equlibrium) */
    FIRST_PLOT = 1;
    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_U_B_R_E_G_I_O_N ( Table.CPG, 
								 FIRST_PLOT, 
								 X, Y, Total_POINTS );

    free(X); free(Y); free(W_GRID_BIS); 

    FIRST_PLOT = 1;
    Table.CPG->AUTOMATIC_CONTOUR = 0;
      /* If AUTOMATIC_CONTOUR is 0, the user should customized contours through
	 the function customized_contour_levels(...);
      */
    Table.CPG->contour_level = customized_contour_levels( Table.CPG );
    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___C_O_N_T_O_U_R( Table.CPG,
							      W_GRID, 
							      FIRST_PLOT,
							      Table.CPG->CPG_SCALE_W, 
							      Table.CPG->CPG_RANGE_W_0,
							      Table.CPG->CPG_RANGE_W_1,
							      i_PLOT );
    /* Annotating the countours by hand */
    // cpgptxt(float x, float y, float angle, float fjust,  const char *text);
    
    cpgsci(1);
    // Solution B:
    float size;
    cpgqch(&size); 
    cpgsch(1.5);
    cpgptxt(0.45, 85000.0, 0.0, 1.0, "T\\d\\fs0\\fn\\u\\(2748)=\\(2748)\\(0766)");  //\(0766) Infinte Symbol  //\(2748) Space
    cpgsch(size);
    cpgsci(7);
    cpgptxt(0.26, 23000.0, 0.0, 0.0, "3.0");
    cpgptxt(0.38, 45000.0, 0.0, 0.0,  "3.0");
    cpgsci(1);
    cpgptxt(0.20, 15000.0, 0.0, 0.0,  "6.0");
    cpgsci(1);
    cpgsch(1.5);
    cpgptxt(0.17, 8000.0, 0.0, 1.0, "R\\d\\fs0\\fn\\u\\(2748)<\\(2748)1");  //\(0766) Infinte Symbol  //\(2748) Space
    cpgsch(size);
    // Solution A:
    /* cpgptxt(0.45, 85000.0, 0.0, 1.0, "T\\d\\fs0\\fn\\u\\(2748)=\\(2748)\\(0766)");  //\(0766) Infinte Symbol  //\(2748) Space */
    /* cpgptxt(0.26, 23000.0, 0.0, 0.0, "3.0"); */
    /* cpgptxt(0.38, 45000.0, 0.0, 0.0,  "3.0"); */
    /* cpgptxt(0.20, 15000.0, 0.0, 0.0,  "6.0"); */
    /* cpgptxt(0.15, 9000.0, 0.0, 1.0, "R\\d\\fs0\\fn\\u\\(2748)<\\(2748)1");  //\(0766) Infinte Symbol  //\(2748) Space     */

    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S___F_R_A_M_E( Table.CPG,
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

float * customized_contour_levels( Parameter_CPGPLOT * C )
{
    int i;

    /* for (i=0; i < C->NC; i++) { */
    /*   clevels[i] = 1.0; */
    /* } */
    /* Two contour levels */
    C->NC = 5;

    float * clevels = (float *)calloc( C->NC, sizeof(float) );
    // Solution A
    /* clevels[0] = 10.0; */
    /* clevels[1] = 12.0; */
    /* clevels[2] = 13.0; */
    /* clevels[3] = 17.0; */
    /* clevels[4] = 20.0; */
    // Solution B
    clevels[0] = 3.0;
    clevels[1] = 6.0;
    clevels[2] = 9.0;
    clevels[3] = 12.0;
    clevels[4] = 20.0;
    
    return(clevels);
}



