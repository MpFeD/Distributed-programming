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

/*

UDP multicast

Réalisez un programme qui permet d’échanger des messages ligne par ligne avec d’autres processus en communiquant par Multicast. Le programme prend sur la ligne de commande :

    l’adresse IP Multicast où la conversation a lieu ;
    le numéro du port sur lequel la conversation a lieu
    le nom (ou pseudonyme) utilisé dans la conversation

Une fois lancé, le programme affiche tous les messages envoyés par d’autres utilisateurs et permet parallèlement d’envoyer des messages pour participer à la conversation. Il utilisera un Thread pour écrire et un autre pour lire.
Exemple d'appel :
$PWD/bin/mychat 225.0.0.10 2001 $USER
*/


sigjmp_buf env;
sigset_t sig;
struct sigaction action;
int mysignal,sockserv;
struct sockaddr_in addr;
socklen_t len = sizeof(struct sockaddr_in);
char *nom;

void sig_hand(int sig){
  siglongjmp (env,sig);
}


void *Ecriture(){
  char m[1024],buf[1];
  int i;
  while(1){
    strcpy(m,nom);
    strcat(m, " : ");
    i=strlen(m);
    while(1)
      if((m[i++]=getchar()) == '\n')
	break;
    sendto(sockserv,m,sizeof(m)+1,0,(struct sockaddr *)&addr, sizeof(addr));
    memset(m,0,sizeof(m));
  }
  pthread_exit ((void*)NULL);
}

void *Lecture(){
  char host[64],message[1024];
  while(1){
    recvfrom(sockserv,message,sizeof(message),0,0,&len);
    printf("%s\n",message);
    fflush(stdout);
  }
  pthread_exit ((void*)NULL);
}


int main (int argc, char** argv){
  
  
  action.sa_mask=sig;
  action.sa_flags=0;
  action.sa_handler = sig_hand;
  sigaction(SIGINT, &action,NULL);

  int i,PORT=atoi(argv[2]);
  struct ip_mreq imr;
  strcpy(nom,argv[3]);
  
  sockserv = socket (AF_INET,SOCK_DGRAM,0);
  
  imr.imr_multiaddr.s_addr = inet_addr(argv[1]);
  imr.imr_interface.s_addr = htonl(INADDR_ANY);
  
  setsockopt(sockserv,IPPROTO_IP,IP_ADD_MEMBERSHIP, (char *)&imr, sizeof(struct ip_mreq));
  setsockopt(sockserv, SOL_SOCKET, SO_REUSEADDR,(char *)&imr , sizeof(struct ip_mreq) );
  
  memset((void*)&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port=htons(PORT);
  addr.sin_addr.s_addr = inet_addr(argv[1]);

  bind(sockserv, (struct sockaddr *)&addr, sizeof(addr));

  pthread_t tid [2];
  pthread_create (&(tid[0]),NULL,Ecriture,NULL);
  pthread_create (&(tid[1]),NULL,Lecture,NULL);
  
  printf("Pour terminer, envoyez un ^C\n");
  while (1){
    mysignal = sigsetjmp (env,1);
    if(mysignal == SIGINT)
      break;
  }

  close(sockserv);
  
  return EXIT_SUCCESS;
}
