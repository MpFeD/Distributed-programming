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

UDP client

Le client du programme précédent prend sur la ligne de commande l’adresse du serveur et son port. Ensuite il lit sur le flux d’entrée une suite de requêtes dont chacune doit avoir l’une des formes suivantes :

    S identificateur valeur, pour un Set ;
    G identificateur, pour un Get.
    Q, pour quitter le client.

Le client construit le message correspondant à la requête et envoie ce message au serveur en utilisant une socket et le protocole UDP. Il attend alors la réponse du serveur et l’envoie sur le flux de sortie.
Exemple d'appel :
echo "S USER moi;G USER;Q;"|tr ";" "\n"|$PWD/bin/env_client 127.0.0.1 2001
*/
int main (int argc, char** argv){

  if (argc != 3){       
    perror("arguments");
    return EXIT_FAILURE;
  }
 
  int port=atoi(argv[2]);
  int sock;
  struct sockaddr_in dest;
  memset(&dest,0,sizeof(struct sockaddr_in));
  dest.sin_family = AF_INET;
  dest.sin_port = htons(port);
  sock = socket(AF_INET,SOCK_DGRAM,0);

  int i=0;
  char message[1024],c;
  int len = sizeof(dest);

  struct addrinfo *result;

  getaddrinfo(argv[1],0,0,&result);

  memcpy((void*)&((struct sockaddr_in*)result->ai_addr)->sin_addr,(void*)&dest.sin_addr, sizeof(dest));

  while(1){
    memset(message,'\0',sizeof(message));
    i=0;
    while((c=getchar())!='\n')
      message[i++]=c;
    
    sendto(sock,message,strlen(message)+1,0,(struct sockaddr *)&dest,sizeof(dest));

    if(message[0]=='G'){
      recvfrom(sock,message,sizeof(message),0,(struct sockaddr *)&dest,&len);
      printf("%s\n",message);
    }
    
    if(message[0]=='Q')
      break;
  }
  close(sock);
  return EXIT_SUCCESS;
}
