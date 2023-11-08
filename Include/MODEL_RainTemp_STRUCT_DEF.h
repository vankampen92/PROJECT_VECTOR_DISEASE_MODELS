typedef struct Day_Month_RAIN_Info
{
  double day;
  double month;
  double rain;
}Day_Month_RAIN;

typedef struct RainTempinfo
{
  int No;        /* No of Points of time Series (time dependent parameters) */
  int No_Ave;    /* Number of Poits of the average year (usually 12 months) */
  int No_Ini;
  double T_i;        /* Interval between data points */ 
  double *Rain;      /* Rainfall    */

  double *Temp;  /* Temperature */
  double *Case;
  double *Time;
  
  double *Year; /* Cummulative number of days (in year units) */
  double *Days; /* Cummulative number of days (in days units) */
  Day_Month_RAIN * DDMM;
  
  int Total_No_of_Days;
  double INITIAL_YEAR;

  double *Rain_Ave;
  double *Temp_Ave;
  double *Case_Ave;

  double *Rain_Var;
  double *Temp_Var;
  double *Case_Var;

  double *Rain_Smooth;
  double *Rain_PerCen;
  double *Temp_Smooth;
  double *Time_Ave;

  double Ave_Rain; /* Average time values for the whole time period */
  double Ave_Temp;
  double Ave_Case;
  double TEMP__SHIFT;
  double T_ELEVATION;
  double x;        /* Fraction of time at the outdoor temperature */

  double EMPIRICAL_AVE;
  double EMPIRICAL_VAR;
  double EMPIRICAL_AbDEV;
       
}RainTemp;
