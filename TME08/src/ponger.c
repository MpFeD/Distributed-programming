#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <setjmp.h>
#include <signal.h>
#include <netinet/in.h>
#define _XOPEN_SOUCE 700

int PORT= 9999;


sigjmp_buf env;
sigset_t sig;
struct sigaction action;
int mysignal;

void sig_hand(int sig){
  siglongjmp (env,sig);
}


int main (int argc, char** argv){
  
  action.sa_mask=sig;
  action.sa_flags=0;
  action.sa_handler = sig_hand;
  sigaction(SIGINT, &action,NULL);

  char message[32]={'\0'};
  int i,s;
  struct sockaddr_in addr;
  socklen_t len = sizeof(struct sockaddr_in);
  
  s = socket (AF_INET,SOCK_DGRAM,0);
  
  memset((void*)&addr, 0, sizeof(addr));
 
  addr.sin_family = AF_INET;
  addr.sin_port=htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

  int broadcastEnable=1;
  setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &broadcastEnable, sizeof(broadcastEnable));

   
  bind(s, (struct sockaddr *)&addr, sizeof(addr));

  
  printf("Pour terminer, envoyez un ^C\n");
  while (1){
    mysignal = sigsetjmp (env,1);
    if(mysignal == SIGINT)
      break;
    recvfrom(s,message,sizeof(message),0,0,&len);
    if ((strcmp(message,"PING"))==0){
      strcpy(message,"PONG");
      sendto(s,message,sizeof(message)+1,0,(struct sockaddr *)&addr, sizeof(addr));
      }
    memset(message,0,sizeof(message));
    sleep(1);
  }

  close(s);
  return EXIT_SUCCESS;
}

