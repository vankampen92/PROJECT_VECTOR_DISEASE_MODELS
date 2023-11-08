
	    
	    case 'E': /* Error function parameters */
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%lf",&Error_Parameter_0);
	      else if(argv[argcount][2]=='1')
		sscanf(argv[argcount+1],"%lf",&Error_Parameter_1);
              else exit(0);
	      skip++;
	      break;
	    
