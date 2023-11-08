/* Plasmodium Parameters */ 
	    
	    case 'P': /* Mosquito larva parameters */
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%d",&n_V);
	      else if(argv[argcount][2]=='1')
		sscanf(argv[argcount+1],"%lf",&M_Gamma);
              else exit(0);
	      skip++;
	      break;
	    
