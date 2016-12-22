#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define N 5

sigset_t sig;
struct sigaction action;


/*

Reprenez la chaîne de processus de l’exercice 1 (avec le dernier descendant ayant la connaissance du pid de tous les processus de la chaîne.) Supposons que vous ne pouvez pas utiliser la fonction wait ni le signal SIGCHLD dans votre programme. Cependant, nous voulons toujours assurer qu’aucun processus ne puisse se terminer avant que tous les autres aient été créés.

Modifiez le programme en conséquence en utilisant des signaux (mais pas SIGCHILD).

N.B : vous n’avez pas à produire ni récupérer la valeur aléatoire dans cet exercice.

  */

void sig_hand(int sig){
}

int main (int argc, char** argv){

  sigfillset(&sig);
  sigdelset(&sig,SIGINT);
  sigprocmask(SIG_SETMASK,&sig,NULL);
  action.sa_mask=sig; 
  action.sa_flags=0; 
  action.sa_handler = sig_hand;
  sigaction(SIGINT, &action,NULL);
  

  pid_t tab[N],fils,principal=getpid();
  int i,status;
  

  for(i=0;i<N;i++){
    if ((fils=fork())==0){
      tab[i]=getpid();
      if (i==N-1){
	for(i=0;i<N;i++)
	  printf("pid = %d\n",tab[i]);
	kill(getppid(),SIGINT);
	exit(0);
	
      }
    }
    else{  
      sigsuspend(&sig);
      printf("mon pere = %d, moi = %d, mon fils = %d\n",getppid(),getpid(),fils);
      if(principal!=getpid())
	kill(getppid(),SIGINT);
      
      break;
    }
  }

  return EXIT_SUCCESS;
  
}
