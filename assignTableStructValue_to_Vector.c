#include <MODEL.h>

double AssignStructValue_to_VectorEntry(int j, Parameter_Table * P)
{
  double value;

  switch(j)
    {

    case 0:   /* Human Population */
              value = P->H;

              break;
    case 1:   /* H_Delta */
              value = P->H_Delta;

              break;
    case 2:
	      value = P->H_Birth  ;

	      break;
    case 3:
              value = P->H_Sigma_0  ;

	      break;
    case 4:
	      value = P->H_Recov_0  ;

	      break;
    case 5:
	      value = (double)P->n_H;

	      break;
    case 6:
	      value = P->H_Gamma    ;

	      break;
    case 7:
              value = P->Imm      ;

	      break;
    case 8:
	      value = P->H_Xhi      ;

              break;
    case 9:
	      value = P->H_Rho      ;

	      break;
    case 10:
	      value = P->H_Eta     ;

	      break;
    case 11:
	      value = P->H_Nu      ;

	      break;
    case 12:
      // #if defined TIME_DEPENDENCE  // see time_Oscillation_Parameter_Forcing.c!!!
      //      value = P->M_a_Mean_Value;
      // #else
	     value = P->M_a;
      // #endif
	      break;
    case 13:
	      value = P->M_b     ;

              break;
    case 14:
	      value = P->M_c     ;

              break;
    case 15:
	      value = P->M_Delta  ;

              break;
    case 16:
	      value = P->M_Delta_R  ;

	      break;
    case 17:
	      value = P->M_Delta_PE  ;

	      break;
    case 18:
	      value = P->M_Fecundity  ;

	      break;
    case 19:
	      value = P->M_NoEggs  ;

	      break;
    case 20:
	      value = P->L_Devel  ;

	      break;
    case 21:
	      value = P->L_Delta_0  ;

	      break;
    case 22:
	      value = P->L_Delta_P  ;

	      break;
    case 23:
	      value = P->L_Delta_R  ;

	      break;
    case 24:
	      value = P->L_Delta_PE ;

	      break;
    case 25:
      // #if defined TIME_DEPENDENCE  // see time_Oscillation_Parameter_Forcing.c!!!
      //       value = P->K_Mean_Value;
      // #else
	     value = P->K_0;
      // #endif
	      break;
    case 26:
	      value = P->K_Sigma  ;

              break;
    case 27:
	      value = P->K_A  ;

	      break;
    case 28:
	      value = P->K_p ;

	      break;
    case 29:
	      value = P->K_E ;

	      break;
    case 30:
	      value = (double)P->n_V;

	      break;
    case 31:
	      value = P->M_Gamma  ;

              break;

    case 32:
	      /*  Shift in temperature for adult mosquitoes  */
              value = P->R_T.TEMP__SHIFT;
              break;
    case 33:
	      /*  Shift in temperature due to elevation  */
              value = P->R_T.T_ELEVATION;
              break;
    case 34:
              /*  External Influx of Adult Mosquitoes into the system */
              value = P->M_Imm;
              break;
    case 35:
              /*  Initial fraction of susceptible humans  */
              value = P->s__0;
              break;
    case 36:
              /*  Initial fraction of exposed */
              value = P->e__0;
              break;
    case 37:
              /*  Initial fraction of infected */
              value = P->i__0;
              break;
    case 38:
              /*  Initial fraction of cases */
              value = P->c__0;
              break;
    case 39:
              /*  Maturation rate of water into water available */
              value = P->K_Maturation;
              break;
    case 40:
              /*  Maturation rate of water into water available */
              value = P->Error_Parameter_0;
              break;
    case 41:
              /*  Maturation rate of water into water available */
              value = P->Error_Parameter_1;
              break;
    case 42:
              /*  Fraction of time mosquitoes spend at lower ourdoor
		  temperature */
              value = P->R_T.x;
              break;
    case 43:

              value = P->M_c_1;
              break;
    case 44:

              value = P->M_c_2;
              break;
    case 45:

              value =  P->e__2;
              break;
    case 46:

              value =  P->m;
              break;
    case 47:
        /* Modifier on loss of immunity  */
              value = P->H_mSigma;
              break;
    case 48:
        /* Modifier on recovery from infection  */
              value = P->H_mRecov;
              break;
    case 49:
	      /* Modifier on human susceptibility  */
              value =  P->H_mBeta;
              break;
    case 50:
        /* Modifier on human infectiousness  */
              value =  P->H_mM_c;
              break;
    case 51:
        /* Temperature  */
              value =  P->Temp;
              break;
    case 52:
        /* Initial fraction of S1 (SnInR models) */
              value =  P->s1__0;
              break;
    case 53:
        /* Initial fraction of I1 (SnInR models) */
              value =  P->i1__0;
              break;
    case 54:
        /* Initial fraction of S2 (SnInR models) */
              value =  P->s2__0;
              break;
    case 55:
        /* Initial fraction of I2 (SnInR models) */
              value =  P->i2__0;
              break;
    case 56:
        /* Initial fraction of S3 (SnInR models) */
              value =  P->s3__0;
              break;
    case 57:
        /* Initial fraction of I3 (SnInR models) */
              value =  P->i3__0;
              break;
    default:
      printf(".... INVALID PARAMETER KEY (key = %d)\n", j);

#ifndef PRE_GENETIC_ALGORITHM_CODE
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Input_Parameters(stdout, P);
#else
      printf(" The maximum number of parameters is Number_PAR_MAX\n");
      printf(" The permited number of keys go from 0, to %d\n", Number_PAR_MAX-1);
#endif
      exit(0);
    }

  return(value);

}
