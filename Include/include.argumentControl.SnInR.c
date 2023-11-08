/* Human class Parameters for SnInR model*/

	    case 'N': /* Class dependency parameters */
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%lf",&H_mSigma);
	      else if(argv[argcount][2]=='1')
		sscanf(argv[argcount+1],"%lf",&H_mRecov);
              else if(argv[argcount][2]=='2')
		sscanf(argv[argcount+1],"%lf",&H_mBeta);
	      else if(argv[argcount][2]=='3')
		sscanf(argv[argcount+1],"%lf",&H_mM_c);
	      else exit(0);
	      skip++;
	      break;
