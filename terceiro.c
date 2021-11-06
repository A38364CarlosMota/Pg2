#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>

#define tamanho_char_em_bits (sizeof(char)* CHAR_BIT)
#define NUM_BYTES (4)
#define tamanho (1024)
#define TAM_MAX_STRING (255)
#define BUFFER_SIZE (1024)

void printBytes( char a[], int i, int n);
int charLeadingOnes ( char value);
int utf8Length(char a[], int i);
void separatorUnify( char str[] );

int main()
{	
	
	FILE *fp;
	
	fp=fopen("teste.txt","r");
	
	if ( fp == NULL){
		printf("Erro na abertura\n");
		return -1;
	}
	
	char buffer[BUFFER_SIZE];
	int reads = 0;	
	
	do{
		if(fgets(buffer,BUFFER_SIZE,fp) == NULL) break;
		reads++;
		separatorUnify(buffer);
	}
	while(1);
	
	return 0;
}

void printBytes( char a[], int i, int n){
	
	int b;
	
	printf(" {");
	
	for( b=i ; b < (i+n) ; b++){
		printf("%02x ", a[b] & 0xff);
	}
	printf("} ");
		
}

int charLeadingOnes ( char value){
	
	int count = 0;  
	for (unsigned int mask = 1 << (CHAR_BIT -1); mask >= 1  ; mask >>= 1 ){
		if ((value & mask) == 0) return count;
		else if ((value & mask)) count ++;
	}		
	return count;
}


		

int utf8Length(char a[], int i){
	
	int mask= 1;
	
	mask = mask << (tamanho_char_em_bits-1);
	if((a[i] & mask) == 0 ) return 1;   // retorna 1 byte
	
	return charLeadingOnes(a[i]);
		
}

void separatorUnify( char str[] ){
	
	int tamanho_string = strlen(str);
	int i, num_caract=0;
	char new_string[TAM_MAX_STRING];
	
	for( i = 0; i < tamanho_string; i++ ){
		if(isspace(str[i]) && isspace(str[i+1])) continue; // ignora dois espaços seguidos
		
		new_string[num_caract]=str[i]; // põe o caracter seguido aos dois espaços.
		if(new_string[0]==' '){ // se for espaço no inicio da frase retira o espaço
			 num_caract=0;
			 continue;
		 }
		num_caract++; //conta o numero de caracteres para saber a ultima posição da string
		
		}
	
		
	new_string[num_caract]=0;
	int b = strlen(new_string);
	
	for(int a= 0; a < b; a++){
		
		printf("%c", new_string[a]);
		if(utf8Length(new_string,a) > 1 ) printBytes( new_string,a,utf8Length(new_string,a));
	}
	
}
