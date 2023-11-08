#include <MODEL.h>

/* -n 20 -v0 2 -v1 3 -v2 4 -v3 8 -v4 9 -v5 12 -v6 15 -v7 16 -v8 17 -v9 20 -v10 21 -v11 22 -v12 23 -v13 24 -v14 26 -v15 27 */

#define WILD_vs_RESISTANT
#define FECUNDITY_CORRECTION

// #if defined APPLYING_TREND
// #include <include.Trend_Control.extern.h>
// #endif

extern gsl_rng * r;

double definition_Scan_Function( Parameter_Table * P )
{
  double x;
  double * y;

  /* Important note: only some out variables can be used here:
     18 ---> V_0 Vectorial capacity
     19 ---> R_0_Next_Generation_Matrix
     20 ---> R_0_Next_Generation_Matrix * R_0_Next_Generation_Matrix
   */
  int j = P->IO_VARIABLE_LIST[0];

#if defined MacDonaldRoss
  assert( j == 19 );
#else
  assert( j == 18 || j == 19 || j == 20 );
#endif

  x = definition_OutPut_Variables( j, y, 0.0, P );

  return (x);
}

double definition_OutPut_Variables(int j, double * y, const double t, Parameter_Table * P)
{
  int i;
  double x = 0.0;
  double H, m, M;
  int S, E_1, E_2, E, I, R, C, S1, I1, S2, I2, S3, I3, A;
  int L, X, U, W, K_W, K;
  double AA, BB;

  M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P,
                                            &S, &E, &I, &R, &C, &S1, &I1, &S2, &I2, &S3, &I3,
                                            &L, &X, &U, &W, &A,
                                            &K );

  switch(j)
    {
    case 1:
      /* Total mosquito population, which varies in time */
      x =  Total_Mosquito_Dynamic_State(P, y);
      //x =  Total_Mosquito_Steady_State(P);
      break;
    case 2:
      /* True cases y[C] vs accumulated cases y[A] */
#if defined CASES_33
      x  = y[A];
#endif
#if defined CASES_1
      x  = y[C];
#endif
      break;
    case 3:
      /* Fraction of infectious humans  */
      /* If K_L_E_I_N is defined x will be
       * the fraction of humans in the
       * 2nd immunity class (I_2 [I] + S_2 [R])
       */
      H  = total_Humans(y, P);
#if defined K_L_E_I_N
      x  = ( y[I] + y[R] )/H;
#endif
#if defined CASES_33
      x  = ( y[I] + y[C] )/H;
#endif
#if defined CASES_1
      x  = ( y[I] + y[C] )/H;
#endif
#if defined NO_CASES
      x  = ( y[I] )/H;
#endif
#if defined SEnI
      x  = ( y[I] )/H;
#endif
#if defined SI
      x  = ( y[I] )/H;
#endif
#if defined MacDonaldRoss
      x  = y[I];
#endif
#if defined SnInR
      x = (y[I1] + P->H_mM_c*y[I2] + pow(P->H_mM_c,2)*y[I2])/H;
#endif
      if (x > 1.0 || x < 0){
	printf(" Error in definition_OutPut_Variables.c.\n");
	printf(" The fraction,  x = %g , is not a\n", x);
	printf(" Infectious Humans y[I] = %g\n", y[I]);
	printf(" well-defined fraction. The program\n");
	printf(" E X I T   ! ! !\n"); exit(0);
      }

      break;
    case 4:
      /* Total number of mosquitoes per human */
      H  = total_Humans(y, P);
      x  = Total_Mosquito_Dynamic_State(P, y) / H;

#if defined XW
      x  = P->m;
#endif
#if defined XVnW
      x  = P->m;
#endif
#if defined MacDonaldRoss
      x  = P->m;
#endif
      break;
    case 5:
      /* Total number of infectious mosquitoes per human */
#if defined MacDonaldRoss
      x  = y[W];
#else
      H  = total_Humans(y, P);
      x = y[W] / H;
#endif
      break;
    case 6:
      /* Force of infection, Beta  (for SnInR -- on effective susceptible population)*/
#if defined MacDonaldRoss
      x  = P->M_b*P->M_a *y[W];
#else
      x = P->H_Beta;
#endif
      break;
    case 7:
      /* Immigration driven force of infection *//*  Imm      */
      x = P->Imm;
      break;
    case 8: /* Local transmission driven force of infection */
#if defined MacDonaldRoss
      x  = P->M_b*P->M_a *y[W];
#else
      H  = total_Humans(y, P);
      x  = P->M_b * P->M_a * y[W] / H;
#endif
      break;
    case 9:
      /* Fraction of force of infection due to intrinsic internal
	 transmission within the local population */
#if defined MacDonaldRoss
      x  = P->M_b*P->M_a *y[W];
#else
      H  = total_Humans(y, P);
      x  = P->M_b * P->M_a * y[W] / H;
#endif
      x = x / (x + P->Imm);
      break;
    case 10:
      /* Fraction of force of infection due to external
	 transmission due to immigration-movement processes */
#if defined MacDonaldRoss
      x  = P->M_b*P->M_a *y[W];
#else
      x = P->H_Beta;
#endif
      x = P->Imm / x;
      break;
    case 11:
      /* Intrinsic vs Extrinsic force of infection ratio */
#if defined MacDonaldRoss
      x  = P->M_b*P->M_a *y[W];
#else
      x = P->H_Beta;
#endif
      x = (x - P->Imm )/P->Imm;
      break;
    case 12:
      /* Fraction of infectious mosquitoes in the mosquito population [ W/M ] */
#if defined MacDonaldRoss
      x = y[W] / P->m;
#endif
#if defined LXVnW
      M =  Total_Mosquito_Dynamic_State(P, y);
      x = y[W]/ M;
#endif
#if defined XkVnW
      M =  Total_Mosquito_Dynamic_State(P, y);
      x = y[W] / M;
#endif
#if defined XVnW
      M =  P->m * P->H;
      x = y[W] / M;
#endif
#if defined XW
      M =  P->m * P->H;
      x = y[W] / M;
#endif
      break;
    case 13:
      /* output_Var_Name(Label, " T E M P E R A T U R E ");    */
      /* corrected for elevation                               */
#if defined RAIN_TEMPERATURA_DATA
      x = temperature_Day(P, t) + P->R_T.T_ELEVATION;
#endif
      break;
    case 14:
      /* output_Var_Name(Label, " R A I N F A L L ");          */
#if defined RAIN_TEMPERATURA_DATA
      x = rain_Day(P, t);
#endif
      break;
    case 15:
      /* Forcing: Carrying capacity */
#if defined CASES_33
      x = y[K];
#else
      x = P->K_0;
#endif
      break;
    case 16:
      /* Fraction of susceptible humans */
      H  = total_Humans(y, P);
#ifndef ODE_RESTRICTED_JACOBIAN
  #if defined SnInR
        x  = (H - y[I1] - y[I2] - y[I3] - y[R])/H;
  #endif
      x  = y[S]/H;
#else
     double y_E = total_Exposed( y, P );
#if defined SI
      x  = H - y[I];
#endif
#if defined SEnI
      x  = H - y_E - y[I];
#endif
#if defined NO_CASES
      x  = H - y_E - y[I] - y[R];
#endif
#if defined CASES_1
      x  = H - y_E - y[I] - y[R] -y[C];
#endif

#endif
#if defined MacDonaldRoss
      x = 1.0 - y[I];
#endif
      break;
    case 17:
      /* Dynamical Vectorial Capacity */
      H  = total_Humans(y, P);
      M  = Total_Mosquito_Dynamic_State(P, y);
      m  = M/H;
      x  = m * P->M_a * P->M_a * exp( - P->M_Delta / P->M_Gamma ) / P->M_Delta;
      break;
    case 18:
      /* Vectorial Capacity (from the next generation calculation
	 giving rise to a value for R_0, see R_0.c) */
      H  = P->H;                    /* H = total_Humans(y, P); */
#if defined FECUNDITY_CORRECTION
      P->M_Fecundity = Fecundity_Correction ( P );
#endif
      M  = Total_Mosquito_Steady_State( P );
      m  = M/H;
      x  = Vectorial_Capacity_Next_Gen_Matrix ( m, P );
      break;
    case 19:
#if defined MacDonaldRoss
      x  = R_0_MacDonaldRoss (P);
#else
      /* R_0 assuming stationarity at those environmental conditions */
      x = R_0_Next_Gen_Matrix(P);
      // x = R_0 ( P );  /* R_0 evaluation without treatment */
#endif
      break;
    case 20:
      /* R_0 assuming stationarity at those environmental conditions (R_0^2) */
      x = R_0_Next_Gen_Matrix_2(P);
      break;
    case 21:
      /* Annual number of infective bites per human (EIR) */
#if defined MacDonaldRoss
      x = P->M_a * y[W] * P->K_Period;
#else
      x = P->M_a * y[W]/P->H * P->K_Period;  /* K_Period of one year in the same time units
      						as the rate M_a */
#endif
      break;
    case 22:
      /* First infection average time of a totally naive individual (months): */
#if defined MacDonaldRoss
      x = P->M_b * P->M_a * y[W] + P->Imm;
#else
      x = P->M_b * P->M_a * y[W] / P->H + P->Imm;
#endif
      x = 1./ x /30.0/12.0;
      break;
    case 23:
#if defined MacDonaldRoss
      x = P->M_a * y[W];
#else
      x = P->M_a * y[W]/P->H;
#endif
      x = x / ( exp(x/P->H_Recov_0) - 1. );
      /* Average duration of the exposure-enhanced infectious period (months) */
      x = 1./ x /30.0;
      break;
    case 24:
#if defined MacDonaldRoss
      x = P->M_a * y[W];
#else
      x = P->M_a * y[W]/P->H;
#endif
      x = x / ( exp(x/P->H_Sigma_0) - 1. );
      /* Average duration of the exposure-enhanced immune period (months) */
      x = 1./ x /30.0;
      break;
    case 25:
      /* Malaria incidence, measured ad average number of clinical cases per
	 100,000 humans */
      x = y[C]/P->H * 100000;

      break;
    case 26:
      /* Accumulated cases */
      x =  y[A];
#if defined ERROR_FUNCTION
      /* Sampling a value with empirical measurement error */
      x = M_E_A_S_U_R_E_M_E_N_T___E_R_R_O_R___F_U_N_C_T_I_O_N (r,  P, x);
#endif
      break;
    case 27:
      /* Expected number of cases according to our error distribution */
      //x =  Expected_Value_Probability_Error(y[A]);
      x =  1.8909 * y[A];
      break;
#if defined EVOLUTION_of_RESISTANCE
    case 28: /* Type of Strain Favored by Natural Selection */

      x = (double)Strain_Type_With_Evolutionary_Advantage(P, y);

      //printf("Evolution of Resistance Type: %g\n", x);
      //assert( (int)x == 3 );
      break;
    case 29: /* Threshold value for the evolution of the resistance
		strain */
      //x = Evolution_of_Resistance_Threshold(P, P->Evolution_of_Resistance_Parameter, &AA, &BB);

      x = R_r (P, y) - R_w (P, y);
      break;
#endif
   case 30:
#if defined APPLYING_TREND
     x = AssignStructValue_to_VectorEntry(P->Tr->Tr_Input_Parameter, P);
#else
     Print_Press_Key(1, 1, "Error at definition_OutPut_Variables.c (Key = 30)");
#endif
     break;
   case 31: /* Tracking Percentual Treatment Effectiveness */
      x = P->H_Rho / (P->H_Rho + P->H_Nu) ;
      break;
   case 32: /* Tracking Human Population */
      x = H  = total_Humans(y, P);
      x = H + P->Human_Growing_Population;
      break;
#if defined TIME_DEPENDENCE
   case 33: /* Tracking Human Population */
     x = K_p_Precipitation(t, P);        /* Rainfall intensity in mm per day */
     x *= 30.0;                          /* Accumulated Rainfall in a 30-day month */
     break;
#endif
   default:
      printf(" INVALID VARIABLE CODE in ./${PROJECTK_DIR}/definition_OutPut_Variables.c (variable = %d)\n"
	     , j);
      printf(" Program will exit!  "); printf("Press any key..."); getchar();
      exit(0);
    }

  return (x);
}

void fprintf___variable(int j, FILE *fp)
{
  /*
     See assignLabel_to_Output_Variable.c
     for a shorter definition of this output variables
  */

  switch(j)
    {
    case INTEGER_CODE_FOR_TIME_DIMENSION:
      fprintf(fp, " Time (years)\n");

      break;
    case 1:
      fprintf(fp, " Total Mosquito Population [ M = Total_Mosquito_Dynamic_State(P, y) ]\n");

      break;
    case 2:
      fprintf(fp, " Accumulated malaria clinical cases per period (usually, one month)\n");

      break;
    case 3:
      fprintf(fp, " Fraction of infectious humans: [ (I+C)/H ] \n");

      break;
    case 4:
      fprintf(fp, " Total number of mosquitoes per human\n");

      break;
    case 5:
      fprintf(fp, " Total number of infectious mosquitoes per human\n");

      break;
    case 6:
      fprintf(fp, " Force of infection, Beta\n");

      break;
    case 7:
      fprintf(fp, " Immigration driven force of infection\n");

      break;
    case 8:
      fprintf(fp, " Local Force of infection\n");

      break;
    case 9:
      //fprintf(fp, " Fraction of force of infection due to intrinsic
      //internal transmission within the local population\n");
      fprintf(fp, " Fraction of force of infection due to intrinsic transmission within the local population\n");

      break;
    case 10:
      fprintf(fp, " Fraction of force of infection due to external transmission due to immigration-movement processes\n");

      break;
    case 11:
      fprintf(fp, " Intrinsic vs Extrinsic force of infection ratio\n");

      break;
    case 12:
      fprintf(fp, " Fraction of infecting mosquitoes [ W/M ]\n");

      break;
    case 13:
      fprintf(fp, " [ T ]   T E M P E R A T U R E \n");

      ;
      break;
    case 14:
      fprintf(fp, " [ R ]   R A I N F A L L \n");

      ;
      break;
    case 15:
      fprintf(fp, " [ K ]   C a r r y i n g    C a p a c i t y\n");

      break;
    case 16:
      fprintf(fp, " [ s ]   Fraction of susceptible humans [ S / H ]\n");

      break;
    case 17:
      fprintf(fp, " [ V ]   Vectorial Capacity (Klein etal 2008)\n");

      break;
    case 18:
      fprintf(fp, " [ V ]   Vectorial Capacity (based on a Next Generation result)\n");

      break;
    case 19:
      fprintf(fp, " [ R_0 ] R_0, Next generation matrix method )\n");

      break;
    case 20:
      fprintf(fp, " [ R_0 * R_0 ] R_0, Next generation matrix method (squared)\n");

      break;
    case 21:
      fprintf(fp, " [ E I R ] : Annual average number of infectve bites per human:\n");

      break;
    case 22:
      fprintf(fp, " [ A__0 ] : First infection average age of a totally naive individual (years)\n");

      break;
    case 23:
      fprintf(fp, " [ T__Infectious ] x: Average duration of the ""exposure-enhanced"" infectious period (in months)\n");

      break;
    case 24:
      fprintf(fp, " [ T__Immunity ] : Average duration of the ""exposure-enhanced"" immunity period (in months)\n");

      break;
    case 25:
      fprintf(fp, " [ C_100000 ] : Malaria incidence (clinical cases per 100,000 h.)\n");

      break;
    case 26:
      fprintf(fp, " Accumulated malaria clinical cases per time interval (usually, one month)\n");
      fprintf(fp, " with measurement error\n");

      break;
    case 27:
      fprintf(fp, " Accumulated malaria clinical cases per time interval\n");
      fprintf(fp, " Expected value, according to the error distribution\n");

      break;
#if defined EVOLUTION_of_RESISTANCE
    case 28:
      fprintf(fp, " Evolution of Resistance\n");
      fprintf(fp, " Type of Strain Favored by Natural Selection (see evolution_of_resistance.c)\n");

      break;

    case 29: /* Threshold value for the evolution of the resistance strain */
      fprintf(fp, " Threshold value determining whether one of the two strains (the wild type vs the resistant strain)\n");
      fprintf(fp, " would be favored by natural selection until outcompeting the other one\n");
      fprintf(fp, " provided the same conditions were maintained constant for a long period of time)\n");

      break;
#endif
    case 30: /* Tracking Treatment Clearance Rate [ H_Rho ]*/
      fprintf(fp, " H_Rho: Treatment Clearance Rate\n");
      break;
    case 31: /* Tracking Treatment Efficiency */
      fprintf(fp, " Treatment Efficiency: e = H_Rho / (H_Rho + H_Nu)\n");
      break;
    case 32: /* Human Population */
      fprintf(fp, " Human Population\n");
      break;
    case 33: /* Human Population */
      fprintf(fp, " Precipitation (rain per day)\n");
      break;
    default:
      printf(" INVALID VARIABLE CODE in ./GA_Stable_v1.0/TimeSeries_1st_GENE_T_SHIFT/no_of_variable_to_save.c (variable = %d)\n"
	     , j);
      printf(" Program will exit!\n"); printf("Press any key..."); getchar();
      exit(0);
    }
}
