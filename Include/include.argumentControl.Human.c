/* Human Parameters */ 
	    
	    case 'H': /* Maximum and Minimum Transmission Rate */
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%lf",&H_Beta);
	      else if(argv[argcount][2]=='1')
		sscanf(argv[argcount+1],"%lf",&H_Birth);
              else if(argv[argcount][2]=='2')
		sscanf(argv[argcount+1],"%lf",&H_Delta);
	      else if(argv[argcount][2]=='3')
		sscanf(argv[argcount+1],"%lf",&H_Sigma_0);
              else if(argv[argcount][2]=='4')
		sscanf(argv[argcount+1],"%lf",&H_Recov_0);
              else if(argv[argcount][2]=='5')
		sscanf(argv[argcount+1],"%d",&n_H);
	      else if(argv[argcount][2]=='6')
		sscanf(argv[argcount+1],"%lf",&H_Gamma);
	      else if(argv[argcount][2]=='7')
		sscanf(argv[argcount+1],"%lf",&Imm);
	      else exit(0);
	      skip++;
	      break;
	    
