/**
 * @author Juan Carlos Ramirez
 *
 * This program will convert text into hex and binary
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

void toHex(char* s);
void toBin(char* s);

int main(int argc, char** argv){

  if(argc != 2){

   fprintf(stderr,"Usage: %s <text here>",argv[0]);
   return -1;
  }

  printf("\nOriginal Text: %s\n\n",argv[1]);
  
  toHex(argv[1]);

  toBin(argv[1]);

  return 0;

}

void toHex(char* s){
 
  printf("Hex Text: ");

  for(unsigned int i = 0; i < strlen(s); i++){
    printf("%x",s[i]);
  }
 printf("\n\n");
  return;
}
void toBin(char* s){

  printf("Bin Text: ");

  for(unsigned int i = 0; i < strlen(s); i++){
    for(int x = 7; x >= 0; x--){
        unsigned int curChar = s[i];
        curChar = curChar >> x;
        curChar = curChar & 1;
        printf("%d",curChar);
    }
  }

  printf("\n\n");
  return;
}
