#include <stdio.h>
#include <limits.h>

#define tamanho_char_em_bits (sizeof(char)* CHAR_BIT)

int charLeadingOnes( char value );

int main()
{
	printf(" %d tem %d 1s\n",242,charLeadingOnes(0xF2));
	printf(" %d tem %d 1s\n",40,charLeadingOnes(40));
	printf(" %d tem %d 1s\n",100,charLeadingOnes(100));
	printf(" %d tem %d 1s\n",255,charLeadingOnes(255));
	printf(" %d tem %d 1s\n",0x00,charLeadingOnes(0x00));
	printf(" %d tem %d 1s\n",0x01,charLeadingOnes(0x01));
	printf(" %d tem %d 1s\n",0x02,charLeadingOnes(0x02));
	printf(" %d tem %d 1s\n",0x03,charLeadingOnes(0x03));
	printf(" %d tem %d 1s\n",0x04,charLeadingOnes(0x04));
	printf(" %d tem %d 1s\n",0x05,charLeadingOnes(0x05));
	printf(" %d tem %d 1s\n",0x06,charLeadingOnes(0x06));
	printf(" %d tem %d 1s\n",0x07,charLeadingOnes(0x07));
	printf(" %d tem %d 1s\n",0x08,charLeadingOnes(0x08));
	printf(" %d tem %d 1s\n",0x09,charLeadingOnes(0x09));
	printf(" %d tem %d 1s\n",0x0A,charLeadingOnes(0x0A));
	printf(" %d tem %d 1s\n",0x0B,charLeadingOnes(0x0B));
	printf(" %d tem %d 1s\n",0x0C,charLeadingOnes(0x0C));
	printf(" %d tem %d 1s\n",0x0D,charLeadingOnes(0x0D));
	printf(" %d tem %d 1s\n",0x0E,charLeadingOnes(0x0E));
	printf(" %d tem %d 1s\n",0x0F,charLeadingOnes(0x0F));
	printf(" %d tem %d 1s\n",0xA4,charLeadingOnes(0xA2));
	printf(" %d tem %d 1s\n",0xFF,charLeadingOnes(0xFF));
	return 0;
}

int charLeadingOnes ( char value){
	/*
	char countBits = 0;
	char countAux = 0;
	int mask =( 1 << (tamanho_char_em_bits-1));
	int i;
	
	for(i=0; i< tamanho_char_em_bits ; i++){
		if( value & mask ) countAux++;
		else if(countAux >= countBits){
			countBits = countAux;
			countAux=0;
		}
			
		mask=mask>>1;
	}
	
	return (countAux > countBits ? countAux:countBits );*/
		int count = 0;  
		for ( int mask = 1 << (CHAR_BIT -1); mask >= 1  ; mask >>= 1 ){
		if ((value & mask) == 0) return count;
		else if ((value & mask)) count ++;
	}		
	return count;
	
		
}
