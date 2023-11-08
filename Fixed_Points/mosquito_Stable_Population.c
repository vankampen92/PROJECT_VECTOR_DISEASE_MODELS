#include "../Include/MODEL.h"
#include "../Include/include.extern.par.HumanMos.h"

double mosquito_Stable_Population(Parameter_Table *P)
{
  double M;
  
  M = P->K_0* P->L_Devel/P->M_Delta* (1. - (1.+ P->L_Delta/P->L_Devel) *P->M_Delta/P->M_Fecundity);
    
  return (M);
}

double larva_Stable_Population(Parameter_Table *P)
{
  double L;
  
  
  L = P->K_0* (1. - (1.+ P->L_Delta/P->L_Devel) *P->M_Delta/P->M_Fecundity);
  
  return (L);
}
