#include "./Include/MODEL.h"

void variable_Name(char * Label, char * Title_In);

void AssignLabel_to_Model_Variables(int j, char * Label, Parameter_Table *P)
{
  int jj;
  int S, E, I, R, C, S1, I1, S2, I2, S3, I3, A;
  int L, X, U, W, K_W, K;
  char No[2];
  char *pFile;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (P, &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,  &L, &X, &U, &W, &A, &K);

  if(j == S){

    variable_Name(Label, "S");

  }
  else if (j > S && j < I){

    Label[0]='\0';
    if (I-S > 2)  {
          pFile = strcat(Label, "E_");
          sprintf(No, "%d", j);
          pFile = strcat(Label, No);
    }
    else  pFile = strcat(Label, "E");

  }
  else if(j == I){

    variable_Name(Label, "I");

  }
  else if(j == R){

    variable_Name(Label, "R");

  }
  else if(j == C){

    variable_Name(Label, "C");

  }
  else if(j == S1){

    variable_Name(Label, "S1");

  }
  else if(j == I1){

    variable_Name(Label, "I1");

  }
  else if(j == S2){

    variable_Name(Label, "S2");

  }
  else if(j == I2){

    variable_Name(Label, "I2");

  }
  else if(j == S3){

    variable_Name(Label, "S3");

  }
  else if(j == I3){

    variable_Name(Label, "I3");

  }
#if defined CASES_33
  else if(j == A){

    variable_Name(Label, "Accumulated Cases");

  }
#endif
  else if(j == L){

    variable_Name(Label, "L");

  }
  else if(j == X){

    variable_Name(Label, "X");

  }
  else if(j > X && j < W){

    Label[0]='\0';
    jj = j - X;
    if (W-X > 2)  {
          pFile = strcat(Label, "V_");
          sprintf(No, "%d", jj);
          pFile = strcat(Label, No);
    }
    else  pFile = strcat(Label, "V");

  }
  else if(j == W){

    variable_Name(Label, "W");

  }
  else if(j == K){

    variable_Name(Label, "K");

  }
  else if(j == K_W){

    variable_Name(Label, "K_W");

  }
  else{
    printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
    printf(".... The permited correspondences are:\n");
    printf(".... The program will exit\n");
    exit(0);
  }
}

void variable_Name(char * Label, char * Title_In)
{
  char * p;
  Label[0] = '\0';
  p = strcat( Label, Title_In );
}
