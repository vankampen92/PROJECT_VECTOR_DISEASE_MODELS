/* Time Control Definition */ 
	    
	    case 't': 
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%d",&I_Time);
              else if(argv[argcount][2]=='1')
		sscanf(argv[argcount+1],"%lf",&Time_0);
              else if(argv[argcount][2]=='2')
		sscanf(argv[argcount+1],"%lf",&Time_1);
              else if(argv[argcount][2]=='3')
		sscanf(argv[argcount+1],"%lf",&Time_Scale_Unit);
              else if(argv[argcount][2]=='4')
		sscanf(argv[argcount+1],"%d",&TYPE_of_TIME_DEPENDENCE);
              else exit(0);
	      skip++;
	      break;
	    
            case 'e': /* * * *  */
	      sscanf(argv[argcount+1],"%lf",&EPSILON);
	      skip++;
	      break;
	    
	    
