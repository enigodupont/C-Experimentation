/**
	Juan Carlos Ramirez
	Single-byte XOR cipher
	TODO: Still need to weigh characters
*/

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){
	
	if(argc < 2){
		fprintf(stderr, "Usage: %s <hexString>\n",argv[0]);
		return -1;
	}
	
	if((strlen(argv[1]) % 2) != 0){
		fprintf(stderr, "Odd number of Hex\n");
		return -1;
	}
	
	char* resultStorage[256];
	int rankingStorage[256];
	
	memset(rankingStorage,0,255);
	for(int i = 0; i <= 255; i++){
		resultStorage[i] = (char*)malloc((strlen(argv[1])/2)+1);
		int currentSize = 0;
		
		for(int x = 0; x + 1 < strlen(argv[1]); x+=2){
			char src1[2] = {argv[1][x],argv[1][x+1]};
			
			int num1 = (int)strtol(src1, NULL, 16);
			int num2 = i;
			
			int newNum = num1 ^ num2;
			char curCharacter = 32 + newNum;
			
			//snprintf(resultStorage[i] + x,3,"%X",newNum);
			resultStorage[i][currentSize++] = curCharacter;
			
			//Rank the strings
			//Add 5 points if the character is alphanumeric
			if((curCharacter >= 48 && curCharacter <= 57) | (curCharacter >= 65 && curCharacter <= 90) | (curCharacter >= 97 && curCharacter <= 122)){
				rankingStorage[i] += 5;
			}
			
		}
		resultStorage[i][currentSize] = '\0';
		
	}
	
	
	for(int i = 0; i <= 255; i++){
		for(int x = i; x < 255; x++){
			if(rankingStorage[x] < rankingStorage[x+1]){
				swap(rankingStorage[x],rankingStorage[x+1]);
				swap(resultStorage[x],resultStorage[x+1]);
			}
		}
	}
	
	
	for(int i = 0; i <= 255; i++){
		printf("Rank %d - %s\n",i,resultStorage[i]);
		free(resultStorage[i]);
	}
	
	return 0;
}
