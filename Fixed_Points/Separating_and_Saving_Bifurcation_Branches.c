#include <MODEL.h>

void Separating_Bifurcation_Branches ( double Epsilon,
				       double * x_Data,
				       double * y_LOWER, double * y_INTER, double * y_UPPER,
				       int No_of_POINTS, 				    
				       double * x_Lower, double * y_Lower, int * N_Lower, 
				       double * x_Inter, double * y_Inter, int * N_Inter, 
				       double * x_Upper, double * y_Upper, int * N_Upper)
{
  int i;
  int n_Lower, n_Upper, n_Inter;
  int Branch_Type, Branch_Type_Previous, Intermediate_Branch;
  int i_Intermediate_0, i_Intermediate_1;
  
  int * Intermediate = (int *)calloc( No_of_POINTS, sizeof(int) ); 
 
  n_Inter = 0;
  Branch_Type = 0; Branch_Type_Previous = 0; 
  for(i=0; i < No_of_POINTS; i++) {
    
    Branch_Type = Determining_Intermediate_Branch ( Epsilon, 
						    y_LOWER[i], y_INTER[i], y_UPPER[i] );
    if (Branch_Type == 1){
      if (Branch_Type == 1 && Branch_Type_Previous == 0) {
	i_Intermediate_0 = i;
	Branch_Type_Previous = Branch_Type;
      }
      /* Inter... */
      x_Inter[n_Inter] = x_Data[i]; y_Inter[n_Inter] = y_INTER[i];
      
      Intermediate[i]  = 1;
      n_Inter++;
    }
  }
  i_Intermediate_1 = i_Intermediate_0 + n_Inter - 1;

  n_Lower = 0;   n_Upper = 0; Intermediate_Branch = 0;
  for(i=0; i < No_of_POINTS; i++) {
    
    if ( Intermediate[i] == 0 ){
      /* There is only one branch */
      if ( Intermediate_Branch == 0 ) {
	if( y_LOWER[0] < y_LOWER[No_of_POINTS-1] ){
	  x_Lower[n_Lower] = x_Data[i]; y_Lower[n_Lower] = y_LOWER[i];
	  n_Lower++;
	}
	else {
	  x_Upper[n_Upper] = x_Data[i]; y_Upper[n_Upper] = y_UPPER[i];
	  n_Upper++;
	}
      }
      else {
	if( y_LOWER[0] < y_LOWER[No_of_POINTS-1] ){
	  x_Upper[n_Upper] = x_Data[i]; y_Upper[n_Upper] = y_UPPER[i];
	  n_Upper++;
	}
	else {
	  x_Lower[n_Lower] = x_Data[i]; y_Lower[n_Lower] = y_LOWER[i];
	  n_Lower++;
	}
      }
    }
    else {
      /* There are upper and lower braches */
     	
      x_Lower[n_Lower] = x_Data[i]; y_Lower[n_Lower] = y_LOWER[i];
      n_Lower++;
      
      x_Upper[n_Upper] = x_Data[i]; y_Upper[n_Upper] = y_UPPER[i];
      n_Upper++;
      
      Intermediate_Branch = 1;
    }
  }

  * N_Lower = n_Lower;
  * N_Inter = n_Inter;
  * N_Upper = n_Upper; 
  
  free(Intermediate);
}

int Determining_Intermediate_Branch ( double Epsilon, 
				      double y_LOWER, double y_INTER, double y_UPPER )
{
  int Branch_Type;

  if ( X_apx_Y( y_LOWER, y_INTER, Epsilon ) == 0 && X_apx_Y( y_LOWER, y_UPPER, Epsilon ) == 0 ){
    /* Existence of Intermediate Branch is True */
    Branch_Type = 1;   
  }
  else {
    /* At this point only a sinble branch (upper or lower) exist */
    Branch_Type = 0;   
  }

  return(Branch_Type);
}

void Saving_Bifurcation_Files( char * Bifurcation,
			       int Bifurcation_Parameter, 
			       double * x_LOWER, double * y_LOWER, int No_of_POINTS_LOWER,
			       double * x_INTER, double * y_INTER, int No_of_POINTS_INTER,
			       double * x_UPPER, double * y_UPPER, int No_of_POINTS_UPPER,
			       int Output_Variable )
{
  int i;
  char file[100]; 
  FILE *fp;
  
  /* BEGIN: Saving Lower branch */
     file[0]='\0';    
     fitxer(file, Bifurcation, Output_Variable, "_LOWER");
     fitxer(file, "_Bifurcation_Parameter_", Bifurcation_Parameter, ".dat");
     printf("Saving file %s\n",file);
     fp = fopen(file, "w");
     for(i=0; i < No_of_POINTS_LOWER; i++)
       fprintf( fp,"%g\t%g\n", x_LOWER[i], y_LOWER[i] );
     fclose(fp);
  /*    END: Saving Lower branch */

  /* BEGIN: Saving Inter branch */
     file[0]='\0';    
     fitxer(file, Bifurcation, Output_Variable, "_INTER");
     fitxer(file, "_Bifurcation_Parameter_", Bifurcation_Parameter, ".dat");
     printf("Saving file %s\n",file);
     fp = fopen(file, "w");
     for(i=0; i < No_of_POINTS_INTER; i++)
       fprintf( fp,"%g\t%g\n", x_INTER[i], y_INTER[i] );
     fclose(fp);
  /*    END: Saving Inter branch */

  /* BEGIN: Saving Upper branch */
     file[0]='\0';    
     fitxer(file, Bifurcation, Output_Variable, "_UPPER");
     fitxer(file, "_Bifurcation_Parameter_", Bifurcation_Parameter, ".dat");
     printf("Saving file %s\n",file);
     fp = fopen(file, "w");
     for(i=0; i < No_of_POINTS_UPPER; i++)
       fprintf( fp,"%g\t%g\n", x_UPPER[i], y_UPPER[i] );
     fclose(fp);
  /*    END: Saving Upper branch */
}
