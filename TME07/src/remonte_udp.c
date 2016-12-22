#define _XOPEN_SOURCE 700


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

/*

UDP UNIX 

Reprendre l’exercice Remontée de valeurs par partage de mémoire pour que les valeurs aléatoires transmises par les fils au père passent non plus par un segment de mémoire partagée, mais par datagrammes UDP. Le programme devra créer une socket UDP et la rendre accessible par bind, puis l’utiliser à la fois pour les envois (par sendto) et les réceptions (par recvfrom) de datagrammes (évidement d’autres solutions seraient possibles). Le programme prendra en premier argument le nom de la socket, et en deuxième argument le nombre de processus à créer.

Remarque : afin de permettre plusieurs exécutions de ce programme, veiller avant sa terminaison à appliquer unlink sur le nom de la socket afin de le rendre disponible si vous utilisez une socket de type AF_UNIX.
Exemple d'appel :
$PWD/bin/remonte_udp sockudp 4
*/


int N;
int sock;
struct sockaddr_un addr;

void remonte_udp(){
 int i;
 int somme=0;
 char message[128];
 int len = sizeof(addr);
 memset(message,'\0',sizeof(message));
 for (i=0;i<N;i++){
   if (fork()==0){
     srand(getpid());
     int a = (int) (10*(float)rand()/ RAND_MAX);
     message[0]=a + '0';
     printf("%c\n",message[0]);
     sendto(sock,message,strlen(message)+1,0,(struct sockaddr *)&addr,sizeof(addr));
     close(sock);
     exit(0);
   }
 }

 for (i=0;i<N;i++){
   wait(NULL);
 }
 
 for (i=0;i<N;i++){
   recvfrom(sock,message,sizeof(message),0,0,&len);
   somme+= message[0]-'0';
 }

 printf ("Somme = %d\n",somme);
   
}

int main (int argc, char** argv){

 if (argc != 3){       
   perror("arguments");
   return EXIT_FAILURE;
 }

 memset(&addr,0,sizeof(struct sockaddr_un));
 addr.sun_family = AF_UNIX;
 strcpy(addr.sun_path,argv[1]);
 sock = socket(AF_UNIX,SOCK_DGRAM,0);
 bind (sock, (struct sockaddr *)&addr,sizeof(struct sockaddr_un));

 N = atoi(argv[2]);
 
 remonte_udp();


 close(sock);
 unlink(argv[1]);

 return EXIT_SUCCESS;
}
