/* Mosquito Parameters */ 
	    
	    case 'M': /* Mosquito parameters */
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%lf",&M_a);
	      else if(argv[argcount][2]=='1'){
		if(argv[argcount][3]=='0'){
		  sscanf(argv[argcount+1],"%lf",&M_c_1);
		}
                else if(argv[argcount][3]=='1'){
		  sscanf(argv[argcount+1],"%lf",&M_c_2);
	        }
		else{
		  sscanf(argv[argcount+1],"%lf",&M_b);
		}
	      }
	      else if(argv[argcount][2]=='2')
		sscanf(argv[argcount+1],"%lf",&M_c);
              else if(argv[argcount][2]=='3')
		sscanf(argv[argcount+1],"%lf",&M_Delta);
              else if(argv[argcount][2]=='4')
		sscanf(argv[argcount+1],"%lf",&M_Delta_R);
              else if(argv[argcount][2]=='5')
		sscanf(argv[argcount+1],"%lf",&M_Delta_PE);
              else if(argv[argcount][2]=='6')
		sscanf(argv[argcount+1],"%lf",&M_Fecundity);
	      else if(argv[argcount][2]=='7')
		sscanf(argv[argcount+1],"%lf",&M_NoEggs);
              else if(argv[argcount][2]=='8')
		sscanf(argv[argcount+1],"%lf",&M_Imm);
              else if(argv[argcount][2]=='9')
		sscanf(argv[argcount+1],"%lf",&m);
	      else exit(0);
	      skip++;
	      break;
	    
