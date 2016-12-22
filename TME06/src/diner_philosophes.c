#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>


/* Diner des philosophes */

int N;
int *baguettes;
sem_t *s1;

void prendre(int n){
  int d=n;
  int g;
  if (n==0)
    g=N-1;
  else
    g=n-1;

  sem_wait(&s1[d]);
  sem_wait(&s1[g]);
  
  if(baguettes[g]==1 && baguettes[d]==1)
    printf("erreur baguettes prises\n");

  baguettes[g]=1;
  baguettes[d]=1;
  
}

void poser(int n){
  int d=n;
  int g;
  if (n==0)
    g=N-1;
  else
    g=n-1;

  if(baguettes[g]==0 && baguettes[d]==0)
    printf("erreur baguettes possées\n");
  
  baguettes[g]=0;
  baguettes[d]=0;

  sem_post(&s1[d]);
  sem_post(&s1[g]);
}

int main(int argc, char** argv){
  
  N = atoi(argv[1]);
  int C = atoi(argv[2]);
  int P = atoi(argv[3]);
  int M = atoi(argv[4]);
  int i, j;

  
  /*
   * Voici les segments de mémoire,
   * un segment pour le tableau des
   * baguettes
   */

  int fd = shm_open ("seg",O_CREAT | O_TRUNC | O_RDWR,0666);
  ftruncate(fd, N*sizeof(int));
  baguettes = mmap(NULL, N*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  int fd2 = shm_open ("seg2",O_CREAT | O_TRUNC | O_RDWR,0666);
  ftruncate(fd2, N*sizeof(sem_t));
  s1 = mmap(NULL, N*sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);


  /*
   * Inialisation des semaphores
   */
  
  for(i=0;i<N;i++){
    baguettes[i]=0;
    sem_init(&s1[i], 1, 1);
  }

  
  for(i=0;i<N;i++){
    if(fork()==0){
       for(j=0;j<C;j++){
	 printf("Le philosophe %d pense\n",i);
	 fflush(stdout);
	 sleep(P);
	 prendre(i);
	 printf("Le philosophe %d mange\n",i);
	 fflush(stdout);
	 sleep(M);
	 poser(i);
       }
       printf("Fin %d\n",i);
       exit(0);
    }
  }

  for(i=0;i<N;i++){
    wait(NULL);
  }


  printf("Fin\n");

  for (i=0;i<N;i++){
    sem_destroy(&s1[i]);
  }

  munmap(baguettes, N * sizeof(int));
  shm_unlink("seg");
  munmap(s1, N * sizeof(sem_t));
  shm_unlink("seg2");
  
  return EXIT_SUCCESS;
}
