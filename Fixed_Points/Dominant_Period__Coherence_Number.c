#include <MODEL.h>

void dominant_Eigenvalue( float * l_re, float * l_im, int n, 
			  float * D_re, float * D_im)
{
  float l_re_MAX;
  int i, i_MAX;

  l_re_MAX = l_re[1];  i_MAX= 1;

  for(i = 1; i<= n; i++) {
   
    l_re_MAX = MAX (l_re_MAX, l_re[i] );
   
    if(l_re_MAX == l_re[i]){ 
      i_MAX = i;
    }
  }

  (* D_re) = l_re[i_MAX];
  (* D_im) = l_im[i_MAX];

}

double Dominant_Period__Coherence_Number( float *l_re, float *l_im, int n, double * coherence_Number, int Sub_Dominant )
{
  double Dominant_Period, Relaxation_Time;
  float D_re;
  float D_im;

  if(Sub_Dominant == 1){

    Dominant_Period = characteristic_Times__Coherence_No (l_re, l_im, n, 
							  coherence_Number );
  }
  else if (Sub_Dominant == 0) {

     dominant_Eigenvalue( l_re, l_im, n, &D_re, &D_im);

     Dominant_Period = 2.*M_PI/fabs( (double)D_im );
      
     Relaxation_Time = -1./(double)D_re;
      
      ( * coherence_Number ) = Relaxation_Time/Dominant_Period;
      
     Dominant_Period  = Dominant_Period/360.0;   /* Dominant period expressed in year units */
     
  }
  else {
    /* The program should never pass trough here by logic construction */
    printf(" Message from Dominant_Period__Coherence_Number.c\n");
    int showing = showing_eigenValues(l_re, l_im, n); 
    printf(" Press any key to continue.../n"); getchar();
    exit(0);
  }

  return(Dominant_Period);
}


