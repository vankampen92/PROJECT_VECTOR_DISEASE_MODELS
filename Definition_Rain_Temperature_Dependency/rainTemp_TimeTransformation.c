#include "../Include/MODEL.h"

double Intermediate_Time(Parameter_Table *P, double t_0, double t_1)
{
  /* t_0 and t_1 are given in days */
  int i_0, i_1;
  double T_i;

  i_0 = Month_From_Day(t_0);
  i_1 = Month_From_Day(t_1);

  assert(i_0 != i_1);

  T_i = (P->R_T.Time[i_1] - P->R_T.Time[0])*366.0; /* 12 times 30.5 */
  
  if((t_0 > T_i) || (t_1 < T_i)){
    printf("t_0 = %g\tT_i = %g\tt_1 = %g\n", t_0, T_i, t_1);
  }
  
  assert((t_0 < T_i) && (t_1 > T_i));

  return(T_i);
}

double temperature_Day(Parameter_Table *P, double t)
{
  /* t, time given in days as an input. */
  int i;
  double Temp;

  i = Month_From_Day(t);

  if (i < P->R_T.No){
    Temp = P->R_T.Temp[i]/10.;  /* Temperature in Celsius degrees */
  }
  else{
    printf(" Problems in rainTemp_timeTransform_Monthly_Dependence.c\n");
    printf(" The function Month_From_Day(t) returns a month number which\n");
    printf(" which is higher the the number of months in the initial time\n");
    printf(" series. The program will exit\n");
    printf(" Month Number: %d\t Max Month Number: %d\n", i, P->R_T.No-1); exit(0);
  }

  if(Temp > 100){
    printf("Environmental temperature is higher than boiling temperature (T = %g)\n", Temp);
    printf("Something is very wrong here!!\n");
    exit(0);
  }

  return(Temp);
}

double temperature_Day_Smooth(Parameter_Table *P, double t)
{
  /* t, time given in days as an input. */
  int i;
  double Temp;

  i = Month_From_Day(t);

  if (i < P->R_T.No){
    Temp = P->R_T.Temp_Smooth[i]/10.;  /* Temperature in Celsius degrees */
  }
  else{
    printf(" Problems in rainTemp_timeTransform_Monthly_Dependence.c\n");
    printf(" The function Month_From_Day(t) returns a month number which\n");
    printf(" which is higher the the number of months in the initial time\n");
    printf(" series. The program will exit\n");
    printf(" Month Number: %d\t Max Month Number: %d\n", i, P->R_T.No-1); exit(0);
  }

  if(Temp > 100){
    printf(" Environmental temperature is higher than boiling temperature (T = %g)\n", Temp);
    printf(" Something is very wrong here!!\n");
    exit(0);
  }

  return(Temp);
}

double rain_Day(Parameter_Table *P, double t)
{


  /* t, time given in days as an input. 
     Daily rain for the current month $i$ is given in 
     Rain */
  int i, i_time;
  double Rain; 
  
#if defined MONTH_TIME_INTEGRATION 

  i = Month_From_Day(t);

  if (i < P->R_T.No){
    Rain = P->R_T.Rain[i]/P->R_T.T_i/10.0;
  }
  else{
    printf(" Problems in rainTemp_timeTransform_Monthly_Dependence.c\n");
    printf(" The function Month_From_Day(t) returns a month number which\n");
    printf(" which is higher the the number of months in the initial time\n");
    printf(" series. The program will exit\n");
    printf(" Month Number: %d\t Max Month Number: %d\n", i, P->R_T.No-1); exit(0);
  }

#else

  i_time = (int)floor(t); //i_time = (int)ceil(t);
 
  Rain      = P->R_T.DDMM[i_time].rain;              /* Actual daily rain */

#endif

  return (Rain);
}

double rain_Day_Smooth(Parameter_Table *P, double t)
{
  /* t, time given in days as an input. 
     Daily rain for the current month $i$ is given in 
     Rain */
  int i;
  double Rain; 
  
  i = Month_From_Day(t);
  
  if (i < P->R_T.No){
    Rain = P->R_T.Rain_Smooth[i]/P->R_T.T_i/10.0;
  }
  else{
    printf(" Problems in rainTemp_timeTransform_Monthly_Dependence.c\n");
    printf(" The function Month_From_Day(t) returns a month number which\n");
    printf(" which is higher the the number of months in the initial time\n");
    printf(" series. The program will exit\n");
    printf(" Month Number: %d\t Max Month Number: %d\n", i, P->R_T.No-1); exit(0);
  }
  
  return (Rain);
}

int Month_From_Day(double t)
{
  int i;
  double t_0;

  t_0 = t/30.5;       /* Time in double (30.5-day ideal) average months plus a fraction 
			 of current month */
  i = floor(t_0);     /* Integral Months: from i=0 to i=NO_of_POINTS-1, where the NO_of_POINTS
                         are the number of points in the time series 
	              */
  return(i);
}

double Day_From_Month( Parameter_Table * P, double time )
{
  /* BEGIN : Transforming time in months in time in days * * * * */
  double x;

  int Year_Shift;
  double Month;
  double T_obs    = P->R_T.T_i;

  Year_Shift  = (int)(P->R_T.INITIAL_YEAR - P->R_T.Time[0]);
  Month    =  12.0 * Year_Shift + time;

  printf(" Inflection point for the trend: t       = %g (months)\n", time);
  printf(" Inflection point for the trend: t + t_0 = %g (months)\n", Month);
  printf(" Initial Time: %g", P->R_T.Time[0]);
  printf(" Year Shift: t_0 = %d (years)", Year_Shift); 
  
#if defined MONTH_TIME_INTEGRATION

  x = Month * T_obs; 

#else

  if (Year_Shift > 0)  x = P->R_T.Days[ Year_Shift*12 + (int)Month ];
  else                 x = 0.0;
  
  printf(" PUTA PUTA PUTA PUTA: rainTemp_TimeTransformation.c: EXIT"); exit(0);

#endif
  
  printf(" Inflection point for the trend: t + t_0 = %g (days)\n", x);
  Press_Key();

  return(x);
/*   END : Transforming time in months in time in days * * * * */
}
