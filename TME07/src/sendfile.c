#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>

/*

TCP client

On souhaite écrire un programme transmettant au programme précédent le contenu d’un fichier, au moyen d’une connexion TCP.

Le programme prend en ligne de commande :

    l’adresse à laquelle le récepteur attend les demandes de connexion ;
    le numéro du port sur lequel le récepteur attend les demandes de connexion ;
    le nom du fichier à recopier.

Lorsqu’il obtient sa connexion avec le programme récepteur, il envoie d’abord le nom du fichier, puis le contenu de celui-ci.
Exemple d'appel :
$PWD/bin/sendfile 127.0.0.1 2000 makefile
*/

int main (int argc, char** argv){

  if (argc != 4){       
    perror("arguments");
    return EXIT_FAILURE;
  }
 
  int port=atoi(argv[2]);
  int sock;
  struct sockaddr_in dest;
  memset(&dest,0,sizeof(struct sockaddr_in));
  dest.sin_family = AF_INET;
  dest.sin_port = htons(port);
  sock = socket(AF_INET,SOCK_STREAM,0);

  int i;
  char message[1024];
  int len = sizeof(dest);
  memset(message,'\0',sizeof(message));

  struct addrinfo *result;

  getaddrinfo(argv[1],0,0,&result);

  memcpy((void*)&((struct sockaddr_in*)result->ai_addr)->sin_addr,(void*)&dest.sin_addr, sizeof(dest));
  
  connect(sock, (struct sockaddr *) &dest, sizeof(dest));

  strcpy(message,argv[3]);
  write(sock,message,sizeof(message));
  
  int fd = open (argv[3],O_RDONLY,0666);
  
  shutdown(sock,2);
  sock = socket(AF_INET,SOCK_STREAM,0);
  
  connect(sock, (struct sockaddr *) &dest, sizeof(dest));

  memset(message,'\0',sizeof(message));
  read(fd, message, sizeof(message));

  connect(sock, (struct sockaddr *) &dest, sizeof(dest));

  write(sock,message,sizeof(message));

  shutdown(sock,2);
  close(sock);
  return EXIT_SUCCESS;
}
