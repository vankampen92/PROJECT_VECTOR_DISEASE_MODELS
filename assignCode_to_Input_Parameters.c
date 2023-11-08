#include "./Include/MODEL.h"

void parameter_Name(char * Label, char * Title_In);

void AssignCodes_to_Parameters(int j, char * Label, Parameter_Table *P)
{

  switch(j)
    {

    case 0:   /* H */
              parameter_Name(Label, "-Q");

              ;
	      break;
    case 1:   /* H_Delta */
              parameter_Name(Label, "-H2");

              ;
	      break;
    case 2:   /* H_Birth */
	      parameter_Name(Label, "-H1");

	      ;
	      break;
    case 3:
              parameter_Name(Label, "-H3");

	      ;
	      break;
    case 4:
	      parameter_Name(Label, "-H4");

	      ;
	      break;
    case 5:
	      parameter_Name(Label, "-H5");

	      ;
	      break;
    case 6:
	      parameter_Name(Label, "-H6");

	      ;
	      break;
    case 7:
	      parameter_Name(Label, "-H7");

	      ;
	      break;
    case 8:
	      parameter_Name(Label, "-C0");

              ;
	      break;
    case 9:
	      parameter_Name(Label, "-C1");

	      ;
	      break;
    case 10:
	      parameter_Name(Label, "-C2");

	      ;
	      break;
    case 11:
	      parameter_Name(Label, "-C3");

	      ;
	      break;
    case 12:
	      parameter_Name(Label, "-M0");

	      ;
	      break;
    case 13:
	      parameter_Name(Label, "-M1");

              ;
	      break;
    case 14:
	      parameter_Name(Label, "M2");

              ;
	      break;
    case 15:
	      parameter_Name(Label, "-M3");

              ;
	      break;
    case 16:
	      parameter_Name(Label, "-M4");

	      ;
	      break;
    case 17:
	      parameter_Name(Label, "-M5");

	      ;
	      break;
    case 18:
	      parameter_Name(Label, "-M6");

	      ;
	      break;
    case 19:
	      parameter_Name(Label, "-M7");

	      ;
	      break;
    case 20:
	      parameter_Name(Label, "-L0");

	      ;
	      break;
    case 21:
	      parameter_Name(Label, "-L1");

	      ;
	      break;
    case 22:
	      parameter_Name(Label, "-L9");

	      ;
	      break;
    case 23:
	      parameter_Name(Label, "-L10");

	      ;
	      break;
    case 24:
	      parameter_Name(Label, "-L11");

	      ;
	      break;
    case 25:
	      parameter_Name(Label, "-L2");

	      ;
	      break;
    case 26:
	      parameter_Name(Label, "-L3");

              ;
	      break;
    case 27:
	      parameter_Name(Label, "-L6");

	      ;
	      break;
    case 28:
	      parameter_Name(Label, "-L7");

	      ;
	      break;
    case 29:
	      parameter_Name(Label, "-L8");

	      ;
	      break;
    case 30:
	      parameter_Name(Label, "-P0");

	      ;
	      break;
    case 31:
	      parameter_Name(Label, "-P1");

              ;
	      break;


    case 32:
	      /*  Shift in temperature for adult mosquitoes */
              parameter_Name(Label, "-R3");
              ;
	      break;
    case 33:
	      /*  Shift in temperature due to altitude  */
              parameter_Name(Label, "-R4");
              ;
	      break;
    case 34:
	      /* External Influx of Adult Mosquitoes   */
              parameter_Name(Label, "-M8");
              break;
    case 35:
	      /*  Initial Fraction of Susceptible  */
              parameter_Name(Label, "-X0");//Initial Fraction of Susceptible");
              break;
    case 36:
	      /*  Initial Fraction of Exposed  */
              parameter_Name(Label, "-X1");//Initial Fraction of Exposed");
              break;
    case 37:
	      /*  Initial Fraction of Infectious  */
              parameter_Name(Label, "X2");//Initial Fraction of Infectious");
              break;
    case 38:
	      /*  Initial Fraction of cases  */
              parameter_Name(Label, "-X3");//Initial Fraction of cases");
              break;
    case 39:
	      /*  Carrying capacity maturation rate */
              parameter_Name(Label, "-L12");
              break;
    case 40:
	      /* Error Parameter */
              parameter_Name(Label, "-E0");
              break;
    case 41:
	      /* Error Parameter */
              parameter_Name(Label, "-E1");
              break;
    case 42:
	      /* Parameter related to the difference between Inner/Outdoor temperature, R_T.x */
              parameter_Name(Label, "-R6");
              break;
    case 43:
	      /* KLEIN: M_c_1 */
              parameter_Name(Label, "-M9");
              break;
    case 44:
	      /* KLEIN: M_c_2 */
              parameter_Name(Label, "-M10");
              break;
    case 45:
	      /* Error Parameter */
              parameter_Name(Label, "-X4");
              break;
    case 46:
        /* Total mosquitoes per human  */
              parameter_Name(Label, "-M9");
              break;
    case 47:
	      /* Modifier on loss of immunity  */
              parameter_Name(Label, "-Z0");
              break;
    case 48:
	      /* Modifier on recovery from infection  */
              parameter_Name(Label, "-Z1");
              break;
    case 49:
	      /* Modifier on human susceptibility  */
              parameter_Name(Label, "-Z2");
              break;
    case 50:
        /* Modifier on human infectiousness  */
              parameter_Name(Label, "-Z3");
              break;
    case 51:
        /* Temperature  */
              parameter_Name(Label, "-T0");
              break;
    case 52:
	      /*  Initial Fraction of Susceptible (S1) - SnInR classes model */
              parameter_Name(Label, "-X7");
              break;
    case 53:
	      /*  Initial Fraction of Infectious (I1)  */
              parameter_Name(Label, "X8");
              break;
    case 54:
	      /*  Initial Fraction of Susceptible (S2)  */
              parameter_Name(Label, "-X9");
              break;
    case 55:
	      /*  Initial Fraction of Infectious (I2)  */
              parameter_Name(Label, "X10");
              break;
    case 56:
	      /*  Initial Fraction of Susceptible (S3)  */
              parameter_Name(Label, "-X11");
              break;
    case 57:
	      /*  Initial Fraction of Infectious (I3)  */
              parameter_Name(Label, "X12");
              break;

    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Input_Parameters(stdout, P);
      exit(0);
    }
}
