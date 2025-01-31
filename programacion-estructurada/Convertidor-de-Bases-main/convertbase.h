void convertDecOctBin(long int, int);
char *convertDecHex(long int);
long int convertHexDec(char *);
void convertHexBin(char *);
void convertHexOct(char *);
long int convertOctDec(long int);
char *convertOctHex(long int);
void convertOctBin(long int);
long int convertBinDec(long int);
char *convertBinHex(long int);
void convertBinOct(long int);


char * convertDecHex(long int dec)
{
	int aux,i=1; //the var aux saves the letter of digits of hexadecimal number.
	while(dec!=0){
		aux = dec % 16; //aux saves numbers of 0 to 15 (0-F)
		dec = (int) dec / 16;
		switch(aux){ //is a letter or a number?
			case 10:	base[i-1]='A';	break;
			case 11: 	base[i-1]='B';	break;
			case 12: 	base[i-1]='C';	break;
			case 13: 	base[i-1]='D';	break;
			case 14: 	base[i-1]='E';	break;
			case 15: 	base[i-1]='F';	break;
			default:
				base[i-1] = aux + '0'; /*If aux values is 0, the number of base in char is aux+'0'*/
		}
		base = (char *) realloc(base, sizeof(char) * (i+1));
		if(base==NULL)	sendError(2);
		i++;
	}
	reverseArr(base, i-2);
	base[i-1] = '\0';
	return base;
}

void convertDecOctBin(long int dec, int op) //two funtions in 1
{
	int i=1,bs_op=0;
	long int aux=0;
	bs_op = (op==1)?	8 : (op==2)? 2 : 0;
	while(dec!=0){
		aux = dec % bs_op;
		base_n[i-1] = aux;
		base_n = (long int *) realloc(base_n,sizeof(long int) * (i+1));
		dec /= bs_op;
		i++;
	}
	eputs(base_n, i-2);
}

long int convertHexDec(char *hex)
{
	int aux;
	long int dec=0;
	for(int i=0; i<strlen(hex); i++){
		switch(hex[i]){
			case 'A': aux=10; break;
			case 'B': aux=11; break;
			case 'C': aux=12; break;
			case 'D': aux=13; break;
			case 'E': aux=14; break;
			case 'F': aux=15; break;
			default:
				aux = hex[i] - '0';
		}
		dec += aux*(pow(16,strlen(hex)-i-1));
	}
	return dec;
}

long int convertOctDec(long int oct)
{
	long int aux,i=0;
	long int dec=0;
	while(oct>=1){
		aux = oct % 10;
		oct = oct / 10;
		dec+= (aux * pow(8,i)); //n * (8)^i
		i++;
	}	
	return dec;
}

long int convertBinDec(long int num)
{
	long int dec=0;
	int i=0,aux=0;
	while(num>=1){
		aux = num % 10; //digits
		num = num / 10;
		dec += (aux * pow(2,i));
		i++;
	}
	return dec;
}

void convertHexOct(char *hex)
{
	long int num = convertHexDec(hex);
	convertDecOctBin(num,1);
}

void convertHexBin(char *hex)
{
	long int num = convertHexDec(hex);
	convertDecOctBin(num,2);
}

char *convertOctHex(long int oct)
{
	long int num = convertOctDec(oct);
	char *oct_hex = convertDecHex(num);
	return oct_hex;	
}

void convertOctBin(long int oct)
{
	long int num = convertOctDec(oct);
	convertDecOctBin(num,2);
}

char *convertBinHex(long int num)
{
	long int dec = convertBinDec(num);
	char *bin_hex = convertDecHex(dec);
	return bin_hex;
}

void convertBinOct(long int num)
{
	long int dec = convertBinDec(num);
	convertDecOctBin(dec,1);
}
