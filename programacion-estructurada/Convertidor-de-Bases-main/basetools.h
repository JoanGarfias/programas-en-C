void showOptionScreen(int *);
void showExtOpScreen(int *, int);
void requestNumber(int);
void eputs(long int *, int);
int checkOp(long int, int);
int checkOpHex(char *);
void sendError(int);
void reverseArr(char *, int);


void showOptionScreen(int *op)
{
	do{
		printf("\n1.- DECIMAL\n2.- HEXADECIMAL\n3.- OCTAL\n4.- BINARY\n5.- EXIT");
		printf("\n\nType the number of your option: \t");
		scanf("%d",op);
	}while(*op <= 0 || *op>5);
}

void showExtOpScreen(int *opExt, int type)
{
	system("cls");
	do{
		switch(type){
			case 1:
				printf("\nDecimal to...\n");
				printf("\n1.- HEXADECIMAL\n2.- OCTAL\n3.- BINARY\n4.- EXIT");
			break;
			case 2:
				printf("\nHexadecimal to...\n");
				printf("\n1.- DECIMAL\n2.- OCTAL\n3.- BINARY\n4.- EXIT");
				break;
			case 3:
				printf("\nOctal to...\n");
				printf("\n1.- DECIMAL\n2.- HEXADECIMAL\n3.- BINARY\n4.- EXIT");
				break;
			case 4:
				printf("\nBinary to...\n");
				printf("\n1.- DECIMAL\n2.- HEXADECIMAL\n3.- OCTAL\n4.- EXIT");
				break;
		}
		printf("\n\nType the number of your option: \t");
		scanf("%d",opExt);
		system("cls");
		if(*opExt==4)	exit(0);
		if(*opExt <= 0 || *opExt>=5)	sendError(1);
	}while(*opExt <= 0 || *opExt>=5);
}

int checkOp(long int num, int op)
{
	int aux;			//octal
	while(num!=0){
			aux=num%10;
			num/=10;
		if(op==3){
			if(aux==8 || aux==9){	sendError(1); return 0;	}
			else{continue;}
		}
		else if(op==4){
			if(aux==0 || aux==1){ continue; }
			else{
				sendError(1); return 0;
			}
		}
	}
	return 1;
}

int checkOpHex(char *hex)
{
	for(int i=0; i<strlen(hex); i++){
		if(hex[i]=='A' || hex[i]=='B' || hex[i]=='C' || hex[i]=='D' || hex[i]=='E' ||hex[i]=='F' || isdigit(hex[i]))
			continue;
		sendError(1);
		return 0;
	}
	return 1;
}


void requestNumber(int op)
{
	system("cls");
	if(op==1||op==3||op==4){
		do{
			printf("\nType the ");
			(op==1)? printf("Decimal number:\t") : (op==3)? printf("Octal number:\t") : printf("Binary number:\t");
			fflush(stdin);
			scanf("%ld",&number);
		}while(!checkOp(number,op));
	}
	else{ //hexadecimal
		do{
		printf("\nType the Hexadecimal number:\t");
		fflush(stdin);
		gets(hex);
		}while(!checkOpHex(hex));
	}
}

void eputs(long int *arr, int tam)
{
	int temp=0;
	for(int i=0; i<=tam/2; i++){
		temp = arr[i];
		arr[i] = arr[tam-i];
		arr[tam-i] = temp;
	}
	
	for(int i=0; i<=tam; i++){
		printf("%ld",arr[i]);
	}
}

void reverseArr(char *arr, int tam){
	char temp;
	for(int i=0; i<=tam/2; i++){
		temp = arr[i];
		arr[i] = arr[tam-i];
		arr[tam-i] = temp;
	}
}

void sendError(int type)
{
	printf((type==1)? "\nERROR: An error has occurred with your entered data. Please check them." : "ERROR: An internal error has occurred.");	
}
