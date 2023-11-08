double y_Function (const double W, void *params);

double y_Function (const double W, void *params)
{
  double y, y_H, y_M;

  Parameter_Table * P = (Parameter_Table *)params;

  y_M = Inverted_Mosquito_Steady_State(W,P); 
  y_H = Infectious_Human_Steady_State_Fraction(W,P);

  y = y_H - y_M;
  
  return(y);
}


     
