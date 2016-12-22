#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define N 5

sigset_t sig;
struct sigaction action;


/*
Nous voulons maintenant changer le programme de la manière suivante. L’exécution de tous les processus, à l’exception du processus initial, doit être stoppée avec un signal SIGSTOP. Lorsque tous les processus sont effectivement stoppés, le processus initial affiche : Tous les descendants stoppés. L’exécution de ces processus doit alors reprendre pour que ceux-ci se terminent. Lorsque tous se sont terminés, le programme initial affiche Fin du programme.

Observations :

    Vous ne pouvez pas utiliser les fonctions de la famille wait (e.g. wait, waitpid, wait3, etc) pour attendre la fin d’un processus ; trouvez une autre méthode.
    Utilisez toujours la fonction fork pour créer des processus.

  */

void sig_hand(int sig){
}

int main (int argc, char** argv){
  
  sigfillset(&sig); 
  action.sa_mask=sig; 
  action.sa_flags=0; 
  action.sa_handler = sig_hand; 
  sigaction(SIGINT, &action,NULL);
  sigprocmask(SIG_SETMASK,&sig,NULL);

  pid_t tab[10],fils,principal=getpid();
  int i=0, j=1;
  tab[i++]=getpid();
  for(i=1;i<10;i++){
    if((fils=fork())==0){
      tab[i]=getpid();
      if (i==9){//Dernier Fils
	printf("Le dernier fils affiche la liste de tous les pid : \n");
	printf("pid du processus numéro %d = %d\n",0,principal);
	while(j<9){
	  printf("pid du processus numéro %d = %d\n",j,tab[j]);
	  kill(tab[j++],SIGSTOP);
	}
	printf("pid du processus numéro %d = %d\n",9,tab[9]);
	if (j==9){
	  kill(principal,SIGINT); //Deblocage sigsuspend A
	  kill(getpid(),SIGSTOP); 
	  kill(principal,SIGINT); //Deblocage sigsuspend C
	  exit(0);
	}
      }
    }
    else
      break;
  }
  if (principal==getpid()){
    sigdelset(&sig,SIGINT);
    sigsuspend(&sig); // A
    sigaddset(&sig,SIGINT);
    printf("Tous les processus sont stoppés\n");
    kill(fils,SIGCONT); 
    kill(fils,SIGINT); //Deblocage du sigsupend B
  }
  else{
    sigdelset(&sig,SIGINT);
    sigsuspend(&sig); // B
    sigaddset(&sig,SIGINT);
    if(j!=9){
      kill(fils,SIGCONT);
      kill(fils,SIGINT);
    }
  }
  printf ("Mon pid : %d, le pid de mon pere : %d, le pid de mon fils : %d\n",getpid(), getppid(),fils);
  if (principal==getpid()){
    sigdelset(&sig,SIGINT);
    sigsuspend(&sig); // C
    sigaddset(&sig,SIGINT);
    printf("Fin du programme\n");
    kill(fils,SIGINT);
  }else{
    sigsuspend(&sig);
    if(j!=9)
      kill(fils,SIGINT);
  }
  
  return EXIT_SUCCESS;

}
