#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define N 5

/*
Ecrire un programme où le processus principal crée N processus fils. Chaque processus fils génère une valeur aléatoire random_val qu’il insère dans un fichier à destination du processus principal. La valeur aléatoire est calculée par :

(int) (10*(float)rand()/ RAND_MAX)

De son côté, le processus principal doit attendre la terminaison de tous ses fils, puis extraire toutes les valeurs du fichier pour ensuite les additionner et enfin afficher la somme résultante.

*/



int main (int argc, char **argv) {
  struct stat stat_info;

  int fd1, fd2, fd3;
  fd1 = open ("./fichier", O_RDWR | O_CREAT | O_TRUNC, 0600);

  char c[1];
  int i,somme=0;
  for (i=0;i<N;i++){
    if(fork()==0){
      srand(getpid());
      int n = (int) (10*(float)rand()/ RAND_MAX);
      sprintf (c,"%d",n);
      printf ("%c\n",c[0]);
      write (fd1,c,1);
      exit(0);
    }
    wait(NULL);
  }

  lseek(fd1,0,SEEK_SET);
  
  for (i=0;i<N;i++){
    read(fd1,c,1);
    somme+=atoi(c);
  }
  
  printf("Somme = %d\n",somme);
  
  return EXIT_SUCCESS;

}
