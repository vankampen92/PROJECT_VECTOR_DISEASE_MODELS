#include "../Include/MODEL.h"

extern gsl_rng * r;

#define PRINTING_MORE_INFORMATION_OUT
#define DATA_SUPPLEMENTATION

void setting_proper_daily_time(Parameter_Table *P, int N)
{
  /* N, Number of year in the time series */
  int i,j,k;
  double time_0, any;
  int mo[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  int bi[12]={31,29,31,30,31,30,31,31,30,31,30,31};

  /* BEGIN: Day month correspondence */
  P->R_T.DDMM[0].day   = 0.0;
  P->R_T.DDMM[0].month = 0.0;
  time_0               = P->R_T.Time[0];

  int time_Days_Accumulation = 0;
  int time_Days = 0;

  for ( i = 0; i < N; i++ ){
    
    j = i%12;
    
    any = floor ( (double)i/12.0 + time_0 );
    
    if( ((int)any-1968)%4 == 0) {
      
      for(k = 0; k<bi[j]; k++){
	
	time_Days ++;
	
	P->R_T.DDMM[time_Days].day   = (double)time_Days;
	P->R_T.DDMM[time_Days].month = (double)j;

      }
      
    }
    else{
      
      for(k = 0; k<mo[j]; k++){
      
	time_Days ++;
	
	P->R_T.DDMM[time_Days].day   = (double)time_Days;
	P->R_T.DDMM[time_Days].month = (double)j;
	
      }
    } 
  }
  
  printf(" T o t a l   n u m b e r   o f   d a y s :   %d\n", time_Days);

  P->R_T.Total_No_of_Days = time_Days;

  P->R_T.Year[0] = time_0; /* Usually, 1970.0 */
 
  time_Days_Accumulation = 0.0;

  P->R_T.Days[0] = time_Days_Accumulation;  

  /* time_Days_Accumulation is neccessary for
     exact numerical integration on a  daily basis */

  for ( i = 0; i < N; i++ ){

    j = i%12;
    
    if ( i%12 == 0 ){ 
      time_Days = 0.0;
    }
    
    any = floor ( i/12 + time_0 );

    if( ((int)any-1968)%4 == 0) {
      
      time_Days              += (double)bi[j];
      P->R_T.Year[i+1] = any + time_Days/366.0;

      time_Days_Accumulation += (double)bi[j];
      P->R_T.Days[i+1] = time_Days_Accumulation; 
    }
    else{

      time_Days += (double)mo[j]; 
      P->R_T.Year[i+1] = any + time_Days/365.0;

      time_Days_Accumulation += (double)mo[j];
      P->R_T.Days[i+1] = time_Days_Accumulation;
    }
  }
  
  printf(" Time has been set successfully...\n");

}

/* void pre_processing_daily_Rain(char * File_to_Read, Parameter_Table * P, int N) */
/* { */
/*   int any, i,j,k, time_Days, time_Days_0, time_Days_1, N_Data_File; */
/*   double x,y,time_0; */
/*   FILE * fp; */
/*   int mo[12]={31,28,31,30,31,30,31,31,30,31,30,31}; */
/*   int bi[12]={31,29,31,30,31,30,31,31,30,31,30,31}; */
/*   char month[12][4]={"GEN", "FEB", "MAR", "ABR", "MAY", "JUN", "JUL", "AUG", "SET", "OCT", "NOV", "DEC"}; */
  
/*   double *** rain_dia_month = (double ***)malloc( 7 * sizeof(double **) ); */
/*   for (j = 0; j<7; j++){     */
/*     rain_dia_month[j] = (double **)malloc( 12 * sizeof(double *) ); */
/*     for( i = 0; i < 12; i++) { */
/*       rain_dia_month[j][i] = (double *)calloc( bi[i], sizeof(double) ); */
/*     } */
/*   } */

/*   /\* BEGIN : Reading rainfall data from ../../../rainHailDaily_RawData.dat.  */
/*      From JUL 1973 to DEC 1979  */
/*   *\/ */
/*   fp = fopen(File_to_Read, "r"); */
/*   if (fp == NULL) { */
/*     printf(" File %s does not exist in specified path\n", File_to_Read); */
/*     printf(" The program will exit\n"); */
/*     exit(0); */
/*   } */
/*   P->R_T.DDMM[0].rain  = 0.0;  */
/*   /\* The files starts the first of July of 1973 *\/ */
/*   time_Days_0 = 365 + 365 + 366 + 31 + 28 + 31 + 30 + 31 + 30; */
/*   time_Days   = time_Days_0; */
  
/*   N_Data_File = N - 42;   /\* There are 42 moths of missing data  */
/* 			     (from GEN 1970 to JUN 1973). */
/* 			     GEN 1975 and ABR 1976 also missing. */
/* 			     They were replaced by GEN 1980 and  */
/* 			     ABR 1980, respectively. */
/* 			  *\/ */
/*   int any_0 = 1973;       /\* Starting year in the data file: */
/* 			     ../../../rainHailDaily_RawData.dat */
/* 			  *\/ */

/*   for(i = 0; i < N_Data_File; i++) { */
/*     /\* Each line or row represents the i-th month of  */
/*        the data set *\/ */
    
/*     fscanf(fp, "%lf\t%lf\t", &x, &y); */
/*     j = (int)y - 1; */

/*     any = (int)x - any_0; */

/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/*     printf("ANY: %d\t%g\t%g\tMonth: %s\t", any, x,y, month[j]); Press_Key(); */
/* //#endif */

/*     if( ((int)x-1968)%4 == 0 ) { */

/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	printf("Number of days: %d\n", bi[j]); */
/* //#endif */
/*       for(k = 0; k<bi[j]; k++){ */
	
/* 	time_Days ++; */
	
/* 	if( k < (bi[j]-1) ){  */
/* 	  fscanf(fp, "%lf\t", &x); */

/* //#if defined PRINTING_MORE_INFORMATION_OUT	   */
/* 	  printf("%g\t", x); */
/* //#endif        */
/* 	} */
/* 	else{  */
/* 	  fscanf(fp, "%lf\n", &x);  */

/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	  printf("%g\n", x);  */
/* //#endif       */
/* 	} */

/* 	P->R_T.DDMM[time_Days].rain  = x; */

/* 	rain_dia_month[any][j][k]    = x;   */

/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	printf("RAIN[any--month--dia] = RAIN[%d--%d--%d] = %g\n",  */
/* 	       any,j,k, rain_dia_month[any][j][k]); */
/* //#endif */
/*       } */
/*     } */
/*     else{ */
   
/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	printf("Number of days: %d\n", mo[j]); */
/* //#endif      */
/* 	for(k = 0; k<mo[j]; k++){ */

/* 	  time_Days ++; */
	  
/* 	  if( k < (mo[j]-1) ){  */
/* 	    fscanf(fp, "%lf\t", &x);  */

/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	    printf("%g\t", x);        */
/* //#endif */
/* 	  } */
/* 	  else{  */
/* 	    fscanf(fp, "%lf\n", &x);  */

/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	    printf("%g\n", x);        */
/* //#endif */
/* 	  } */
	  
/* 	  P->R_T.DDMM[time_Days].rain  = x; */
	  
/* 	  rain_dia_month[any][j][k] = x; */
	  
/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	  printf("RAIN[any--month--dia] = RAIN[%d--%d--%d] = %g\n",  */
/* 		 any,j,k, rain_dia_month[any][j][k]); */
/* //#endif */
/* 	} */
/*     } */
/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/*     Press_Key(); */
/* //#endif */
/*   } */
/*   /\* END   : Reading file * * * * * * * * * * * * * * * * * * * * * * *\/ */

/*   time_Days_1 = time_Days; */

/* //#if defined DATA_SUPPLEMENTATION */
/*   /\* BEGIN : Climatic Pseudo Data Supplementation for years 1970, 1971 and */
/*      1972 until JUN 1973 inclusive *\/ */
/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/*   printf("  Entering pseudo data generation to fill missing data\n");  */
/*   printf("  4 2  i n i t i a l   m i s s i n g   m o n t h s !  "); Press_Key(0); */
/* //#endif */

/*   time_0               = P->R_T.Time[0]; */
/*   time_Days            = 0; */
/*   for( i = 0; i < 42; i++){ */

/*     j = i%12; */
/*     any = (int) floor ( (double)i/12.0 + time_0 ); */
   
/*     if( (any-1968)%4 == 0) { */
      
/*       for(k = 0; k<bi[j]; k++){ */
	
/* 	time_Days ++; */

/* 	any = 1 + gsl_rng_uniform_int (r, 5); //random year between 1 and */
/* 	                                      //6, both inclusively;  */
/* 	x = rain_dia_month[any][j][k]; */

/* 	P->R_T.DDMM[time_Days].rain  = x; */

/* 	if( k < (bi[j]-1) ){  */
/* 	  //fscanf(fp, "%lf\t", &x); */

/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	  printf("%g\t", x);        */
/* //#endif  */
/* 	}               */
/* 	else{  */
/* 	  // fscanf(fp, "%lf\n", &x); */

/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	    printf("%g\n", x); */
/* //#endif */
/* 	} */
/*       }       */
/*     } */
/*     else{ */
      
/*       for(k = 0; k<mo[j]; k++){ */
      
/* 	time_Days ++; */

/* 	any = 1 + gsl_rng_uniform_int (r, 5); //random year between 1 and */
/* 	                                      //6, both inclusively;  */
/* 	x = rain_dia_month[any][j][k]; */
	
/* 	P->R_T.DDMM[time_Days].rain  = x; */
	
/* 	if( k < (mo[j]-1) ){ */
 
/* 	  //fscanf(fp, "%lf\t", &x);  */
	  
/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	  printf("%g\t", x);  */
/* //#endif */
/* 	} */
/* 	else{ */

/* 	  //fscanf(fp, "%lf\n", &x); */

/* //#if defined PRINTING_MORE_INFORMATION_OUT */
/* 	  printf("%g\n", x); */
/* //#endif */
/* 	} */
/*       } */
/*     }  */
/*   } */
/*   /\* END   : Pseudo Data: completing missing data in data file *\/ */
/* //#endif //[corresponing to defined variable DATA_SUPPLEMENTATION] */

/* //#if defined PRINTING_MORE_INFORMATION_OUT   */
/*   /\* BEGIN : Checking artificially generated data *\/ */
/*   printf(" Printing the whole structure R_T->DDMM containing Day - Month - Rain data... "); Press_Key(); */
/*   printf(" [ Day  ---  Month  ---  Rain ] = \n");  */
/*   for( i = 0; i <= time_Days_0; i++){ */
/*     printf(" [ Day: %g --- Month: %g --- Rain: %g]\n",  */
/* 	   P->R_T.DDMM[i].day, P->R_T.DDMM[i].month, P->R_T.DDMM[i].rain); */
/*   } */
/*   Press_Key(); */
/*   printf(" [ Day  ---  Month  ---  Rain ] = \n");  */
/*   for( i = time_Days_0+1; i <= time_Days_1; i++){ */
/*     printf(" [ Day: %g --- Month: %g --- Rain: %g]\n",  */
/* 	   P->R_T.DDMM[i].day, P->R_T.DDMM[i].month, P->R_T.DDMM[i].rain); */
/*   } */
/*   printf("Checking has been done successfully... "); Press_Key(); */
/*   /\*   END : Checking reading *\/ */
  
/*   /\* BEGIN : Data saving in rainHailDaily_Data.dat *\/ */
/*   fp = fopen("rainHailDaily_Data.dat", "w"); */
/*   time_Days = 0; */
/*   time_0    = P->R_T.Time[0]; */

/*   for(i = 0; i < N; i++) { /\* N month - N rows in file *\/ */

/*     j = i%12; */
    
/*     any = floor ( (double)i/12.0 + time_0 ); */
/*     x   = (double)j + 1.0; */

/*     fprintf(fp, "%g\t%g\t", (double)any, x); */
    
/*     if( ((int)any-1968)%4 == 0) { */
      
/*       for(k = 0; k<bi[j]; k++){ */
	
/* 	time_Days ++; */
	
/* 	x = P->R_T.DDMM[time_Days].rain; */

/* 	if( k < (bi[j]-1) ){  */
/* 	  fprintf(fp, "%g\t", x); */
/* 	} */
/* 	else{  */
/* 	  fprintf(fp, "%g\n", x);  */
/* 	}	 */

/*       } */
      
/*     } */
/*     else{ */
      
/*       for(k = 0; k<mo[j]; k++){ */
      
/* 	time_Days ++; */
	
/* 	x = P->R_T.DDMM[time_Days].rain; */

/* 	if( k < (mo[j]-1) ){  */
/* 	  fprintf(fp, "%g\t", x); */
/* 	} */
/* 	else{  */
/* 	  fprintf(fp, "%g\n", x);  */
/* 	} */

/*       } */
/*     }   */
/*   } */
/*   /\*   END : Data saving in rainHailDaily_Data.dat *\/ */
/*   fclose(fp); */
/*   printf("Saving file ""rainHailDaily_Data.dat"" has been done successfully... "); Press_Key(); */
/* //#endif  */
  
/*   /\* BEGIN : Careful memory de-allocation *\/ */
/*   for (j = 0; j < 7; j++){ */
/*     for( i = 1; i < 12; i++) { free (rain_dia_month[j][i]); } */
/*     free( rain_dia_month[j] ); */
/*   } */
/*   free (rain_dia_month); */
/*   /\*  END : Careful memory de-allocation *\/ */
/* } */

