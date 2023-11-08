#include "../Include/MODEL.h"

extern gsl_rng * r;

//#define PRINT_OUT
#define DATA_SUPPLEMENTATION
#define DATA_BLANK_FILLING

void processing_Daily_Rain_Hail_File(char * File_to_Read, Parameter_Table * P, int N)
{
  /* This function process a specific file 'rainhailDaily_RawDat.dat',
     check for missing data and completes the file furnishing those
     months with no avaiable data.

     As an output a corrected file 'rainDaily.dat' is saved. 
  */     
  int  missing_month(int j, int any);
  int any, any_random, MISSING;
  int i,j,k,l,l_0, time_Days, time_Days_0, time_Days_1, N_Data_File;
  double x,y,time_0;
  FILE * fp;
  int year[4] = { -2, -1, 1, 2 };
  int mo[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  int bi[12]={31,29,31,30,31,30,31,31,30,31,30,31};
  char month[12][4]={"GEN", "FEB", "MAR", "ABR", "MAY", "JUN", "JUL", "AUG", "SET", "OCT", "NOV", "DEC"};
  int MAX_YEAR;

  /* The first 7 years (1973-1979) are used to fill the initial
     missing months corresponding to the years: 1970-1972.
     IMPORTANT: There is a maximum of 35 years of data to be read.
  */

  MAX_YEAR = (int)ceil((double)N/12.0); // N / 12: N is the number of
					// moths, which, when divided by 12
					// months a year, produces MAX_YEAR

  double *** rain_dia_month = (double ***)malloc( MAX_YEAR * sizeof(double **) );
  for (j = 0; j < MAX_YEAR; j++){    
    rain_dia_month[j] = (double **)malloc( 12 * sizeof(double *) );
    for( i = 0; i < 12; i++) {

      rain_dia_month[j][i] = (double *)calloc( bi[i], sizeof(double) );
    }
  }

  /* Data in rainhailDaily_RawDat.dat are fake because missing months
     have been provisionally filled with dummy data. Those data
     will be rewritten with a sampling of daily data from the two
     immediately previous and the two immediately posterior years.
  */

  /* BEGIN : Reading rainfall data from ../../../rainHailDaily_RawData.dat. 
     From JUL 1973 to DEC 1979 
  */
  fp = fopen(File_to_Read, "r");
  if (fp == NULL) {
    printf(" File %s does not exist with the specified path.\n", File_to_Read);
    printf(" The program will exit.\n");
    exit(0);
  }
  P->R_T.DDMM[0].rain  = 0.0; 
  /* The files starts the first of July of 1973 */
  time_Days_0 = 365 + 365 + 366 + 31 + 28 + 31 + 30 + 31 + 30;
  time_Days   = time_Days_0;
  
  N_Data_File = N - 42;   /* There are 42 initial months of missing data: 
			     from GEN 1970 to JUN 1973.

			     ### Missing data have been filled provisionally with data from previous or posterior years:
			     ### GEN 1975 ---> GEN 1980 [1975 0]
			     ### 
			     ### ABR 1976 ---> APR 1980 [1976 3]
			     ###
			     ### FEB 1986 ---> FEB 1985 [1986 1] 
			     ### MAR 1986 ---> MAR 1985 [1986 2]
			     ### APR 1986 ---> APR 1995 [1986 3]
			     ### JUN 1986 ---> JUN 1985 [1986 5]
			     ###
			     ### JUL 1989 ---> JUL 1988 [1989 6]
			     ###
			     ### FEB 1991 ---> FEB 1989 [1991 1]
			     ### JUN 1991 ---> JUN 1990 [1991 5]
			     ###
			     ### MAR 1993 ---> MAR 1992 [1993 2]
			     ###
			     ### AUG 1995 ---> AUG 1995 [1995 7]
			     ### OCT 1995 ---> OCT 1995 [1995 9]
			     ###
			     ### DEC 2004 ---> DEC 2003 [2004 11]
			  */

  int any_0 = 1973;       /* Starting year in the data file:
			     ../../../rainHailDaily_RawData.dat
			  */

  for(i = 0; i < N_Data_File; i++) {
    /* Each line or row represents the i-th month of 
       the data set */
    
    fscanf(fp, "%lf\t%lf\t", &x, &y);
    j = (int)y - 1;

    any = (int)x - any_0;

#if defined PRINT_OUT
    printf("ANY: %d\t%g\t%g\tMonth: %s\t", any, x,y, month[j]);
#endif

    if( ((int)x-1968)%4 == 0 ) {

#if defined PRINT_OUT
	printf("Number of days: %d\n", bi[j]);
#endif
      for(k = 0; k<bi[j]; k++){
	
	time_Days ++;
	
	if( k < (bi[j]-1) ){ 
	  fscanf(fp, "%lf\t", &x);

#if defined PRINT_OUT	  
	  printf("%g\t", x);
#endif       
	}
	else{ 
	  fscanf(fp, "%lf\n", &x); 

#if defined PRINT_OUT
	  printf("%g\n", x); 
#endif      
	}

	P->R_T.DDMM[time_Days].rain  = x;

	rain_dia_month[any][j][k]    = x;  

#if defined PRINT_OUT
	printf("RAIN[any--month--dia] = RAIN[%d--%d--%d] = %g\n", 
	       any,j+1,k+1, rain_dia_month[any][j][k]);
#endif
      }
    }
    else{
   
#if defined PRINT_OUT
	printf("Number of days: %d\n", mo[j]);
#endif     
	for(k = 0; k<mo[j]; k++){

	  time_Days ++;
	  
	  if( k < (mo[j]-1) ){ 
	    fscanf(fp, "%lf\t", &x); 

#if defined PRINT_OUT
	    printf("%g\t", x);       
#endif
	  }
	  else{ 
	    fscanf(fp, "%lf\n", &x); 

#if defined PRINT_OUT
	    printf("%g\n", x);       
#endif
	  }
	  
	  P->R_T.DDMM[time_Days].rain  = x;
	  
	  rain_dia_month[any][j][k] = x;
	  
#if defined PRINT_OUT
	  printf("RAIN[any--month--dia] = RAIN[%d--%d--%d] = %g\n", 
		 any,j+1,k+1, rain_dia_month[any][j][k]);
#endif
	}
    }
#if defined PRINT_OUT
    //Press_Key(0);
#endif
  }
  /* END   : Reading file * * * * * * * * * * * * * * * * * * * * * * */

  time_Days_1 = time_Days;


#if defined DATA_BLANK_FILLING

  printf(" F i l l i n g   m i s s i n g   d a t a . . . \n");
  printf(" S i n g l e   m i s s i n g   m o n t h s ... \n");

#if defined PRINT_OUT
  Press_Key();
#endif

  time_Days   = time_Days_0;

  for(i = 0; i < N_Data_File; i++) {
    /* Each line or row represents the i-th month of 
       the data set */
    j = (i+6)%12;   /* ... because first data month is not JAN 1973, 
		       but JUL 1973
		    */
    any = (int) floor ( (double)i/12.0 + any_0 );
    
    MISSING = missing_month(j, any); /* This returns 0 if (j, any) is
					not a missing month and 1
					otherwise
				     */
    if( (any-1968)%4 == 0) {
      
      for(k = 0; k<bi[j]; k++){
	
	time_Days ++;

	if (MISSING == 1) { /* Filling with a randomly sampled day */
	
	  any_random = gsl_rng_uniform_int (r, 3);
	  l   = any - any_0 + year[any_random];
	  l_0 = any - any_0; 
	  
#if defined PRINT_OUT
	  printf( "Missing month...\n");
	  printf("RAIN[any--month--dia] = RAIN[%d--%d--%d] = %g\n", 
		 any,j+1,k+1, rain_dia_month[l_0][j][k]);
	  Press_Key();
#endif

	  if( k == 28 && j == 1) {
	    /* This corresponds to the last day of FEB of a year where FEB has 29 days 
	     */	    
	    P->R_T.DDMM[time_Days].rain  = rain_dia_month[l][j][k-1];
	    
	    rain_dia_month[l_0][j][k]    = rain_dia_month[l][j][k-1];  
	  }
	  else{
	    
	    P->R_T.DDMM[time_Days].rain  = rain_dia_month[l][j][k];
	    
	    rain_dia_month[l_0][j][k]    = rain_dia_month[l][j][k];  
	  }
	}
      }
    }
    else{
      
      for(k = 0; k<mo[j]; k++){
      
	time_Days ++;

	if (MISSING == 1) { /* Filling with a randomly sampled day */

#if defined PRINT_OUT
	  printf( "Missing month... YEAR %d MONTH %d DAY %d\n", any, j, k);

	  printf("RAIN[any--month--dia] = RAIN[%d--%d--%d] = %g\n", 
		 any,j+1,k+1, rain_dia_month[l_0][j][k]);
	  Press_Key();
#endif

	   any_random = gsl_rng_uniform_int (r, 3);
	   l = any - any_0 + year[any_random];
	   l_0 = any - any_0; 

	   P->R_T.DDMM[time_Days].rain  = rain_dia_month[l][j][k];
	   
	   rain_dia_month[l_0][j][k]    = rain_dia_month[l][j][k];  
	
	}
      }
    }
  }
#endif 

#if defined DATA_SUPPLEMENTATION

  /* BEGIN : Climatic Pseudo Data Supplementation for years 1970, 1971 and
     1972 until JUN 1973 inclusive */
#if defined PRINT_OUT
  printf("  Entering pseudo data generation to fill initial missing data:\n");
  printf("  1970-1971-1972-GEN to JUN 1973.\n"); 
  printf("  4 2  i n i t i a l   m i s s i n g   m o n t h s !  "); Press_Key(0);
#endif

  time_0               = P->R_T.Time[0];
  time_Days            = 0;
  for( i = 0; i < 42; i++){

    j = i%12;
    any = (int) floor ( (double)i/12.0 + time_0 );
   
    if( (any-1968)%4 == 0) {
      
      for(k = 0; k<bi[j]; k++){
	
	time_Days ++;

	any = 1 + gsl_rng_uniform_int (r, 5); //random year between 1 and
	                                      //6, both inclusively
	                                      //(Notice that 1973,
	                                      //which is the first
	                                      //year with actual data,
	                                      //is not complete) 
	x = rain_dia_month[any][j][k];

	P->R_T.DDMM[time_Days].rain  = x;

#if defined PRINT_OUT
	if( k < (bi[j]-1) ){ 
	  //fscanf(fp, "%lf\t", &x);

	  printf("%g\t", x);       
	}              
	else{ 
	  //fscanf(fp, "%lf\n", &x);
	    printf("%g\n", x);
	}
#endif

      }      
    }
    else{
      
      for(k = 0; k<mo[j]; k++){
      
	time_Days ++;

	any = 1 + gsl_rng_uniform_int (r, 5); //random year between 1 and
	                                      //6, both inclusively; 
	x = rain_dia_month[any][j][k];
	
	P->R_T.DDMM[time_Days].rain  = x;
	
#if defined PRINT_OUT
	if( k < (mo[j]-1) ){ 
	  //fscanf(fp, "%lf\t", 
	  printf("%g\t", x); 
	}
	else{
	  //fscanf(fp, "%lf\n", &x);
	  printf("%g\n", x);
	}
#endif

      }
    } 
  }
  /* END   : Pseudo Data: completing missing data in data file */
#endif //[corresponing to defined variable DATA_SUPPLEMENTATION]

#if defined PRINT_OUT  
  /* BEGIN : Checking artificially generated data */
  printf(" Printing the whole structure R_T->DDMM containing Day - Month - Rain data... "); Press_Key();
  printf(" [ Day  ---  Monty  ---  Rain ] = \n"); 
  for( i = 0; i <= time_Days_0; i++){
    printf(" [ Day: %g --- Month: %g --- Rain: %g]\n", 
	   P->R_T.DDMM[i].day, P->R_T.DDMM[i].month, P->R_T.DDMM[i].rain);
  }
  Press_Key();
  printf(" [ Day  ---  Monty  ---  Rain ] = \n"); 
  for( i = time_Days_0+1; i <= time_Days_1; i++){
    printf(" [ Day: %g --- Month: %g --- Rain: %g]\n", 
	   P->R_T.DDMM[i].day, P->R_T.DDMM[i].month, P->R_T.DDMM[i].rain);
  }
  printf("Checking has been done successfully... "); Press_Key();
  /*   END : Checking reading */
  
  /* BEGIN : Data saving in rainHailDaily_Data.dat */
  fp = fopen("rainHailDaily_Data.dat", "w");
  time_Days = 0;
  time_0    = P->R_T.Time[0];
  for(i = 0; i < N; i++) { /* N month - N rows in file */

    j = i%12;
    
    any = floor ( (double)i/12.0 + time_0 );
    x   = (double)j + 1.0;

    fprintf(fp, "%g\t%g\t", (double)any, x);
    
    if( ((int)any-1968)%4 == 0) {
      
      for(k = 0; k<bi[j]; k++){
	
	time_Days ++;
	
	x = P->R_T.DDMM[time_Days].rain;

	if( k < (bi[j]-1) ){ 
	  fprintf(fp, "%g\t", x);
	}
	else{ 
	  fprintf(fp, "%g\n", x); 
	}	

      }
      
    }
    else{
      
      for(k = 0; k<mo[j]; k++){
     

	time_Days ++;
	
	x = P->R_T.DDMM[time_Days].rain;

	if( k < (mo[j]-1) ){ 
	  fprintf(fp, "%g\t", x);
	}
	else{ 
	  fprintf(fp, "%g\n", x); 
	}

      }
    }
  }
  /*   END : Data saving in rainHailDaily_Data.dat */
  fclose(fp);
  printf("Saving file ""rainHailDaily_Data.dat"" has been done successfully... "); Press_Key();
#endif 
  
  /* BEGIN : Careful memory de-allocation */
  for (j = 0; j < MAX_YEAR; j++){

    for( i = 1; i < 12; i++) { free (rain_dia_month[j][i]); }

    free( rain_dia_month[j] );
  }

  free (rain_dia_month);

  /*  END : Careful memory de-allocation */
}

int  missing_month(int j, int any)
{
  
  // Missing data have been filled provisionally with data from previous or posterior years:
	
		     // GEN 1975 ---> GEN 1980 [1975 0]
                     // 
                     // ABR 1976 ---> APR 1980 [1976 3]
		     //
		     // FEB 1986 ---> FEB 1985 [1986 1] 
		     // MAR 1986 ---> MAR 1985 [1986 2]
	             // APR 1986 ---> APR 1995 [1986 3]
	     	     // JUN 1986 ---> JUN 1985 [1986 5]
	       	     //
	       	     // JUL 1989 ---> JUL 1988 [1989 6]
	       	     //
	       	     // FEB 1991 ---> FEB 1989 [1991 1]
	       	     // JUN 1991 ---> JUN 1990 [1991 5]
	       	     //
	       	     // MAR 1993 ---> MAR 1992 [1993 2]
	       	     //
	       	     // AUG 1995 ---> AUG 1995 [1995 7]
	       	     // OCT 1995 ---> OCT 1995 [1995 9]
	       	     //
	       	     // DEC 2004 ---> DEC 2003 [2004 11]

  /* This returns 0 if (j, any) is  not a missing month and 1
     otherwise. The first month is not counted and it has 
     previosly filled in manually.
  */
  int i, m;
 
  int month[11] = {3, 1, 2, 3, 5, 6, 1, 5, 2, 7, 9};
  int years[11] = {1976, 1986, 1986, 1986, 1986, 1989, 1991, 1991, 1993, 1995, 1995};

  m = 0;

  for( i = 0; i < 11; i++ ){
    if( month[i] == j && years[i] == any){
      m = 1;
    }
  }
  
  return (m);
}
