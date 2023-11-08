#include <MODEL.h>

double Type_of_Stability_of_Equilibria( float *l_re, float *l_im, int n, int Sub_Dominant )
{
  double Type_of_Stability;

  if(Sub_Dominant == 1){
    Type_of_Stability = Type_of_Stability_of_Equilibria_Subdominant( l_re, l_im, n );
  }
  else if (Sub_Dominant == 0) {
    Type_of_Stability = Type_of_Stability_of_Equilibria_Dominant( l_re, l_im, n );
  }
  else {
    /* The program should never pass trough here by logic construction */
    printf(" Message from Type_of_Stability_of_Equilibria.c\n");
    int showing = showing_eigenValues(l_re, l_im, n); 
    printf(" Press any key to continue.../n"); getchar();
    exit(0);
  }

  return(Type_of_Stability);
}

double Type_of_Stability_of_Equilibria_Dominant( float *l_re, float *l_im, int n )
{
  /* 
     l = (l_re[i],  l_im[i]), where l is the complex valued eigenvalue a given 
     matrix. 
  */
  /* Only three possible return values:
     1.0 : Unstable equilibrium 
     2.0 : Stable equilibrium 
           presenting "stable node" type of stability
     3.0 : Stable equilibrium 
           presenting "damped oscillations" type of stability 
  */
  float l_re_MAX, l_im_MAX;

  dominant_Eigenvalue( l_re, l_im, n, &l_re_MAX, &l_im_MAX ); 
			 
  if( l_re_MAX >= 0.0 ) {
    /* 1.0 : Unstable equilibrium. Notice that if l_re_MAX = 0, then 
       that eigen value is associated to neutral stability 
    */
    return (1.0);
  }
  else if ( l_im_MAX  == 0.0 ) {
    /* 2.0 : Stable equilibrium 
           presenting "stable node" type of stability
    */
    return (2.0);
  }
  else {
    /* 3.0 : Stable equilibrium 
           presenting "damped oscillations" type of stability 
    */
    return (3.0);
  }
}

double Type_of_Stability_of_Equilibria_Subdominant( float *l_re, float *l_im, int n )
{
  /* Only three possible return values:
     1.0 : Unstable endemic equilibrium 
     3.0 : Stable equilibrium (with one neutral mode) 
           presenting "stable node" type of stability
     4.0 : Stable equilibrium (with one neutral mode) 
           presenting "damped oscillations" type of stability 
  */
  int i, i_nul, i_dominant; 
  float l_re_min, l_re_MAX, l_re_NUL;
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
  
  /*   i_dominant defines the mode corresponding to the eigenvector
       whose eigenvalue has the largest real part (discounting
       the eigenvalue corresponding to the neutral mode).            */
  /*   END: Sub-dominant mode calculation                            */

  if ( l_re_MAX >= 0.0 ) {
    /* Unstable endemic equilibrium  */
    printf(" l_re_SUB_DOMINANT = %g\n l_re_NUL = %g\n", l_re_MAX, l_re_NUL);
    return( 1.0 );
  }
  else if ( l_re_MAX < 0.0 ) {

    if ( l_im[i_dominant] == 0.0) {
      /* Stable equilibrium (with one neutral mode) 
	 presenting "stable node" type of stability 
      */
      return ( 2.0 );
    }
    else {
      /* Stable equilibrium (with one neutral mode) 
	 presenting "damped oscillations" type of stability 
      */
      return ( 3.0 );
    }
    
  }
  else {
    /* The program should never pass trough here by logic construction */
    printf(" Message from Type_of_Stability_of_Equilibria.c:\n");
    printf(" Function:\n");
    printf(" double Type_of_Stability_of_Equilibria_Subdominant( float * l_re,\n");
    printf("                                                     float *l_im,\n");
    printf("                                                     n )\n");
    printf(" The program should never pass through here by logic construction\n");
    printf(" l_re_SUB_NUL = %g\n l_re_NUL = %g\n", l_re_MAX, l_re_NUL);
    int showing = showing_eigenValues(l_re, l_im, n); 
    printf(" Press any key to continue.../n"); getchar();
    exit(0);
  }
}
