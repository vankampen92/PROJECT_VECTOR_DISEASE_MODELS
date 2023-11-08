#include <MODEL.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

//#define BREAK_if_W_is_NEGATIVE

#define EPSILON 1.0e-20

double Beta_Function_MacDonaldRoss(Parameter_Table * P, double W)
{
  double B, EIR;

  EIR = P->M_a * W; /* Bitting Intensity */

  /* Classical Frequency-Dependent Transmision (plus external infection) */
  B = P->M_b * EIR  + P->Imm;

  /* Frequency-Dependent Transmission (plus exteranl infection) */
  //B = 1./P->M_b * I /(1 + I/P->M_b) * I  + P->Imm;

  /* Logistic-Frequency-Dependent transmission (plus external infection) */
  //B = (1./(1+exp(-1.*(I-P->M_b))) - 1./(1+exp(+1.*(I+P->M_b)))) * I + P->Imm; 

  return(B);
}

double Beta_Function(Parameter_Table * P, double W)
{
  double B, I;
  
  I = P->M_a * W/P->H; /* Bitting Intensity */

  /* Classical Frequency-Dependent Transmision (plus external infection) */
  B = P->M_b * I  + P->Imm;                      

  /* Frequency-Dependent Transmission (plus exteranl infection) */
  //B = 1./P->M_b * I /(1 + I/P->M_b) * I  + P->Imm;

  /* Logistic-Frequency-Dependent transmission (plus external infection) */
  //B = (1./(1+exp(-1.*(I-P->M_b))) - 1./(1+exp(+1.*(I+P->M_b)))) * I + P->Imm; 
                                                    
  return(B);
}

double Beta_Derivative_1(Parameter_Table * P, double W)
{
  double B;
  
  B = P->M_b * P->M_a / P->H; 
  
  return(B);
}

double Beta_Function_Fraction_Infectious_Mosquitoes(Parameter_Table *P, double W)
{
  double B, I;
  
  I = P->M_a * P->m * W; /* EIR, Bitting Intensity, where W is 
                            the fraction of infectious mosquitoes
                            */

  /* Classical Frequency-Dependent Transmision (plus external infection) */
  B = P->M_b * I  + P->Imm;                      

  /* Frequency-Dependent Transmission (plus exteranl infection) */
  //B = 1./P->M_b * I /(1 + I/P->M_b) * I  + P->Imm;

  /* Logistic-Frequency-Dependent transmission (plus external infection) */
  //B = (1./(1+exp(-1.*(I-P->M_b))) - 1./(1+exp(+1.*(I+P->M_b)))) * I + P->Imm; 
  
  return(B);
}

double Beta_Derivative_1_Fraction_Infectious_Mosquitoes(Parameter_Table *P, double W)
{
  /* where input argument W is 
     the fraction of infectious mosquitoes
  */
  double B;
  
  B = P->M_b * P->M_a * P->m; 
  
  return(B);
}

#if defined NON_SUPERINFECTION

double Queu_Function(Parameter_Table *P, double W, double F_0, double T)
{
  return (F_0);
}

double Derivative_Queu_Function(double B, double F_0, double T)
{
  /* First derivative with respect to B */
  /* T, Threshold in biting intesity (B) over which F will be P->H_Delta */
  return (0.0);
}

double Queu_Function_Fraction_Infectious_Mosquitoes(Parameter_Table *P, double W, double F_0, double T)
{
  return (F_0);
}    

#else //with SUPERINFECTION, Dietz' approach is used//

double Queu_Function(Parameter_Table * P, double W, double F_0, double T)
{
  /* T, Threshold in biting intesity (B) over which F will be P->H_Delta */
  /* W, Number of infectious mosquitos */
  /* B, Number of Mosquito bites per human per unit time $\hat(\beta) = a * W/N */
  double B, F;

  
  B = P->M_a * W/P->H; 

  if(B < 0.){
    printf("-");
    //printf("... Error in /home/dalonso/C_pro/Stochastics/SIC_MALARIA/K_Queue_Mosquito.c\n");
    //printf("a = %g\tW = %g\tN = %g\n", P->M_a, W, P->H);

    /* If W is really very negative, exit!! */ 
    if ( W < -1.0 ){
      printf("... Error in /home/dalonso/C_pro/Stochastics/SIC_MALARIA/K_Queue_Mosquito.c\n");
      printf("a = %g\tW = %g\tN = %g\n", P->M_a, W, P->H);
      printf(" If W is really very negative. If control variable BREAK_if_W_is_NEGATIVE is defined,\n");
      printf(" the program will exit\n");
#if defined BREAK_if_W_is_NEGATIVE
      exit(0);
#endif
    }
    else{
      /* Otherwise, assume B = 0. Then F takes F_0 value */
      F = F_0; //Since F = B/(exp(B/F_0) - 1.), when B --> 0, then  F --> F_0
    }
  }
  else if (B == 0.){
    F = F_0;
  }
  else{

#if defined QUEU_FUNCTION_THRESHOLD    
    if (B < T){
      F = B/(exp(B/F_0) - 1.);
    }
    else{
      F = P->H_Delta;
    }
#else    
    F = B/(exp(B/F_0) - 1.);
#endif

  }

  return F;
}

double Queu_Function_Fraction_Infectious_Mosquitoes(Parameter_Table *P, double W, double F_0, double T)
{
  /* T, Threshold in biting intesity (B) over which F will be P->H_Delta */
  /* W, the input argument W is the fraction of infectious mosquitoes    */
  /* B, Number of Mosquito bites per human per unit time $\hat(\beta) = a * W/N */
  double B, F;

  B = P->M_a * P->m * W;  /* W, Fraction of mosquitoes infectious */ 

  if(B < 0.){
    printf("-");
    //printf("... Error in /home/dalonso/C_pro/Stochastics/SIC_MALARIA/K_Queue_Mosquito.c\n");
    //printf("a = %g\tW = %g\tN = %g\n", P->M_a, W, P->H);

    /* If W is really very negative, exit!! */ 
    if ( W < -1.0 ){
      printf("... Error in /home/dalonso/C_pro/Stochastics/SIC_MALARIA/K_Queue_Mosquito.c\n");
      printf("a = %g\tW = %g\tN = %g\n", P->M_a, W, P->H);
      printf(" If W is really very negative. If control variable BREAK_if_W_is_NEGATIVE is defined,\n");
      printf(" the program will exit\n");
#if defined BREAK_if_W_is_NEGATIVE
      exit(0);
#endif
    }
    else{
      /* Otherwise, assume B = 0. Then F takes F_0 value */
      F = F_0; //Since F = B/(exp(B/F_0) - 1.), when B --> 0, then  F --> F_0
    }
  }
  else if (B == 0.){
    F = F_0;
  }
  else{

#if defined QUEU_FUNCTION_THRESHOLD    
    if (B < T){
      F = B/(exp(B/F_0) - 1.);
    }
    else{
      F = P->H_Delta;
    }
#else    
    F = B/(exp(B/F_0) - 1.);
#endif

  }

  return F;
}

double Derivative_Queu_Function(double B, double F_0, double T)
{
  /* First derivative with respect to B */
  /* T, Threshold in biting intesity (B) over which F will be P->H_Delta */

  double F, x, x_0;
  
  //if(B < T){
  
  if(B < 0.){
    //printf(".");
    printf("... Error in /home/dalonso/C_pro/Stochastics/SIC_MALARIA/Derivative_Queue_Function.c\n");
    printf("... Biting Intensity [B = a W/N ]\t B =  %g\t H_[Sigma or Recov]_0 = %g\n", B, F_0);
    
    /* If B is really very negative, exit!! */ 
    /* otherwise, assume it is actually 0   */
    if ( B < -1.0 ){
#if defined BREAK_if_W_is_NEGATIVE
      exit(0);
#endif
      
    }
    else{
      F = -0.5;
    } 
  }
  else{
    x = B/F_0;   assert(x >= 0.0);

    x_0 = 1.0/2.0/exp(x);
    
      if (B == 0.0){
	F = -0.5;
      }
      else if(B>0 && x_0 > EPSILON){
	F = 1.0/(exp(x) - 1.0) * (exp(x) -1.0 - x*exp(x))/(exp(x) - 1.0);
      }
      else{
	F = EPSILON;
      }
      
  }
  
  return F;
}
#endif
