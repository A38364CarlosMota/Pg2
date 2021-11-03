#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAM_MAX_STRING (255)
#define BUFFER_SIZE (1024)

void separatorUnify( char str[] );

int main()
{
	FILE*fp = fopen("teste.txt", "r");
	if(fp==NULL)
	{
		printf("Error opening the file \n");
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
		
	fclose(fp);
	
	return 0;
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
	printf("%s" , new_string);
	}
