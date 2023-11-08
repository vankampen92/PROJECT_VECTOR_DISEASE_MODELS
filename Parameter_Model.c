#include "./Include/MODEL.h"

void  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N ( Parameter_Table * Table,
						        Parameter_Model * P )
{
  /* This function transfer a subset of table parameters
     into the Parameter_Model structure. Parameter_Model parameters
     control the dynamical model.
  */
  /* param label *//* Human parameters */
                P->POPULATION  = Table->POPULATION;
  /* n =  0  */ P->H           = Table->H;
  /* n =  1  */ P->H_Delta     = Table->H_Delta;
  /* n =  2  */ P->H_Birth     = Table->H_Birth;
  /* n =  3  */ P->H_Sigma_0   = Table->H_Sigma_0;     P->H_Sigma   = Table->H_Sigma_0;
  /* n =  4  */ P->H_Recov_0   = Table->H_Recov_0;     P->H_Recov   = Table->H_Recov_0;
  /* n =  5  */ P->n_H         = Table->n_H;           /* Human Latent class: those incubating malaria */
  /* n =  6  */ P->H_Gamma     = Table->H_Gamma ;      /* 1/H_Gamma is the average latent time         */
  /* n =  7  */ P->Imm         = Table->Imm;

  P->Human_Growing_Population = Table->Human_Growing_Population;
  P->H_Beta                   = Table->H_Beta;       /* Force of infection */

  /* Human parameter for clinical malaria (C) */
  /* Human parameters to deal with clinical malaria */
  /* n =  8  */ P->H_Xhi = Table->H_Xhi;
  /* n =  9  */ P->H_Rho = Table->H_Rho;
  /* n = 10  */ P->H_Eta = Table->H_Eta;
  /* n = 11  */ P->H_Nu  = Table->H_Nu;

	/* Human parameter for malaria with multiple classes (SnInR) */
	/* n = 47  */ P->H_mSigma = Table->H_mSigma;
	/* n = 48  */ P->H_mRecov = Table->H_mRecov;
	/* n = 49  */ P->H_mBeta = Table->H_mBeta;
	/* n = 50  */ P->H_mM_c  = Table->H_mM_c;

	/* Temperature Parameter for mosquito derived parameters */
  /* n = 51  */ P->Temp = Table->Temp;  P->Temp_Mean_Value = Table->Temp_Mean_Value; 

  /* Mosquito (adult) parameters */
  /* n = 12  */ P->M_a = Table->M_a;   P->M_a_Mean_Value = Table->M_a_Mean_Value;
  /* n = 13  */ P->M_b = Table->M_b;
  /* n = 14  */ P->M_c = Table->M_c;

  /* n = 48 */ P->M_c_1 = Table->M_c_1; /* these two are not called from command line */
  /* n = 49 */ P->M_c_2 = Table->M_c_2;

  /* n = 15  */ P->M_Delta     = Table->M_Delta;
  /* n = 16  */ P->M_Delta_R   = Table->M_Delta_R;
  /* n = 17  */ P->M_Delta_PE  = Table->M_Delta_PE;
  /* n = 18  */ P->M_Fecundity = Table->M_Fecundity;
  /* n = 19  */ P->M_NoEggs    = Table->M_NoEggs;

                P->W_Sigma = Table->W_Sigma;
		P->W_Recov = Table->W_Recov;

  /* Mosquito (larva) parameters */
  /* n = 20  */ P->L_Devel    = Table->L_Devel;
  /* n = 21  */ P->L_Delta_0  = Table->L_Delta_0;
  /* n = 22  */ P->L_Delta_P  = Table->L_Delta_P;
  /* n = 23  */ P->L_Delta_R  = Table->L_Delta_R;
  /* n = 24  */ P->L_Delta_PE = Table->L_Delta_PE;
		P->L_Delta    = Table->L_Delta_P + Table->L_Delta_0;

  /* Seasonal forcing // Rain-driven carrying capacity --
		 Slight misnomer: these parameters are used for forcing on Temp & M_a as well as K*/
  /* n = 25  */ P->K_0       = Table->K_0;            /* Larva carrying capacity on average   */
                P->m         = Table->m;              /* Number of Total Mosquitoes per Human */
  /* n = 26  */ P->K_Sigma   = Table->K_Sigma;        /* Variance (when random) */
  /* n = 27  */ P->K_A       = Table->K_A;
                P->K_Period  = Table->K_Period;
		P->K_Seasonal_Intensity = Table->K_Seasonal_Intensity; /* Scaled amplitude forcing parameter (not only for K)*/
		P->K_Mean_Value         = Table->K_Mean_Value; /* Mean value forcing parameter (not only for K) */
  /* n = 28  */ P->K_p          = Table->K_p;
  /* n = 29  */ P->K_E          = Table->K_E;
  /* n = 44  */	P->K_Maturation = Table->K_Maturation;

  /* Recorded history */
  //double *History_X;
  //double *History_Y;
  //double *History_Time;1

  /* Plasmodioum */
		P->Plasmodium_Sigma = Table->Plasmodium_Sigma;
                P->Plasmodium_Devel = Table->Plasmodium_Devel;
  /* n = 30  */ P->n_V     = Table->n_V;            /* Mosquito Latent class: those incubating malaria */
  /* n = 31  */ P->M_Gamma = Table->M_Gamma;    /* 1/M_Gamma is the average time for Plasmodium to develop */

  /* Parameter mimicing a non-zero flux of adult mosquitoes from
     outside the system */
  /* n = 39  */ P->M_Imm = Table->M_Imm;

#if defined ERROR_FUNCTION
  /* n = 45  */ P->Error_Parameter_0 = Table->Error_Parameter_0;
  /* n = 46  */ P->Error_Parameter_1 = Table->Error_Parameter_1;
#endif


   /* Initial Conditions */
   P->s__0 = Table->s__0;
   P->e__0 = Table->e__0;
   P->i__0 = Table->i__0;
   P->r__0 = Table->r__0;
   P->c__0 = Table->c__0;

   P->e__2 = Table->e__2;

   P->m__i = Table->m__i;

	 P->s1__0 = Table->s1__0;
	 P->i1__0 = Table->i1__0;
	 P->s2__0 = Table->s2__0;
	 P->i2__0 = Table->i2__0;
	 P->s3__0 = Table->s3__0;
	 P->i3__0 = Table->i3__0;

#if defined EVOLUTION_of_RESISTANCE
		P->Evolution_of_Resistance_Parameter = Table->Evolution_of_Resistance;
		P->Drug_Efficiency                   = Table->Drug_Efficiency;
#endif

  P->MODEL_OUTPUT_VARIABLES = Table->MODEL_OUTPUT_VARIABLES;   /* Actual no of MODEL (output) VARIABLES */
  P->MODEL_INPUT_PARAMETERS = Table->MODEL_INPUT_PARAMETERS;  /* Actual no of MODEL (input) PARAMETERS */
  P->MODEL_STATE_VARIABLES  = Table->MODEL_STATE_VARIABLES;  /* Actual no of MODEL (state) VARIABLES  */

  P->TYPE_of_MODEL        = Table->TYPE_of_MODEL;
  P->Growth_Function_Type = Table->Growth_Function_Type;

  //P->Time_Scale_Unit      = Table->T->Time_Scale_Unit;
}

void P_A_R_A_M_E_T_E_R___M_O_D_E_L___F_R_E_E( Parameter_Model * P)
{
  free ( P );
}
