double m;            /* m = M/H Number of Mosquitoes per Human */
/* POPULATION and Human */
int POPULATION;
double H;            /* Total Human Population */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Human parameters: see include.default.Human.c */
double H_Beta;
double H_Delta;
double H_Birth;
double H_Sigma_0;
double H_Recov_0;
double H_Sigma;
double H_Recov;
int n_H;            /* Human Latent class: those incubating malaria */
double H_Gamma;     /* 1/H_Gamma is the average latent time */
double Imm;         /* External Immigration */
double Human_Growing_Population;
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Cases: Human parameters to deal with clinical malaria:
          see include.default.Cases.c */
double H_Xhi;
double H_Rho;
double H_Eta;
double H_Nu;
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* SnInR: Human parameters to deal with multiple classes of infection:
              see include.default.SnInR.c */
#include <include.global.SnInR.h>
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Temperature: to calculate temp. dependent mosquito parameters
              see include.default.Temperature.c */
double Temp; double Temp_Mean_Value; 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Mosquito (Adult) parameters:
          see include.default.MosAdult.c */
double M_a; double M_a_Mean_Value;
double M_b;
double M_c;

double M_c_1;      // Specific KLEIN parameters
double M_c_2;      // c_1, c_2

double M_Delta;
double M_Delta_R;  // M_Delta = M_Delta(T) + M_Delta_R (Only if Rain is heavier than the 'M_Delta_PE'
double M_Delta_PE; //                                   percentile)
double M_Fecundity;
double M_NoEggs;
double M_Imm;      /* Parameter mimicing a non-zero flux of adult mosquitoes from
    outside the system */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Extra parameters: thresholds in mosquito biting intensity
   that produce H_Sigma = H_Delta and H_Recov = H_Delta, resp. */
double W_Sigma;
double W_Recov;
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Mosquito (larva) parameters:
          see include.default.MosLarva.c */
double L_Devel;
double L_Delta;
double L_Delta_0;  //Different Possibilities:
double L_Delta_P;  //L_Delta = L_Delta_P + L_Delta_0(T) + L_Delta_R * HeavySide(Rain - <Rain>) (mm/day);
double L_Delta_R;  //L_Delta = L_Delta_P + L_Delta_0(T) + L_Delta_R * fabs(Rain - <Rain>) (mm/day);
double L_Delta_PE; //L_Delta = L_Delta_P + L_Delta_0(T) + L_Delta_R
       //(Only if Rain is heavier that the 'L_Delta_PE' percentile)
double K_0;            /* Larva carrying capacity on average */
                       /* Consistently, K_0 = P->K_A*P->K_p/P->K_E */
double K_Sigma;        /* Carrying capacity Variance */
double K_A;            /* Carrying capacity equivalent
        of a daily input of rainfal in an typical area A */
double K_p;            /* Typical Rainfall input */
double K_E;            /* Decaying of avaible water through evaporation */
double K_Period;
double K_Seasonal_Intensity;
double K_Mean_Value;
double K_Maturation;     /* Maturation rate of rain water into water
        available for larva to grow */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Extra parameters: Recorded history */
double *History_X;
double *History_Y;
double *History_Time;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Plasmodioum:
           see include.default.Plasmodium.c */
double Plasmodium_Sigma;
double Plasmodium_Devel;
int n_V;               /* Mosquito Latent class: those incubating malaria */
double M_Gamma;        /* 1/M_Gamma is the average time for Plasmodium to develop */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int MODEL_OUTPUT_VARIABLES;   /* Actual no of MODEL (output) VARIABLES */
int MODEL_INPUT_PARAMETERS;  /* Actual no of MODEL (input) PARAMETERS */
int MODEL_STATE_VARIABLES;  /* Actual no of MODEL (state) VARIABLES  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Type of model */
#include <include.Type_Model.global.h>

#if defined ERROR_FUNCTION
/* The model is defined with some measurement error the determinisic predictio */
 double DETERMINISTIC_CASES;
 /* Detection Probability Parameters: Mesurament Error */
#include <include.global.Error_Function.h>
#endif

/* Environmental Parameter Control Switchers */
#include <include.global.EnvParControl.h>
