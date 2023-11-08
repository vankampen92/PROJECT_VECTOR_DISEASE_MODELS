
             case 'C': 
	      if(argv[argcount][2]=='0')
                sscanf(argv[argcount+1],"%lf", &H_Xhi);
	      else if(argv[argcount][2]=='1')
		sscanf(argv[argcount+1],"%lf", &H_Rho);
              else if(argv[argcount][2]=='2')
		sscanf(argv[argcount+1],"%lf", &H_Eta);
	      else if(argv[argcount][2]=='3')
                sscanf(argv[argcount+1],"%lf", &H_Nu);
	      else exit(0);
	      skip++;
	      break;
