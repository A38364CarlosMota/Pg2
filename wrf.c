#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_BIT (8)
#define FIRST_BYTE_UTF  (0xc3)
#define FIRST_LOWERCASE (0xa0)
#define CONVR_UPTOLOW  (0x20)
#define MAX_CHARS_LINE (3250)
#define MAX_WORD_SIZE (24)
#define MAX_WORDS_IN_TEXT (120000)

typedef struct{ 
    char word[MAX_WORD_SIZE]; 
    int freq; 
} WordFreq;

int compararNome (const void *a, const void *b) {
  WordFreq *wordA = (WordFreq*) a;
  WordFreq *wordB = (WordFreq*) b;

  return strcmp (wordA->word,wordB->word);
}

int charLeadingOnes (char value);
char *lineSplitFirst(char line[]);
char *lineSplitNext();
int utf8SetLower(char* symb);
char *normalize( char *word);


int main(int argc, char** argv){

  char line[MAX_CHARS_LINE];
  char word_from_Texto[MAX_WORD_SIZE];
  WordFreq words_array[MAX_WORDS_IN_TEXT];

  FILE *fpRead=fopen(argv[1] , "r");
  FILE *fpWrite=fopen("Texto.txt" , "w");

   if(fpRead == NULL) {
      perror("Error opening ");
      return(-1);
   }
   if(fpWrite == NULL) {
      perror("Error opening ");
      fclose(fpRead);
      return(-1);
   }

   while( fgets (line, MAX_CHARS_LINE, fpRead) != NULL ) {
      char* word = lineSplitFirst(line);
      
      while ( word != NULL){
        if(charLeadingOnes(*word)<=2)
        {
        
        fputs(normalize(word), fpWrite);
        fputs("\n", fpWrite);
		}
        word = lineSplitNext();
        
      }
   }
   fclose(fpWrite);
   fclose(fpRead);

/*----------------------------------------------*/
  
  FILE *fpRead_Texto=fopen("Texto.txt" , "r");
   
  if(fpRead_Texto == NULL) 
  {
      printf("Error opening ");
      return(-1);
  }

  for (int i=0; i < MAX_WORDS_IN_TEXT; i++)
  {
   words_array[i].freq = 0;
   strcpy(words_array[i].word, "");
  } 

  strcpy(words_array[0].word, fgets(word_from_Texto, MAX_WORD_SIZE, fpRead_Texto));
  words_array[0].freq = 1;
  int counter = 1;

  while( fgets (word_from_Texto, MAX_WORD_SIZE, fpRead_Texto) != NULL ) {

    for (int i=0; i < MAX_WORDS_IN_TEXT; i++){
      if(strcmp(word_from_Texto, "\n") == 0) continue;
      if(strcmp(words_array[i].word, word_from_Texto) == 0)
      {
        words_array[i].freq++;
        break;
      }
      else if(strcmp(words_array[i].word, "") == 0 )
      {
		counter ++;
        strcpy(words_array[i].word, word_from_Texto);
        words_array[i].freq++;
        break;
      }
    }
  }
//MAX_WORDS_IN_TEXT

  /*for (int i=0; i < MAX_WORDS_IN_TEXT; i++){
   printf("Palavra: %s Freq:%d\n", words_array[i].word, words_array[i].freq);
   if(words_array[i].freq < 1) break;
   else continue;
  }
  */

  qsort(words_array, counter, sizeof(WordFreq),compararNome);
 
  printf("\n\nARRAY ORDENADO:\n\n");

  for (int i=0; i < counter; i++){
   //printf("Palavra: %s Freq:%d i:%d ", words_array[i].word, words_array[i].freq, i );
	printf("\n[ Palabra: %s ", words_array[i].word);
	printf(" Frequencia: %d]", words_array[i].freq);
  
  }

  //char* pointerKey = "unicos";
  WordFreq *foundedKey;
  foundedKey = (struct WordFreq*)bsearch("ó", words_array, counter,sizeof(WordFreq) , compararNome);

  if(foundedKey != NULL){
	  puts("exists");
  }
  else{
	  puts("doesn't exist");
  }
  //foundedKey != NULL ? printf("\nYes: %s", *foundedKey): printf("\nNo");
  /*
  do{
    printf("CHOOSE AN OPTION:\n");
		printf("a : alphabetic order\n");
    printf("w <word>: word frequency\n");
		printf("+ <number> : most frequent words \n");
		printf("- <number> : least frequent words\n");
		printf("q : quit\n");
		
		printf("\n> ");
		
		char option;
		
		
		//option = getMenuOption();
		
		//switch(option)

  }
  while( getchar() == 'q')
  */


return 0;
}

int charLeadingOnes (char value){

 int count = 0;  
  for (unsigned int mask = 1 << (CHAR_BIT -1); mask >= 1  ; mask >>= 1 ){
    if ((value & mask) == 0) return count;
    else if ((value & mask)) count ++;
  }
  return count;
}

char *lineSplitFirst(char line[]){

  if (strlen(line)==0) return NULL;

  char delimeters[] = {' ', '\t', '\n', '.', ',',':', ';', '!', '?', '"'};

  return strtok(line, delimeters);
}

char *lineSplitNext(){

  char delimeters[] = {' ', '\t', '\n', '.', ',',':',';', '!', '?', '"'};

  return strtok(NULL,delimeters);
}

int utf8SetLower(char* symb){

  for (; *symb != '\0' ; symb++){
    
    if (*symb == (char)FIRST_BYTE_UTF){
      if(*(symb + 1) < (char)FIRST_LOWERCASE)
        *(symb+1) = *(symb+1) + CONVR_UPTOLOW;
    }
    if( *symb >= 'A' && *symb <= 'Z' )
      *symb = *symb + CONVR_UPTOLOW;
    
    else continue;
  }  
  
  return charLeadingOnes(*symb);
}

char *normalize( char *word){

  char *ptrFirst = word;
  int j = 0;
  int flagSpecialChar = 0;
  
  
  
  for(int i=0; i<strlen(word); i++){
	
    if (word[i] == '-' || word[i] == '\'' ){
      if(!flagSpecialChar) {
        ptrFirst[j++] = word[i];
        flagSpecialChar = 1;
      }
    }
    if( isalnum(word[i])){
      utf8SetLower(word+i);
      ptrFirst[j++] = word[i];
    }
    if(word[i] == (char)FIRST_BYTE_UTF){
      utf8SetLower(word + i);
      ptrFirst[j++] = word[i];
      i++;
      ptrFirst[j++] = word[i];
    }
    if(word[i]==' ') continue;
  }
  ptrFirst[j] = '\0';

  return ptrFirst;
}

/*
char* firstChar(char *mixWord){
  while ((!(*mixWord>='A' && *mixWord<='Z') && !(*mixWord>='a' && *mixWord <='z') && !(*mixWord == (char)FIRST_BYTE_UTF))){
      ++mixWord;
  }
  return mixWord;
}
*/
