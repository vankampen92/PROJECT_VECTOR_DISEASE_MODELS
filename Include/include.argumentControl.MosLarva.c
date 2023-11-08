/* Mosquito larva Parameters */ 
	    
	    case 'L': /* Mosquito larva parameters */
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%lf",&L_Devel);

	      else if(argv[argcount][2]=='1'){
		if(argv[argcount][3]=='0'){
		  sscanf(argv[argcount+1],"%lf",&L_Delta_R);
		}
		else if(argv[argcount][3]=='1'){
		  sscanf(argv[argcount+1],"%lf",&L_Delta_PE);
		}
		else if(argv[argcount][3]=='2'){
		  sscanf(argv[argcount+1],"%lf",&K_Maturation);
		}
		else{
		  sscanf(argv[argcount+1],"%lf",&L_Delta_0);
		}
	      }
	      else if(argv[argcount][2]=='2')
		sscanf(argv[argcount+1],"%lf",&K_0);
              else if(argv[argcount][2]=='3')
		sscanf(argv[argcount+1],"%lf",&K_Sigma);
	      else if(argv[argcount][2]=='4')
		sscanf(argv[argcount+1],"%lf",&K_Period);		
	      else if(argv[argcount][2]=='5')
		sscanf(argv[argcount+1],"%lf",&K_Seasonal_Intensity);
	      else if(argv[argcount][2]=='6')
		sscanf(argv[argcount+1],"%lf",&K_A);
              else if(argv[argcount][2]=='7')
		sscanf(argv[argcount+1],"%lf",&K_p);
	      else if(argv[argcount][2]=='8')
		sscanf(argv[argcount+1],"%lf",&K_E);
              else if(argv[argcount][2]=='9')
		sscanf(argv[argcount+1],"%lf",&L_Delta_P);
              else exit(0);
	      skip++;
	      break;
