            case 'f': /* Name of the file to be read */
	      if(argv[argcount][2]=='0')
                sscanf(argv[argcount+1],"%s", File_to_Read_0);
	      else if(argv[argcount][2]=='1')
	        sscanf(argv[argcount+1],"%s", File_to_Read_1);
              else if(argv[argcount][2]=='2')
	        sscanf(argv[argcount+1],"%s", File_to_Read_2);
              else if(argv[argcount][2]=='3')
	        sscanf(argv[argcount+1],"%s", File_to_Read_3);
	      else exit(0);
	      skip++;
	      break;
