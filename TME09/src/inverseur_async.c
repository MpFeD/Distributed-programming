#define _XOPEN_SOURCE 700

#include <aio.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

/*
Ecrire un programme qui lit un fichier par paquet de 10 caractères et les recopie dans un autre fichier en inversant l’ordre des caractères (mais pas des paquets). La lecture est synchrone, mais la recopie est asynchrone pour chaque caractère lio_listio.
Exemple d'appel :
$PWD/bin/inverseur_async source.txt dest.txt

*/ 

int main (int argc, char** argv){

 if (argc != 3){       
   perror("arguments");
   return EXIT_FAILURE;
 }

 struct aiocb a[128];
 struct aiocb *list[128];
 
 int fd = open(argv[1],O_RDWR, 0666);
 int fd2 = open(argv[2],O_CREAT | O_TRUNC | O_RDWR, 0666);
 int i=0,j,x,fin=0;
 char buf[10],c[128][10];

 while (read(fd,buf,10)){
   
    for(x=0;x<10;x++){
      if(buf[x]=='\n'){
        fin=1;
      }
    }

    if(fin)
      break;

   for(x=0;x<10;x++){
     c[i][9-x]=buf[x];
   }
   c[i][10]='\0';
   
   a[i].aio_fildes=fd2;
   a[i].aio_buf=c[i];
   a[i].aio_nbytes=10;
   a[i].aio_reqprio=0;
   a[i].aio_offset=i*10;
   a[i].aio_lio_opcode = LIO_WRITE;
   i++;
 }

 for(j=0;j<i;j++){
   list[j]=&a[j];
 }
 
 lio_listio(LIO_WAIT,list,j, NULL);
 
 return EXIT_SUCCESS;
}
