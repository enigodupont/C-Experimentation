/*
	Juan Carlos Ramirez
	Convert's Hex to Base 64
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define DEBUG 0

char* base64_chars =  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int hex2dec(char* src);
void dec2base64(int* src, int size);

int main(int argc, char** argv){
	
	if(argc < 2){
		fprintf(stderr, "Usage: %s <hexString>\n",argv[0]);
		return -1;
	}
	
	if((strlen(argv[1]) % 2) != 0){
		fprintf(stderr, "Odd number of Hex\n");
		return -1;
	}
	
	int bufferSize = strlen(argv[1]) / 2;
	if(DEBUG) printf("Buffer Size = %d\n",bufferSize);
	
	char hexBuffer[2];
	//Need to create a resizable buffer 
	int* buffer = malloc(sizeof(int)*bufferSize);
	int curBufferSize = 0;
	
	for(int i = 0; (i+1) < strlen(argv[1]); i+=2 ){
		hexBuffer[0] = toupper(argv[1][i]);
		hexBuffer[1] = toupper(argv[1][i+1]);
		hexBuffer[2] = '\0';
		
		if(DEBUG) printf("Test: %s\n",hexBuffer);
		
		//Need to append result to buffer
		buffer[curBufferSize++] = hex2dec(hexBuffer);
		
	}
	
	if(DEBUG){
		for(int i = 0; i < curBufferSize; i++){
			printf("Buffer[%d] = %d\n",i,buffer[i]);
		}
	}
	
	
	dec2base64(buffer,curBufferSize);
	printf("\n");
	
	free(buffer);
	return 0;
	
}


int hex2dec(char* src){
	return (int)strtol(src, NULL, 16);
}
void dec2base64(int* src, int size){
	
	char array_3[3];
	char array_4[4];
	int temp = 0;
	
	for(unsigned int  i = 0; i < size; i++){
		array_3[temp++] = src[i];
		if(temp == 3){
			array_4[0] = (array_3[0] & 0xfc) >> 2;
			array_4[1] = ((array_3[0] & 0x03) << 4) + ((array_3[1] & 0xf0) >> 4);
			array_4[2] = ((array_3[1] & 0x0f) << 2) + ((array_3[2] & 0xc0) >> 6);
			array_4[3] = array_3[2] & 0x3f;
			
			for(int x = 0; x < 4; x++){
				printf("%c",base64_chars[array_4[x]]);
			}
			temp = 0;
		}
	}

	if(temp){
			for(int j = temp; j < 3; j++){
				array_3[j] = 0;
			}
			array_4[0] = (array_3[0] & 0xfc) >> 2;
			array_4[1] = ((array_3[0] & 0x03) << 4) + ((array_3[1] & 0xf0) >> 4);
			array_4[2] = ((array_3[1] & 0x0f) << 2) + ((array_3[2] & 0xc0) >> 6);
			array_4[3] = array_3[2] & 0x3f;
			
			for(int j = 0; j < temp + 1; j++){
				printf("%c",base64_chars[array_4[j]]);
			}
			
			while(temp++ < 3){
				printf("%c",'=');
			}
		}		
}