/* Scan Parameters */ 

/* -Z no_Func --- Number of environmental dependent paremters */ 	   

/* Plasmodium Parameters */ 
	    
	    case 'Z': /* Number of parametres in the I vector */
	      sscanf(argv[argcount+1],"%d",&no_Func);
              skip++;
              break;

	    case 'I': /* Activation Pattern */
	      if(argv[argcount][2]=='0')
		sscanf(argv[argcount+1],"%d",&I0);
	      else if(argv[argcount][2]=='1')
		sscanf(argv[argcount+1],"%d",&I1);
              else if(argv[argcount][2]=='2')
		sscanf(argv[argcount+1],"%d",&I2);
	      else if(argv[argcount][2]=='3')
		sscanf(argv[argcount+1],"%d",&I3);
              else if(argv[argcount][2]=='4')
		sscanf(argv[argcount+1],"%d",&I4);
              else if(argv[argcount][2]=='5')
		sscanf(argv[argcount+1],"%d",&I5);
	      else if(argv[argcount][2]=='6')
		sscanf(argv[argcount+1],"%d",&I6);
              else if(argv[argcount][2]=='7')
		sscanf(argv[argcount+1],"%d",&I7);
              else if(argv[argcount][2]=='8')
		sscanf(argv[argcount+1],"%d",&I8);
              else if(argv[argcount][2]=='9')
		sscanf(argv[argcount+1],"%d",&I9);
	      else exit(0);
	      skip++;
	      break;
           

