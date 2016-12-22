#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
/*

TCP server

On souhaite écrire un programme attendant sur un port une demande de connexion de la part d’un client. Ce programme prend en ligne de commande le numéro du port sur lequel il attend les demandes de connexion. Lorsqu’une connexion s’ouvre, il lit la première ligne envoyée et considère que c’est le nom d’un fichier ; il crée alors dans son répertoire d’exécution un fichier vide portant ce nom. Il lit ensuite les données transmises jusqu’à la fin de la connexion, et les recopie dans le fichier créé précédemment.

Le programme récepteur stocke les fichiers recopiés dans son répertoire d’exécution.
Exemple d'appel :
$PWD/bin/recvfile 2000 &
*/

int main (int argc, char** argv){
  
  if (argc != 2){       
    perror("arguments");
    return EXIT_FAILURE;
  }
 
  int port=atoi(argv[1]);
  int sock;
  int scom;
  
  struct sockaddr_in sin;
  struct sockaddr_in exp;
  memset(&sin,0,sizeof(struct sockaddr_in));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sock = socket(AF_INET,SOCK_STREAM,0);
  bind (sock, (struct sockaddr *)&sin,sizeof(sin));

  listen(sock,1);

  int i=0;
  char message[1024];
  int len = sizeof(sock);
  char c;
  memset(message,'\0',sizeof(message));
  
  scom = accept(sock, (struct sockaddr *)&exp,&len);
  while(1){
    read(scom,&c,1);
    if (c == '\0')
      break;
    else
      message[i++]=c;
  }
  
  strcat(message,"_copie");
  int fd = open (message, O_CREAT | O_TRUNC | O_RDWR, 0666);
  shutdown(scom,2);
  close(scom);

  memset(message,'\0',sizeof(message));
  scom = accept(sock, (struct sockaddr *)&exp,&len);
  read(scom,message,sizeof(message));
  write(fd,message,sizeof(message));
  shutdown(scom,2);
  close(scom);
  close(sock);
  return EXIT_SUCCESS;
}
