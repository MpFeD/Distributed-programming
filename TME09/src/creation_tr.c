#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

/*
Ecrire un programme qui crée une chaîne de N processus, N étant l’argument du programme. Chaque processus créé doit afficher son Pid ainsi que son ordre de création, mais l’ordre des affichages se fait dans l’ordre inverse des créations. Cet ordre sera imposé en utilisant des signaux POSIX 4. N.B : vous n’utiliserez pas de processus coordinateur pour effectuer cette synchronisation.
Exemple d'appel :
$PWD/bin/src/creation_tr 4

*/

void sig_hand(int sig){
}

int main (int argc, char** argv){

  sigset_t sig;
  struct sigaction action;

  sigfillset(&sig); 
  action.sa_mask=sig; 
  action.sa_flags=0; 
  action.sa_handler = sig_hand; 
  sigaction(SIGRTMIN, &action,NULL);
  sigprocmask(SIG_SETMASK,&sig,NULL);

  union sigval val;
  
 if (argc != 2){       
   perror("arguments");
   return EXIT_FAILURE;
 }
 int N = atoi(argv[1]);
 pid_t pid[N];

 int i=0,n;
 for(i=0;i<N;i++)
   if((pid[i]=fork())==0){
     sigwait(&sig,&n);
     printf("pid : %d ordre : %d\n",getpid(),i);
     fflush(stdout);
     exit(0);
   }
 
 for(i=0;i<N;i++){
   sigqueue(pid[N-i-1],SIGRTMIN,val);
   wait(NULL);
 }
 
 return EXIT_SUCCESS;
}
