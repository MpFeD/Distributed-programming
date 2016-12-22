#define _SVID_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

/*
Reprenez l’exercice Des producteurs et des consommateurs en remplaçant les Threads secondaires par des processus fils, et en construisant la pile dans un segment de mémoire partagée.
*/

#define MAX 100

sigset_t sig_proc;
struct sigaction action;

void sig_hand(){
}

char *pile;
int *stack_size;

int sem_id;
int nbprod,nbcons;

struct sembuf operation;

void P (int sem)
{
  operation.sem_num=sem;
  operation.sem_op=-1;
  operation.sem_flg=SEM_UNDO;
  semop (sem_id, &operation, 1);
};

void V(int sem)
{
  operation.sem_num=sem;
  operation.sem_op=1;
  operation.sem_flg=SEM_UNDO;
  semop (sem_id, &operation, 1);
};

void push (char c){
  P(0);
  int i;
  if(stack_size[0] == MAX)
    P(1);
  pile[stack_size[0]++]=c;
  printf ("char push : %c\n",c);
  fflush(stdout);
  if (stack_size[0]==1)
    for(i=0;i<nbcons;i++)
      V(2);
  V(0);
}

char pop (){
  int i;
  P(0);
  char ret='\0';
  if(stack_size[0] == 0)
    P(2);
  ret = pile[--stack_size[0]];
  printf ("char pop : %c\n",ret);
  fflush(stdout);
  pile[stack_size[0]]='\0';
  if (stack_size[0]==MAX)
    for(i=0;i<nbprod;i++)
      V(1);
  V(0);
  return ret;
}

void Producteur(){
  int c;
  while((c = getchar()) != EOF){
    push(c);
  }
  exit(0);
}

void Consommateur(){
  while(1) {
    putchar(pop());
    fflush(stdout);
  }
  exit(0);
}

int main (int argc, char** argv) {

  if(argc != 3){
    perror("arguments\n");
    return EXIT_FAILURE;
  }

  int i;
  nbprod=atoi(argv[1]),nbcons=atoi(argv[2]);
  pid_t pid[nbcons];
  struct shmid_ds *buf;
 
  /*
   *Segment mémoire pour la pile
   */
  key_t cle;
  cle = ftok(argv[0], (int)((char)('a' & 11111111)));
  int shm_id = shmget (cle,MAX*sizeof(char), 0666 | IPC_CREAT);
  char *adr_att;
  adr_att = shmat(shm_id, 0, 0600);
  pile = (char*) adr_att;

  /*
   *Segment mémoire pour la variable stack_size (taille actuelle de la pile)
   */
  key_t cle2;
  cle2 = ftok(argv[0], (int)((char)('b' & 11111111)));
  int shm_id2 = shmget (cle2,sizeof(int), 0666 | IPC_CREAT);
  char *adr_att2;
  adr_att2 = shmat(shm_id2, 0, 0600);
  stack_size = (int*) adr_att2;

  /*
   *Semaphores
   */
  key_t cle3;
  cle3 = ftok(argv[0], (int)((char)('c' & 11111111)));
  sem_id = semget (cle3,3, 0666 | IPC_CREAT);
  semctl(sem_id,0, SETVAL, 1);
  semctl(sem_id,1, SETVAL, 0);
  semctl(sem_id,2, SETVAL, 0);


  for(i=0;i<nbprod;i++)
    if(fork()==0)
      Producteur();
       
  for(i=0;i<nbcons;i++)
    if((pid[i]=fork())==0)
      Consommateur();

  for(i=0;i<nbprod;i++)
    wait(NULL);




  
  /*
   *Utilisation de signaux pour terminer proprement
   */

  sigfillset(&sig_proc);
  action.sa_mask=sig_proc;
  action.sa_flags=0;
  action.sa_handler = sig_hand;
  sigdelset(&sig_proc,SIGINT);
  sigaction(SIGINT, &action,NULL);
  sigprocmask(SIG_SETMASK,&sig_proc,NULL);

  sleep(1);
 
  printf ("\nPour terminer proprement, utiliser C-c (SIGINT)\n");
  fflush(stdout);
  sigsuspend(&sig_proc);
 
  /*
   *On tue les consommateurs qui bouclent à l'infini
   */
  for(i=0;i<nbcons;i++)
    kill(pid[i],SIGKILL);

  for(i=0;i<nbcons+nbprod;i++)
    wait(NULL);

  shmdt(adr_att);
  shmdt(adr_att2);
  shmctl(shm_id, IPC_RMID, buf);
  shmctl(shm_id2, IPC_RMID, buf);
  semctl(sem_id, 0, IPC_RMID, 0);
  semctl(sem_id, 1, IPC_RMID, 0);
  semctl(sem_id, 2, IPC_RMID, 0);
  printf ("\nFin programme principal\n");
  
  
  return EXIT_SUCCESS;
}
