/**
	Juan Carlos Ramirez
	Fixed XOR should take input from equal length buffers and produce their XOR
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void twoBufferXOR(char* s1, char* s2, char* dest);

int main(int argc, char** argv){
	
	if(argc < 3){
		fprintf(stderr,"Usage: %s s1 s2\n",argv[0]);
		return -1;
	}
	
	if(strlen(argv[1]) != strlen(argv[2])){
		fprintf(stderr,"Buffer lengths do not match\n");
		return -1;
	}
	
	if(strlen(argv[1]) % 2 != 0){
		fprintf(stderr,"Buffer lengths are odd\n");
		return -1;
	}
	
	char* result = malloc(strlen(argv[1] + 1));
	
	twoBufferXOR(argv[1],argv[2],result);
	
	printf("%s\n",result);
	
	free(result);
	
	return 0;
}


void twoBufferXOR(char* s1, char* s2, char* dest){
	
	for(int i = 0; i+1 < strlen(s1); i += 2){
		
		char src1[2] = {s1[i],s1[i+1]};
		char src2[2] = {s2[i],s2[i+1]};
		
		int num1 = (int)strtol(src1, NULL, 16);
		int num2 = (int)strtol(src2, NULL, 16);
		
		int newNum = num1 ^ num2;
		
		snprintf(dest + i,3,"%X",newNum);
		
	}
	
	dest[strlen(s1)] = '\0';
}
	