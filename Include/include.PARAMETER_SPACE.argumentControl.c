/* Parameter Space */ 
	    
	    case 'S': 
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%d",&SUB_MODEL_PARAMETERS);
	      else if(argv[argcount][2]=='1')
	      	sscanf(argv[argcount+1],"%lf",&A_n);
              else if(argv[argcount][2]=='2')
	      	sscanf(argv[argcount+1],"%lf",&A_d);
              else if(argv[argcount][2]=='3')
	      	sscanf(argv[argcount+1],"%d",&No_of_POINTS);
              else if(argv[argcount][2]=='4')
	      	sscanf(argv[argcount+1],"%d",&Input_Parameter);
              else if(argv[argcount][2]=='5')
	      	sscanf(argv[argcount+1],"%lf",&Value_0);
              else if(argv[argcount][2]=='6')
	      	sscanf(argv[argcount+1],"%lf",&Value_1);
              else exit(0);
	      skip++;
	      break;
	    
	    
