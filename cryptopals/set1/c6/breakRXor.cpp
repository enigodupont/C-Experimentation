#include <stdio.h>
#include <string.h>
double bitHamDistance(char* s1, char* s2){

  int dist = 0;

  for(int i = 0; i < strlen(s1); i++){
    for(int x = 0; x < 8; x++){
      if(( (s1[i] >> x) & 1) != ( (s2[i] >> x) & 1)){
        dist++;
      }
    }
  }

  return dist;

}

void processkeyPoints(double* pointStorage, int minKeySize, int maxKeySize, char* data){

  for(int curKeySize = minKeySize; curKeySize <= maxKeySize; curKeySize++){

   char* b1 = new char[curKeySize];
   for(int x = 00; x < curKeySize; x++){
    b1[x] = data[x];
   } 

   char* b2 = new char[curKeySize];
   for(int x = curKeySize; x < (curKeySize + curKeySize); x++){
    b1[x-curKeySize] = data[x];
   } 


   pointStorage[curKeySize] = bitHamDistance(b1,b2) / curKeySize;


   delete b1;
   delete b2;

  }

}

int processKeySize(double* pointStorage,int minSize,  int size){

  int keySize = minSize;
  double curKeyDistance = pointStorage[minSize];
  for(int i = minSize; i < size; i++){
   if(curKeyDistance > pointStorage[i]){
     curKeyDistance = pointStorage[i];
     keySize = i;
   } 
  }

  return keySize;

}

int main(int argc, char** argv){

  if(argc < 2){
    fprintf(stderr,"Usage: %s <textBlock>\n",argv[0]);
  }

  //Try to guess keysize
  int minKeySize = 2, maxKeySize = 40;
  double* pointStorage = new double[maxKeySize];

  processkeyPoints(pointStorage, minKeySize, maxKeySize,argv[1]);

  int trueKeySize = processKeySize(pointStorage, minKeySize, maxKeySize);
  printf("True Key Size %d, distance of %f\n",trueKeySize,pointStorage[trueKeySize]);

  delete pointStorage;


  //Break text into keysized blocks
  
  
  int numBlocks = strlen(argv[1]) / trueKeySize;
  printf("We will have %d blocks of %d, from a OG size of %d\n",numBlocks, trueKeySize, strlen(argv[1]));
  char** keyBlocks = new char*[numBlocks];
  
  int curChar = 0;
  for(int i = 0; i < numBlocks; i++){
    keyBlocks[i] = new char[trueKeySize];
    for(int x = 0; x < trueKeySize; x++){
  
      keyBlocks[i][x] = argv[1][curChar];
      curChar++;
    }
    printf("We are on block %d, it has %s\n",i,keyBlocks[i]);
  }


  //Break blocks into blocks of bytes
  char** byteBlocks = new char*[trueKeySize];
  for(int i = 0; i < trueKeySize; i++){
    byteBlocks[i] = new char[numBlocks];
    for(int x = 0; x < numBlocks; x++){
      byteBlocks[i][x] = keyBlocks[x][i];
    } 
    printf("We are on block %d, it has %s\n",i,byteBlocks[i]);
  }


  delete [] keyBlocks[numBlocks];
  delete [] byteBlocks[trueKeySize];
  return 0;
}
