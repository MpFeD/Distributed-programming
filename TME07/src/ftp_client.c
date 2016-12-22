#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <dirent.h>

/*

TCP client

Le client prend sur la ligne de commande l’adresse IP du serveur et son numéro de port. Il s’y connecte immédiatement, et en cas de réussite rentre dans une boucle de lecture ligne par ligne des requêtes de l’utilisateur au clavier. Pour chaque ligne, il vérifie que la requête demandée est bien l’une des trois indiquée dans l’énoncé, si oui l’envoie au serveur, attend sa réponse et l’affiche dans le flux de sortie.
Exemple d'appel :
$PWD/bin/ftp_client 127.0.0.1 2000
*/

int main (int argc, char** argv){

  if (argc != 3){       
    perror("arguments");
    return EXIT_FAILURE;
  }
  DIR *pt_Dir;
  struct dirent* dirEnt;
  char buff_path[1024];

  
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
  char c;
  memset(message,'\0',sizeof(message));

  struct addrinfo *result;

  getaddrinfo(argv[1],0,0,&result);

  memcpy((void*)&((struct sockaddr_in*)result->ai_addr)->sin_addr,(void*)&dest.sin_addr, sizeof(dest));

  while(1){
    i=0;
    sock = socket(AF_INET,SOCK_STREAM,0);
    connect(sock, (struct sockaddr *) &dest, sizeof(dest));
    memset(message,'\0',sizeof(message));
    while((c=getchar())!='\n')
      message[i++]=c;

    message[i]='\0'; 
  
    write(sock,message,sizeof(message));
    if(strcmp(message,"QUIT")==0)
      break;
    
    if(strcmp(message,"UPLOAD")==0){
      getcwd (buff_path, 1024);
      pt_Dir = opendir (buff_path);
      printf("Quel fichier voulez vous upload\n");
      while ((dirEnt= readdir (pt_Dir)) !=NULL) {
	if ((strcmp(dirEnt->d_name,".") ==0) || (strcmp(dirEnt->d_name,"..") ==0))
	  continue;
        printf("%s\n",dirEnt->d_name);
      }
      i=0;
      while((c=getchar())!='\n')
	message[i++]=c;
      message[i]='\0';
      write(sock,message,sizeof(message));
      int fd = open (message, O_RDWR, 0666);
      memset(message,'\0',sizeof(message));
      read (fd,message,sizeof(message));
      write(sock,message,sizeof(message));
      shutdown(sock,2);
    }
    
    if(strcmp(message,"LIST")==0){
      read(sock,message,sizeof(message));
      printf("%s\n",message);
      shutdown(sock,2);
    }


    if(strcmp(message,"DOWNLOAD")==0){
      i=0;
      memset(message,'\0',sizeof(message));
      printf("Quel fichier voulez vous download\n");
      fflush(stdout);
      while((c=getchar())!='\n')
	message[i++]=c;
      message[i]='\0';
      write(sock,message,sizeof(message));
      printf("message=%s\n",message);
      fflush(stdout);
      int fd = open (message,O_CREAT | O_TRUNC| O_RDWR, 0666);
      memset(message,'\0',sizeof(message));
      read (sock,message,sizeof(message));
      printf("message=%s\n",message);
      fflush(stdout);
      write(fd,message,sizeof(message));
      shutdown(sock,2);
    }
    
    
  }
  
  shutdown(sock,2);
  close(sock);
  return EXIT_SUCCESS;
}
