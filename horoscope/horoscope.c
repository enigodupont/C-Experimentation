#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char* msg) {
  perror(msg);
  exit(-1);
}

char* parseResponse(char* res){
  return res;
}

int main(int argc, char** argv){

  int DEBUG = 0;
  char* apiCallAddr = "widgets.fabulously40.com";//?sign=" + argv[1];
  int portno = 80;
  
  struct hostent *server;
  struct sockaddr_in serv_addr;
  int sockfd, bytes, sent, recieved, total;
  char response[4096], message[1024];
 
  if(argc < 2){
    fprintf(stderr, "Usage: %s <Astrology Sign> \n",argv[0]);
    return -1;
  }else if(argc > 2){
    DEBUG = 1;
  }
 
  strcat(message, "GET /horoscope.json?sign=leo HTTP/1.1\n");
  //strcat(message, "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\n");
  strcat(message, "Host: ");
  strcat(message,apiCallAddr);
  strcat(message, "\nCache-Control: no-cache");
  strcat(message, "\nPostman-Token: 18121329-75b4-c5a3-6887-6ea2efd6895d");
  /*
  strcat(message,"\nContent-Type: application/x-www-form-urlencoded\n");
  strcat(message,"Content-Length: ");
  char contentLen[10];
  sprintf(contentLen, "%d",5 + strlen(argv[1])); // The 5 is the amount of characters in sign=
  strcat(message,contentLen);
  strcat(message,"\n\nsign=");
  strcat(message,argv[1]);
  */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) error("ERROR: Opening Socket");

  server = gethostbyname(apiCallAddr);
  if(server == NULL) error("ERROR: No such host.");
  
  memset(&serv_addr,0,sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

  if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
    error("ERROR connecting");
  }

  total = strlen(message);
  sent = 0;
  do{
      bytes = write(sockfd, message+sent, total-sent);
      if(bytes < 0) error("ERROR writing message");
      if(bytes == 0) break;
      sent+=bytes;
  }while(sent < total);
  if(DEBUG) printf("Sent------\n%s\n", message);
  memset(response,0,sizeof(response));
  total = sizeof(response)-1;
  recieved = 0;
  do{
      bytes = read(sockfd,response+recieved,total-recieved);
      if(bytes < 0) error("ERROR reading response");
      if(bytes == 0) break;
      recieved += bytes;
  }while(recieved < total);
 
  if(recieved == total) error("ERROR storing complete response");
  if(DEBUG) printf("Recieved------\n%s\n", response);

  close(sockfd);

  printf(parseResponse(response));

  return 0;
}
