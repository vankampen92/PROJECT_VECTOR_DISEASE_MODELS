//  #include <MODEL.h>

/* B E G I N :  Mosquito submodel */
double Infectious_Mosquito_Steady_State(const double y, Parameter_Table *P)
{
  double M, W, g;

  if (P->n_V == 0){
	g = 1.0;
  }
  else {	
  	g = P->n_V * P->M_Gamma /(P->n_V * P->M_Gamma + P->M_Delta);
        g = pow(g,(double)P->n_V);
  }

  M = Total_Mosquito_Steady_State(P);

  W = M *P->M_a*P->M_c * y/(P->M_Delta + P->M_a*P->M_c * y) * g; 

  return(W);
}

double Inverted_Mosquito_Steady_State(const double W, Parameter_Table *P)
{
  /* This function is only the inversion of the previous one */

  double y;
  double g;
  double M, w;
  
  M = Total_Mosquito_Steady_State(P);

  if (P->n_V == 0){
        g = 1.0;
  }  
  else {
        g = P->n_V * P->M_Gamma /(P->n_V * P->M_Gamma + P->M_Delta);
        g = pow(g,(double)P->n_V);
  }

  w = W/M;
  y = 1./g * P->M_Delta * w/P->M_c/P->M_a/(1.- 1./g*w);

  return (y); 
}
/* E N D :  Mosquito submodel */

