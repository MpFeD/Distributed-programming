#define _XOPEN_SOURCE 700

#include <aio.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

/*Reprenez l’exercice Remontée de valeurs par communication distante pour que les valeurs aléatoires transmises par les fils soient échangées avec le père en passant par un fichier lur et écrit de manière asynchrone.

Exemple d'appel :
$PWD/bin/remonte_async 4
*/
   

int main (int argc, char** argv){

 if (argc != 2){       
   perror("arguments");
   return EXIT_FAILURE;
 }

 int N = atoi(argv[1]);
 
 struct aiocb a;
 struct aiocb *list[1]={&a};
 
 int fd = open("./remonte",O_CREAT | O_TRUNC | O_RDWR, 0666);

 char c;
 
 a.aio_fildes=fd;
 a.aio_buf=&c;
 a.aio_nbytes=1;
 a.aio_reqprio=0;
 
 int i;
 int somme=0;
 for (i=0;i<N;i++){
   if (fork()==0){
     a.aio_offset=i;
     srand(getpid());
     int n = (int) (10*(float)rand()/ RAND_MAX);
     c=n+'0';
     printf("%c\n",c);
     aio_write(&a);
     aio_suspend((const struct aiocb **)list,1,NULL);
     exit(0);
   }
 }

 
 for (i=0;i<N;i++){
   wait(NULL);
 }
 
 for (i=0;i<N;i++){
   a.aio_offset=i;
   aio_read(&a);
   aio_suspend((const struct aiocb **)list,1,NULL);
   somme+=c-'0';
 }

 printf ("Somme = %d\n",somme);


 return EXIT_SUCCESS;
}
