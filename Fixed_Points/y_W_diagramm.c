/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                             MALARIA ODE with "Gamma" DELAYS               */
/*                                                                           */
/*                         Recursive Calculation of Fixed Points             */
/*                                                                           */
/*                                 David Alonso, 2006 (c)                    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <MODEL.h>

void y_W_diagramm(int k_File, Parameter_Table *P)
{
  int i;
  double w, y_1,y_2;
  double w_Max;
  double *y_Sol;
  FILE *fp;
  char file[100];

  w_Max = Infectious_Mosquito_Steady_State(1., P);
  printf("Max number of infectious mosquitoes (if fraction infectious human was 1)... %g\n",
         w_Max);

  file[0]='\0';
  fitxer(file, "y_W_", k_File, ".dat");
  fp = fopen(file, "w");
  for(i=0; i < 1000; i++){

    w = (double)i*0.001*w_Max; /*Total Infectious Mosquitos */

    y_1 = Inverted_Mosquito_Steady_State(w, P);
    y_2 = Infectious_Human_Steady_State_Fraction(w, P);

    fprintf(fp, "%g\t%g\t%g\n", w, y_1, y_2);

  }
  fclose(fp);
}

double I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M( Parameter_Table *P, int No,
						      double *x_Data, double *y_1, double *y_2 )
{
  double x, w_Max, w;
  int i;

  x = 0.0;

  w_Max = Infectious_Mosquito_Steady_State(1., P);

  for(i=0; i < No; i++){

    w = (double)i * w_Max / (double)No; /* Total Infectious Mosquitos */
    x_Data[i] = w;

    y_1[i] = Inverted_Mosquito_Steady_State(w, P);
    y_2[i] = Infectious_Human_Steady_State_Fraction(w, P);

    //printf("%g\t%g\t%g\n", w, y_1[i], y_2[i]);
  }

  return(x);
}

#if defined CPGPLOT_REPRESENTATION
void I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M___S_I_N_G_L_E___P_L_O_T ( Parameter_Table * P,
                                                                             int N, double * x_Data, double ** y,
                                                                             char * Title_In )
{
      char * p_DUMMY;
      char * X_label  = (char *)malloc( sizeof(char) * 500 );
      char * Y_label  = (char *)malloc( sizeof(char) * 500 );
      /*********************************************************************/
      X_label[0] = '\0';
      p_DUMMY = strcat( X_label, "  Number of Infectious Mosquitoes per Human ");
      Y_label[0] = '\0';
      p_DUMMY = strcat( Y_label, "  Fraction of Infectious Humans ");
      Title_In[0] = '\0';
      /*********************************************************************/
      CPGPLOT___X_Y_n___P_L_O_T_T_I_N_G ( P->CPG,
                                          N, 2,
                                          x_Data, y,
                                          X_label, Y_label, Title_In,
                                          P->CPG->CPG_SCALE_X, P->CPG->CPG_SCALE_Y );

      free(X_label); free(Y_label);
}


void P_L_O_T_T_I_N_G___I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M( Parameter_Table * P,
								      int N,
								      int No_of_POINTS,
								      int Input_Parameter )
{
  char * p_DUMMY;
  char * X_label  = (char *)malloc( sizeof(char) * 500 );
  char * Y_label  = (char *)malloc( sizeof(char) * 500 );
  char * Title_In = (char *)malloc( sizeof(char) * 500 );
  char * Number   = (char *)malloc( sizeof(char) * 50  );

  double Value, Value_0, Value_1;
  int j;

  /*********************************************************************/
  X_label[0] = '\0';
  p_DUMMY = strcat( X_label, "  Mosquito Population  ");
  Y_label[0] = '\0';
  p_DUMMY = strcat( Y_label, "  Fraction of Infectious Humans ");
  /*********************************************************************/

  double * x_Data = (double *)calloc( N, sizeof(double) );
  double ** y     = (double **)calloc( 2, sizeof(double) );
  y[0]            = (double *)calloc( N, sizeof(double) );
  y[1]            = (double *)calloc( N, sizeof(double) );

  // Boundary( Input_Parameter, &Value_0, &Value_1 );
  Value_0 = P->S->Value_0;
  Value_1 = P->S->Value_1;

  for( j = 0; j < No_of_POINTS; j++ ){

    Value = Value_0 + j * (Value_1 - Value_0)/(double)(No_of_POINTS - 1);

    AssignVectorEntry_to_Structure(P, Input_Parameter, Value);
    P->M_Fecundity = P->M_a * P->M_NoEggs;

    double x = I_N_T_E_R_S_E_C_T_I_O_N___y_W___D_I_A_G_R_A_M( P, N, x_Data, y[0], y[1]);

    Title_In[0] = '\0';
    p_DUMMY = strcat( Title_In, "  I n t e r s e c t i o n:  ");
    p_DUMMY = strcat( Title_In, P->Name_Parameters[Input_Parameter] );
    p_DUMMY = strcat( Title_In, "  =  ");

    // doubletochar( Value, Number );
    sprintf(Number, "%g", Value);
    p_DUMMY = strcat( Title_In, Number);

    CPGPLOT___X_Y_n___P_L_O_T_T_I_N_G ( P->CPG, N, 2, x_Data, y,
					X_label, Y_label, Title_In,
					P->CPG->CPG_SCALE_X,
					P->CPG->CPG_SCALE_Y );

    Title_In[0] = '\0';
    p_DUMMY = strcat( Title_In, "a=" );
    p_DUMMY = strcat( Title_In, Number);
    p_DUMMY = strcat (Title_In, "___");
    Saving_to_File_double(Title_In, x_Data, y[0], N, 0);
    Saving_to_File_double(Title_In, x_Data, y[1], N, 1);

    getchar();
  }

  free (Title_In); free(X_label); free(Y_label); free (Number);
  free (x_Data); free (y[0]); free (y[1]); free(y);
}
#endif
