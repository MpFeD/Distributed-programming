#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

/*

  TCP multi server

Ecrire un programme serveur, sans sous-processus ni Thread, qui prend sur la ligne de commande un nombre arbitraire de numéro de ports, et attend en parallèle un client sur chacun de ces ports. On utilisera bien sûr la fonction select. Il enregistre dans le fichier cx.log les adresses des clients successifs.

Le code du processus client vous est fourni en annexe. Il prend sur sa ligne de commande l’adresse du serveur et un numéro de port où il écoute.
Exemple d'appel :
$PWD/bin/journal_serveur 2820 2821 2822 2823 &

*/

int main (int argc, char** argv){
  
  if (argc <= 1){       
    perror("arguments");
    return EXIT_FAILURE;
  }

  
  int port[argc-1],i,j;
  int fd = open("./cx.log",O_CREAT | O_TRUNC | O_RDWR,0666);
  char host[64];
  int sock[argc-1];
  int scom;
  
  struct sockaddr_in exp;
  struct sockaddr_in sin[argc-1];

   
  fd_set mselect;
  FD_ZERO(&mselect);

  for(i=0;i<argc-1;i++){
    sock[i] = socket(AF_INET,SOCK_STREAM,0);
    port[i]=atoi(argv[i+1]);
    memset(&sin[i],0,sizeof(struct sockaddr_in));
    sin[i].sin_family = AF_INET;
    sin[i].sin_port = htons(port[i]);
    sin[i].sin_addr.s_addr = htonl(INADDR_ANY);
    bind (sock[i],(struct sockaddr *)&sin[i],sizeof(sin[i]));
    listen(sock[i],1);
  }

  socklen_t len = sizeof(struct sockaddr_in);
  
  while(1){
    FD_SET(0,&mselect); /* stdin */
    for(i=0;i<argc-1;i++)
      FD_SET(sock[i],&mselect);
  
    select(sock[argc-2]+1,&mselect,NULL,NULL,NULL);
    if (FD_ISSET(0,&mselect))
      break;
    for(i=0;i<argc-1;i++){
      if(FD_ISSET(sock[i],&mselect)){
	scom = accept(sock[i], (struct sockaddr *)&sin[i],&len);
	getnameinfo((struct sockaddr*)&exp, sizeof(exp),host, sizeof(host), 0, 0, 0);
	strcat(host,"\n");
	write(fd,host,strlen(host));
	fflush(stdout);
	shutdown(scom,2);
	break;
      }
    }
  }
  
  close(scom);
  for(i=0;i<argc-1;i++)
    close(sock[i]);
  return EXIT_SUCCESS;
}
