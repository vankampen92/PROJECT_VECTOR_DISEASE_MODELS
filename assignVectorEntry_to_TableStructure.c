#include <MODEL.h>

void AssignVectorEntry_to_Structure(Parameter_Table * P, int j, double value)
{

  switch(j)
    {

    case 0:   /* H */
              P->H = value;
              break;
    case 1:   /* H_Delta */
              P->H_Delta = value;

              break;
    case 2:
	      P->H_Birth  = value;

	      break;
    case 3:
              P->H_Sigma_0  = value;

	      break;
    case 4:
	      P->H_Recov_0  = value;

	      break;
    case 5:
              P->n_H      = (int)value; //(int)value + 1;

	      break;
    case 6:
	      P->H_Gamma    = value;

	      break;
    case 7:
	      P->Imm      = value;

	      break;
    case 8:
	      P->H_Xhi      = value;

              break;
    case 9:
	      P->H_Rho      = value;

	      break;
    case 10:
	      P->H_Eta     = value;

	      break;
    case 11:
	      P->H_Nu      = value;

	      break;
    case 12:
	     P->M_a     = value;
	     
	      break;
    case 13:
	      P->M_b     = value;

              break;
    case 14:
	      P->M_c     = value;

              break;
    case 15:
	      P->M_Delta  = value;

              break;
    case 16:
	      P->M_Delta_R  = value;

	      break;
    case 17:
	      P->M_Delta_PE = value;

	      break;
    case 18:
	      P->M_Fecundity  = value;

	      break;
    case 19:
	      P->M_NoEggs  = value;

	      break;
    case 20:
	      P->L_Devel  = value;

	      break;
    case 21:
	      P->L_Delta_0  = value;

	      break;
    case 22:
	      P->L_Delta_P  = value;

	      break;
    case 23:
	      P->L_Delta_R  = value;

	      break;
    case 24:
	      P->L_Delta_PE   = value;

	      break;
    case 25:
              P->K_0   = value;
	      
	      break;
    case 26:
	      P->K_Sigma  = value;

              break;
    case 27:
	      P->K_A  = value;

	      break;
    case 28:
	      P->K_p = value;

	      break;
    case 29:
	      P->K_E = value;

	      break;
    case 30:
              P->n_V = (int)value; // (int)value + 1;

	      break;
    case 31:
	      P->M_Gamma  = value;

              break;

    case 32:
	      /*  Shift in temperature for adult mosquitoes */
              P->R_T.TEMP__SHIFT = value;
              break;
    case 33:
	      /*  Shift in temperature due to altitude  */
              P->R_T.T_ELEVATION = value;
              break;
    case 34:
              /*  External Influx of Adult Mosquitoes into the system */
              P->M_Imm = value;
              break;
    case 35:
              /*  External Influx of Adult Mosquitoes into the system */
              P->s__0 = value;
              break;
    case 36:
              /*  External Influx of Adult Mosquitoes into the system */
              P->e__0 = value;
              break;
    case 37:
              /*  External Influx of Adult Mosquitoes into the system */
              P->i__0 = value;
              break;
    case 38:
              /*  External Influx of Adult Mosquitoes into the system */
              P->c__0 = value;
              break;
    case 39:
              /*  Maturation rate of water into available water */
              P->K_Maturation = value;
              break;
    case 40:
              /*   */
              P->Error_Parameter_0 = value;
              break;
    case 41:
              /*   */
              P->Error_Parameter_1 = value;
              break;
    case 42:
              /*   */
              P->R_T.x = value;
              break;
    case 43:

              P->M_c_1 = value;
              break;
    case 44:

              P->M_c_2 = value;
              break;
    case 45:

              P->e__2 = value;
              break;
    case 46:

              P->m = value;
              break;
    case 47:
        /* Modifier on loss of immunity  */
              P->H_mSigma = value;
              break;
    case 48:
        /* Modifier on recovery from infection  */
              P->H_mRecov = value;
              break;
    case 49:
        /* Modifier on human susceptibility  */
              P->H_mBeta = value;
              break;
    case 50:
        /* Modifier on human infectiousness  */
              P->H_mM_c = value;
              break;
    case 51:
        /* Temperature  */
              P->Temp= value;
              values_TempDependency(P->Temp, P);
              break;
    case 52:
        /* Initial fraction of S1 (SnInR)  */
              P->s1__0= value;
              break;
    case 53:
        /* Initial fraction of I1 (SnInR)  */
              P->i1__0= value;
              break;
    case 54:
        /* Initial fraction of S2 (SnInR)  */
              P->s2__0= value;
              break;
    case 55:
        /* Initial fraction of I2 (SnInR)  */
              P->i2__0= value;
              break;
    case 56:
        /* Initial fraction of S3 (SnInR)  */
              P->s3__0= value;
              break;
    case 57:
        /* Initial fraction of I3 (SnInR)  */
              P->i3__0= value;
              break;
    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      int No_of_PARAMETERS = MODEL_PARAMETERS_MAXIMUM;
      printf(" The maximum number of parameters is %d\n", No_of_PARAMETERS);
      printf(" The permited number of keys go from 0, to %d\n", No_of_PARAMETERS-1);
      exit(0);
    }
}
