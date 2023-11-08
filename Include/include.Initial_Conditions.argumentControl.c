/* Scan Parameters */

	    case 'X': /* s__0, e__0, i__0, r__0, c__0 */
	      if(argv[argcount][2]=='0')
					sscanf(argv[argcount+1],"%lf",&s__0);
	      else if(argv[argcount][2]=='1')
					sscanf(argv[argcount+1],"%lf",&e__0);
	      else if(argv[argcount][2]=='2')
					sscanf(argv[argcount+1],"%lf",&i__0);
	      else if(argv[argcount][2]=='3')
					sscanf(argv[argcount+1],"%lf",&r__0);
	      else if(argv[argcount][2]=='4')
					sscanf(argv[argcount+1],"%lf",&c__0);
	      else if(argv[argcount][2]=='5')
					sscanf(argv[argcount+1],"%lf",&e__2);
	      else if(argv[argcount][2]=='6')
    			sscanf(argv[argcount+1],"%lf",&m__i);
	      else if(argv[argcount][2]=='7') {
					if(argv[argcount][3]=='1'){
					  sscanf(argv[argcount+1],"%lf",&s1__0);
					}
					else if(argv[argcount][3]=='2'){
					  sscanf(argv[argcount+1],"%lf",&i1__0);
					}
					else if(argv[argcount][3]=='3'){
					  sscanf(argv[argcount+1],"%lf",&s2__0);
					}
					else if(argv[argcount][3]=='4'){
					  sscanf(argv[argcount+1],"%lf",&i2__0);
					}
					else if(argv[argcount][3]=='5'){
					  sscanf(argv[argcount+1],"%lf",&s3__0);
					}
					else if(argv[argcount][3]=='6'){
					  sscanf(argv[argcount+1],"%lf",&i3__0);
					}
					else {
					  printf("-X71 to -X76 are the only allowable keys. You have typed -X7%d",argv[argcount][3]);
					  exit(0);
					}
	      }
	      else if(argv[argcount][2]=='n') {
		sscanf(argv[argcount+1],"%d",&TYPE_of_INITIAL_CONDITION);
	      }
	      else{
		printf("-Xn -X0 to -X6 and -X71 to -X76 are the only allowable keys. You have typed -X%d",argv[argcount][3]);
		exit(0);
	      }
	      skip++;
	      break;
