int saving_eigenValues(FILE *fp, float *l_re, float *l_im, int n);

int showing_eigenValues(float *l_re, float *l_im, int n);

int fprintf_to_File_Matrix_gsl(FILE * Out, gsl_matrix * A, int MM, int NN);

int gsl_matrix_to_NR_matrix(gsl_matrix * A, float **a,  int MM, int NN);

double characteristic_Times( float *l_re, float *l_im, int n, int LABEL );

double characteristic_Times__Coherence_No( float *l_re, float *l_im, int n, 
					   double * Coherence_No );

double subdominant_Eigenvalue( float *l_re, float *l_im, int n );

double coherence_Number(float *l_re, float *l_im, int n);

double damped_Oscillation_Function(Parameter_Table *P, int NO, int W, double EPSILON);

void eigenVectors_Function(Parameter_Table *P, int NO, int W, double EPSILON, 
			   float **mm, float *l_re, float *l_im);
