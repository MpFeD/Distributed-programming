#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

/*
Rédigez un programme qui prend en paramètres deux noms de fichier et recopie intégralement le contenu du premier dans le second, en respectant 3 conditions :

    le premier nom doit désigner un fichier régulier et accessible en lecture ;
    le second ne doit pas désigner un fichier existant,
    le second doit pouvoir être créé dans le répertoire courant.

*/



int main (int argc, char **argv) {
  struct stat stat_info;

  int fd1, fd2, fd3;
  fd1 = open (argv[1], O_RDONLY, 0600);

  /* 
   * Test si fichier régulier
   */
  
  stat (argv[1], &stat_info);
  if (!S_ISREG(stat_info.st_mode))
    return EXIT_FAILURE;


  fd2 = open (argv[2], O_RDWR | O_CREAT | O_EXCL, 0600);

  /* 
   * Test si fichier existant
   */
  
  if (errno==EEXIST)
    return EXIT_FAILURE;

  /* 
   * Création dans rep courant
   */
  
  int i=0;
  while(argv[2][i] != '\0'){
    if (argv[2][i] == '/'){
      printf ("Erreur un caractère '/' est détécté dans le nom du deuxieme fichier\nMerci de rentrer un nom de fichier valide pour que le fichier soit créer dans le répertoire courant\n");
      return EXIT_FAILURE;
    }
    i++;
  }

  
  
  char c[1];
  
  while (read (fd1,c,1)){
    write (fd2,c,1);
  }

  
  return EXIT_SUCCESS;

}
