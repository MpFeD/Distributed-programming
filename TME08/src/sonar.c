#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>

/*

  UDP Sonar broadcast

On cherche à créer une application qui permet, à la manière d’un sonar, de repérer tous les nœuds disponibles sur le réseau local. Un programme sonar diffuse toutes les 3 secondes un message "PING" en mode Broadcast sur le port 9999, puis attend en réponse un message "PONG" des sites disponibles et affiche leur identité. Le sonar comporte deux Threads : un qui attend les réponses sur le port 9999, et un autre qui s’occupe de la diffusion. De leurs côtés, les nœuds disponibles exécutent le programme Ponger qui attend l’arrivée de messages sur le port de diffusion, et renvoie à l’émetteur de tout "PING" un message "PONG".

N.B : Pour obtenir l’adresse valide de Broadcast sur votre sous-réseau, utilisez la valeur INADDR_BROADCAST.
Exemple d'appel :
$PWD/bin/sonar

(on s'arrete apres la diffusion de 5 pong)

*/

char host[64];
int sock;
struct sockaddr_in myexp;
struct sockaddr_in mysin;
socklen_t len = sizeof(struct sockaddr_in);
char message[1024];


void *emission (void *arg){
  int i=0;
  strcpy(message,"PING");
  while(1){
    sendto(sock,message,sizeof(message)+1,0,(struct sockaddr *)&mysin, sizeof(mysin));
    if (i==5)
      break;
    i++;
    sleep(3);
  }
  pthread_exit ((void*)0);
}

void *reception (void *arg){
  int i=0;
  while(1){
    recvfrom(sock,message,sizeof(message),0,(struct sockaddr *)&myexp,&len);
    printf("message = %s\n",message);
    fflush(stdout);
    if ((strcmp(message,"PONG"))==0){
      getnameinfo((struct sockaddr *)&myexp, sizeof(myexp),host, sizeof(host), 0, 0, 0);
      printf("%s\n",host);
      fflush(stdout);
      i++;
    }
    if (i==5)
      break;
  }
  pthread_exit ((void*)0);
}



int main (int argc, char** argv){
  sock = socket(AF_INET,SOCK_DGRAM,0);
  int port=9999;
  pthread_t tid [2];
  memset(&mysin,0,sizeof(struct sockaddr_in));
  memset(&myexp,0,sizeof(struct sockaddr_in));
  mysin.sin_family = AF_INET;
  mysin.sin_port = htons(port);
  mysin.sin_addr.s_addr = htonl(INADDR_BROADCAST);
  

  int broadcastEnable=1;
  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &broadcastEnable, sizeof(broadcastEnable));

  bind (sock,(struct sockaddr *)&mysin,sizeof(mysin));
       
  pthread_create (&(tid[0]),NULL,emission,NULL);
  pthread_create (&(tid[1]),NULL,reception,NULL);
  pthread_join (tid[0],NULL);
  pthread_join (tid[1],NULL);
  
  close(sock);
  printf ("\nFin programme principal\n");
  return EXIT_SUCCESS;
}
