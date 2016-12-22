#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define N 5

/*
Créez un programme qui prend en paramètre un nom de fichier, le lit caractère par caractère pour l’écrire de manière inversée dans un autre fichier.

Par exemple, si le premier fichier contient "fichier ok" alors le deuxième devra contenir "ko reihcif".

N.B : votre programme doit impérativement utiliser la fonction lseek pour modifier l’offset lors de la lecture.
*/



int main (int argc, char **argv) {
  struct stat stat_info;
  off_t o=-2;

  int fd1, fd2;
  
  fd1 = open (argv[1], O_RDONLY, 0600);
  
  fd2 = open ("./resultat", O_RDWR | O_CREAT | O_TRUNC, 0600);
  

  char c[1];
  
  while( lseek (fd1,o,SEEK_END)!=-1) {
    read(fd1,c,1);
    write(fd2,c,1);
    o--;
  }
  
    return EXIT_SUCCESS;

}
