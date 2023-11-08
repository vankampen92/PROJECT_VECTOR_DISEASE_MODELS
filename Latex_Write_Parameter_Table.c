#include <MODEL.h>

//#if defined CPGPLOT_REPRESENTATION
//#include <include.CPG.extern.h>
//#endif
//#include "./Include/include.Time_Control.extern.h"
//#include "./Include/include.Output_Variables.extern.h"
#include <include.Parameter_Model.extern.h>
#include <include.PARAMETER_SPACE.extern.h>
//#include "./Include/include.Initial_Conditions.extern.h"
//#include "./Include/include.Stochastic_Realizations.extern.h"

void write_Parameter_Table___RANGES___VALUES___LATEX ( char * table_Param, char * parameter_Space_Code, Parameter_Table * P,
                                                 	 double * Par_MAX, double * Par_min, int no_Par )
{
  double Par_Value;
  int i, k;
  FILE *fp = fopen( table_Param, "w" );
  char Parameter_Name[100];
  char Parameter_Symbol[50];

  printf(" Writing latex parameter table...\n");
  printf(" Parameter Space Definition Code : %s\n", parameter_Space_Code);
  
  fprintf(fp, "\\begin{table}\n");
  fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\begin{tabular}{p{5cm}ccccc}\n");
  fprintf(fp, "{\\bf Model Parameter} & {\\bf Symbol} & {\\bf Min. Value} & {\\bf Max. Value} & {\\bf A} & {\\bf B}""\\""""\\""\n");
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");

  for ( i = 0; i < no_Par; i++){

    k = P->Index[i];

    Par_Value = AssignStructValue_to_VectorEntry (k, P);

    AssignLabel_to_Parameters__LATEX(k , Parameter_Name, P);

    AssignLabel_to_Parameters__LATEX__SYMBOL(k , Parameter_Symbol, P);

    fprintf(fp, "%s & %s & %4.2g & %4.2g & %4.2g & %4.2g""\\""""\\""\n", 
	    Parameter_Name, Parameter_Symbol, Par_min[i], Par_MAX[i], Par_Value, Par_Value);
  }

  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  fprintf(fp, "\\smallskip\n");

  fprintf(fp, "\\end{tabular}\n");
  //fprintf(fp, "\\vspace{1cm}\n");
  fprintf(fp, "\\noindent");

  fprintf(fp, "{\\bf Table 2:} A and B are the two parameter combinations around which we have done most of the exploration of the parameter space. See figures. Minimum and maximum values define the subregion of the parameter space we have explored. Legend: {\\small H: Human, M: Mosquito, L: Larva, P: {\\em Plasmodium}} \n");

  fprintf(fp, "\\end{table}\n");
  fclose(fp);

  printf(" End writing latex parameter table!\n");
}


void write_Param_Table_PARAMETER_RANGES___LATEX ( char * table_Param, char * parameter_Space_Code, Parameter_Table *P, 
						  double * Par_MAX, double * Par_min, int no_Par )
{
  int i, k;
  FILE *fp = fopen( table_Param, "w" );
  char Parameter_Name[100];
  char Parameter_Symbol[50];

  fprintf(fp, "\\begin{table}\n");
  fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\begin{tabular}{lccc}\n");  
  fprintf(fp, "{\\bf Model Parameter} & {\\bf Symbol} & {\\bf Min. Value} & {\\bf Max. Value}""\\""""\\""\n"); 
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  
  for ( i = 0; i < no_Par; i++){

    k = P->Index[i];
    
    AssignLabel_to_Parameters__LATEX(k , Parameter_Name, P);

    AssignLabel_to_Parameters__LATEX__SYMBOL(k , Parameter_Symbol, P);
    
    fprintf(fp, "%s & %s & %g & %g""\\""""\\""\n", Parameter_Name, Parameter_Symbol, Par_min[i], Par_MAX[i]);
  }

  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  fprintf(fp, "\\smallskip\n");

  fprintf(fp, "\\end{tabular}\n");
  //fprintf(fp, "\\vspace{1cm}\n");
  fprintf(fp, "\\noindent");

  fprintf(fp, "{\\bf Table 2:} Malaria model parameter defining the GA search. (Parameter space definition code: $%s$). Legend: {\\small H: Human, M: Mosquito, L: Larva, P: {\\em Plasmodium}, R: Rain, T: Temperature, $T_e$: Effective temperature, $(T_i - T_o)= %g^{oC}$: Maximum difference between indoors and outdoors temperature}\n", parameter_Space_Code, P->R_T.TEMP__SHIFT );

  fprintf(fp, "\\end{table}\n");
  fclose(fp);
}

void write_Param_Table_AVE_STD___LATEX( char * table_Param, Parameter_Table *P, 
					double * Par_AVE, double * Par_STD, int no_Par )
{
  int i, k;
  FILE *fp = fopen( table_Param, "w" );
  char Parameter_Name[100];
  char Parameter_Symbol[50];

  fprintf(fp, "\\begin{table}\n");
  fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\begin{tabular}{lccc}\n");  
  fprintf(fp, "{\\bf Model Parameter} & {\\bf Symbol} & {\\bf Average} & {\\bf Stardard Deviation}""\\""""\\""\n"); 
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  
  for ( i = 0; i < no_Par; i++){

    k = P->Index[i];
    
    AssignLabel_to_Parameters__LATEX(k , Parameter_Name, P);

    AssignLabel_to_Parameters__LATEX__SYMBOL(k , Parameter_Symbol, P);
    
    fprintf(fp, "%s & %s & %5.3g & %5.3g""\\""""\\""\n", Parameter_Name, Parameter_Symbol, Par_AVE[i], Par_STD[i]);
  }

  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  fprintf(fp, "\\smallskip\n");

  fprintf(fp, "\\end{tabular}\n");
  //fprintf(fp, "\\vspace{1cm}\n");
  fprintf(fp, "\\noindent");

  fprintf(fp, "{\\bf Table 1:} Malaria model parameters. Legend: {\\small H: Human, M: Mosquito, L: Larva, P: {\\em Plasmodium}, R: Rain, T: Temperature, $T_e$: Effective temperature, $(T_i - T_o)= %g^{oC}$: Maximum difference between indoors and outdoors temperature}\n", P->R_T.TEMP__SHIFT);

  fprintf(fp, "\\end{table}\n");
  fclose(fp);
}

void write_Param_Table_AVE_CI___LATEX( char * table_Param, Parameter_Table *P, 
				       double * Par_AVE, double ** Confidence_Interval, int no_Par )
{
  int i, k;
  FILE *fp = fopen( table_Param, "w" );
  char Parameter_Name[100];
  char Parameter_Symbol[50];

  fprintf(fp, "\\begin{table}\n");
  fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\begin{tabular}{lccc}\n");  
  fprintf(fp, "{\\bf Model Parameter} & {\\bf Symbol} & {\\bf Average} & {\\bf Confidence Interval}""\\""""\\""\n"); 
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  
  for ( i = 0; i < no_Par; i++){

    k = P->Index[i];
    
    AssignLabel_to_Parameters__LATEX(k , Parameter_Name, P);

    AssignLabel_to_Parameters__LATEX__SYMBOL(k , Parameter_Symbol, P);
    
    fprintf(fp, "%s & %s & %5.3g & (%5.3g, %5.3g)""\\""""\\""\n", Parameter_Name, Parameter_Symbol, 
	    Par_AVE[i], Confidence_Interval[i][0], Confidence_Interval[i][1]);
  }

  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  fprintf(fp, "\\smallskip\n");

  fprintf(fp, "\\end{tabular}\n");
  //fprintf(fp, "\\vspace{1cm}\n");
  fprintf(fp, "\\noindent");

  fprintf(fp, "{\\bf Table 1:} Malaria model parameters. Legend: {\\small H: Human, M: Mosquito, L: Larva, P: {\\em Plasmodium}, R: Rain, T: Temperature, $T_e$: Effective temperature, $(T_i - T_o)= %g^{oC}$: Maximum difference between indoors and outdoors temperature}\n", P->R_T.TEMP__SHIFT);

  fprintf(fp, "\\end{table}\n");
  fclose(fp);
}

void write_Param_Table_Default_Values( char * table_Param, Parameter_Table * P, 
				       int no_Par )
{
  int i, k;
  Parameter_Space * S = P->S;
  FILE *fp = fopen( table_Param, "w" );
  char Parameter_Name[100];
  char Parameter_Symbol[50];
  double value;
  //int no_Par_Default = 11;
  //int Index[11] = {1, 3, 4, 5, 6, 9, 10, 13, 48, 49, 30}; 
  //int no_Par_Default = 3;
  //int Index[4] = {1, 48, 49}; 

  fprintf(fp, "\\begin{table}\n");
  fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\begin{tabular}{lcc}\n");  
  fprintf(fp, "{\\bf Model Parameter} & {\\bf Symbol} & {\\bf Value}""\\""""\\""\n"); 
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  
  for ( i = 0; i < no_Par; i++){

    k = S->I[i];
    
    value = AssignStructValue_to_VectorEntry(k, P);

    AssignLabel_to_Parameters__LATEX(k , Parameter_Name, P);

    AssignLabel_to_Parameters__LATEX__SYMBOL(k , Parameter_Symbol, P);
    
    fprintf(fp, "%s & %s & %g""\\""""\\""\n", Parameter_Name, Parameter_Symbol, value);
  }

  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  fprintf(fp, "\\smallskip\n");

  fprintf(fp, "\\end{tabular}""\\""""\\""\n");
  
  //fprintf(fp, "\\vspace{1cm}\n");
  
  fprintf(fp, "\\noindent");
 
  fprintf(fp, "{\\bf Table 1:} Malaria model parameters. Legend: {\\small H: Human, M: Mosquito, L: Larva, P: {\\em Plasmodium}}\n");
  
//fprintf(fp, "{\\bf Table 1:} Malaria model parameters. Legend: {\\small H: Human, M: Mosquito, L: Larva, P: {\\em Plasmodium}, R: Rain, T: Temperature, $T_e$: Effective temperature, $T_i - T_o$: Maximum difference between indoors and outdoors temperature}\n");
  
  fprintf(fp, "\\end{table}\n");
  fclose(fp);
}

void write_Param_Table(Parameter_Table *P)
{ 
  double I;
  FILE *fp = fopen("tableParam.tex", "w");
  
  
  /* Biting intensity per human at beta = P->H_Beta */
  I = (P->H_Beta + sqrt(P->H_Beta*P->H_Beta + 4.*P->H_Beta*P->M_b))/2.;

  /* Writing a parameter structure into latex table */
  /* Begin Table environment */
  
  fprintf(fp, "\\begin{table}\n");
  fprintf(fp, "\\noindent\n");
  fprintf(fp, "\\begin{tabular}{lccc}\n");  
  fprintf(fp, "{\\bf Model Parameter} & {\\bf Definition} & {\\bf Key} & {\\bf Value}""\\""""\\""\n"); 
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");

  fprintf(fp, "Human Parameters:&&""\\""""\\""\n"); 
  fprintf(fp, "Force of infection at equilibrium         &{\\small $\\beta$}  &-H0 & %g""\\""""\\""\n", P->H_Beta);
  fprintf(fp, "Per capita birth rate (balancing natural deaths)     &{\\small $\\frac{B}{N}$}  &-H1 & %g""\\""""\\""\n", P->H_Birth);
  fprintf(fp, "Per capita death rate (natural mortality)            &{\\small $\\delta_H$}  &-H2 & %g""\\""""\\""\n", P->H_Delta);
  fprintf(fp, "Average life time (days)              &{\\small $\\tau$}  &--- & %g""\\""""\\""\n", 1./P->H_Delta);
  fprintf(fp, "Average life time (years)             &{\\small $\\tau$}  &--- & %g""\\""""\\""\n", 1./P->H_Delta/365.);
  fprintf(fp, "Loss of immunity rate (day$^{-1}$, at $\\beta=0$)    &{\\small $\\sigma_0$}  &-H3 & %g""\\""""\\""\n", P->H_Sigma_0); 
  fprintf(fp, "Loss of immunity typical time (years, at $\\beta=0$)   &{\\small $\\frac{1}{\\sigma_0}$}  &--- & %g""\\""""\\""\n", 1./P->H_Sigma_0/365.); 
  fprintf(fp, "Loss of immunity typical time (years, at steady-state)  &{\\small $\\frac{1}{\\sigma}$}  &--- & %g""\\""""\\""\n", 1./P->H_Sigma/365.); 
  fprintf(fp, "Recovery rate (day$^{-1}$, at at $\\beta=0$)            &{\\small $r_0$}  &-H4 & %g""\\""""\\""\n", P->H_Recov_0);
  fprintf(fp, "Average recovery time (years, at $\\beta=0$)           &{\\small $\\frac{1}{r_0}$}  &--- & %g""\\""""\\""\n", 1./P->H_Recov_0/365.); 
  fprintf(fp, "Average recovery time (years, at steady-state)         &{\\small $\\frac{1}{r}$}  &--- & %g""\\""""\\""\n", 1./P->H_Recov/365.); 
  
  fprintf(fp, "Number of latent classes (for $E$)   &{\\small $n_H$}  &-H5 & %d""\\""""\\""\n", P->n_H);
  fprintf(fp, "Typical latent time (days) &{\\small $\\frac{1}{\\gamma_H}$}  &-H6  & %g""\\""""\\""\n", 1./P->H_Gamma);
  fprintf(fp, "Standard deviation around the average(days) &{\\small $\\sigma_H$}  &---& %g""\\""""\\""\n", sqrt(1./(P->n_H * P->H_Gamma * P->H_Gamma)));
  fprintf(fp, "\\hline\n");

  fprintf(fp, "Parameters controling clinical malaria:&&""\\""""\\""\n");
  fprintf(fp, "Clinical Case Probability from $C$    &{\\small $\\xi$}  &-C0  & %g""\\""""\\""\n", P->H_Xhi);
  
  fprintf(fp, "Clinical Case Probability form $I$    &{\\small $\\eta$}  &-C2  & %g""\\""""\\""\n", P->H_Eta);
  
  fprintf(fp, "Recovery rate under treatment to $S$  &{\\small $\\rho$}  &-C1 & %g""\\""""\\""\n", P->H_Rho);
  
  fprintf(fp, "Recovery rate under treatment to $I$  &{\\small $\\nu$}  &-C3 & %g""\\""""\\""\n", P->H_Nu);  
  
  fprintf(fp, "\\hline\n");

  fprintf(fp, "Adult mosquito parameters:&&""\\""""\\""\n");
  fprintf(fp, "Biting rate                              &{\\small $a$}  &-M0 & %g""\\""""\\""\n", P->M_a);
  fprintf(fp, "Critical biting intensity (day$^{-1}$)               &{\\small $b_c$}  &-M1 & %g""\\""""\\""\n", P->M_b);
  fprintf(fp, "Biting intensity (day$^{-1}$, at steady-state)         &{\\small $b$}  &--- & %g""\\""""\\""\n", I);
  fprintf(fp, "Infectivity (human to mosquitoes)        &{\\small $c$}  &-M2 & %g""\\""""\\""\n", P->M_c);
  fprintf(fp, "Average life time of mosquitoes (days) &{\\small $\\frac{1}{\\delta_M}$}  &-M3 & %g""\\""""\\""\n", 1./P->M_Delta);
  fprintf(fp, "Fecundity in larves per adult and day    &{\\small $f$}  &-M4 & %g""\\""""\\""\n", P->M_Fecundity); 
  fprintf(fp, "\\hline\n");
  
  fprintf(fp, "Larva mosquito parameters:&&""\\""""\\""\n");
  fprintf(fp, "Average development time (days)       &{\\small $\\frac{1}{d_L}$ }  &-L0 & %g""\\""""\\""\n", 1./P->L_Devel); 
  fprintf(fp, "Avarage life time (days)              &{\\small $\\frac{1}{\\delta_L}$ }  &-L1 & %g""\\""""\\""\n", 1./P->L_Delta);
  /* Seasonal forcing */
  fprintf(fp, "Average larva carrying capacity          &{\\small $K$}  &-L2 & %g""\\""""\\""\n", P->K_0);
  fprintf(fp, "Stardard deviation around the average    &{\\small $\\sigma_K$}  &-L3 & %g""\\""""\\""\n", P->K_Sigma);  
  fprintf(fp, "Seasonal period (in years)&{\\small $T$}  &-L4 & %g""\\""""\\""\n", 1./P->K_Period*365.);
  fprintf(fp, "Seasonal Forcing Intesity, $(0<s<1)$     &{\\small $s$}  &-L5 & %g""\\""""\\""\n", P->K_Seasonal_Intensity);
  fprintf(fp, "\\hline\n");

  fprintf(fp, "{\\em Plasmodium} related parameters:&&""\\""""\\""\n");
  fprintf(fp, "Number of mosquito latent class ({\\em Plasmodium})  &{\\small $n_P$}  &-P0 & %d""\\""""\\""\n", P->n_V);        
  fprintf(fp, "Average development time (days, {\\em Plasmodium}) &{\\small $\\frac{1}{\\gamma_P}$}  &-P1 & %g""\\""""\\""\n", 1./P->M_Gamma);     
  fprintf(fp, "Standard deviation around this average (days)      &{\\small $\\sigma_P$}  &-P2 & %g""\\""""\\""\n", sqrt(1./(P->n_V * P->M_Gamma * P->M_Gamma)));
  fprintf(fp, "\\hline");
  fprintf(fp, "\\hline\n");
  fprintf(fp, "\\smallskip\n");

  fprintf(fp, "\\end{tabular}\n");
  fprintf(fp, "\\vspace{1cm}\n");
  fprintf(fp, "\\noindent");
  fprintf(fp, "{\\bf Table 1: {\\Large Malaria model parameters.}}\n");
  fprintf(fp, "\\end{table}\n");
  fclose(fp);
}
