#define _XOPEN_SOURCE 700

#include <aio.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
/*
Ecrire un programme qui prend en argument un nom de fichier et une chaîne de caractères, crée un fichier vide à partir du nom donné en argument, puis écrit la chaîne de caractères dans le fichier avec aio_write, de sorte que la fin de cet appel asynchrone soit notifiée par un signal SIGRTMIN. Pendant l’écriture le programme crée un nouveau descripteur vers le même fichier, puis attend la fin de l’écriture pour aller lire le contenu du fichier et l’affiche avant de se terminer.
Exemple d'appel :
$PWD/bin/notifier_async contenant.txt contenu
*/

void sig_hand(int sig){
}


int main (int argc,char **argv){

  sigset_t sig;
  struct sigaction action;

  sigfillset(&sig); 
  action.sa_mask=sig; 
  action.sa_flags=0; 
  action.sa_handler = sig_hand; 
  sigdelset(&sig,SIGRTMIN);
  sigaction(SIGRTMIN, &action,NULL);
  sigprocmask(SIG_SETMASK,&sig,NULL);

  
  char *buf;
  buf=malloc(strlen(argv[2]));
  strcpy(buf,argv[2]);
  int fd = open(argv[1],O_CREAT | O_TRUNC | O_RDWR, 0666);
  struct aiocb a;
  a.aio_fildes=fd;
  a.aio_buf=buf;
  a.aio_nbytes=strlen(argv[2]);
  a.aio_offset=0;
  a.aio_reqprio=0;
  a.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
  a.aio_sigevent.sigev_signo = SIGRTMIN;

  aio_write(&a);

  
  int fd2 = open(argv[1],O_RDWR, 0666);
  sigsuspend(&sig);
  read(fd2,buf,strlen(buf));
  printf ("Contenu du fichier :\n%s\n",buf);
  free(buf);
  
  return EXIT_SUCCESS;
}
