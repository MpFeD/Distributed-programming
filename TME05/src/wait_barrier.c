#define _SVID_SOURCE 1
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/types.h>
/*
Une barrière est un mécanisme de synchronisation. Elle permet à N processus de prendre rendez-vous en un point donné de leur exécution. Quand un des processus atteint la barrière, il reste bloqué jusqu’à ce que tous les autres arrivent à la barrière. Lorsque les N processus sont arrivés à la barrière, chacun peut alors reprendre son exécution.

Sans utiliser de compteur partagé, programmez la fonction wait_barrier prenant en argument un entier N et qui permet à N processus de se synchroniser sur une barrière. Ecrire ensuite un programme main créant autant de processus que demandé sur la ligne de commande, chacun exécutant le code suivant :

void process (int NB_PCS) {
   printf ("avant barrière);
   wait_barrier (NB_PCS);
   printf ("après barrière);
   exit (0);
}

L’affichage devra être le suivant :

avant barrière
avant barrière
après barrière
après barrière

En d’autres termes, on veut que tous les messages « avant barrière » soient affichés avant les messages « après barrière ». 

*/



int N;
char *nomprog;
struct sembuf operation;
key_t cle;
int semid;

void P (int n){
  operation.sem_num = 0;
  operation.sem_op = -n; 
  operation.sem_flg = SEM_UNDO;
  semop (semid , &operation, 1); 
};


void V (int n){
  operation.sem_num = 0;
  operation.sem_op = n; 
  operation.sem_flg = SEM_UNDO;
  semop (semid , &operation, 1); 
};


void wait_barrier(int NB_PCS){
  V(1);
  P(N);
  V(N+N); /* Sur la plupart des systemes, V(N) suffit. */
}



void process (int NB_PCS) {
  printf ("avant barrière\n");
  wait_barrier (NB_PCS);
  printf ("après barrière\n");
  exit (0);
}


int main(int argc, char** argv){

  int i,j,max_msg_i,envoi,somme=0;
  N=atoi(argv[1]);
  nomprog=argv[0];
  cle =ftok(nomprog, getpid());
  semid=semget(cle,1, IPC_CREAT | 0666);
  semctl(semid, 0, SETVAL, 0 );
  
  for(i=0;i<N;i++)
    if(fork()==0)
      process(N);
    
  
  for(i=0;i<N;i++)
   wait(NULL);


  semctl(semid,1, IPC_RMID,0);

  return EXIT_SUCCESS;
}
