#include <MODEL.h>

double Maximum_Lag_Correlation_double_Vector_Annual(double * y_0, double * y_1, int N)
{
  /* This code calculates the maximum correlation between two time series across
     increasing time lags */
  /* The first third of the two series is rejected to get rid of possible transients */
  /* The other 2/3 are used, and only a number of lags between 0 and 1/3 of N is 
     considered to calculate the maximum */
  /* In this "Annual" version the two series are accummulated every 12 points, which 
     represent 12 months. */
  int L, n, i, j, k, l;
  double corr, max_corr;
  double accum_0, accum_1;
  
  double AVE_0, VAR_0; 
  double AVE_1, VAR_1;

  n = (int)( (double)N/3.0 );

  double * y_std_0 = (double *)calloc( N, sizeof(double) );
  double * y_std_1 = (double *)calloc( N, sizeof(double) );

  /* BEGIN : Descarting the 1/3 of the time series to get rid of
             possible transients
  */
  j = 0;
  for(i = 0; i<N; i++) {
    if( i > n) {
      y_std_0[j] = y_0[i];
      y_std_1[j] = y_1[i];
      j++;
    }
  }
  L = j; /* Length of stardarized vectors */
  /*   END : End of descarting */
  
  double * y_acc_0 = (double *)calloc( N, sizeof(double) );
  double * y_acc_1 = (double *)calloc( N, sizeof(double) );
  
  /* BEGIN : Accumulation in 12 moths */
  int Y = L/12; 

#if defined VERBOSE  
  printf( "Number of Years: %d\n", Y);
  Press_Key();
#endif

  for( j = 0; j<Y; j++) {
    accum_0 = 0.0;
    accum_1 = 0.0;
    for (i = 12*j; i < 12*(j+1); i++) {
      accum_0 += y_std_0[i];
      accum_1 += y_std_1[i];
    }
    y_acc_0[j] = accum_0;
    y_acc_1[j] = accum_1;
  }
  /*  END : Accumulation              */
  free( y_std_0 ); free ( y_std_1 ); 

  double * y_lag_1 = (double *)calloc( N, sizeof(double) );

  n = (int)( (double)Y/2.0 ); // No of Lags

  max_corr = 0.0;
  for( j = 0; j < n; j++ ){
    
    if( n + j < Y ){
      for(l = 0; l<(Y-j); l++) {y_lag_1[l] = y_acc_1[l+j]; }

      Average_and_Variance_double_Vector(y_acc_0, Y-j, &AVE_0, &VAR_0 );
      Average_and_Variance_double_Vector(y_lag_1, Y-j, &AVE_1, &VAR_1 );
    }
  
    corr    = 0.0; k = 0;
    for(i = 0; i < Y; i++) {

      if( i + j < Y ){
	corr += (y_acc_0[ i ] - AVE_0) * (y_lag_1[ i ] - AVE_1);
	k++;
      }
    }
    corr  /= (double)k; 
    
    if( VAR_0 != 0.0 && VAR_1 != 0.0 ) corr  /= sqrt(VAR_0 * VAR_1);

    max_corr = MAX( corr, max_corr );
  }

  free( y_acc_0 ); free ( y_acc_1 ); free( y_lag_1 );
  
  return(max_corr);
}

double Maximum_Lag_Correlation_double_Vector(double * y_0, double * y_1, int N, 
                                             double * std_var, int * max_LAG )
{
  /* This code calculates the maximum correlation between two time series across
     increasing time lags */

  /* The output of this function gives a correlation either standarizing by the
     two variances:

        1. corr  /= sqrt(VAR_0 * VAR_1);  ( True correlation )
	
     or, just by one variance:            ( Standarized covariance )

    	2. corr  /= sqrt(VAR_0);

   */ 

  /* The first third of the two series is dimissed to get rid of possible transients */
  /* The other 2/3 are used, and only a number of lags between 0 and 1/3 of N is 
     considered to calculate the maximum */

  int L, n, i, j, k, l;
  double corr, correlation, max_corr;
  double max_var, covariance;
  int max_lag;
  
  double AVE_0, VAR_0; 
  double AVE_1, VAR_1;

  n = (int)( (double)N/3.0 );

  double * y_std_0 = (double *)calloc( N, sizeof(double) );
  double * y_std_1 = (double *)calloc( N, sizeof(double) );
  double * y_lag_1 = (double *)calloc( N, sizeof(double) );

  /* BEGIN : Descarting the 1/3 of the time series to get rid of
             possible transients
  */
  j = 0;
  for(i = 0; i<N; i++) {
    if( i > n) {
      y_std_0[j] = y_0[i];// - AVE_0)/sqrt(VAR_0);
      y_std_1[j] = y_1[i];// - AVE_1)/sqrt(VAR_1);
      j++;
    }
  }
  L = j; /* Length of stardarized vectors */
  /*   END : End of descarting */

  max_corr = 0.0; max_lag = 0; max_var = 0.0;
  for( j = 0; j < n; j++ ){
    
    if( n + j < L ){
      
      for(l = 0; l<(L-j); l++) {y_lag_1[l] = y_std_1[l+j]; }
      
      Average_and_Variance_double_Vector(y_std_0, L-j, &AVE_0, &VAR_0 );
      Average_and_Variance_double_Vector(y_lag_1, L-j, &AVE_1, &VAR_1 );
    }
  
    corr    = 0.0; k = 0;
    for(i = 0; i < L; i++) {

      if( i + j < L ){
	corr += (y_std_0[ i ] - AVE_0) * (y_lag_1[ i ] - AVE_1);
	//corr += y_std_0[ i ] * y_std_1[ i + j ];
	k++;
      }
    }
    corr  /= (double)k; 
    
    correlation  = corr / sqrt(VAR_0 * VAR_1);

    covariance   = corr / sqrt(VAR_0);

    if( correlation > max_corr ) { max_lag = j; }

    max_corr = MAX( correlation, max_corr );
	
    max_var  = MAX( covariance, max_var );
  }
  
  free( y_std_0 ); free ( y_std_1 ); free( y_lag_1 );

  ( * std_var ) = max_var; 	
  ( * max_LAG ) = max_lag; 
 
  return (max_corr);
}

