#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>

/*

UDP server

On souhaite réaliser un mini-serveur d’environnement qui communique avec ses clients par UDP, sur un port dont le numéro est donné sur la ligne de commande du serveur à son démarrage. Ce qu’on appelle ici un environnement est une liste de couples identificateur, valeur. Les identificateurs et les valeurs sont de type chaîne de caractères.

Le serveur reconnait deux opérations :

    set(identificateur, valeur) : pour fixer la valeur d’un identificateur ;
    get(identificateur) : pour obtenir la valeur d’un identificateur.

Pour éviter d’avoir à définir et à gérer une structure de données, on pourra utiliser directement l’environnement du processus serveur via les fonctions getenv et setenv.
Exemple d'appel :
$PWD/bin/env_serveur 2001 &
*/

int main (int argc, char** argv){
  
  if (argc != 2){       
    perror("arguments");
    return EXIT_FAILURE;
  }
 
  int port=atoi(argv[1]);
  int sock;
  
  struct sockaddr_in sin;
  struct sockaddr_in exp;
  memset(&sin,0,sizeof(struct sockaddr_in));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sock = socket(AF_INET,SOCK_DGRAM,0);
  bind (sock, (struct sockaddr *)&sin,sizeof(sin));

  int i=0,j=0;
  char message[1024];
  char name[1024];
  char value[1024];
  int len = sizeof(sock);
  char c;
  
  while(1){
    memset(message,'\0',sizeof(message));
    recvfrom(sock,message,sizeof(message),0,(struct sockaddr *)&exp,&len);
    if (message[0]=='Q')
      break;
    if (message[0]=='S'){
      i=2;
      while(1){
	if (message[i]==' '){
	  i++;
	  break;
	}
	name[j]=message[i];
	i++;
	j++;
      }
      name[j]='\0';
      j=0;
      while(1){
	if (message[i]=='\0')
	  break;
	value[j]=message[i];
	i++;
	j++;
      }
      value[j]='\0';
      setenv(name,value,1);
    }

    j=0;
    if (message[0]=='G'){
      i=2;
      while(1){
	if (message[i]=='\0'){
	  break;
	}
	name[j]=message[i];
	i++;
	j++;
      }
      name[j]='\0';
      strcpy(message,getenv(name));
      sendto(sock,message,strlen(message)+1,0,(struct sockaddr *)&exp,sizeof(exp));
    }
  }
  
  close(sock);
  return EXIT_SUCCESS;
}
