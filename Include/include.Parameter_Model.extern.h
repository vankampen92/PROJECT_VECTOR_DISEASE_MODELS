/* Human parameters */
extern double m;   /* No of total mosquitoes per human */
extern int POPULATION;
extern double H;      /* Human Population */

extern double H_Beta;
extern double H_Birth;
extern double H_Delta;
extern double H_Sigma_0;
extern double H_Recov_0;
extern int n_H;            /* Human Latent class: those incubating malaria */
extern double H_Gamma;     /* 1/H_Gamma is the average latent time */
extern double Imm;         /* External Per capita Infection Rate */
extern double Human_Growing_Population;

/* Human parameters to deal with clinical malaria */
extern double H_Xhi;
extern double H_Rho;
extern double H_Eta;
extern double H_Nu;

/* Human parameters to deal with multiple classes of infection */
#include <include.extern.SnInR.h>

/* Temperature to calculate mosquito temp. dependent parameters */

extern double Temp;  extern double Temp_Mean_Value; 


/* Mosquito (adult) parameters */
extern double M_a; extern double M_a_Mean_Value;
extern double M_b;
extern double M_c;
extern double M_c_1;
extern double M_c_2;
extern double M_Delta;
extern double M_Delta_R;
extern double M_Delta_PE;
extern double M_Fecundity;
extern double M_NoEggs;
/* Parameter mimicing a non-zero flux of adult mosquitoes from
   outside the system */
extern double M_Imm;

/* Mosquito (larva) parameters */
extern double L_Devel;
extern double L_Delta;
extern double L_Delta_0;
extern double L_Delta_P;
extern double L_Delta_R;
extern double L_Delta_PE;

/* Seasonal forcing */
extern double K_0;            /* Larva carrying capacity on average */
extern double K_Sigma;
extern double K_Period;
extern double K_Seasonal_Intensity;
extern double K_Mean_Value;
extern double K_A;            /* Carrying capacity equivalent
         of a daily input of rainfal in an typical area A */
extern double K_p;            /* Typical Rainfall input */
extern double K_E;            /* Decaying of avaible water through evaporation */
extern double K_Maturation;   /* Maturation rate of Rain into
         available Water */

/* Recorded history */
extern double *History_X;
extern double *History_Y;
extern double *History_Time;

/* Plasmodioum */
extern double Plasmodium_Sigma;
extern double Plasmodium_Devel;
extern int n_V;               /* Mosquito Latent class: those incubating malaria */
extern double M_Gamma;        /* 1/M_Gamma is the average time for Plasmodium to develop */

extern int MODEL_OUTPUT_VARIABLES;   /* Actual no of MODEL (output) VARIABLES */
extern int MODEL_INPUT_PARAMETERS;  /* Actual no of MODEL (input) PARAMETERS */
extern int MODEL_STATE_VARIABLES;  /* Actual no of MODEL (state) VARIABLES  */

/* Type of model */
#include <include.Type_Model.extern.h>

#if defined ERROR_FUNCTION
/* The model is defined with some measurement error the determinisic predictio */
 extern double DETERMINISTIC_CASES;
 /* Detection Probability Parameters: Mesurament Error */
#include <include.global.Error_Function.h>
#endif

/* Environmental Parameter Control Switchers */
#include <include.global.EnvParControl.h>
