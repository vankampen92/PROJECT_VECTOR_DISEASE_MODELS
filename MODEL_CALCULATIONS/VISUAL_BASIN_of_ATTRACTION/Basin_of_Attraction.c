#include "../../Include/MODEL.h"

#define EPSILON 1.0E-10

extern gsl_rng * r;

/* B E G I N : Auxiliary functions of: int B_A_S_I_N___o_f___A_T_T_R_A_C_T_I_O_N ( ... ) */
int BASIN_CALCULATION ( Parameter_Table *  , 
	                      double * , double * , 
	                      int , double * , double * , 
	                      int , double * , double * );

int Basin_Calculation ( Parameter_Table * , 
			double * , double * , double , 
			int , double * , double * , 
			int , double * , double * );

double D_I_S_T_A_N_C_E (Parameter_Table * , double * , double * );

void C_P_G___P_L_O_T_T_I_N_G___M_U_L_T_I_S_T_A_B_I_L_I_T_Y ( Parameter_Table * Table ); 
/*     E N D : --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */

int B_A_S_I_N___o_f___A_T_T_R_A_C_T_I_O_N ( int TYPE_of_CALCULATION, 
					    Parameter_Table * Table, 
					    int No_of_POINTS_0, double * X_0, double * Y_0,
					    int No_of_POINTS_1, double * X_1, double * Y_1,
					    int Realizations, 
					    double * W_GRID, 
					    int * N_0, int * N_1 )
{
  int bool_BASIN;
  
  int n_0; 
  int n_1; 

  int S; int E; int I; int R; int C; int S1; int I1; int S2; int I2; int S3; int I3;  
  int L; int X; int U; int W; 
  int A; 
  int K;

  int i,j,k, n;
  int I_Time, no_Patch;
  int Bad_Times;
  Parameter_Model * P;  

  I_Time    = Table->T->I_Time;

#if defined LXVnW
        Table->M_Fecundity = Table->M_a * Table->M_NoEggs;
#endif
#if defined XkVnW
        Table->M_Fecundity = Table->M_a * Table->M_NoEggs;
#endif
#if defined XVnW
        /* Total mosquito population constant */
        Table->M_Fecundity = Table->M_Delta;
#endif
#if defined XW
        /* Total mosquito population constant */
        Table->M_Fecundity = Table->M_Delta;
#endif

  P = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (Table, P);
  Table->P  = P;
  printf(" Parameter_Model structure has been correctly allocated and initiated\n");

  printf(" Deterministic dynamics will not have parameter time dependencies.\n");
#if defined TIME_DEPENDENCE 
  printf(" Time dependencies make no sense here. The program will exit.\n");
  printf(" Message from:\n");
  printf(" ~/VECTOR_DISEASE_MODELS/MODEL_CALCULATIONS/VISUAL_BASIN_of_ATTRACTION/MODEL.c\n)");
  exit(0);  
#endif
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
  /* Code definitions and dimension of the state model variables */
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (Table, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  &L, &X, &U, &W, &A, &K);
  int MODEL_STATE_VARIABLES = K+1; 
  Table->MODEL_STATE_VARIABLES = MODEL_STATE_VARIABLES;
  
  Table->Vector_Model_Variables_Time_0 = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );
  Table->Vector_Model_Variables = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );
  Table->Vector_Model_Variables_Stationarity = (double *)calloc( MODEL_STATE_VARIABLES, sizeof(double) );  

  /* B E G I N : Calculation of Stationary Points */
  Table->Vector_Model_Variables_MultiStability[0] = (double *)calloc( MODEL_STATE_VARIABLES, 
								      sizeof(double) ); 
  Table->Vector_Model_Variables_MultiStability[1] = (double *)calloc( MODEL_STATE_VARIABLES, 
								      sizeof(double) ); 
  Table->Vector_Model_Variables_MultiStability[2] = (double *)calloc( MODEL_STATE_VARIABLES, 
								      sizeof(double) );
  double * y_UPPER = Table->Vector_Model_Variables_MultiStability[0]; 
  double * y_INTER = Table->Vector_Model_Variables_MultiStability[1];  
  double * y_LOWER = Table->Vector_Model_Variables_MultiStability[2]; 
  
  F_I_X_E_D___A_L_L___P_O_I_N_T_S( Table, 
				   y_LOWER, y_INTER, y_UPPER, 
				   EPSILON ); 
  printf("Lower Fixed Point (model variables):\t"); 
  for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) printf("y_LOWER[%d] = %g\t", 
							  k, y_LOWER[k]);
  printf("\n");
  printf("Inter Fixed Point (model variables):\t"); 
  for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) printf("y_INTER[%d] = %g\t", 
							  k, y_INTER[k]);
  printf("\n");
  printf("Upper Fixed Point (model variables):\t");
  for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) printf("y_UPPER[%d] = %g\t", 
							  k, y_UPPER[k]);
  printf("\n");
  Press_Key();
  /*     E N D : ---------------------------------*/

  n_0 = 0;              n_1 = 0; 
  double w_MAX = Infectious_Mosquito_Steady_State( 1.0, Table);
  
  if ( TYPE_of_CALCULATION == 0 ){
  n = 0; 
  for( i=0; i<No_of_POINTS_0; i++ ) {
    Table->i__0 = (double)(i+1)/(double)No_of_POINTS_0*Table->H;           
    /* Number of infectious humans */

    for( j=0; j<No_of_POINTS_1; j++ ) {
      Table->m__i = w_MAX * (double)(j+1)/(double)No_of_POINTS_1; 
      /* Number of infectious mosquitoes */
     
      bool_BASIN = BASIN_CALCULATION( Table, y_LOWER, y_UPPER, 
	 			      n_0, X_0, Y_0, 
		                      n_1, X_1, Y_1 );
      W_GRID[n++] = (double)bool_BASIN;
      
      if      (bool_BASIN == 0) n_0++;
      else if (bool_BASIN == 1) n_1++;
      else    printf ("-");
    }
  }
  }
  else if ( TYPE_of_CALCULATION == 1 ){
  for( i=0; i<Realizations; i++ ) {

    Table->i__0 =  gsl_rng_uniform(r) * (double)Table->POPULATION;
    Table->m__i =  gsl_rng_uniform(r) * w_MAX;
    
    bool_BASIN = BASIN_CALCULATION( Table, y_LOWER, y_UPPER, 
				    n_0, X_0, Y_0, 
				    n_1, X_1, Y_1 );
#if defined CPGPLOT_REPRESENTATION
#if defined DRAW_LINES_PHASE_DIAGRAM
    //Press_Key();
    /* B E G I N  : Plotting temporal evolutions * * * * * * * * * * * * * */
    Table->CPG->type_of_Line   = 1;
    Table->CPG->type_of_Width  = 1;   Table->CPG->type_of_Symbol = 1;
    
    Table->CPG->CPG_RANGE_X_0  = 0.0;   
    Table->CPG->CPG_RANGE_X_1  = w_MAX / (double)Table->POPULATION; 
     
    if (bool_BASIN == 0 ) Table->CPG->color_Index = 7;
    else                  Table->CPG->color_Index = 8;

    C_P_G___P_H_A_S_E____D_I_A_G_R_A_M___S_A_M_E ( Table,
						   //			   i,
                                                   1,
						   1, 0,
						   Table->T->I_Time, Table->CPG->y_Time );
    /*     E N D : --- --- --- --- --- --- --- --- --- --- --- --- --- --- */ 
#endif
#endif
    if      (bool_BASIN == 0) n_0++;
    else if (bool_BASIN == 1) n_1++;
    else printf ("-");
  }
  }
  else if ( TYPE_of_CALCULATION == 2 ){
#if defined CPGPLOT_REPRESENTATION
    /* B E G I N  : Plotting temporal evolutions * * * * * * * * * * *  *  * */
    Table->CPG->type_of_Line   = 1;
    Table->CPG->type_of_Width  = 1;   Table->CPG->type_of_Symbol = 1;
    Table->CPG->CPG_RANGE_X_0  = 0.0;
    Table->CPG->CPG_RANGE_X_1  = w_MAX / (double)Table->POPULATION;
    /*     E N D : --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */
    for( i=0; i<No_of_POINTS_0; i++ ) {
      Table->i__0 = (double)(i+1)/(double)No_of_POINTS_0*Table->H;
      Table->m__i = 0.0 ; 
      bool_BASIN = BASIN_CALCULATION(Table, y_LOWER, y_UPPER, 
				     n_0, X_0, Y_0, n_1, X_1, Y_1);
      
      if (bool_BASIN == 0 )      { Table->CPG->color_Index = 7; n_0++; } 
      else if (bool_BASIN == 1)  { Table->CPG->color_Index = 8; n_1++; }
      else printf ("-");
      C_P_G___P_H_A_S_E____D_I_A_G_R_A_M___S_A_M_E ( Table,  1,  1, 0,
						     Table->T->I_Time, Table->CPG->y_Time );  
    }    
    for( i=0; i<No_of_POINTS_0; i++ ) {
      Table->i__0 = (double)(i+1)/(double)No_of_POINTS_0*Table->H;
      Table->m__i = w_MAX;
      bool_BASIN = BASIN_CALCULATION(Table, y_LOWER, y_UPPER,
    				     n_0, X_0, Y_0, n_1, X_1, Y_1);
      
      if (bool_BASIN == 0 )     { Table->CPG->color_Index = 7; n_0++; }
      else if (bool_BASIN == 1) { Table->CPG->color_Index = 8; n_1++; }
      else printf ("-");
      C_P_G___P_H_A_S_E____D_I_A_G_R_A_M___S_A_M_E ( Table,  1,  1, 0,
    						     Table->T->I_Time, Table->CPG->y_Time );
    }
    for( j=0; j<No_of_POINTS_1; j++ ) {
      Table->i__0 = 0.0;
      Table->m__i = w_MAX * (double)(j+1)/(double)No_of_POINTS_1;
      bool_BASIN = BASIN_CALCULATION(Table, y_LOWER, y_UPPER,
    				     n_0, X_0, Y_0, n_1, X_1, Y_1);
      
      if (bool_BASIN == 0 )     { Table->CPG->color_Index = 7; n_0++; }
      else if (bool_BASIN == 1) { Table->CPG->color_Index = 8; n_1++; }
      else printf ("-");
      C_P_G___P_H_A_S_E____D_I_A_G_R_A_M___S_A_M_E ( Table,  1,  1, 0,
    						     Table->T->I_Time, Table->CPG->y_Time );
    }
    for( j=0; j<No_of_POINTS_1; j++ ) {
      Table->i__0 = Table->H;
      Table->m__i = w_MAX * (double)(j+1)/(double)No_of_POINTS_1;
      bool_BASIN = BASIN_CALCULATION(Table, y_LOWER, y_UPPER,
    				     n_0, X_0, Y_0, n_1, X_1, Y_1);
      
      if (bool_BASIN == 0 )     { Table->CPG->color_Index = 7; n_0++; }
      else if (bool_BASIN == 1) { Table->CPG->color_Index = 8; n_1++; }
      else printf ("-");
      C_P_G___P_H_A_S_E____D_I_A_G_R_A_M___S_A_M_E ( Table,  1,  1, 0,
    						     Table->T->I_Time, Table->CPG->y_Time );
    }
#endif
  }
  else {
    printf(" TYPE_of_CALCULATION is out of possible range!\n TYPE_of_CALCULATION = %d\n", 
	   TYPE_of_CALCULATION );
    printf(" The program will exit!\n");
    printf(" Error from Basin_of_Attraction.c\n");
    exit(0);
  }
  
  (* N_0) = n_0;
  (* N_1) = n_1; 
  
  free( Table->Vector_Model_Variables_Time_0);
  free( Table->Vector_Model_Variables );
  free( Table->Vector_Model_Variables_Stationarity );
  
  free ( P );

  return(0);
}

int BASIN_CALCULATION ( Parameter_Table * Table , 
	                      double * y_LOWER, double * y_UPPER, 
	                      int n_0, double * X_0, double * Y_0, 
	                      int n_1, double * X_1, double * Y_1 )
{ 
	int bool_Basin;
	double x;
	
	D_E_T_E_R_M_I_N_I_S_T_I_C___T_I_M_E___D_Y_N_A_M_I_C_S( Table, 0 ) ;
        
        bool_Basin = Basin_Calculation ( Table, y_LOWER, y_UPPER, 1.0,
                                         n_0, X_0, Y_0,
                                         n_1, X_1, Y_1 );

	return (bool_Basin);
}
	 
int Basin_Calculation ( Parameter_Table * Table, 
			double * y_LOWER, double * y_UPPER, double Epsi, 
			int n_0, double * X_0, double * Y_0, 
			int n_1, double * X_1, double * Y_1 )
{
  int bool_BASIN;
  int k, kk;
  double D__0, D__1, D__S;

  D__S = D_I_S_T_A_N_C_E (Table, y_UPPER, y_LOWER);
  D__0 = D_I_S_T_A_N_C_E (Table, Table->Vector_Model_Variables, y_LOWER);
  D__1 = D_I_S_T_A_N_C_E (Table, Table->Vector_Model_Variables, y_UPPER);
  
  if (D__0 < D__1 && D__0 < (Epsi*D__S) ){
    bool_BASIN = 0;
          for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
	    kk = Table->IO_VARIABLE_LIST[k]; 
	    if (k == 1) 
	      X_0[n_0] = definition_OutPut_Variables(kk, 
						     Table->Vector_Model_Variables_Time_0, 
						     Table->T->Time_Vector[0], Table);
	    if (k == 0)
	      Y_0[n_0] = definition_OutPut_Variables(kk, 
						     Table->Vector_Model_Variables_Time_0, 
						     Table->T->Time_Vector[0], Table); 
	  }
  }
  else if (D__1 < D__0 && D__1 < (Epsi*D__S) ){
    bool_BASIN = 1;
          for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
	    kk = Table->IO_VARIABLE_LIST[k]; 
	    if (k == 1) 
	      X_1[n_1] = definition_OutPut_Variables(kk, 
						     Table->Vector_Model_Variables_Time_0, 
						     Table->T->Time_Vector[0], Table);
	    if (k == 0)
	      Y_1[n_1] = definition_OutPut_Variables(kk, 
						     Table->Vector_Model_Variables_Time_0, 
						     Table->T->Time_Vector[0], Table); 
	  }
  }
  else { 
    bool_BASIN = 2;
  }

  return( bool_BASIN );
}

double D_I_S_T_A_N_C_E (Parameter_Table * Table, double * Y_1, double * Y_2 )
{
  double D;
  int k, kk;
  double x_1, x_2;
  
  D = 0.0;
  for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
    kk = Table->IO_VARIABLE_LIST[k];
    
    x_1 = definition_OutPut_Variables(kk, Y_1, 0.0, Table); 
    x_2 = definition_OutPut_Variables(kk, Y_2, 0.0, Table);
      
    D += (( x_1 - x_2 ) * ( x_1 - x_2 ));
  }
  D = sqrt(D);	
  return (D);
}

void C_P_G___P_L_O_T_T_I_N_G___M_U_L_T_I_S_T_A_B_I_L_I_T_Y ( Parameter_Table * Table ) 
{
  /* Representing the upper, inter and lower steady-state stationary point */

  double * y_UPPER = Table->Vector_Model_Variables_MultiStability[0]; 
  double * y_INTER = Table->Vector_Model_Variables_MultiStability[1];  
  double * y_LOWER = Table->Vector_Model_Variables_MultiStability[2]; 
  
  double Radius;
  double y_Center_Upper, x_Center_Upper;
  double y_Center_Inter, x_Center_Inter;
  double y_Center_Lower, x_Center_Lower;
  double l_x, l_y;
  double X1, Y1, X2, Y2;
  
  int k_1 = Table->IO_VARIABLE_LIST[1];
  int k_0 = Table->IO_VARIABLE_LIST[0];
  
  Radius  =  D_I_S_T_A_N_C_E (Table, y_UPPER, y_LOWER ) / 200.0;
      
      /* UPPER */
  y_Center_Upper = definition_OutPut_Variables(k_0, y_UPPER, 0.0, Table);
  x_Center_Upper = definition_OutPut_Variables(k_1, y_UPPER, 0.0, Table);
  
  /* INTER */
  y_Center_Inter = definition_OutPut_Variables(k_0, y_INTER, 0.0, Table);
  x_Center_Inter = definition_OutPut_Variables(k_1, y_INTER, 0.0, Table);
  
  /* LOWER */
  y_Center_Lower = definition_OutPut_Variables(k_0, y_LOWER, 0.0, Table);
  x_Center_Lower = definition_OutPut_Variables(k_1, y_LOWER, 0.0, Table);
  
  l_y = y_Center_Upper - y_Center_Lower; assert( l_y );
  l_x = x_Center_Upper - x_Center_Lower; assert( l_x );
      
  /* UPPER */
  Table->CPG->color_Index = 0;
  X1 = x_Center_Upper - Radius * l_x/l_y;
  Y1 = y_Center_Upper - Radius;
  X2 = x_Center_Upper + Radius * l_x/l_y;
  Y2 = y_Center_Upper + Radius;
  CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___R_E_C_T_A_N_G_L_E ( Table->CPG,
							  X1, Y1,  X2, Y2, 
							  2);  
                                                         //Last argument: type_of_Filling;
  /* INTER */                                            //1: solid type of Filling.
  Table->CPG->color_Index = 1;    
  X1 = x_Center_Inter - Radius * l_x/l_y;
  Y1 = y_Center_Inter - Radius;
  X2 = x_Center_Inter + Radius * l_x/l_y;
  Y2 = y_Center_Inter + Radius;
  CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___R_E_C_T_A_N_G_L_E ( Table->CPG,    
							  X1, Y1,  X2, Y2, 
							  2);  
  //2: open type of Filling: 
  // no filling.
  
  /* LOWER */
  Table->CPG->color_Index = 0;    
  X1 = x_Center_Lower - Radius * l_x/l_y;
  Y1 = y_Center_Lower - Radius;
  X2 = x_Center_Lower + Radius * l_x/l_y;
  Y2 = y_Center_Lower + Radius;
  CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___R_E_C_T_A_N_G_L_E ( Table->CPG, 
							  X1, Y1,  X2, Y2, 
							  2 ); 
}
  
/* #if defined BASIN_SCAN  */
/*   for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) {  */
/*        printf("Vector Model Variables: y_1[%d] = %g\t",  */
/* 	      k, Table->Vector_Model_Variables[k]); */
/*   } */
/*   printf("\n"); */
/*   for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) {  */
/*        printf("Initial Vector Model Variables: y_0[%d] = %g\t",  */
/* 	      k, Table->Vector_Model_Variables_Time_0[k]); */
/*   } */
/*   printf("\n"); */
/*   for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) {  */
/*        printf("Lower Vector Model Variables: y_LOWER[%d] = %g\t",  */
/* 	      k, y_LOWER[k]); */
/*   } */
/*     printf("\n"); */
/*   for (k=0; k < Table->MODEL_STATE_VARIABLES; k++) {  */
/*        printf("Upper Vector Model Variables: y_UPPER[%d] = %g\t",  */
/* 	      k, y_UPPER[k]); */
/*   } */
/*   printf("\n"); */
/* #endif */
  
