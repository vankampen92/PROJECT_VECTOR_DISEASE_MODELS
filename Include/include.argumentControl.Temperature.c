/* Temperature parameters to adjust temp. dependent mosquito paramaters with values_TempDependency function*/

	    case 'Y': /* Temperature parameters */
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%lf",&Temp);
	      else exit(0);
	      skip++;
	      break;
