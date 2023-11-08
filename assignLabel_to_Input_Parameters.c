#include "./Include/MODEL.h"

void parameter_Name(char * Label, char * Title_In);

void AssignLabel_to_Parameters(int j, char * Label, Parameter_Table *P)
{


  switch(j)
    {

    case 0:   /* H */
              parameter_Name(Label, "POPULATION");

              ;
	      break;
    case 1:   /* H_Delta */
              parameter_Name(Label, "\\gd\\dH\\u");

              ;
	      break;
    case 2:
	      parameter_Name(Label, "H_Birth");

	      ;
	      break;
    case 3:
              parameter_Name(Label, "\\gs\\d\\fs0\\fn\\u");

	      ;
	      break;
    case 4:
      //parameter_Name(Label, "H_Revov_0");
	      parameter_Name(Label, "r\\d\\fs0\\fn\\u");

	      ;
	      break;
    case 5:
	      parameter_Name(Label, "n\\dH\\u");

	      ;
	      break;
    case 6:
	      parameter_Name(Label, "\\gg\\dH\\u");

	      ;
	      break;
    case 7:
              parameter_Name(Label, "\\gb\\de\\u"); /* Immigration */

	      ;
	      break;
    case 8:
	      parameter_Name(Label, "\\gx");

              ;
	      break;
    case 9:
	      parameter_Name(Label, "\\gr");

	      ;
	      break;
    case 10:
	      parameter_Name(Label, "\\gy");

	      ;
	      break;
    case 11:
	      parameter_Name(Label, "\\gn");

	      ;
	      break;
    case 12:
	      parameter_Name(Label, "a");

	      ;
	      break;
    case 13:
	      parameter_Name(Label, "b");

              ;
	      break;
    case 14:
	      parameter_Name(Label, "c");

              ;
	      break;
    case 15:
	      parameter_Name(Label, "\\gd\\dM\\u");

              ;
	      break;
    case 16:
	      parameter_Name(Label, "M_Delta_R");

	      ;
	      break;
    case 17:
	      parameter_Name(Label, "M_Delta_PE");

	      ;
	      break;
    case 18:
	      parameter_Name(Label, "M_Fecundity");

	      ;
	      break;
    case 19:
	      parameter_Name(Label, "M_Nol_Eggs");

	      ;
	      break;
    case 20:
	      parameter_Name(Label, "d\\dL\\u");

	      ;
	      break;
    case 21:
	      parameter_Name(Label, "\\gd\\dL\\u");

	      ;
	      break;
    case 22:
	      parameter_Name(Label, "L_Delta_P");

	      ;
	      break;
    case 23:
	      parameter_Name(Label, "L_Delta_R");

	      ;
	      break;
    case 24:
	      parameter_Name(Label, "L_Delta_PE");

	      ;
	      break;
    case 25:
      //parameter_Name(Label, "K_0");
	      parameter_Name(Label, "K\\d\\fs0\\fn\\u");

	      ;
	      break;
    case 26:
	      parameter_Name(Label, "var(K_0)");

              ;
	      break;
    case 27:
	      parameter_Name(Label, "K_A");

	      ;
	      break;
    case 28:
	      parameter_Name(Label, "K_p");

	      ;
	      break;
    case 29:
	      parameter_Name(Label, "K_E");

	      ;
	      break;
    case 30:
	      parameter_Name(Label, "n_V");

	      ;
	      break;
    case 31:
	      parameter_Name(Label, "\\gg\\dM\\u");

              ;
	      break;
    case 32:
	      /*  Shift in temperature for adult mosquitoes */
              parameter_Name(Label, "TEMP__SHIFT");
              ;
	      break;
    case 33:
	      /*  Shift in temperature due to altitude  */
              parameter_Name(Label, "TEMP_ELEVATION");
              ;
	      break;
    case 34:
	      /*  Temperature shift to ajust for elevation  */
              parameter_Name(Label, "External Influx of Adult Mosquitoes");
              break;
    case 35:
	      /*  Initial Fraction of Susceptible  */
              parameter_Name(Label, "y_0[S]");//Initial Fraction of Susceptible");
              break;
    case 36:
	      /*  Initial Fraction of Exposed  */
              parameter_Name(Label, "y_0[E]");//Initial Fraction of Exposed");
              break;
    case 37:
	      /*  Initial Fraction of Infectious  */
              parameter_Name(Label, "y_0[I]");//Initial Fraction of Infectious");
              break;
    case 38:
	      /*  Initial Fraction of Recovered  */
              parameter_Name(Label, "y_0[R]"); //(or cases!!! ---> Initial Fraction of cases");
              break;
    case 39:
	      /*  Carrying capacity maturation rate */
              parameter_Name(Label, "K_Maturation");
              break;
    case 40:
	      /* Error Parameter  */
              parameter_Name(Label, "Err_0");
              break;
    case 41:
	      /* Error Parameter */
              parameter_Name(Label, "Err_1");
              break;
    case 42:

              parameter_Name(Label, "x");
              break;
    case 43:

              parameter_Name(Label, "c_1");
              break;
    case 44:

              parameter_Name(Label, "c_2");
              break;
    case 45:

              parameter_Name(Label, "e__2");
              break;
    case 46:

              parameter_Name(Label, "m");
              break;
    case 47:
	      /* Modifier on loss of immunity  */
              parameter_Name(Label, "mSigma");
              break;
    case 48:
	      /* Modifier on recovery from infection  */
              parameter_Name(Label, "mRecov");
              break;
    case 49:
	      /* Modifier on human susceptibility  */
              parameter_Name(Label, "mb");
              break;
    case 50:
        /* Modifier on human infectiousness  */
              parameter_Name(Label, "mc");
              break;
    case 51:
        /* Modifier on human infectiousness  */
              parameter_Name(Label, "Temp");
              break;
    case 52:
        /* Initial fraction of S1 (SnInR model)  */
              parameter_Name(Label, "y_0[S1]");
              break;
    case 53:
        /* Initial fraction of I1 (SnInR model)  */
              parameter_Name(Label, "y_0[I1]");
              break;
    case 54:
        /* Initial fraction of S1 (SnInR model)  */
              parameter_Name(Label, "y_0[S2]");
              break;
    case 55:
        /* Initial fraction of I1 (SnInR model)  */
              parameter_Name(Label, "y_0[I2]");
              break;
    case 56:
        /* Initial fraction of S1 (SnInR model)  */
              parameter_Name(Label, "y_0[S3]");
              break;
    case 57:
        /* Initial fraction of I1 (SnInR model)  */
              parameter_Name(Label, "y_0[I3]");
              break;
    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Input_Parameters(stdout, P);
      exit(0);
    }
}

void parameter_Name(char * Label, char * Title_In)
{
  char * p;

  Label[0] = '\0';
  p = strcat( Label, Title_In );

}
