#include "./Include/MODEL.h"

/*  Note on an example of how to call this function:

   int S_; int E_; int I_; int R_; int C_;
   int L_; int X_; int U_; int W_; int A_;
   int K_;
   M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E ( P,
                                             &S_, &E_, &I_, &R_, &C_,
					     &L_, &X_, &U_, &W_, &A_,
					     &K_);
*/

void M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (Parameter_Table * P,
					      int * S, int * E, int * I, int * R, int * C,
								int * S1, int * I1, int * S2, int * I2, int * S3, int * I3,
					      int * L, int * X, int * U, int * W, int * A,
					      int * K)
{
  int TYPE_of_MODEL = P->TYPE_of_MODEL;

  switch( TYPE_of_MODEL )
    {
   /* CASES_1 models * * * * * * * * * * * * * * * * * * * * * * */
   case 11: /* CASES_1-LXVnW */
      S_E_I_R_C___L_X_U_W___C_O_D_E_S( P,
					 S, E, I, R, C, L, X, U, W );
      (* A) = (* W);
      (* K) = (* W);
      break;
   case 12: /* CASES_1-XkVnW */
      S_E_I_R_C___L_X_U_W___C_O_D_E_S( P,
					 S, E, I, R, C, L, X, U, W );
      /* Mosquito codes */
      (* X) = (*C ) + 1;     /************************/ /* X  */
      (* U) = (*C ) + 2;    /************************/  /* U, first latent mosquito class */
      (* W) = (*C ) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;
   case 13: /* CASES_1-XVnW */
      S_E_I_R_C___L_X_U_W___C_O_D_E_S( P,
				       S, E, I, R, C,  L, X, U, W );

      /* Mosquito codes */
      (* X) = (* C) + 1;     /************************/                 /* X  */
      (* U) = (* C) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* C) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;
   case 14: /* CASES_1-XW */
      S_E_I_R_C___L_X_U_W___C_O_D_E_S( P,
				       S, E, I, R, C,  L, X, U, W );

      assert(P->n_V == 0);
      /* Mosquito codes */
      (* X) = (* C) + 1;     /************************/                 /* X  */
      (* U) = (* C) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* C) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;

   /* NO_CASES models * * * * * * * * * * * * * * * * * * * * * * */
   case 21: /* NO_CASES-LXVnW */
      S_E_I_R___L_X_U_W___C_O_D_E_S( P,
					 S, E, I, R,  L, X, U, W );
      (* C) = (* R); /* Last human class */

      (* A) = (* W);
      (* K) = (* W);
      break;
   case 22: /* NO_CASES-XkVnW */
      S_E_I_R___L_X_U_W___C_O_D_E_S( P,
					 S, E, I, R,  L, X, U, W );
      (* C) = (* R); /* Last human class */

      /* Mosquito codes */
      (* X) = (* R) + 1;     /************************/                 /* X  */
      (* U) = (* R) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* R) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;
   case 23: /* NO_CASES-XVnW */
      S_E_I_R___L_X_U_W___C_O_D_E_S( P,
				       S, E, I, R,  L, X, U, W );
      (* C) = (* R); /* Last human class */

      /* Mosquito codes */
      (* X) = (* R) + 1;     /************************/                 /* X  */
      (* U) = (* R) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* R) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;
   case 24: /* NO_CASES-XW */
      S_E_I_R___L_X_U_W___C_O_D_E_S( P,
				       S, E, I, R,  L, X, U, W );
      (* C) = (* R); /* Last human class */

      assert(P->n_V == 0);
      /* Mosquito codes */
      (* X) = (* R) + 1;     /************************/                 /* X  */
      (* U) = (* R) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* R) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;

    /* SEnI models * * * * * * * * * * * * * * * * * * * * * * */
   case 31: /* SEnI-LXVnW */
      S_E_I___L_X_U_W___C_O_D_E_S( P,
				   S, E, I,  L, X, U, W );
      (* C) = (* I); /* Last human class */

      (* A) = (* W);
      (* K) = (* W);
      break;
   case 32: /* SEnI-XkVnW */
      S_E_I___L_X_U_W___C_O_D_E_S( P,
				   S, E, I,  L, X, U, W );
      (* C) = (* I); /* Last human class */

      /* Mosquito codes */
      (* X) = (* I) + 1;     /************************/                 /* X  */
      (* U) = (* I) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* I) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;
   case 33: /* SEnI-XVnW */
      S_E_I___L_X_U_W___C_O_D_E_S( P,
				   S, E, I,  L, X, U, W );
      (* C) = (* I); /* Last human class */

      /* Mosquito codes */
      (* X) = (* I) + 1;     /************************/                 /* X  */
      (* U) = (* I) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* I) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;
   case 34: /* SEnI-XW */
      S_E_I___L_X_U_W___C_O_D_E_S( P,
				   S, E, I,  L, X, U, W );
      (* C) = (* I); /* Last human class */

      assert(P->n_V == 0);
      /* Mosquito codes */
      (* X) = (* I) + 1;     /************************/                 /* X  */
      (* U) = (* I) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* I) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;

    /* SI models * * * * * * * * * * * * * * * * * * * * * * */
    case 41: /* SI-LXVnW */
      S_I___L_X_U_W___C_O_D_E_S( P,
				   S, E, I,  L, X, U, W );
      (* C) = (* I); /* Last human class */

      (* A) = (* W);
      (* K) = (* W);
      break;
    case 42: /* SI-XkVnW */
      S_I___L_X_U_W___C_O_D_E_S( P,
				   S, E, I,  L, X, U, W );
      (* C) = (* I); /* Last human class */

      /* Mosquito codes */
      (* X) = (* I) + 1;     /************************/                 /* X  */
      (* U) = (* I) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* I) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;
    case 43: /* SI-XVnW */
      S_I___L_X_U_W___C_O_D_E_S( P,
				   S, E, I,  L, X, U, W );
      (* C) = (* I); /* Last human class */

      /* Mosquito codes */
      (* X) = (* I) + 1;     /************************/                 /* X  */
      (* U) = (* I) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* I) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;
    case 44: /* SI-XW */
      S_I___L_X_U_W___C_O_D_E_S( P,
				   S, E, I,  L, X, U, W );
      (* C) = (* I); /* Last human class */

      assert(P->n_V == 0);
      /* Mosquito codes */
      (* X) = (* I) + 1;     /************************/                 /* X  */
      (* U) = (* I) + 2;    /************************/                 /* U, first latent mosquito class */
      (* W) = (* I) + 2 + P->n_V;                                     /* W, infectious mosquitos */

      /* Per convention... */
      (* L) = (* X);
      (* A) = (* W);
      (* K) = (* W);
      break;

		/* CLASSES (SnInR) models * * * * * * * * * * * * * * * * * * * * * * */
	 case 51: /* SnInR-LXVnW */
		   S_n_I_n_R___L_X_U_W___C_O_D_E_S( P,
					 S, E, I, R,  S1, I1, S2, I2, S3, I3, L, X, U, W );
	    (* C) = (* R); /* Last human class */

		  (* A) = (* W);
		  (* K) = (* W);
		  break;

   case 0: /* CASES_33 */
      S_E_I_R_C___L_X_U_W_A___K___C_O_D_E_S( P,
					     S, E, I, R, C, L, X, U, W, A, K );
      break;

   case 2: /* MacDonald and Ross */
      (* W) = 1; /* Number of infectious mosquitoes per human */
      (* I) = 0; /* Fraction of infectious humans */
      (* K) = (* W);

      (* C) = (* I); /* Last human class */
      break;

   default:
      printf(" This TYPE_of_MODEL (%d) code is not defined. Check input argument list", TYPE_of_MODEL);
      exit(0);
   }
  /* Conventionally, the last label in the argument list of M_O_D_E_L___V_A_R_I_A_B_L_E_S___C_O_D_E (...),
     (*K), should be the label of the last model state variable. Then ( * K) + 1 becomes de total
     number of dynamic variables.
  */
}

void S_E_I___X_U_W___C_O_D_E_S( Parameter_Table * P,
                                  int * S, int * E, int * I,
                                  int * X, int * U, int * W )
{
  /* Human codes */
  * S = 0;
  * E = 1; //P->n_H;
  * I = 1 + P->n_H;      /************************/                 /* I   */

  /* Mosquito codes */
  * X = *I + 1;     /************************/                 /* X  */
  * U = *I + 2;    /************************/                 /* U, first latent mosquito class */
  * W = *I + 2 + P->n_V;                                     /* W, infectious mosquitos */
}

void S_I___L_X_U_W___C_O_D_E_S( Parameter_Table * P,
				  int * S, int * E, int * I,
				  int * L, int * X, int * U, int * W )
{
  /* Human codes */
  * S = 0;
  * E = 0;
  * I = 1 ;            /************************/                 /* I   */

  /* Mosquito codes  */
  * L = *I + 1;      /************************/                 /* L  */
  * X = *I + 2;     /************************/                 /* X  */
  * U = *I + 3;    /************************/                 /* U, first latent mosquito class */
  * W = *I + 3 + P->n_V;                                     /* W, infectious mosquitos */
}


void S_E_I___L_X_U_W___C_O_D_E_S( Parameter_Table * P,
				  int * S, int * E, int * I,
				  int * L, int * X, int * U, int * W )
{
  /* Human codes */
  * S = 0;
  * E = 1; //P->n_H;
  * I = 1 + P->n_H;      /************************/                 /* I   */

  /* Mosquito codes */
  * L = *I + 1;      /************************/                 /* L  */
  * X = *I + 2;     /************************/                 /* X  */
  * U = *I + 3;    /************************/                 /* U, first latent mosquito class */
  * W = *I + 3 + P->n_V;                                     /* W, infectious mosquitos */

}

void S_E_I_R___L_X_U_W___C_O_D_E_S( Parameter_Table * P,
                                           int * S, int * E, int * I, int * R,
                                           int * L, int * X, int * U, int * W )
{
  /* Human codes */
  * S = 0;
  * E = 1; //P->n_H;
  * I = 1 + P->n_H;      /************************/                 /* I   */
  * R = 2 + P->n_H;     /************************/                 /* R   */

  /* Mosquito codes */
  * L = *R + 1;      /************************/                 /* L  */
  * X = *R + 2;     /************************/                 /* X  */
  * U = *R + 3;    /************************/                 /* U, first latent mosquito class */
  * W = *R + 3 + P->n_V;                                     /* W, infectious mosquitos */

}


void S_E_I_R_C___L_X_U_W___C_O_D_E_S( Parameter_Table * P,
					   int * S, int * E, int * I, int * R, int * C,
					   int * L, int * X, int * U, int * W )
{
  /* Human codes */
  * S = 0;
  * E = 1; //P->n_H;
  * I = 1 + P->n_H;      /************************/                 /* I   */
  * R = 2 + P->n_H;     /************************/                 /* R   */
  * C = 3 + P->n_H;    /************************/                 /* C   */

  /* Mosquito codes */
  * L = *C + 1;      /************************/                 /* L  */
  * X = *C + 2;     /************************/                 /* X  */
  * U = *C + 3;    /************************/                 /* U, first latent mosquito class */
  * W = *C + 3 + P->n_V;                                     /* W, infectious mosquitos */

}

void S_E_I_R_C___L_X_U_W_A___K___C_O_D_E_S(Parameter_Table * P,
					   int * S, int * E, int * I, int * R, int * C,
					   int * L, int * X, int * U, int * W,
					   int * A,
					   int * K)
{
  /* Human codes */
  * S = 0;
  * E = 1; //P->n_H;
  * I = 1 + P->n_H;      /************************/                 /* I   */
  * R = 2 + P->n_H;     /************************/                 /* R   */
  * C = 3 + P->n_H;    /************************/                 /* C   */

  /* Mosquito codes */
  * L = *C + 1;      /************************/                 /* L  */
  * X = *C + 2;     /************************/                 /* X  */
  * U = *C + 3;    /************************/                 /* U, first latent mosquito class */
  * W = *C + 3 + P->n_V;                                     /* W, infectious mosquitos */

  /* Acummulated cases and Carrying capicity */
  * A = *W + 1;  /************************/                 /* A, Accummulated no of cases */
  * K = *A + 1; /************************/                 /* K, Karrying capacity */
}




void S_n_I_n_R___L_X_U_W___C_O_D_E_S( Parameter_Table * P,
                                           int * S, int * E, int * I, int * R, int * S1, int * I1, int * S2, int * I2, int * S3, int * I3,
                                           int * L, int * X, int * U, int * W)
{
  /* Human codes */
  * S = 0;
  * E = 0; //P->n_H;
  * I = 0; //+ P->n_H;      /************************/                 /* I   */
  * R = 7; //+ P->n_H;     /************************/                 /* R   */

	/* Human HumanSnInR codes */
	* S1 = 1;
	* I1 = 2;
	* S2 = 3;
	* I2 = 4;
	* S3 = 5;
	* I3 = 6;

  /* Mosquito codes */
  * L = *R + 1;      /************************/                 /* L  */
  * X = *R + 2;     /************************/                 /* X  */
  * U = *R + 3;    /************************/                 /* U, first latent mosquito class */
  * W = *R + 3 + P->n_V;                                     /* W, infectious mosquitos */
	/*  K = *W; /* Must have K as last state variable in Fixed Point calculations this is set in */

	* C = *R; /* For LXVnW jacobian calculation */

}
