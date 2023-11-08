#include "./Include/MODEL.h"
#include "./Include/include.Parameter_Model.extern.h"
#include "./Include/include.extern.par.Trend.h"

void T_R_E_N_D___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (Parameter_Table * Table, Trend Tr)
{
  /* Trend parameter definition */
  /* n = 32  */ Tr.No_of_Jumps = Table->No_of_Jumps;		
  /* n = 33  */ Tr.value_0     = Table->value_0; 
  /* n = 34  */ Tr.value_1     = Table->value_1;
  /* n = 35  */ Tr.time_0      = Table->time_0;
  /* n = 36  */ Tr.time_1      = Table->time_1;
		Tr.TREND_TYPE  = Table->TREND_TYPE;
}

void init_Trend(Parameter_Table * P)
{
  double x;

  switch (P->TREND_TYPE)
    {
    case 0:
      {
	/* No trend ... */
	//printf(".");	
	break;
      }
    case 1:
      {
	/* Mosquito Carrying Capacity */
	P->Tr.value_0 = P->K_0;
	break;
      }
    case 2:
      {
	/* Drug Resistence */
        /* Times are introduces as monthy times. They should
	   be transformed into days */
#if defined RAIN_TEMPERATURA_DATA
        P->Tr.time_0    = Day_From_Month(P, time_0);  
        P->Tr.time_1    = Day_From_Month(P, time_1);
#endif
	P->H_Rho        = P->Tr.value_0/(1.-P->Tr.value_0) * P->H_Nu; /* f_0=P->Tr.value_0 */
	P->Tr.value_0   = P->H_Rho;
	P->Tr.value_1   = P->Tr.value_1/(1.-P->Tr.value_1) * P->H_Nu;
	break;
      }
    case 3:
      {
	/* External Infection */
	P->Tr.value_0 = P->Imm;
	break;
      }
    case 4:
      {
        P->Tr.value_0 = P->H_Rho;
        P->Tr.value_1 = 0.0;
	break;
      }
    case 5:
      {
        /* Drug Resistence */
	printf(" Value changes linearly from %g at time (time_0) %g (moths)\n", P->Tr.value_0, time_0);
	printf(" to value %g at time (time_1) %g (months)\n", P->Tr.value_1, time_1); //Press_Key();
	
	printf(" Value changes linearly from %g at time (P->Tr.time_0) %g (months)\n", P->Tr.value_0, P->Tr.time_0);
	printf(" to value %g at time (P->Tr.time_1) %g (months)\n", P->Tr.value_1, P->Tr.time_1); //Press_Key();

        //x = Day_From_Month(P, time_0); /* time_0 is in months should be in days !!! */
        P->Tr.time_0    = time_0 * P->R_T.T_i;
	//x  = Day_From_Month(P, time_1); /* time_1 is in months should be in days !!! */
	P->Tr.time_1    = time_1 * P->R_T.T_i;
	
        P->Tr.value_0   = P->H_Rho;
        P->Tr.value_1   = 0.0;

	//printf(" Value changes linearly from %g at time %g (days)\n", P->Tr.value_0, P->Tr.time_0);
	//printf(" to value %g at time %g (days)\n", P->Tr.value_1, P->Tr.time_1);
        break;
      }
    case 6:
      {
        /* Trend in External Force of Infection */
	//printf(" Value changes linearly from %g at time (time_0) %g (moths)\n", P->Tr.value_0, time_0);
	//printf(" to value %g at time (time_1) %g (months)\n", P->Tr.value_1, time_1); //Press_Key();
	
	//printf(" Value changes linearly from %g at time (P->Tr.time_0) %g (months)\n", P->Tr.value_0, P->Tr.time_0);
	//printf(" to value %g at time (P->Tr.time_1) %g (months)\n", P->Tr.value_1, P->Tr.time_1); //Press_Key();

        //x = Day_From_Month(P, time_0); /* time_0 is in months should be in days !!! */
        P->Tr.time_0    = time_0 * P->R_T.T_i;
	//x  = Day_From_Month(P, time_1); /* time_1 is in months should be in days !!! */
	P->Tr.time_1    = time_1 * P->R_T.T_i;
	
	/* This is already set up at include.default.Trend.c */
        /* P->Tr.value_0   = P->Imm;  /\* Initially : absence of trend *\/  */
        /* P->Tr.value_1   = P->Imm; */

	//printf(" Value changes linearly from %g at time %g (days)\n", P->Tr.value_0, P->Tr.time_0);
	//printf(" to value %g at time %g (days)\n", P->Tr.value_1, P->Tr.time_1);
        break;
      }
    default :
      {
	printf(" ... applying_Trend.c: Type of Trend is not defined\n");
	printf(" -Tp n, where n = 0, 1, 2, 3, 4 are all possible defintions\n");
        printf(" but here Trend Type is %d\n", P->TREND_TYPE); Press_Key();
        exit(0);
      }
    }
}

void applying_Trend(Parameter_Table *P, double t)
{
  /* This sets the time-dependent parameter at its corresponding 
     value at time t */
  int i;
  double Slope_Trend;
     
  Slope_Trend = (P->Tr.value_1 - P->Tr.value_0)/(P->Tr.time_1 - P->Tr.time_0);
 
  switch (P->TREND_TYPE)
    {
    case 0:
      {
	/* No trend ... */
	//printf(".");//printf(" \n -----> No trend at work\n\n");
	break;
      }
    case 1:
      {
	/* Mosquito Carrying Capacity */
	if(t > P->Tr.time_0 && t< P->Tr.time_1)
	  P->K_0 = P->Tr.value_0 + Slope_Trend * (t - P->Tr.time_0);		
	break;
      }
    case 2:
      {
	/* Drug Resistence */
        if(t >= 0 && t < P->Tr.time_0 ){
	   P->H_Rho = P->Tr.value_0; /* H_Rho */
	} 
	else if (t >= P->Tr.time_0 && t < P->Tr.time_1){
	   P->H_Rho = P->Tr.value_0 + Slope_Trend * (t - P->Tr.time_0);
        }
        else if (t >= P->Tr.time_1 ){
           P->H_Rho = P->Tr.value_1;
        }
        else{
	  printf(" Attention! Negative time: t = %g\n", t);
          printf(" The program will be aborted!"); Press_Key(); exit(0);
        }
	break;
      }
    case 3:
      {
	/* External Infection */
	if(t > P->Tr.time_0 && t< P->Tr.time_1)
	   P->Imm = P->Tr.value_0 + Slope_Trend * (t - P->Tr.time_0);
	break;
      }
    case 4:
      {
        /* Drug Resistence: HARD TREND */
#if defined RAIN_TEMPERATURA_DATA
        i = Month_From_Day(t);
#endif
        if(i >   time_0         )  P->H_Rho = 0; 
        break;
      }
    case 5:
      {
        /* Drug Resistence */
        if(t >= 0 && t < P->Tr.time_0 ){
           P->H_Rho = P->Tr.value_0; /* H_Rho */
        } 
        else if (t >= P->Tr.time_0 && t < P->Tr.time_1){
           P->H_Rho = P->Tr.value_0 + Slope_Trend * (t - P->Tr.time_0);
        }
        else if (t >= P->Tr.time_1 ){
           P->H_Rho = P->Tr.value_1;
        }
        else{
          printf(" Attention! Negative time: t = %g\n", t);
          printf(" The program will be aborted!"); Press_Key(); exit(0);
        }
        //printf("Rho_0(Tr.time_0 = %g) = %g\tRho(t = %g) = %g\tRho_1(Tr.Time_1 = %g) = %g\n", 
	//       P->Tr.time_0, P->Tr.value_0, t, P->H_Rho, P->Tr.time_1, P->Tr.value_1);
        break;
      }
    case 6:
      {
        /* Trend in External Force of Infection */
        if(t >= 0 && t < P->Tr.time_0 ){
           P->Imm = P->Tr.value_0; 
        } 
        else if (t >= P->Tr.time_0 && t < P->Tr.time_1){
           P->Imm = P->Tr.value_0 + Slope_Trend * (t - P->Tr.time_0);
        }
        else if (t >= P->Tr.time_1 ){
           P->Imm = P->Tr.value_1;
        }
        else{
          printf(" Attention! Negative time: t = %g\n", t);
          printf(" The program will be aborted!"); Press_Key(); exit(0);
        }
	
        //printf("Rho_0(Tr.time_0 = %g) = %g\tRho(t = %g) = %g\tRho_1(Tr.Time_1 = %g) = %g\n", 
	//       P->Tr.time_0, P->Tr.value_0, t, P->H_Rho, P->Tr.time_1, P->Tr.value_1);
        break;
      }
    default :
    	{ 
        printf(" ... applying_Trend.c: Type of Trend is not defined\n");
        printf(" -Tp n, where n = 0, 1, 2, 3, 4 are all possible defintions\n");
        printf(" but here Trend Type is %d\n", P->TREND_TYPE); Press_Key();
        exit(0);
      	}
    }
}

double Birth_PerCapita_Rate(Parameter_Table * P, double t)
{
  double Birth;
  double year, t_0, R;
  /* R is defined hear as a population percapita increase per year: R = (N_1 - N_0)/N_0 */

  t_0  = (P->R_T.INITIAL_YEAR - P->R_T.Time[0]) * 12 * P->R_T.T_i;             /* ( P->R_T.T_i = 30.5 ) */ 
 
  year = P->R_T.INITIAL_YEAR + (t - t_0)/ 12.0 / P->R_T.T_i;                   /*                       */

  double FACTOR = 1.0;	

  if( year < 1970.0 ){ 
    R = FACTOR * 0.034;
  }
  else if( year >= 1970.0 && year < 1980.0 ){
    R = FACTOR * 0.032;
  }
  else if ( year >= 1980.0 && year < 1990.0 ){
    R = FACTOR * 0.042;
  }
  else if (  year >= 1990.0 &&  year < 2003.0 ){
    R = FACTOR * 0.036;
  }
  else { 
    R = 0.0;
  }
  
  Birth = 1.0/365.5 * log(1 + R) + P->H_Delta;
  
  return(Birth);
}  

double Birth_PerCapita_Rate_Kericho_Town(Parameter_Table * P, double t)
{
  double Birth;
  double year, t_0, r;
  
  /* r is defined hear as a percapita increase per year: 
     r = 1/(t_1-t_0) * log (1.0 + (N_1 - N_0)/N_0) */
  
  t_0  = (P->R_T.INITIAL_YEAR - P->R_T.Time[0]) * 12 * P->R_T.T_i;            /* ( P->R_T.T_i = 30.5 ) */ 
 
  year = P->R_T.INITIAL_YEAR + (t - t_0)/ 12.0 / P->R_T.T_i;     /*                       */

  double FACTOR = 1.0;	

  if( year >= 1962 && year < 1969.0 ){ 
    r = FACTOR * 0.0483;
  }
  else if( year >= 1969.0 && year < 1979.0 ){
    r = FACTOR * 0.1008;
  }
  else if ( year >= 1979.0 && year < 1989.0 ){
    r = FACTOR * 0.0438;
  }
  else if (  year >= 1989.0 &&  year < 1999.0 ){
    r = FACTOR * 0.0553;
  }
  else if (  year >= 1999.0 &&  year < 2009.0 ){
    r = FACTOR * 0.0553;
  }
  else { 
    r = 0.0;
    assert( r != 0.0 );
  }
  
  Birth = 1.0/365.5 * r + P->H_Delta; 
  
  return(Birth);
}  

double Birth_PerCapita_Rate_Kericho_Town_Average(Parameter_Table * P, double t)
{
  double Birth;
  double year, t_0, r;
  
  Birth = 1.0/365.5 * 0.0639 + P->H_Delta;
  
  return(Birth);
}  

double Intrinsic_PerCapita_Rate(Parameter_Table * P, double t)
{
  double Birth;
  double year, t_0, R;
  /* R is defined hear as a population percapita increase per year: R = (N_1 - N_0)/N_0 */

  t_0  = (P->R_T.INITIAL_YEAR - P->R_T.Time[0]) * 12 * P->R_T.T_i; /* ( P->R_T.T_i = 30.5 ) */ 
  year = P->R_T.INITIAL_YEAR + (t - t_0)/ 12.0 / P->R_T.T_i;      /*                       */

  double FACTOR = 1.0;	

  if( year < 1970.0 ){ 
    R = FACTOR * 0.034;
  }
  else if( year >= 1970.0 && year < 1980.0 ){
    R = FACTOR * 0.032;
  }
  else if ( year >= 1980.0 && year < 1990.0 ){
    R = FACTOR * 0.042;
  }
  else if (  year >= 1990.0 &&  year < 2003.0 ){
    R = FACTOR * 0.036;
  }
  else { 
    R = 0.0;
  }
  
  Birth = 1.0/365.5 * log(1 + R);
  
  return(Birth);
}  

/* Compassion without knowledge is ineffective */
