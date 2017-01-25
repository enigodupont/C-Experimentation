/**
	Juan Carlos Ramirez
	Single-byte XOR cipher
	TODO: Still need to weigh characters
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv){
	
	if(argc < 2){
		fprintf(stderr, "Usage: %s <hexString>\n",argv[0]);
		return -1;
	}
	
	if((strlen(argv[1]) % 2) != 0){
		fprintf(stderr, "Odd number of Hex\n");
		return -1;
	}
	
	char* resultStorage[255];
	
	for(int i = 0; i <= 255; i++){
		resultStorage[i] = malloc((strlen(argv[1])/2)+1);
		int currentSize = 0;
		
		for(int x = 0; x + 1 < strlen(argv[1]); x+=2){
			char src1[2] = {argv[1][x],argv[1][x+1]};
			
			int num1 = (int)strtol(src1, NULL, 16);
			int num2 = i;
			
			int newNum = num1 ^ num2;
			
			//snprintf(resultStorage[i] + x,3,"%X",newNum);
			resultStorage[i][currentSize++] = (char) (32 + newNum);
		}
		resultStorage[i][currentSize] = '\0';
		
	}
	
	for(int i = 0; i <= 255; i++){
		printf("Result %d - %s\n",i,resultStorage[i]);
		free(resultStorage[i]);
	}
	
	return 0;
}
