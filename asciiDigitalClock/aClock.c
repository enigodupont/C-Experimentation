#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#define debug true
int main(){

  char *num0 = " _ \n| |\n|_|\n";
  char *num1 = "  |\n  |\n  |\n";
  char *num2 = "__ \n__|\n|__\n";
  char *num3 = "__ \n__|\n__|\n";
  char *num4 = "| |\n___\n  |\n";
  char *num5 = "__ \n|_ \n__|\n";
  char *num6 = "__ \n|_ \n|_|\n";
  char *num7 = "__ \n  |\n  |\n";
  char *num8 = " _ \n|_|\n|_|\n";
  char *num9 = "__ \n|_|\n _|\n";   

  char *ascii[10] = {num0,num1,num2,num3,num4,num5,num6,num7,num8,num9};
while(true){
  time_t rawTime;
  time(&rawTime);
  struct tm *curTime = localtime(&rawTime);
  if(curTime == NULL){
    fprintf(stderr,"Time is broken, go cry.\n");
  }

  char sec[3];
  int secNum = curTime->tm_sec;
  if(secNum < 10){
    snprintf(sec,3,"0%d",secNum);
  }else{
    snprintf(sec,3,"%d",secNum);
  }

  char min[3];
  int minNum = curTime->tm_min;
  if(minNum < 10){
    snprintf(min,3,"0%d",minNum);
  }else{
    snprintf(min,3,"%d",minNum);
  }

  char hour[3];
  bool pmFlag = false;
  int hourNum = curTime->tm_hour;
  if(hourNum > 12){
    pmFlag = true;
    hourNum -= 12;
  }
  if(hourNum < 10){
    snprintf(hour,3,"0%d",hourNum);
  }else{
    snprintf(hour,3,"%d",hourNum);
  }

  if (debug) printf("%s:%s:%s\n",hour,min,sec);  
  
  printf("%s\n",ascii[hour[0] -48]);
  printf("%s\n",ascii[hour[1] -48]);
 
  printf(ascii[min[0] -48]);
  printf(ascii[min[1] -48]);
 
  printf(ascii[sec[0] -48]);
  printf(ascii[sec[1] -48]);
 

  sleep(1);
}
  return 0;
}
