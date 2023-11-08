#include "../Include/MODEL.h"

#define PRINT_OUT
#define SAVE_OUT
#define LABEL_TEMPERATURE 13
#define LABEL_RAIN 14

void S_E_A_S_O_N_A_L___C_Y_C_L_E___T_R_A_N_S_F_O_R_M_A_T_I_O_N ( int N, Parameter_Table * P , double * x, 
								 double * y,  double * y_Var, 
								 double ** Z, double ** Z_Var )
{
  char File_Name[25] = "Dum_Seasonal.dat";

  int i, j, k;
  
  double * y_Ave = (double*)malloc(sizeof(double) * 12);
  double * y_Dum = (double*)malloc(sizeof(double) * N );

  if( P->R_T.No_Ave != 12 ) printf( " Seasonal cycle is not 12 months... Something weird is happening\n");
  assert(P->R_T.No_Ave == 12);

  for(i=0; i<N-1; i++) y_Dum[i] = y[i+1];
  A_V_E_R_A_G_E___S_E_A_S_O_N_A_L___C_Y_C_L_E ( File_Name, N-1, P->R_T.No_Ave, y_Dum, y_Ave, y_Var );
  for( i=0; i<12; i++) { y[i] = y_Ave[i]; }

  for(j = 0; j < P->NO_OUT_VAR_LIST; j++ ){

    k = P->Out_Var_List[j];
    for(i=0; i<N-1; i++){ 
	if ( k == LABEL_TEMPERATURE || k == LABEL_RAIN ){
            y_Dum[i] = Z[j][i];
	}
	else{
	    y_Dum[i] = Z[j][i+1];
	} 
    }
    A_V_E_R_A_G_E___S_E_A_S_O_N_A_L___C_Y_C_L_E ( File_Name, N-1, P->R_T.No_Ave, y_Dum, y_Ave, Z_Var[j] );
    for( i=0; i<12; i++) { Z[j][i] = y_Ave[i]; }

  }

  free(y_Ave);
  free(y_Dum);
}

void A_V_E_R_A_G_E___S_E_A_S_O_N_A_L___C_Y_C_L_E (char * File_To_Save,
						  const int NO_of_POINTS, const int NO_of_POINTS_AVE, const double * Input_Time_Series, 
						  double * Time_Series_Ave, double * Time_Series_Var )
{
  /* Calculating Average (annual) Seasonal Cycle */
  
  /* This procedure calculates the average seasonal cycle
     of an Input_Time_Series[] of length 'NO_of_POINTS'
  
     The results are stored in:
     Input_Time_Series_Ave[], 
     and 
     Input_Time_Series_Var[],
     two vectors of length 'NO_of_POINTS_AVE'
  */
  int k, i, NO_of_TERMS;
  double SUM_AVE, SUM_VAR;
  double * Time_Ave = (double *)malloc(sizeof(double) * NO_of_POINTS_AVE) ;
  FILE * fp;

#if defined PRINT_OUT
  printf("Calculating average annual cycle...\n");
#endif
  
  for(k = 0; k < NO_of_POINTS_AVE; k++){

    SUM_AVE = 0.0; SUM_VAR = 0.0; 
    NO_of_TERMS = 0;
    Time_Ave[k] = ((double)(k+1))/(double)NO_of_POINTS_AVE; 
    /* Months in (fraction of Year Units: 1/12, 2/12, ... */
    for(i=0; i<NO_of_POINTS; i++){
  
      if(i%NO_of_POINTS_AVE == k){
	SUM_AVE += Input_Time_Series[i];
	SUM_VAR += Input_Time_Series[i] * Input_Time_Series[i];
	NO_of_TERMS ++;
      }
    }
    
    Time_Series_Ave[k] = SUM_AVE/(double)NO_of_TERMS;

    Time_Series_Var[k] = sqrt( SUM_VAR/(double)NO_of_TERMS - Time_Series_Ave[k] * Time_Series_Ave[k] );
  }

#if defined SAVE_OUT
  
  fp = fopen(File_To_Save, "w");

  for (k=0; k<NO_of_POINTS_AVE; k++){
    fprintf(fp, "%g\t%g\t%g\n",
	    Time_Ave[k], Time_Series_Ave[k], Time_Series_Var[k]);
  }
  fclose(fp);

#endif

  free (Time_Ave);
}

void A_V_E_R_A_G_E___S_E_A_S_O_N_A_L___C_Y_C_L_E___T_W_O___P_E_R_I_O_D_S (char * File_To_Save_0, char * File_To_Save_1,
									  const int No, 
									  const int NO_of_POINTS_AVE,
									  const int n_Data,
									  const double * Input_Time_Series, 
									  double * Time_Series_Ave_0, double * Time_Series_Var_0,
									  double * Time_Series_Ave_1, double * Time_Series_Var_1)
{
  /* This procedure calculates the average seasonal cycle
     of an Input_Time_Series[] of length 'NO_of_POINTS'
     in two different periods: at the begining of the 
     time series and at the end of the time series

     The output results are stored in:
     Time_Series_Ave_0[], Time_Series_Var_0[]
     and
     Time_Series_Ave_1[], Time_Series_Var_1[]
     four vectors of length 'NO_of_POINTS_AVE'
  */
  int k, i, NO_of_TERMS, i_0, i_1;
  double SUM_AVE, SUM_VAR;
  double * Time_Ave = (double *)malloc(sizeof(double) * NO_of_POINTS_AVE) ;
  double * Input_Time_Series_End = (double *)malloc( sizeof(double) * n_Data);
  FILE * fp;

  for(k = 0; k < NO_of_POINTS_AVE; k++){

    SUM_AVE = 0.0; SUM_VAR = 0.0; 
    NO_of_TERMS = 0;
    Time_Ave[k] = ((double)(k+1))/(double)NO_of_POINTS_AVE; /* Average Months in (fraction of) Year Units */
    
    for(i=0; i < n_Data; i++){
  
      if(i%NO_of_POINTS_AVE == k){
	SUM_AVE += Input_Time_Series[i];
	SUM_VAR += Input_Time_Series[i] * Input_Time_Series[i];
	NO_of_TERMS ++;
      }
    }
    
    Time_Series_Ave_0[k] = SUM_AVE/(double)NO_of_TERMS;
    Time_Series_Var_0[k] = sqrt( SUM_VAR/(double)NO_of_TERMS - Time_Series_Ave_0[k] * Time_Series_Ave_0[k] );
  }

  fp = fopen(File_To_Save_0, "w");

  for (k=0; k<NO_of_POINTS_AVE; k++){
    fprintf(fp, "%g\t%g\t%g\n",
	    Time_Ave[k], Time_Series_Ave_0[k], Time_Series_Var_0[k]);
  }
  fclose(fp);
  
  /* Building a time series containing the last 120 data points */
  i_0 = No - 12 - n_Data; /* This involves to discard the   */
  i_1 = No - 12;          /* last 12 monthly data of the    */
                          /* last year (usually, 2003) because 
			     the model does not yield a prediction
			     for the DEC of the last year, so it 
			     is not complete */

  for (i = 0; i < n_Data; i++){
    Input_Time_Series_End[i] = Input_Time_Series[i_0 + i];
  }

  for(k = 0; k < NO_of_POINTS_AVE; k++){

    SUM_AVE = 0.0; SUM_VAR = 0.0; 
    NO_of_TERMS = 0;
    
    for(i=0; i < n_Data; i++){
  
      if(i%NO_of_POINTS_AVE == k){
	SUM_AVE += Input_Time_Series_End[i];
	SUM_VAR += Input_Time_Series_End[i] * Input_Time_Series_End[i];
	NO_of_TERMS ++;
      }
    }
    
    Time_Series_Ave_1[k] = SUM_AVE/(double)NO_of_TERMS;
    Time_Series_Var_1[k] = sqrt( SUM_VAR/(double)NO_of_TERMS - Time_Series_Ave_1[k] * Time_Series_Ave_1[k] );
  }

  fp = fopen(File_To_Save_1, "w");

  for (k=0; k<NO_of_POINTS_AVE; k++){
    fprintf(fp, "%g\t%g\t%g\n",
	    Time_Ave[k], Time_Series_Ave_1[k], Time_Series_Var_1[k]);
  }
  fclose(fp);
}
