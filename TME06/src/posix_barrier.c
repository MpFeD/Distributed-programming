#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

/* Wait Barriere */

int N;
sem_t *s1,*s2;

void wait_barrier(int NB_PCS){
  int i;
  if(NB_PCS==N-1){/* Coordinateur */
    for(i=0;i<N-1;i++)
      sem_wait(s2);
    
    for(i=0;i<N-1;i++)
      sem_post(s1);
  }
  
  else{
    sem_post(s2);
    sem_wait(s1);
  }
}


void process (int NB_PCS) {
  printf ("avant barrière\n");
  wait_barrier (NB_PCS);
  printf ("après barrière\n");
  exit (0);
}

int main(int argc, char** argv){
  
  N = atoi(argv[1]);
  int i;
  s1 = sem_open("monsem", O_CREAT | O_TRUNC | O_RDWR, 0600, 0);
  s2 = sem_open("monsem2", O_CREAT | O_TRUNC | O_RDWR, 0600, 0);
  
  for (i=0;i<N;i++)
    if(fork()==0)
      process(i);
  
  for (i=0;i<N;i++)
    wait(NULL);

  sem_close(s1);
  sem_unlink("monsem");
  sem_close(s2);
  sem_unlink("monsem2");
  
  return EXIT_SUCCESS;
}
