#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

/*

  TCP server

  On se propose dans cette séance d’écrire un serveur et un client simulant un service FTP minimal, réduit à 3 opérations :

  "LIST" : obtention de la liste des fichiers conservés sur le serveur ;
  "UPLOAD" : téléchargement de fichier depuis le client vers le serveur ;
  "DOWNLOAD" : téléchargement de fichier depuis le serveur vers le client.

  Dans cette question il s’agit d’écrire le serveur, qui reçoit en ligne de commande le numéro de port où l’appeler, et le répertoire où entreposer les fichiers envoyés par les clients. Les connexions se feront en TCP. On considère qu’un serveur ne peut traiter qu’un client à la fois.
  Exemple d'appel :
  $PWD/bin/ftp_server 2000 /tmp &
*/

int main (int argc, char** argv){
  
  if (argc != 3){       
    perror("arguments");
    return EXIT_FAILURE;
  }

  DIR *pt_Dir;
  struct dirent* dirEnt;
  char buff_path[1024];
 
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

  int i;
  char message[1024];
  int len = sizeof(sock);
  char c;
  
  while(1){
    i=0;
    memset(message,'\0',sizeof(message));
    scom = accept(sock, (struct sockaddr *)&exp,&len);
    read(scom,message,sizeof(message));

    if(strcmp(message,"QUIT")==0)
      break;

    if(strcmp(message,"LIST")==0){
      memset(message,'\0',sizeof(message));
      getcwd (buff_path, 1024);
      strcat(buff_path,argv[2]);
      pt_Dir = opendir (buff_path);
    
      while ((dirEnt= readdir (pt_Dir)) !=NULL) {
	if ((strcmp(dirEnt->d_name,".") ==0) || (strcmp(dirEnt->d_name,"..") ==0))
	  continue;
        strcat(message, strcat(dirEnt->d_name,"\n"));
      }
      closedir (pt_Dir);
      write(scom,message,sizeof(message));
      shutdown(scom,2);
    }

    
    if(strcmp(message,"UPLOAD")==0){
      memset(message,'\0',sizeof(message));
      read(scom,message,sizeof(message));
      getcwd (buff_path, 1024);
      strcat(buff_path,argv[2]);
      strcat(buff_path,"/");
      strcat(buff_path,message);
      int fd = open (buff_path,O_CREAT | O_TRUNC | O_RDWR, 0666);
      memset(message,'\0',sizeof(message));
      read(scom,message,sizeof(message));
      write(fd,message,strlen(message));
      memset(message,'\0',sizeof(message));
      shutdown(scom,2);
    }

    if(strcmp(message,"DOWNLOAD")==0){
      memset(message,'\0',sizeof(message));
      read(scom,message,sizeof(message));
      getcwd (buff_path, 1024);
      strcat(buff_path,argv[2]);
      strcat(buff_path,"/");
      strcat(buff_path,message);
      int fd = open (buff_path,O_RDWR, 0666);
      memset(message,'\0',sizeof(message));
      read(fd,message,sizeof(message));
      write(scom,message,strlen(message));
      memset(message,'\0',sizeof(message));
      shutdown(scom,2);
    }
    
  }
  
  close(scom);
  close(sock);
  return EXIT_SUCCESS;
}
