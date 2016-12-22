#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/*
Barrieres avec signaux Temps Reels

Il faut un processus coordinateur qui connait le pid des processus, et les autres processus connaissent son pid et qui execute pas le meme code. Les processus une fois qu'il sont a la barrier envoient un signal et leurs pids.

Exemple d'appel :
$PWD/bin/src/signale_barriere 4

*/

int n=0;
int NB_PCS;
pid_t coordinateur;
pid_t *pid;
union sigval val;
sigset_t sig;

void wait_barrier(int n){
  int i;
  int mysig;
  if (n==0){
    sigdelset(&sig,SIGRTMIN);
    
    for(i=0;i<NB_PCS-1;i++)
      sigsuspend(&sig);

    for(i=0;i<NB_PCS-1;i++)
      sigqueue(pid[i],SIGRTMIN,val);

  }
  else{
    val.sival_int=getpid();
    sigqueue(coordinateur,SIGRTMIN,val);
    sigwait(&sig,&mysig);
  }
}

void process (int n) {
   printf ("avant barrière\n");
   fflush(stdout);
   wait_barrier (n);
   printf ("après barrière\n");
   fflush(stdout);
   exit (0);
}

void sig_hand(int sig, siginfo_t *info,void *inutile){
  pid[n++]=info->si_value.sival_int;
}


int main (int argc, char** argv){

  struct sigaction action;
  
  sigfillset(&sig); 
  action.sa_mask=sig; 
  action.sa_flags=SA_SIGINFO; 
  action.sa_sigaction= sig_hand;
  sigdelset(&sig,SIGINT);
  sigaction(SIGRTMIN, &action,NULL);
  sigaction(SIGRTMAX, &action,NULL);
  sigprocmask(SIG_SETMASK,&sig,NULL);
  
  
 if (argc != 2){       
   perror("arguments");
   return EXIT_FAILURE;
 }
 
 NB_PCS = atoi(argv[1]);

 
 pid = malloc(NB_PCS * sizeof(pid_t));
 
 int i,somme=0;


 for(i=0;i<NB_PCS;i++){
   if (i == 0){
     if ((coordinateur=fork())==0)
       process(i);
   }
   else
     if (fork()==0)
       process(i);
 }


 
 for(i=0;i<NB_PCS;i++)
   wait(NULL);

 free(pid);
 
 return EXIT_SUCCESS;
}
