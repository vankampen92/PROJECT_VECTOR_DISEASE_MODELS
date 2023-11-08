/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                             MALARIA ODE with "Gamma" DELAYS               */
/*                                                                           */
/*                         Recursive Calculation of Fixed Points             */
/*                                                                           */
/*                                 David Alonso, 2006 (c)                    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "../Include/MODEL.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>

#define LOWER_EQUILIBRIUM

void fixed_Points(Parameter_Table *P, double *y_Sol, double EPSILON)
{
  double W_1, y_1;
  
  if (Feasibility_Condition_M(P) == 1) {

#if defined LOWER_EQUILIBRIUM
    W_y_fixed_Points_Lower(P, EPSILON, &W_1, &y_1);
#else    
    W_y_fixed_Points_Upper(P, EPSILON, &W_1, &y_1);
#endif
    
    stable_Solution(y_1, W_1, P, y_Sol);
  }
  else{
    W_1 = 0;
    stable_Solution_Free_Disease(P, y_Sol);
  }
 
}

void W_y_fixed_Points_Upper(Parameter_Table *P, double EPSILON, double *W, double *y)
{
  double W_0, y_0, W_1, y_1;
  double err_y, err_W;
  int No_Count; 

  /* Solution by default */
  (*W) = 0.0;
  (*y) = 0.0;

  if (Feasibility_Condition_M(P) == 1) {
  
    No_Count = 0;
    y_0 = Infectious_Human_asymptotic_Fraction(P);
    W_0 = Infectious_Mosquito_Steady_State(y_0, P);
    
    do{
      
      y_1 = Infectious_Human_Steady_State_Fraction(W_0, P);
      W_1 = Infectious_Mosquito_Steady_State(y_1, P);
      
      err_y = fabs(y_0 - y_1);
      err_W = fabs(W_0 - W_1);
      
      W_0 = W_1;
      y_0 = y_1;
      
      No_Count++;
      if ( No_Count > 100000) break;
      
    }
    while( (err_y > EPSILON) || (err_W > EPSILON) );
    
    if( (W_1 > EPSILON) && (y_1 > EPSILON) && (y_1 < 1.0) ){
      (*y) = y_1; 
      (*W) = W_1;
    }

    if(No_Count < 100000){
      if(Feasibility_Condition_H(P, W_1, y_1) == 0){
	(*y) = 0.0;
	(*W) = 0.0;
      } 
    }
    else{
      (*y) = 0.0;
      (*W) = 0.0;
    } 
  }
  else{
    (*y) = 0.0;
    (*W) = 0.0;
  }  
}

void W_y_fixed_Points_Lower(Parameter_Table *P, double EPSILON, double *W, double *y)
{
  double W_0, y_0, W_1, y_1;
  double err_y, err_W;
  int No_Count; 

  /* Solution by default */
  (*W) = 0.0;
  (*y) = 0.0;

  if (Feasibility_Condition_M(P) == 1) {
  
    No_Count = 0;
    y_0 = EPSILON; //Infectious_Human_asymptotic_Fraction(P);
    W_0 = Infectious_Mosquito_Steady_State(y_0, P);
    
    do{
      
      y_1 = Infectious_Human_Steady_State_Fraction(W_0, P);
      W_1 = Infectious_Mosquito_Steady_State(y_1, P);
      
      err_y = fabs(y_0 - y_1);
      err_W = fabs(W_0 - W_1);
      
      W_0 = W_1;
      y_0 = y_1;
      
      No_Count++;
      if ( No_Count > 100000) break;
      
    }
    while( (err_y > EPSILON) || (err_W > EPSILON) );
    
    if(No_Count < 100000){
      if(Feasibility_Condition_H(P, W_1, y_1) == 0){
	(*y) = 0.0;
	(*W) = 0.0;
      } 
      else if( (W_1 > EPSILON) && (y_1 > EPSILON) && (y_1 < 1.0) ){
	(*y) = y_1; 
	(*W) = W_1;
      }
    }
    else{
      (*y) = 0.0;
      (*W) = 0.0;
    } 
  }

  else{
    (*y) = 0.0;
    (*W) = 0.0;
  }
  
  assert( (*W) >= 0.0 );
  assert( (*y) >= 0.0 );

}

/* void fixed_Points_Testing(Parameter_Table *P, double *y_Sol, double EPSILON) */
/* {  */
/*   /\* Old code to work on and test, make changes and so on *\/ */
/*   double W_0, y_0, W_1, y_1; */
/*   double err_y, err_W; */
 
/*   /\* Initial Guess *\/ */
/*   y_0 = Infectious_Human_asymptotic_Fraction(P); */
/*   W_0 = Infectious_Mosquito_Steady_State(y_0, P); */
 
/*   /\* */
/*     double* pppp5 = malloc(sizeof(double)*10); */
/*     printf("el nostre3.1\n"); */
/*     free(pppp5); */
/*     printf("be\n"); */
    
    
/*     printf("Infected populations\n"); */
/*     printf("Human Fraction... %g\t Error < %g\n", y_0, EPSILON); */
/*     printf("Mosquito Popuation... %g\t Error < %g\n\n", W_0, EPSILON); */
/*   *\/ */
  
/*   do{ */
   
/*     y_1 = Infectious_Human_Steady_State_Fraction(W_0, P); */
/*     W_1 = Infectious_Mosquito_Steady_State(y_1, P); */
 
/*     err_y = fabs(y_0 - y_1); */
/*     err_W = fabs(W_0 - W_1); */
    
/*     W_0 = W_1; */
/*     y_0 = y_1; */
    
/*     /\* */
/*     printf("Infected populations\n"); */
/*     printf("Human Fraction... %g\t Current absolute Error... %g\n", y_1, err_y); */
/*     printf("Mosquito Popuation... %g\t Current absolute Error... %g\n\n", W_1, err_W); */
/*     *\/ */
/*   } */
/*   while( (err_y > EPSILON) || (err_W > EPSILON) ); */
  
/*   stable_Solution(y_1, W_1, P, y_Sol); */
/* } */
