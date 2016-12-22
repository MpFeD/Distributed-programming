#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>


/*
Remontée de valeurs par partage de mémoire de la séance précédente à la mémoire partagée façon POSIX, c’est-à-dire à l’aide des fonctions mmap et munmap.
*/
  
int *sp;


int main(int argc, char** argv){

  int i,somme=0,N=atoi(argv[1]);

  int fd = shm_open("mon_seg", O_RDWR | O_CREAT | O_TRUNC,0666);
  ftruncate(fd,N*sizeof(int));
  sp=mmap(NULL,N*sizeof(int),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
  
  for(i=0;i<N;i++){
    if(fork()==0){
      srand(getpid());
      printf("%d\n",sp[i]=(int) (10*(float)rand()/ RAND_MAX));
      exit(0);
    }
  }

  for(i=0;i<N;i++)
    wait(NULL);
  
  for(i=0;i<N;i++){
    somme+=sp[i]; 
  }
  
  printf ("Somme=%d\n",somme);
  
  munmap(sp,N*sizeof(int));
  shm_unlink("mon_seg");
  
  return EXIT_SUCCESS;
}
