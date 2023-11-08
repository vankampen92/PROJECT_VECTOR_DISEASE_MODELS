#include "./Include/MODEL.h"

void AssignLabel_to_Parameters__LATEX(int j, char * Label, Parameter_Table *P)
{


  switch(j)
    {

    case 0:   /* H */
              parameter_Name(Label, "  H: POPULATION");

              ;
	      break;
    case 1:   /* H_Delta */
              parameter_Name(Label, "  H: Turnover rate");

              ;
	      break;
    case 2:
	      parameter_Name(Label, "  H: Birth Rate");

	      ;
	      break;
    case 3:
      //parameter_Name(Label, "  H: Rate of ""loss of immunity"" ($R \\rightarrow S$)");
	      parameter_Name(Label, "  H: Rate of loss of immunity");

	      ;
	      break;
    case 4:
	      parameter_Name(Label, "  H: Recovery rate ($I \\rightarrow R$)");

	      ;
	      break;
    case 5:
	      parameter_Name(Label, "  H: ""Exposed"" number");

	      ;
	      break;
    case 6:
	      parameter_Name(Label, "  H: ""Exposed"" rate");

	      ;
	      break;
    case 7:
	      parameter_Name(Label, "  H: External force of infection");

	      ;
	      break;
    case 8:
      //parameter_Name(Label, "  H: Detection probability ($S \\rightarrow C$)");
              parameter_Name(Label, "  H: Detection probability");

              ;
	      break;
    case 9:
	      parameter_Name(Label, "  H: Recovery rate ($C \\rightarrow S$)");

	      ;
	      break;
    case 10:
      //parameter_Name(Label, "  H: Case probability ($I \\rightarrow C$)");
	      parameter_Name(Label, "  H: Case probability");

	      ;
	      break;
    case 11:
	      parameter_Name(Label, "  H: Recovery rate ($C \\rightarrow I$)");

	      ;
	      break;
    case 12:
              parameter_Name(Label, "  M: Biting rate");

	      ;
	      break;
    case 13:
	      parameter_Name(Label, "  M: Infectivity probability ($M \\rightarrow H$)");

              ;
	      break;
    case 14:
              parameter_Name(Label, "  M: Infectivity probability ($H \\rightarrow M$)");

              ;
	      break;
    case 15:
	      parameter_Name(Label, "  M: Death rate");

              ;
	      break;
    case 16:
	      parameter_Name(Label, "  M: Death factor due to rain peaks");

	      ;
	      break;
    case 17:
	      parameter_Name(Label, "  M: $\\delta""_""{PE}$");

	      ;
	      break;
    case 18:
	      parameter_Name(Label, "  M: Fecundity");

	      ;
	      break;
    case 19:
	      parameter_Name(Label, "  M: No of larval recruits per oviposition event");

	      ;
	      break;
    case 20:
	      parameter_Name(Label, "  L: Development rate");

	      ;
	      break;
    case 21:
	      parameter_Name(Label, "  L: Death rate");

	      ;
	      break;
    case 22:
	      parameter_Name(Label, "  L: Additional death rate");

	      ;
	      break;
    case 23:
	      parameter_Name(Label, "  L: Death factor due to rain peaks");

	      ;
	      break;
    case 24:
	      parameter_Name(Label, "  L: $\\delta""_""{PE}$");

	      ;
	      break;
    case 25:
	      parameter_Name(Label, "  L: Carraying capacity");

	      ;
	      break;
    case 26:
	      parameter_Name(Label, "  L: $var(K""_""0)$");

              ;
	      break;
    case 27:
	      parameter_Name(Label, "  R: Carrying capacity conversion factor");

	      ;
	      break;
    case 28:
	      parameter_Name(Label, "  R: $K""_""p$");

	      ;
	      break;
    case 29:
	      parameter_Name(Label, "  R: Carrying capacity loss rate");

	      ;
	      break;
    case 30:
	      parameter_Name(Label, "  P: ""Exposed"" number");

	      ;
	      break;
    case 31:
	      parameter_Name(Label, "  P: ""Exposed"" rate");

              ;
	      break;

    case 32:
	      /*  Tr.No_of_Jumps */
	      parameter_Name(Label, "No of Jumps");
              ;
	      break;
    case 33:
	      /*  Tr.value_0  */
              parameter_Name(Label, "Trend Value 0");
	      ;
	      break;
    case 34:
	      /*  Tr.value_1  */
              parameter_Name(Label, "Trend Value 1");
	      ;
	      break;
    case 35:
	      /*  Tr.time_0  */
              parameter_Name(Label, "Trend Time 0");
	      ;
	      break;
    case 36:
	      /*  Tr.time_1  */
              parameter_Name(Label, "Trend Time 1");
              ;
	      break;
    case 37:
	      /*  Shift in temperature for adult mosquitoes */
              parameter_Name(Label, "  T: Temperature shift:");
              ;
	      break;
    case 38:
	      /*  Shift in temperature due to altitude  */
              parameter_Name(Label, "  T: Temperature correction for elevation:");
              ;
	      break;
    case 39:
	      /*  Temperature shift to ajust for elevation  */
              parameter_Name(Label, "  M: External influx rate of adult mosquitoes");
              break;
    case 40:
	      /*  Initial Fraction of Susceptible  */
              parameter_Name(Label, "  H: Initial fraction of susceptible");
              break;
    case 41:
	      /*  Initial Fraction of Exposed  */
              parameter_Name(Label, "  H: Initial fraction of exposed");
              break;
    case 42:
	      /*  Initial Fraction of Infectious  */
              parameter_Name(Label, "  H: Initial fraction of infectious");
              break;
    case 43:
	      /*  Initial Fraction of cases  */
              parameter_Name(Label, "  H: Initial fraction of cases");
              break;
    case 44:
              /*  Water Maturation Rate  */
              parameter_Name(Label, "  W: Water maturation rate");
              break;
    case 45:
	      /* Error Parameter  */
              parameter_Name(Label, "  Error parameter (1)");
              break;
    case 46:
	      /* Error Parameter */
              parameter_Name(Label, "  Error parameter (2)");
              break;
    case 47:
	      /* Error Parameter */
              parameter_Name(Label, "  T: x parameter $[ T_e = T_o + (1-x) (T_i - T_o) ]$");
              break;
    case 48:
	      /* Error Parameter */
              parameter_Name(Label, "  M: Infectivity probability (H $\\rightarrow$ M)");
              break;
    case 49:
	      /* Error Parameter */
              parameter_Name(Label, "  M: Infectivity probability (H $\\rightarrow$ M)");
              break;
    case 50:
	      /* Error Parameter */
              parameter_Name(Label, "  H: Initial fraction of exposed");
              break;

   default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Input_Parameters(stdout, P);
      exit(0);
    }
}

void AssignLabel_to_Parameters__LATEX__SYMBOL(int j, char * Label, Parameter_Table *P)
{


  switch(j)
    {

    case 0:   /* H */
              parameter_Name(Label, "$H$");

              ;
	      break;
    case 1:   /* H_Delta */
              parameter_Name(Label, "$\\delta$");

              ;
	      break;
    case 2:
	      parameter_Name(Label, "$B$");

	      ;
	      break;
    case 3:
              parameter_Name(Label, "$\\sigma""_""0$");

	      ;
	      break;
    case 4:
	      parameter_Name(Label, "$r""_""0$");

	      ;
	      break;
    case 5:
	      parameter_Name(Label, "$n""_""H$");

	      ;
	      break;
    case 6:
	      parameter_Name(Label, "$\\gamma$");

	      ;
	      break;
    case 7:
	      parameter_Name(Label, "$\\beta_e$");

	      ;
	      break;
    case 8:
	      parameter_Name(Label, "$\\chi$");

              ;
	      break;
    case 9:
	      parameter_Name(Label, "$\\rho$");

	      ;
	      break;
    case 10:
	      parameter_Name(Label, "$\\eta$");

	      ;
	      break;
    case 11:
	      parameter_Name(Label, "$\\nu$");

	      ;
	      break;
    case 12:
              parameter_Name(Label, "$a$");

	      ;
	      break;
    case 13:
	      parameter_Name(Label, "$b$");

              ;
	      break;
    case 14:
              parameter_Name(Label, "$c$");

              ;
	      break;
    case 15:
	      parameter_Name(Label, "$\\delta$");

              ;
	      break;
    case 16:
	      parameter_Name(Label, "$\\delta""_""R$");

	      ;
	      break;
    case 17:
	      parameter_Name(Label, "$\\delta""_""{PE}$");

	      ;
	      break;
    case 18:
	      parameter_Name(Label, "$F$");

	      ;
	      break;
    case 19:
	      parameter_Name(Label, "$N$");

	      ;
	      break;
    case 20:
	      parameter_Name(Label, "$d$");

	      ;
	      break;
    case 21:
	      parameter_Name(Label, "$\\delta""_""0$");

	      ;
	      break;
    case 22:
	      parameter_Name(Label, "$\\delta""_""P$");

	      ;
	      break;
    case 23:
	      parameter_Name(Label, "$\\delta""_""R$");

	      ;
	      break;
    case 24:
	      parameter_Name(Label, "$\\delta""_""{PE}$");

	      ;
	      break;
    case 25:
	      parameter_Name(Label, "$K""_""0$");

	      ;
	      break;
    case 26:
	      parameter_Name(Label, "$var(K""_""0)$");

              ;
	      break;
    case 27:
	      parameter_Name(Label, "$K""_""A$");

	      ;
	      break;
    case 28:
	      parameter_Name(Label, "$K""_""p$");

	      ;
	      break;
    case 29:
              /*  Carrying capacity evaporation rate */
	      parameter_Name(Label, "$K""_""E$");

	      ;
	      break;
    case 30:
	      parameter_Name(Label, "$n""_""V$");

	      ;
	      break;
    case 31:
	      parameter_Name(Label, "$\\gamma$");

              ;
	      break;

    case 32:
	      /*  Tr.No_of_Jumps */
	      parameter_Name(Label, "No of Jumps");
              ;
	      break;
    case 33:
	      /*  Tr.value_0  */
              parameter_Name(Label, "Trend Value 0");
	      ;
	      break;
    case 34:
	      /*  Tr.value_1  */
              parameter_Name(Label, "Trend Value 1");
	      ;
	      break;
    case 35:
	      /*  Tr.time_0  */
              parameter_Name(Label, "Trend Time 0");
	      ;
	      break;
    case 36:
	      /*  Tr.time_1  */
              parameter_Name(Label, "Trend Time 1");
              ;
	      break;
    case 37:
	      /*  Shift in temperature for adult mosquitoes */
              parameter_Name(Label, "$T""_""S$");
              ;
	      break;
    case 38:
	      /*  Shift in temperature due to altitude  */
              parameter_Name(Label, "$T""_""E$");
              ;
	      break;
    case 39:
	      /*  Temperature shift to ajust for elevation  */
              parameter_Name(Label, "$M_i$");
              break;
    case 40:
	      /*  Initial Fraction of Susceptible  */
              parameter_Name(Label, "$y_S[0]$");
              break;
    case 41:
	      /*  Initial Fraction of Exposed  */
              parameter_Name(Label, "$y_{E_1}[0]$");
              break;
    case 42:
	      /*  Initial Fraction of Infectious  */
              parameter_Name(Label, "$y_I[0]$");
              break;
    case 43:
	      /*  Initial Fraction of cases  */
              parameter_Name(Label, "$y_C[0]$");
              break;
    case 44:
              /*  Carrying capacity maturation rate */
              parameter_Name(Label, "$K""_""M$");

              ;
              break;
    case 45:
	      /* Error Parameter  */
              parameter_Name(Label, "$E_0$");
              break;
    case 46:
	      /* Error Parameter */
              parameter_Name(Label, "$E_1$");
              break;
    case 47:
	      /* Error Parameter */
              parameter_Name(Label, "$x$");
              break;
    case 48:
	      /* Error Parameter */
              parameter_Name(Label, "$c_1$");
              break;
    case 49:
	      /* Error Parameter */
              parameter_Name(Label, "$c_2$");
              break;
    case 50:
	      /* Error Parameter */
              parameter_Name(Label, "$y_{E_2}[0]$");
              break;
    case 51:
	      /*  Modifier on loss of immunity */
              parameter_Name(Label, "$m_{\\sigma}$");
              break;
    case 52:
	      /* Modifier on recovery from infection */
              parameter_Name(Label, "$m_{\\gamma}$");
              break;
    case 53:
	      /* Modifier of human susceptibility */
              parameter_Name(Label, "$m_{\\beta}$");
              break;
    case 54:
	      /* Modifier of human infectiousness */
              parameter_Name(Label, "$m_{c}$");
              break;
    case 55:
	      /* Temperature (Temp) */
              parameter_Name(Label, "$T$");
              break;
    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Input_Parameters(stdout, P);
      exit(0);
    }
}
