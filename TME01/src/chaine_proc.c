#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

/*
Nous voulons faire un programme qui crée une chaîne de processus telle que le processus initial (celui du main) crée un processus qui à son tour en crée un second et ainsi de suite jusqu’à la création de N processus (en plus du processus initial). Au moment de sa création, le dernier processus de la chaîne affiche le Process ID de tous les autres processus y compris celui du processus initial. Pour tous les autres processus : chacun attend la terminaison son fils, puis affiche son propre pid, celui de son père et celui de son fils avant de se terminer.

En utilisant la fonction fork, donnez le code du programme décrit ci-dessus.

Supposons que le dernier processus créé génère une valeur aléatoire entre 0 et 100. Pour générer cette valeur aléatoire utilisez : (int)(rand () /(((double) RAND_MAX +1) /100))

Modifiez le programme pour que le processus initial affiche cette valeur aléatoire avant de se terminer.


  */

int main (int argc, char** argv){

  pid_t tab[N],fils,principal=getpid();
  int i,status;
  

  for(i=0;i<N;i++){
    if ((fils=fork())==0){
      tab[i]=getpid();
      if (i==N-1){
	for(i=0;i<N;i++)
	  printf("pid = %d\n",tab[i]);
	srand(time(NULL));
	exit((int)(rand () /(((double) RAND_MAX +1) /100)));
      }
    }
    else{
      wait(&status);
      printf("mon pere = %d, moi = %d, mon fils = %d\n",getppid(),getpid(),fils);
      break;
    }
  }

  if(principal==getpid())
    if(WIFEXITED (status))
      printf("La valeur aléatoire est : %d\n",WEXITSTATUS(status));
	
  if(WIFEXITED (status))
    exit(WEXITSTATUS(status));
  

}
