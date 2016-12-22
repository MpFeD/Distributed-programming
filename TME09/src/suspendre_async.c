#define _XOPEN_SOURCE 700

#include <aio.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

/*
Modifier le programme de l’exercice précédant pour que la fin de l’écriture ne soit plus notifiée par signal, mais soit attendue par un appel à aio_suspend. Pendant l’écriture le programme crée un nouveau descripteur vers le même fichier, puis attend la fin de l’écriture pour aller lire, cette fois-ci de manière asynchrone (aio_read), le contenu du fichier et l’affiche avant de se terminer.
Exemple d'appel :
$PWD/bin/suspendre_async contenant.txt contenu 


*/


int main (int argc,char **argv){
  
  char *buf;
  buf=malloc (strlen (argv[2]));
  strcpy(buf,argv[2]);
  int fd = open(argv[1],O_CREAT | O_TRUNC | O_RDWR, 0666);
  struct aiocb a;
  struct aiocb *list[1];
  list[0]=&a;
   
  a.aio_fildes=fd;
  a.aio_buf=buf;
  a.aio_nbytes=strlen(argv[2]);
  a.aio_offset=0;
  a.aio_reqprio=0;

  aio_write(&a);

  
  int fd2 = open(argv[1],O_RDWR, 0666);

  while(1){
    aio_suspend((const struct aiocb **)list,1,NULL);
    if(aio_error(&a) == EINPROGRESS){
      printf ("ecriture...\n");
      fflush(stdout);
      continue;
    }
    else
      break;
}
  
  a.aio_fildes=fd2;
  aio_read(&a);

  while(1){
    aio_suspend((const struct aiocb **)list,1,NULL);
    if(aio_error(&a) == EINPROGRESS){
      printf ("lecture...\n");
      fflush(stdout);
    }
    else
      break;
   
  }
  
  printf ("Contenu du fichier :\n%s\n",buf);
  
  return EXIT_SUCCESS;
}
