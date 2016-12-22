#define _SVID_SOURCE 1
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*
Modifiez le programme de l’exercice précédent pour que les valeurs aléatoires transmises par les fils passent non plus par une file de messages, mais par un segment de mémoire partagée System V. Il faudra le libérer grâce à la fonction shmctl.
Exemple d'appel :
bin/remonte_partagee 4

*/

char *p_int, *adr_att;


int main(int argc, char** argv){

  int i,somme=0;
  struct shmid_ds *buf;
  key_t cle = ftok(argv[0], getpid());
  int shmid = shmget(cle,1024, 0666 | IPC_CREAT);
  adr_att = shmat(shmid, 0, 0600);
  p_int = adr_att;
  

  for(i=0;i<atoi(argv[1]);i++){
    if(fork()==0){
      srand(getpid());
      printf("%d\n",p_int[i]=(int) (10*(float)rand()/ RAND_MAX));
      exit(0);
    }
  }

  for(i=0;i<atoi(argv[1]);i++)
   wait(NULL);
  
  for(i=0;i<atoi(argv[1]);i++){
    somme+=p_int[i];
  }
  
  printf ("Somme=%d\n",somme);

  shmdt(adr_att);
  shmctl(shmid, IPC_RMID, buf);
  
  
  return EXIT_SUCCESS;
}
