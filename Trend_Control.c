#include "./Include/MODEL.h"

#if defined APPLYING_TREND

void T_R_E_N_D___C_O_N_T_R_O_L___F_R_E_E( Trend_Control * Tr )
{
  free(Tr);
}

void T_R_E_N_D___C_O_N_T_R_O_L___A_L_L_O_C( Trend_Control * Tr, Parameter_Table * P )
{
  /* */
}

void  T_R_E_N_D___C_O_N_T_R_O_L___U_P_L_O_A_D( Trend_Control * T, Parameter_Table * Table )
{ 

  /* Trend parameter definition */
  T->Tr_No_of_Jumps = Table->Tr_No_of_Jumps;
		
  T->Tr_value_0     = Table->Tr_value_0; 
  T->Tr_value_1     = Table->Tr_value_1;
  T->Tr_value_i     = Table->Tr_value_i;

  T->Tr_Time_0      = Table->Tr_Time_0;
  T->Tr_Time_1      = Table->Tr_Time_1;
  T->Tr_Time_i      = Table->Tr_Time_i;

  /* Default: */
  T->Tr_Input_Parameter = Table->Tr_Input_Parameter;
  T->TREND_TYPE         = Table->TREND_TYPE;
  /* -------- */

  Table->Tr           = T;
}

void S_E_T_U_P___T_R_E_N_D___F_R_E_E___T_R_I_A_N_G_L_E ( Trend_Control * T, 
							 Time_Control * Time, 
							 int Input_Parameter )
{
  T->Tr_Input_Parameter = Input_Parameter;
  T->TREND_TYPE         = 0;
}

void S_E_T_U_P___T_R_E_N_D___T_R_I_A_N_G_L_E ( Trend_Control * T, 
					       Time_Control * Time, 
					       int Input_Parameter )
{
  double Value_0, Value_1;

  T->Tr_Time_0      = Time->Time_0;
  T->Tr_Time_1      = Time->Time_1;  
  /* Note that Time_i will be here an intermediate time! */
  T->Tr_Time_i      = (Time->Time_1 - Time->Time_0)/2.0;

  Boundary(Input_Parameter, &Value_0, &Value_1);

  T->Tr_value_0     = Value_0; 
  T->Tr_value_1     = Value_0;
  /* Note that at the intermediate time we have the highest value */
  T->Tr_value_i     = Value_1;

  T->Tr_Input_Parameter = Input_Parameter;
  T->TREND_TYPE         = 0;
}

void S_E_T_U_P___T_R_E_N_D___L_I_N_E_A_R ( Trend_Control * T, 
					   Time_Control * Time, 
					   int Input_Parameter, 
					   int Signature )
{
  double Value_0, Value_1;

  T->Tr_Time_0      = Time->Time_0;
  T->Tr_Time_1      = Time->Time_1;  
  
  Boundary(Input_Parameter, &Value_0, &Value_1);

  if( Signature == +1 ){
    /* Increasing trend */
    T->Tr_value_0     = Value_0; 
    T->Tr_value_1     = Value_1;
  }
  else {
    /* Decreasing trend */
    T->Tr_value_0     = Value_1; 
    T->Tr_value_1     = Value_0;
  }

  T->Tr_Input_Parameter = Input_Parameter;
  T->TREND_TYPE         = 1;
}

void S_E_T_U_P___T_R_E_N_D___F_R_E_E___L_I_N_E_A_R ( Trend_Control * T, 
						     Time_Control * Time, 
						     int Input_Parameter )
{ 
  T->Tr_Input_Parameter = Input_Parameter;
  T->TREND_TYPE         = 1;
}

void A_P_P_L_Y_I_N_G___T_R_E_N_D(Parameter_Table * P, double t)
{
  /* This sets the time-dependent parameter at its corresponding 
     value at time t */
  int Input_Parameter;
  double Slope;
  double value;
  Trend_Control * T = P->Tr;
  double Time_0, Time_i, Time_1;

  Time_0 = T->Tr_Time_0;  Time_i = T->Tr_Time_i;  Time_1 = T->Tr_Time_1;

  Input_Parameter = T->Tr_Input_Parameter;
     
  switch (P->TREND_TYPE)
    {
    case 0: /* TREND_TYPE = 0, Update Time Dependence */
      {
	/* In the corresponding deterministic_time_dynamics.c file
	   the follwing function is defined (sinusoidal-like forcing) 
	*/
	Update_Time_Dependence (P->TYPE_of_TIME_DEPENDENCE, t, P );
	value = AssignStructValue_to_VectorEntry(Input_Parameter, P);
	break;
      }
    case 1: /* TREND_TYPE = 0, Triangular Trend: _.-^-._ */
      {
	if ( t <= Time_0 ) {
	  value = T->Tr_value_0; 
	}
	else if ( t > Time_0 && t <= Time_i ) {
	  Slope  = (T->Tr_value_i - T->Tr_value_0)/(Time_i - Time_0);

	  value = T->Tr_value_0 + Slope * (t - Time_0);		
	}
	else if ( t > Time_i && t < Time_1 ) {
	  Slope  = (T->Tr_value_1 - T->Tr_value_i)/(Time_1 - Time_i);

	  value = T->Tr_value_i + Slope * (t - Time_i);
	}
	else { /* if ( t >= Time_1 ) { */
	  value = T->Tr_value_1; 
	}
      
	AssignVectorEntry_to_Structure(P, Input_Parameter, value);
	break;
      }
    case 2: /* TREND_TYPE = 1, Increasing or Decreasing Trend: _.-^ */
      {
	Slope = (T->Tr_value_1 - T->Tr_value_0)/(Time_1 - Time_0);
	
	if ( t <= Time_0 ) {
	  value = T->Tr_value_0; 
	}
	else if ( t > Time_0 && t <= Time_1 ) {
	  value = T->Tr_value_0 + Slope * (t - Time_0);		
	}
	else{
	  value = T->Tr_value_1; 
	}
      
	AssignVectorEntry_to_Structure(P, Input_Parameter, value);
	break;
      }
    default :
      { 
	printf(" ... Trend_Control.c: Type of Trend is not defined\n");
        printf(" -Tp n, where n = -1, 0, 1, 2, 3, 4 are all possible defintions\n");
        printf(" but here Trend Type is %d\n", P->TREND_TYPE); Press_Key();
        exit(0);
      }
    }
  /* Saving Values */
  
  if ( P->TREND_TYPE != (-1) ) {
    FILE *  fp;
    
    if ( (fp = fopen("Parameter_Trend.dat", "a")) == NULL ) {
      printf(" No file called Parameter_Trend.dat in current directorory\n");
      printf(" The program will exit\n");
      exit(0);
    }
    else {
      fprintf(fp, "%g\t%g\n", t, value);
    }
    
    fclose(fp);
  }
}
#endif


