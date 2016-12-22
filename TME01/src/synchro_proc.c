#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#define N 5

sigset_t sig;
struct sigaction action;




/*

Nous avons un processus P1 qui crée un processus P2 (fils de P1) qui à son tour crée un processus P3 (fils de P2 et petit-fils de P1). Lorsque le processus P3 est créé, il envoie un signal à son grand-père, le processus P1, pour lui signaler sa création, puis se termine juste après. Quand son père, le processus P2, prend connaissance de la terminaison de P3, il envoie un signal à P1, son père, pour signaler la mort de son fils. Après P2 se termine lui aussi. Le processus P1 doit traiter les événements dans l’ordre décrit ci-dessus. Autrement dit, il doit premièrement traiter la délivrance du signal de P3 en affichant le message « Processus P3 créé », ensuite la délivrance du signal de P2 en affichant « Processus P3 terminé » et à la fin afficher « Processus P2 terminé » lorsqu’il prend connaissance de la mort de son fils.

Programmez une telle synchronisation.


  */

void sig_hand(int sig){
}

int main (int argc, char** argv){

  pid_t tab[N],fils,principal=getpid();
  int i,status;

  
  sigfillset(&sig);
  sigdelset(&sig,SIGINT);
  sigprocmask(SIG_SETMASK,&sig,NULL);
  action.sa_mask=sig; 
  action.sa_flags=0; 
  action.sa_handler = sig_hand;
  sigaction(SIGUSR1, &action,NULL);
  sigaction(SIGUSR2, &action,NULL);
  if (fork()==0)
    if (fork()==0){
      kill(principal,SIGUSR1);
      exit(0);
    }
  
  if (getpid()==principal){
    sigdelset(&sig,SIGUSR1);
    sigsuspend(&sig);
    printf("P3 créé\n");
    sigdelset(&sig,SIGUSR2);
    sigsuspend(&sig);
    printf("P3 terminé\n");
    wait(NULL);
    printf("P2 terminé\n");
  }
  else{
    wait(NULL);
    kill(principal,SIGUSR2);
    exit(0);
  }
  return EXIT_SUCCESS;
}
