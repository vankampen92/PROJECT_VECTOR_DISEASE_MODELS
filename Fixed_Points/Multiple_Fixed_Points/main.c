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

#include "global.h"

/* This code calculates fixed points for an ODE system of a human-mosquito 
   coupled model of malaria transmission. Then, it checks them to see
   if they make ODE system derivatives zero. See the function below: 

   void checking_Solution(Parameter_Table * P, double * y_Sol)

   Compilation:
   
   . ~$ make JACOBIAN=ODE H_MODEL=CASES_1 M_MODEL=LXVnW

   Exectution:
  
   . ~$ ./CASES_1-LXVnW -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05

   . ~$ ./CASES_1-LXVnW -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 ; xmgrace -nxy y_W_0.dat 

   . ~$ ./SnInR-LXVnW   -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001 -M0 0.4 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 -Y0 25.0 

*/

void checking_Solution(Parameter_Table * P, double * y_Sol);

#define EPSILON 1.e-8

int fprintf_to_File_Matrix_gsl(FILE * Out, gsl_matrix * A, int MM, int NN){
  int i,j;
  for (i=0;i<MM;i++){
    for (j=0;j<NN;j++){
      fprintf(Out,"%g\t",gsl_matrix_get(A,i,j));
    }
    fprintf(Out,"\n");
  }
  fprintf(Out,"\n");
  return 0;
}

int main(int argc, char **argv)
{
  int i;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3, L, X, U, W, A, K;
  Parameter_Table P;
  FILE *fp;

  /* Default vaules */

#include "default.c"

#if defined CASES_1
  P.TYPE_of_MODEL        = 11;
#endif
#if defined CASES_1LXVnW
  P.TYPE_of_MODEL        = 11;
#endif
#if defined CASES_1XkVnW
  P.TYPE_of_MODEL        = 12;
#endif
#if defined CASES_1XVnW
  P.TYPE_of_MODEL        = 13;
#endif
#if defined CASES_1XW
  P.TYPE_of_MODEL        = 14;
#endif

#if defined NO_CASES
  P.TYPE_of_MODEL        = 21;
#endif
#if defined NO_CASESLXVnW
  P.TYPE_of_MODEL        = 21;
#endif
#if defined NO_CASESXkVnW
  P.TYPE_of_MODEL        = 22;
#endif
#if defined NO_CASESXVnW
  P.TYPE_of_MODEL        = 23;
#endif
#if defined NO_CASESXW
  P.TYPE_of_MODEL        = 24;
#endif

#if defined SEnI
  P.TYPE_of_MODEL        = 31;
#endif
#if defined SEnILXVnW
  P.TYPE_of_MODEL        = 31;
#endif
#if defined SEnIXkVnW
  P.TYPE_of_MODEL        = 32;
#endif
#if defined SEnIXVnW
  P.TYPE_of_MODEL        = 33;
#endif
#if defined SEnIXW
  P.TYPE_of_MODEL        = 34;
#endif

#if defined SI
  P.TYPE_of_MODEL        = 41;
#endif
#if defined SILXVnW
  P.TYPE_of_MODEL        = 41;
#endif
#if defined SIXkVnW
  P.TYPE_of_MODEL        = 42;
#endif
#if defined SIXVnW
  P.TYPE_of_MODEL        = 43;
#endif
#if defined SIXW
  P.TYPE_of_MODEL        = 44;
#endif

#if defined SnInR
  P.TYPE_of_MODEL        = 51;
#endif
#if defined SnInRLXVnW
  P.TYPE_of_MODEL        = 51;
#endif
#if defined SnInRXkVnW /* None of these following SnInR models are unpacked anywhere else yet */
  P.TYPE_of_MODEL        = 52;
#endif
#if defined SnInRint
  P.TYPE_of_MODEL        = 53;
#endif
#if defined SnInRXW
  P.TYPE_of_MODEL        = 54;
#endif

  P_ARG = &P;
 
  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);
  
  values_HumanMos(&P);
  
#if defined CASES_33
  P.TYPE_of_MODEL        = 0;
  printf(" This code cannot be compiled with this option\n");
  printf(" Use the equivalent CASES_1 option instead\n");
  printf(" The program will exit\n");
  exit(0);
#endif
  
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (&P, 
					   &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					   &L, &X, &U, &W, &A, 
					   &K);
  
  P.MODEL_STATE_VARIABLES = K+1; 
  
  double * y_Sol_Lower = (double *)calloc( (W+1), sizeof(double) );
  double * y_Sol_Inter = (double *)calloc( (W+1), sizeof(double) );
  double * y_Sol_Upper = (double *)calloc( (W+1), sizeof(double) );
  
  fixed_Points_All(&P, 
		   y_Sol_Lower, y_Sol_Upper, y_Sol_Inter, 
		   EPSILON);

  /* Checking the three solutions... once at a time */
  /* Lower ... */
  printf(" Lower solution...\n");  
  checking_Solution(&P, y_Sol_Lower);
  
  printf(" Inter solution...\n");  
  checking_Solution(&P, y_Sol_Inter);

  printf(" Upper solution...\n");  
  checking_Solution(&P, y_Sol_Upper);
  
  /* The first argument inf y_W_diagram(...) is just a label
     to save a file: y_W_LABEL.dat, i.e., y_W_0.dat */
  y_W_diagramm(0, &P); /* Plotting Diagramm y versus W */
 
  Parameters_ModelReport("report.txt", P_ARG);    

  double M = Total_Mosquito_Steady_State(&P);
  printf("Total Mosquito Population... %g\n", M);
  double m = M/P.H;
  printf("Total Mosquito Population per Human ... %g\n", m);

  free(y_Sol_Lower);
  free(y_Sol_Upper);
  free(y_Sol_Inter);

  printf("\nEnd of progam\n");
  return (0);
}

void checking_Solution(Parameter_Table * P, double * y_Sol)
{
  int i;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3, L, X, U, W, A, K;
  double Human_Population, M, y;
  char * Label = (char *)calloc( 20, sizeof(char) );
	
  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P, 
					    &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  
					    &L, &X, &U, &W, &A, 
					    &K );

  double * dydt_Sol = (double *)calloc( (W+1), sizeof(double) );
  
  i = function (0, y_Sol, dydt_Sol, P);
  
  /* Writing Solution */
 
  printf("... Writing fixed point solution:\n");
  for(i = 0; i<=W; i++){
     AssignLabel_to_Model_Variables(i, Label, P);  
     printf("y[%s] = %g\n", Label, y_Sol[i]);
  }
  
  /* Evaluationg the ODE at the Solution (This should be zero) */
  printf("... Evaluating derivatives of the ODE system at the fixed point:\n");
  for(i = 0; i<=W; i++){
     AssignLabel_to_Model_Variables(i, Label, P); 
     printf("dydt[%s] = %g\n", Label, dydt_Sol[i]);
  }
  
  Human_Population = total_Humans(y_Sol, P);
  printf("Total Human Population  H = %g\n", Human_Population);
  
  M = Total_Mosquito_Steady_State(P);  
  printf("Total mosquito population... %g\n", M);
  double m = M/P->H;
  printf("Mosquito density per human ... %g\n", m);
  
  y = Infectious_Human_Steady_State_Fraction(y_Sol[W], P);
  
  printf("Fraction of human infection... %g\tTotal Infectious Mosquitoes... %g\n", 
	 y, y_Sol[W]);
  
  free(dydt_Sol);
  free(Label);
}
