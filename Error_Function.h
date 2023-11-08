typedef struct Parameter_Table_Root_Solverinfo
{

  gsl_function * f;
  double      r;

}Parameter_Table_Root_Solver;


double M_E_A_S_U_R_E_M_E_N_T___E_R_R_O_R___F_U_N_C_T_I_O_N (gsl_rng * r, Parameter_Table * P,  double y);

double my_Density_Function (double x, void * params);

double Cummulative_Density_Function( double x_lo, double x_hi, gsl_function * Density_Function );

double Cummulative_Distribution_Function( double x, gsl_function * Density_Function );

double Function_Root_Solver( double x, void * p );

double da_gsl_ran_continuous_Function( const gsl_rng * r, gsl_function * Density_Function, int i, int N );


