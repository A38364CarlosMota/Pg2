#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define CHAR_BIT (8)

void printBin(int n);
int charLeadingOnes(char value);

int main(){
  for(int i = 0 ; i <= 0xFF ; i++){
      printf(" %x está em Hexadecimal e é representado em binario por: ", i);
      printBin(i);
      printf(" e tem os primeitos %d bits 1's \n", charLeadingOnes(i));
    }
    return 0;
}

void printBin(int n){
	int c,k=0;
for (c = (CHAR_BIT-1); c >= 0; c--)
  {
    k = n >> c;

    if (k & 1)
      printf("1");
    else
      printf("0");
  }

  printf("\n");
}

int charLeadingOnes (char value){
 int count = 0;  
  for (unsigned int mask = 1 << (CHAR_BIT -1); mask >= 1  ; mask >>= 1 ){
    if ((value & mask) == 0) return count;
    else if ((value & mask)) count ++;
  }
return count;
}
