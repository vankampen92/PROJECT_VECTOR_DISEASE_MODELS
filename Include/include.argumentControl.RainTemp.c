/* Rain and Temperature time series related parameters */
/* Time Series Parameters */
            case 'r': /* Rain and temperature data related parameters */
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%d", &NO_of_POINTS);
	      else if(argv[argcount][2]=='1')
		sscanf(argv[argcount+1],"%lf",&T_INCREMENT);
              else if(argv[argcount][2]=='2')
		sscanf(argv[argcount+1],"%d", &NO_of_POINTS_AVE);
              else if(argv[argcount][2]=='3')
		sscanf(argv[argcount+1],"%lf",&TEMP__SHIFT);
              else if(argv[argcount][2]=='4')
		sscanf(argv[argcount+1],"%lf",&T_ELEVATION);
              else if(argv[argcount][2]=='5')
		sscanf(argv[argcount+1],"%lf",&INITIAL_YEAR);
              else if(argv[argcount][2]=='6')
		sscanf(argv[argcount+1],"%lf",&x);
	      else exit(0);
	      skip++;
	      break;
