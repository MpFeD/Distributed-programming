#define _XOPEN_SOURCE 700

#include <aio.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
/*
Reprenez à nouveau le premier programme en remplaçant la déclaration du signal par celle d’un temporisateur périodique, examinant toutes les 50 nanosecondes si l’écriture est terminée. Si c’est le cas, il affiche le contenu du fichier puis se termine.
Exemple d'appel :
$PWD/bin/temporiser_async contenant.txt contenu 


*/

void sig_hand(int sig){
  printf("Timer arrive à échéance...\n");
  fflush(stdout);
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
  
  timer_t timerid;
  struct sigevent signal_spec;
  signal_spec.sigev_notify = SIGEV_SIGNAL; 
  signal_spec.sigev_signo = SIGRTMIN; 
  timer_create(CLOCK_REALTIME, &signal_spec, &timerid);
  struct itimerspec tmr;
  tmr.it_value.tv_sec = 0;
  tmr.it_value.tv_nsec = 50;
  tmr.it_interval.tv_sec = 0;
  tmr.it_interval.tv_nsec = 50;
  timer_settime(timerid, 0, &tmr, NULL);
  
  char *buf;
  buf=malloc(strlen(argv[2]));
  strcpy(buf,argv[2]);
  int fd = open(argv[1],O_CREAT | O_TRUNC | O_RDWR, 0666);
  struct aiocb a;
  struct aiocb *list[1]={&a};
  a.aio_fildes=fd;
  a.aio_buf=buf;
  a.aio_nbytes=strlen(argv[2]);
  a.aio_offset=0;
  a.aio_reqprio=0;

  aio_write(&a);
	     
  int fd2 = open(argv[1],O_RDWR, 0666);

  while(1){
    aio_suspend((const struct aiocb **)list,1,(const struct timespec *)&tmr);
    if(aio_error(&a) == EINPROGRESS){
      printf ("ecriture...\n");
      fflush(stdout);
      continue;
    }
    else
      break;
    }
	     
  read(fd2,buf,strlen(buf));
  printf ("Contenu du fichier :\n%s\n",buf);
  
  return EXIT_SUCCESS;
}
