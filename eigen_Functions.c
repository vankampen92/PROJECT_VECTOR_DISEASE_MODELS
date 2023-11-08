#include <MODEL.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

#define DYNAMIC___VERBOSE

int saving_eigenValues(FILE *fp, float *l_re, float *l_im, int n)
{
  int i;
  
  for(i=1; i<=n; i++){
    fprintf(fp, "%f\t%f\n", l_re[i], l_im[i]);
  }
  
  return(0);
}

int showing_eigenValues(float *l_re, float *l_im, int n)
{
  int i;
  
  for(i=1; i<=n; i++){
    printf("( %f ) + i( %f )\n", l_re[i], l_im[i]);
  }
  
  return(0);
}

int fprintf_to_File_Matrix_gsl(FILE * Out, gsl_matrix * A, int MM, int NN)
{
  int i,j;
  for (i=0;i<MM;i++){
    for (j=0;j<NN;j++){
      fprintf(Out,"%g\t",gsl_matrix_get(A,i,j));
    }
    fprintf(Out,"\n");
  }
  fprintf(Out,"\n");
  return 0;
}

int gsl_matrix_to_NR_matrix(gsl_matrix * A, float **a,  int MM, int NN)
{
  /* Utility to transform a gsl matrix into a numerical recipes float matrix */
  int i,j;
  for (i=1;i<=MM;i++){
    for (j=1;j<=NN;j++){
      a[i][j] = (float)gsl_matrix_get(A,i-1,j-1);
    }
  }
  return 0;
}

double coherence_Number(float *l_re, float *l_im, int n)
  {
    /* coherence Number */
  int i;
  double Max_Coherence_No, Coherence_No;
  
  Max_Coherence_No = 0.;
  for(i=1; i <= n; i++){
    if (l_im[i] > 0){
      Coherence_No = -1./(double)l_re[i]/2./ M_PI * (double)l_im[i];
      Max_Coherence_No = MAX(Coherence_No, Max_Coherence_No);
    }
  }
  return(Max_Coherence_No);
}

double damped_Oscillation_Function(Parameter_Table *P, int NO, int W, double EPSILON)
{
  /* If NO = 0, dominat Period is the output */
  /* If NO = 1, the coherence number is the output */
  double dominant_Period, coherence_No;
  int gsl_to_NR;
  float **mm;   
  float *l_re;
  float *l_im;
  
  gsl_vector * y_Sol = gsl_vector_alloc(W+1);
  fixed_Points(P, y_Sol->data, EPSILON);
  /* Calculating the Jacobian at the Fixed Point */
  gsl_matrix * m = gsl_matrix_alloc(W+1, W+1);
  /* Evaluating the Jacobian at the fixed points... */
  evaluating_JACOBIAN_Matrix(m, y_Sol->data, 0., W, P);
  gsl_vector_free(y_Sol);

  mm = matrix(1,W+1, 1,W+1);
  l_re = vector(1, W+1);
  l_im = vector(1, W+1); 
  
  gsl_to_NR = gsl_matrix_to_NR_matrix(m, mm, W+1, W+1);
  gsl_matrix_free(m);  
  /*
  printf("\nInitial Jacobian Matrix...\n");
  show_a_view_FloatMatrix(mm, 1, W+1, 1, W+1);
  Press_Key();
  */
  balanc(mm, W+1); 
  /*
  printf("Balaced Jacobian Matrix...\n");
  show_a_view_FloatMatrix(mm, 1, W+1, 1, W+1);
  Press_Key();
  */
  elmhes(mm, W+1);
  /*
  printf("Corresponding Hessenberg Form of the Jacobian Matrix...\n");
  show_a_view_FloatMatrix(mm, 1, W+1, 1, W+1);
  Press_Key();
  */
  hqr(mm, W+1, l_re, l_im);
  /*
  printf("Eigen Values ...\n");
  int showing = showing_eigenValues(l_re, l_im, W+1);
  */
  dominant_Period = characteristic_Times(l_re, l_im, W+1, 0);
  coherence_No = characteristic_Times(l_re, l_im, W+1, 1); 

  free_vector(l_im, 1,W+1);
  free_vector(l_re, 1,W+1);
  free_matrix(mm, 1,W+1, 1,W+1); 
  
  if(NO == 0)
    return(dominant_Period);
  else if(NO == 1)
    return(coherence_No);
  else{
    printf ("Error in function damped_Oscillation_Function()\n");
    exit(0);
  }
}

void eigenVectors_Function(Parameter_Table *P, int NO, int W, double EPSILON, 
			   float **mm, float *l_re, float *l_im)
{
  /* If NO = 0, dominat Period is the output        */
  /* If NO = 1, the coherence number is the output  */
  double dominant_Period, coherence_No;
  int gsl_to_NR;

  /* Calculating the Jacobian at the fixed point    */
  /* and evaluating the Jacobian at the fixed point */

  gsl_vector * y_Sol = gsl_vector_alloc(W+1);
  fixed_Points(P, y_Sol->data, EPSILON);
  gsl_matrix * m = gsl_matrix_calloc(W+1, W+1);
  evaluating_JACOBIAN_Matrix(m, y_Sol->data, 0., W, P); 
  gsl_to_NR = gsl_matrix_to_NR_matrix(m, mm, W+1, W+1);
  gsl_matrix_free(m);
  
  balanc(mm, W+1);  
  elmhes(mm, W+1);
  hqr(mm, W+1, l_re, l_im);
  
  printf("Eigen Values ...\n");
  int showing = showing_eigenValues(l_re, l_im, W+1);

  gsl_vector_free(y_Sol);
  
}

double characteristic_Times_BACKUP(float *l_re, float *l_im, int n, int LABEL)
{
  /* Dominant characteristic time in years if LABEL is 0 */
  /* Associated coherence number if LABEL is 1           */

  int i, i_min, i_dominant; 
  float l_re_min;
  double Coherence_No, Max_Coherence_No; 
  double Max_Period, Period, Relaxation_Time, Max_Relaxation_Time;
  int count, count_Im;
  
  //float * abs_real_part = (float *)malloc( n * sizeof( float) );

  float * abs_real_part = vector(1, n);  
  
  l_re_min = fabs( l_re[1] );  i_min    = 1;

  for(i = 1; i<= n; i++) {
    abs_real_part[i] = fabs( l_re[i] );
    l_re_min = MIN(l_re_min, abs_real_part[i]);
    if(l_re_min == abs_real_part[i]){ 
      i_min = i;
    }
  }
  
  count = 0; count_Im = 0; i_dominant = 1;
  Max_Period = 0.; Max_Relaxation_Time = 0.; Max_Coherence_No = 0.;
  for(i = 1; i <= n; i++){
    if( i != i_min) {
      
      if(l_re[i] < 0){
	count++;

	if (l_im[i] != 0){
	  count_Im++;
	  
	  Period = 2.*M_PI/fabs((double)l_im[i]);
	  
	  Relaxation_Time = -1./(double)l_re[i];

	  Coherence_No = Relaxation_Time/Period;
	  
	    if(Relaxation_Time > Max_Relaxation_Time){
	      Max_Period = Period;
	      Max_Relaxation_Time = Relaxation_Time;
	      Max_Coherence_No = Coherence_No;
	      i_dominant = i;
	    }
	  
	}
      }

    }
  }

  free_vector(abs_real_part, 1, n);
  
  if (count == (n-1) && fabs(l_im[i_dominant]) > 0.0){
    printf("stability   ");

    if ( LABEL == 0 ){
      /* Returning typical period (year units) */
      return(Max_Period/365.);
    }
    else if ( LABEL == 1 ) {
      return(Max_Coherence_No);
    }
    else{
      printf(" LABEL failed in double characteristic_Times( ... ) from eigen_Functions.c\n");
      printf(" The program will exit\n");
      exit(0);
    }

  }
  else if (count == (n-1) && fabs(l_im[i_dominant]) == 0.0){
    printf("NODE stable ");
    return(0.0);
  }
  else{
    printf("UNSTABILITY ");
    return(-1.0);
  }
}

double characteristic_Times( float *l_re, float *l_im, int n, int LABEL )
{
  /* Dominant characteristic time in years if LABEL is 0 */
  /* Associated coherence number if LABEL is 1           */

  int i, i_nul, i_dominant; 
  float l_re_min, l_re_MAX, l_re_NUL;
  double Coherence_No, Max_Coherence_No; 
  double Max_Period, Period, Relaxation_Time, Max_Relaxation_Time;
  int count, count_Im;
  
  /* BEGIN: Nul mode calculation */
  l_re_min = fabsf( l_re[1] );  i_nul    = 1;
  for(i = 1; i<= n; i++) {
    l_re_min = MIN( l_re_min, fabsf(l_re[i]) );
    if(l_re_min == fabsf(l_re[i]) ){ 
      i_nul = i;
    }
  }
  /*   END: Nul mode calculation */
  l_re_NUL = l_re[i_nul];
  l_re_MAX = l_re_NUL;

  /* All real parts may be negative but the real part associated 
     to the i_nul eigenvector, which is zero by model construction.  
     i_min defines the neutral mode. Since the main model is defined 
     at a constant human population, there is always a mode around
     which perturbations are neutral. By model definition, there will 
     be always an nul eigenvalue */

  /* BEGIN: Sub-dominant mode calculation */
  i = 1; i_dominant = 1;
  while( i <= n && l_re_MAX == l_re_NUL ) l_re_MAX = l_re[i++];
  for(i = 1; i <= n; i++){
    if( i != i_nul) {
      l_re_MAX = MAX(l_re_MAX, l_re[i]);
      if(l_re_MAX == l_re[i]){ 
	i_dominant = i;
      }
    }
  }
  /* i_dominant defines the mode corresponding to the eigenvector
     whose eigenvalue has the largest real part (discounting
     the eigenvalue corresponding to the neutral mode). */
  /*   END: Sub-dominant mode calculation */

  if ( l_re_MAX >= 0.0 ) {
    /* Unstable endemic equilibrium  */
    printf(" l_re_SUB_DOMINANT = %g\n l_re_NUL = %g\n", l_re_MAX, l_re_NUL);
    return( 0.0 );
  }
  else if ( l_re_MAX < 0.0 ) {

    if ( l_im[i_dominant] == 0.0) {
      /* Stable equilibrium (with one neutral mode) 
	 presenting "stable node" type of stability 
      */
      return ( 0.0 );
    }
    else {
      /* Stable equilibrium (with one neutral mode) 
	 presenting "damped oscillations" type of stability 
      */
      Period = 2.*M_PI/fabs((double)l_im[i_dominant]);
      
      Relaxation_Time = -1./(double)l_re[i_dominant];
      
      Coherence_No = Relaxation_Time/Period;
      
      Max_Period   = Period/365.0; /* Dominant period expressed in year units */
      
      if( LABEL == 0 ) {
	return( Max_Period );
      }
      else {
	return( Coherence_No );
      }
    }
  }
  else {
      /* Logic makes this condition impossible. Program will exit!!!  
       */
    printf(" l_re_SUB_NUL = %g\n l_re_NUL = %g\n", l_re_MAX, l_re_NUL);
    int showing = showing_eigenValues(l_re, l_im, n); Press_Key();
    exit(0);
  }
}

double characteristic_Times__Coherence_No( float *l_re, float *l_im, int n, 
					   double * Coherence_No )
{
  /* Dominant characteristic time in years if LABEL is 0 */
  /* Associated coherence number if LABEL is 1           */

  int i, i_nul, i_dominant; 
  float l_re_min, l_re_MAX, l_re_NUL;
  double Max_Period, Period, Relaxation_Time, Max_Relaxation_Time;
  int count, count_Im;
  
  /* BEGIN: Nul mode calculation */
  l_re_min = fabsf( l_re[1] );  i_nul    = 1;
  for(i = 1; i<= n; i++) {
    l_re_min = MIN( l_re_min, fabsf(l_re[i]) );
    if(l_re_min == fabsf(l_re[i]) ){ 
      i_nul = i;
    }
  }
  /*   END: Nul mode calculation */
  l_re_NUL = l_re[i_nul];
  l_re_MAX = l_re_NUL;

  /* All real parts may be negative but the real part associated 
     to the i_nul eigenvector, which should be zero by model construction.  
     i_min defines the neutral mode. Since the main model is defined 
     at a constant human population, there is always a mode around
     which perturbations are neutral. By model definition, there will 
     be always an nul eigenvalue */

  /* BEGIN: Sub-dominant mode calculation */
  i = 1; i_dominant = 1;
  while( i <= n && l_re_MAX == l_re_NUL ) l_re_MAX = l_re[i++];
  for(i = 1; i <= n; i++){
    if( i != i_nul) {
      l_re_MAX = MAX(l_re_MAX, l_re[i]);
      if(l_re_MAX == l_re[i]){ 
	i_dominant = i;
      }
    }
  }
  /* i_dominant defines the mode corresponding to the eigenvector
     whose eigenvalue has the largest real part (discounting
     the eigenvalue corresponding to the neutral mode). */
  /*   END: Sub-dominant mode calculation */

  if ( l_re_MAX >= 0.0 ) {
    /* Unstable endemic equilibrium  */
    printf(" l_re_SUB_DOMINANT = %g\t l_re_NUL = %g\n", l_re_MAX, l_re_NUL);
    
    return( 0.0 );
  }
  else if ( l_re_MAX < 0.0 ) {
            
#if defined PERIOD
    if ( l_im[i_dominant] == 0.0) {
      /* Stable equilibrium (with one neutral mode) 
	 presenting "stable node" type of stability 
      */
      return ( 0.0 );
    }
    else {
      /* Stable equilibrium (with one neutral mode) 
	 presenting "damped oscillations" type of stability 
      */
      Period = 2.*M_PI/fabs((double)l_im[i_dominant]);
      
      Relaxation_Time = -1./(double)l_re[i_dominant];
      
      ( * Coherence_No ) = Relaxation_Time/Period;
      
      Max_Period   = Period/365.0; /* Dominant period expressed in year units */
   
      return(Max_Period);
    }
#endif      
#if defined EIGENVALUE
    ( * Coherence_No ) = 0.0;
    printf(" Dominant Eigenvalue (real part): %g\t Dominant Eigenvalue (imaginary part): %g\n", 
	   (double)l_re[i_dominant], (double)l_im[i_dominant]);

    return( -(double)l_re[i_dominant] );
#endif 

  }
  else {
      /* Logic makes this condition impossible. Program will exit!!!  
       */
    printf(" l_re_SUB_NUL = %g\n l_re_NUL = %g\n", l_re_MAX, l_re_NUL);
    int showing = showing_eigenValues(l_re, l_im, n); Press_Key();
    exit(0);
  }
}

double subdominant_Eigenvalue( float *l_re, float *l_im, int n )
{
  /* Subdominant eigenvalue calculation */

  int i, i_nul, i_dominant; 
  float l_re_min, l_re_MAX, l_re_NUL;
  double value;
  int count, count_Im;
  
  /* BEGIN: Nul mode calculation */
  l_re_min = fabsf( l_re[1] );  i_nul    = 1;
  for(i = 1; i<= n; i++) {
    l_re_min = MIN( l_re_min, fabsf(l_re[i]) );
    if(l_re_min == fabsf(l_re[i]) ){ 
      i_nul = i;
    }
  }
  /*   END: Nul mode calculation */
  l_re_NUL = l_re[i_nul];
  l_re_MAX = l_re_NUL;

  /* All real parts may be negative but the real part associated 
     to the i_nul eigenvector, which is zero by model construction.  
     i_min defines the neutral mode. Since the main model is defined 
     at a constant human population, there is always a mode around
     which perturbations are neutral. By model definition, there will 
     be always an nul eigenvalue */

  /* BEGIN: Sub-dominant mode calculation */
  i = 1; i_dominant = 1;
  while( i <= n && l_re_MAX == l_re_NUL ) l_re_MAX = l_re[i++];
  for(i = 1; i <= n; i++){
    if( i != i_nul) {
      l_re_MAX = MAX(l_re_MAX, l_re[i]);
      if(l_re_MAX == l_re[i]){ 
	i_dominant = i;
      }
    }
  }
  /* i_dominant defines the mode corresponding to the eigenvector
     whose eigenvalue has the largest real part (discounting
     the eigenvalue corresponding to the neutral mode). */
  /*   END: Sub-dominant mode calculation */
  
  value = (double)l_re[i_dominant];

  return(value);
}

double Well_Defined_Matrix_Elements(float **mm, int N, float xmin, float xmax)
{
  /* 
     xmin and xmax are the largest and tiniest float representation
     of a number the machine can handle without producing overflow.
     Out of this range overflow is returned. 
     
     This function assesses whether all elements in matrix mm
     fall within this range and therefore they are all number
     representations the machine will be able to handle without 
     giving neither further problems nor surprises.
  */
  int i,j, count;
  double x;
  
  x = 0.0; 
  count = 0;
  
  for(i=1; i<=N; i++){
    for(j=1; j<=N; j++){
      
      if ( mm[i][j] != 0.0 ) {
	//if(mm[i][j] < xmax && fabsf( mm[i][j] ) >= xmin ){
	if(mm[i][j] < xmax && fabsf( mm[i][j] ) >= 0.0 ){
	  count++;	
#if defined DYNAMIC___VERBOSE
	  printf("Matrix element: A(%d, %d) = %g\n", i,j, mm[i][j]);
#endif
	}
	else{
#if defined DYNAMIC___VERBOSE
	  printf("Ill-defiend matrix element: A(%d, %d) = %g\n", i,j, mm[i][j]);
#endif
	}
      }
      else {
	count++;
#if defined DYNAMIC___VERBOSE
	printf("Nul matrix element: A(%d, %d) = %g\n", i,j, mm[i][j]);
#endif
      }
    }						
  }
  
  if(count == N * N) 
    x = 1.0;
  else
    x = 0.0;

#if defined DYNAMIC___VERBOSE 
  printf("count = %d\t Matrix dimension (N) = %d\t N * N = %d\n", count, N, N*N);
#endif

  return(x);
}
