#include <stdio.h>
#include <string.h>
#include <limits.h>

#define tamanho_char_em_bits (sizeof(char)* CHAR_BIT)
#define NUM_BYTES (4)


void printBytes( unsigned char a[], int i, int n);
int charLeadingOnes ( char value);
int utf8Length(char a[], int i);

int main()
{	
	
	unsigned char x[]= { 4, 1, 5, 0xff, 0x80 };
	printBytes(x, 2, 3 );
	char b[]= "€";
	printf("%x",utf8Length(b,0));
	return 0;
}

void printBytes( unsigned char a[], int i, int n){
	
	int b;
	
	printf("{");
	
	for( b=i ; b < (i+n) ; b++){
		printf("%02x ", a[b] & 0xff);
	}
	printf("} \n");
		
}

int charLeadingOnes ( char value){
	
	char countBits = 0;
	char countAux = 0;
	int mask =( 1 << (tamanho_char_em_bits-1));
	int i;
	
	for(i=0; i< NUM_BYTES ; i++){
		if( value & mask ) countAux++;
		else if(countAux >= countBits){
			countBits = countAux;
			countAux=0;
		}
			
		mask=mask>>1;
	}
	
	return (countAux > countBits ? countAux:countBits );
	
		
}
int utf8Length(char a[], int i){
	
	int mask= 1;
	
	mask = mask << tamanho_char_em_bits;
	if((a[i] & mask) == 0 ) return 1;   // retorna 1 byte
	
	return charLeadingOnes(a[i]);
		
}

