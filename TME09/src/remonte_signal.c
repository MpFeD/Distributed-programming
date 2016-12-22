#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/*
Reprenez à nouveau l’exercice Remontée de valeurs par communication distante pour que les valeurs aléatoires transmises par les fils soient échangées avec le père en envoyant des signaux temps réel POSIX 4.
Exemple d'appel :
$PWD/bin/remonte_signal 4

*/

int *valeurs;
int n=0;

void sig_hand(int sig, siginfo_t *info,void *inutile){
  valeurs[n++]=info->si_value.sival_int;
}

int main (int argc, char** argv){

  sigset_t sig;
  struct sigaction action;
  
  sigfillset(&sig); 
  action.sa_mask=sig; 
  action.sa_flags=SA_SIGINFO; 
  action.sa_sigaction= sig_hand;
  sigdelset(&sig,SIGRTMIN);
  sigaction(SIGRTMIN, &action,NULL);
  sigprocmask(SIG_SETMASK,&sig,NULL);
  
  union sigval val;
  
 if (argc != 2){       
   perror("arguments");
   return EXIT_FAILURE;
 }
 int N = atoi(argv[1]);

 valeurs = malloc(N * sizeof(int));
 
 int i,somme=0;
 for(i=0;i<N;i++)
   if(fork()==0){
     srand(getpid());
     int a = (int) (10*(float)rand()/ RAND_MAX);
     printf("%d\n",a);
     val.sival_int=a;
     sigqueue(getppid(),SIGRTMIN,val);
     exit(0);
   }
 
 for(i=0;i<N;i++){
   sigsuspend(&sig);
   wait(NULL);
 }

 for(i=0;i<N;i++)
   somme+=valeurs[i];

 printf("Somme = %d\n",somme);

 free(valeurs);
 
 return EXIT_SUCCESS;
}
