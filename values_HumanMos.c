#include "./Include/MODEL.h"

#if defined CPGPLOT_REPRESENTATION
#include <include.CPG.extern.h>
#endif

#include "./Include/include.Parameter_Model.extern.h"

/*
   The purpose of this simple function is just to upload
   ALL input parameters, controling both model definition
   and running simulations, and defined as global variables,
   into the corresponding Parameter_Table Structure
*/

void values_HumanMos(Parameter_Table * P)
{
  /* param label *//* Human parameters */
                P->POPULATION = POPULATION;
  /* n =  0  */ P->H         = (double)POPULATION;
  /* n =  1  */ P->H_Delta   = H_Delta;
  /* n =  2  */ P->H_Birth   = H_Birth;
  /* n =  3  */ P->H_Sigma_0 = H_Sigma_0;     P->H_Sigma   = H_Sigma_0;
  /* n =  4  */ P->H_Recov_0 = H_Recov_0;     P->H_Recov   = H_Recov_0;
  /* n =  5  */ P->n_H       = n_H;           /* Human Latent class: those incubating malaria */
  /* n =  6  */ P->H_Gamma   = H_Gamma ;      /* 1/H_Gamma is the average latent time         */
  /* n =  7  */ P->Imm       = Imm;

#if defined HUMAN_CONSTANT_POPULATION
		P->H_Birth   = P->H_Delta;
#endif

  P->Human_Growing_Population = Human_Growing_Population;

  P->H_Beta                  = H_Beta;        /* Force of infection */

  /* Human parameters to deal with clinical malaria */
  /* n =  8  */ P->H_Xhi = H_Xhi;
  /* n =  9  */ P->H_Rho = H_Rho;
  /* n = 10  */ P->H_Eta = H_Eta;
  /* n = 11  */ P->H_Nu  = H_Nu;

  /* Human parameter for malaria with multiple classes (SnInR) */
  /* n = 47  */ P->H_mSigma = H_mSigma;
  /* n = 48  */ P->H_mRecov = H_mRecov;
  /* n = 49  */ P->H_mBeta = H_mBeta;
  /* n = 50  */ P->H_mM_c  = H_mM_c;

  /* Temperature parameter to set temp. dependent Mosquito Parameters */
  /* n = 51  */ P->Temp = Temp; P->Temp_Mean_Value = Temp;

  /* Mosquito (adult) parameters */
  /* n = 12  */ P->M_a = M_a;  P->M_a_Mean_Value = M_a;
  /* n = 13  */ P->M_b = M_b;
  /* n = 14  */ P->M_c = M_c;

  /* n = 48 */ P->M_c_1 = M_c_1;
  /* n = 49 */ P->M_c_2 = M_c_2;

  /* n = 15  */ P->M_Delta = M_Delta;
  /* n = 16  */ P->M_Delta_R = M_Delta_R;
  /* n = 17  */ P->M_Delta_PE = M_Delta_PE;
  /* n = 18  */ P->M_Fecundity = M_Fecundity;
  /* n = 19  */ P->M_NoEggs = M_NoEggs;

		P->W_Sigma = Threshold_Intensity(P, P->H_Sigma_0);
		P->W_Recov = Threshold_Intensity(P, P->H_Recov_0);

                P->m       = m;      /* No of Mosquitoes per human */
  /* Mosquito (larva) parameters */
  /* n = 20  */ P->L_Devel    = L_Devel;
  /* n = 21  */ P->L_Delta_0  = L_Delta_0;
  /* n = 22  */ P->L_Delta_P  = L_Delta_P;
  /* n = 23  */ P->L_Delta_R  = L_Delta_R;
  /* n = 24  */ P->L_Delta_PE = L_Delta_PE;
		P->L_Delta    = L_Delta_P + L_Delta_0;

  /* Seasonal forcing // Rain-driven carrying capacity */
  /* n = 25  */ P->K_0       = K_0;            /* Larva carrying capacity on average */
  /* n = 26  */ P->K_Sigma   = K_Sigma;
  /* n = 27  */ P->K_A       = K_A;
                P->K_Period  = K_Period;
		P->K_Seasonal_Intensity = K_Seasonal_Intensity;

#if defined CASES_33
  P->K_Mean_Value         = K_p;
#endif
#if defined CASES_1
  P->K_Mean_Value         = K_0;
#endif
#if defined MacDonaldRoss
  P->K_Mean_Value         = K_0;
#endif

  //		P->K_Mean_Value         = K_Mean_Value;
  /* n = 28  */ P->K_p = K_p;
  /* n = 29  */ P->K_E = K_E;
  /* n = 44  */	P->K_Maturation = K_Maturation;

  /* Recorded history */
  //double *History_X;
  //double *History_Y;
  //double *History_Time;1

  /* Plasmodioum */
		P->Plasmodium_Sigma = Plasmodium_Sigma;
                P->Plasmodium_Devel = Plasmodium_Devel;
  /* n = 30  */ P->n_V = n_V;            /* Mosquito Latent class: those incubating malaria */
  /* n = 31  */ P->M_Gamma = M_Gamma;    /* 1/M_Gamma is the average time for Plasmodium to develop */


  /* Parameter mimicing a non-zero flux of adult mosquitoes from
     outside the system */
  /* n = 39  */ P->M_Imm = M_Imm;

#if defined ERROR_FUNCTION
  /* n = 45  */ P->Error_Parameter_0 = Error_Parameter_0;
  /* n = 46  */ P->Error_Parameter_1 = Error_Parameter_1;
#endif
		/* n = 37 */ /* R_T.TEMP_SHIFT  */
		/* n = 38 */ /* R_T.T_ELEVATION */
		/* n = 47 */ /* R_T.x */

#if defined EVOLUTION_of_RESISTANCE
		P->Evolution_of_Resistance_Parameter = Evolution_of_Resistance;
		P->Drug_Efficiency                   = Drug_Efficiency;
#endif
}

void Resetting_Parameter_Combination( Parameter_Table * Table,
                                      double HH_Delta, double HH_Sigma_0, double HH_Recov_0, int nn_H, double Beta_e,
                                      double HH_Rho, double HH_Nu,
                                      double LL_Devel, double LL_Delta, double KK_0,
                                      double MM_a, double MM_b, double MM_c, double MM_Delta,
                                      int nn_V, double MM_Gamma )
{
  /* -H2 */ Table->H_Delta   = HH_Delta;    //1.0/40.0/360
  /* -H3 */ Table->H_Sigma_0 = HH_Sigma_0;  //3.0E-3
  /* -H4 */ Table->H_Recov_0 = HH_Recov_0;  //9.0E-3;
  /* -H5 */ Table->n_H       = nn_H;        //5
  ///* -H6 */ Table->H_Gamma   = HH_Gamma;
  /* -H7 */ Table->Imm       = Beta_e;      //0.00001

  ///* -C0 */ Table->H_Xhi     = HH_Xhi;
  /* -C1 */ Table->H_Rho     = HH_Rho;    // 0.2
  ///* -C2 */ Table->H_Eta     = HH_Eta;    // 0.2;
  /* -C3 */ Table->H_Nu      = HH_Nu;     // 0.2;

  /* -L0 */ Table->L_Devel     = LL_Devel; // 6.7E-2  /* Temperature Driven */
  /* -L1 */ Table->L_Delta_0   = LL_Delta; // 0.5        /* Temperature Driven */
            Table->L_Delta     = LL_Delta; // 0.5
  /* -L2 */ Table->K_0         = KK_0;     // 4.0E4;

  /* -M0 */ Table->M_a       = MM_a;       //0.3       /* Temperature Driven */
  /* -M1 */ Table->M_b       = MM_b;       //0.8
  /* -M2 */ Table->M_c       = MM_c;       //0.2
  /* -M3 */ Table->M_Delta   = MM_Delta;   // 0.06;     /* Temperature driven */

  /* -P0 */ Table->n_V       = nn_V;       // 10
  /* -P1 */ Table->M_Gamma   = MM_Gamma;   // 0.05 /* Temperature driven */
}

void values_TempDependency(double Temp, Parameter_Table * P)
{
  /* DESCRIPTION : function that updates mosquito parameters based on Temperature
                   Temp. relationships are from Mordecai et al. 2013

    TO UPDATE : introduce TEMP___SHIFT parameter for indoor/outdoor temp difference */

  /* We should make sure that rates are always positive!!! */
  /* Mosquito (adult) parameters */
    P->M_a = (0.000203*(Temp)*(Temp-11.7)*pow(42.3-Temp, 0.5));
    P->M_a = MAX(P->M_a, 0.0);                   /* biting rate */

    P->M_Delta = (-log(-0.000828*pow(Temp,2.0)+0.0367*Temp+0.522));
    P->M_Delta = MAX(P->M_Delta, 0.0);         /* adult mortality */

    P->M_Fecundity = -0.153*pow(Temp,2.0)+8.61*Temp-97.7 ;
    P->M_Fecundity = MAX(M_Fecundity, 0.0); /* EFD = N_L*a, offspring per female per day */

    if( P->M_a > 0.0 ) { 
    P->M_NoEggs = P->M_Fecundity/P->M_a;
    P->M_NoEggs = MAX(P->M_NoEggs, 0.0);       /* # of eggs per oviposition event */
    }
    else P->M_NoEggs = 0.0;
    
  /* Mosquito (larva) parameters */
    P->L_Devel = 0.00011*Temp*(Temp-14.7)*pow(34-Temp, 0.5);
    P->L_Devel = MAX(P->L_Devel, 0.0);         /* Larval development rate */

    P->L_Delta = -log(-0.00925*pow(Temp,2.0)+0.453*Temp-4.77)*P->L_Devel;
    P->L_Delta = MAX(P->L_Delta, 0.0);         /* Larval mortality */

  /* Plasmodium parameters */
    P->M_Gamma = (0.000111*Temp*(Temp-14.7)*pow(34.4-Temp, 0.5));
    P->M_Gamma = MAX(P->M_Gamma, 0.0);         /* 1/M_Gamma is the average time for Plasmodium to develop */
}
