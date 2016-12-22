#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>


/*
Rédigez un programme extended-grep qui cherche dans un répertoire les fichiers contenant une chaîne de caractères donnée.

Le programme sera appelé de la manière suivante :

extended-grep <expr> <chemin>

avec

    expr : la chaîne de caractères recherchée
    chemin : le chemin du répertoire qui contient les fichiers à analyser

extended-grep lit le contenu de tous les fichiers réguliers présents dans chemin, affiche le nom de chaque fichier qui contient la chaîne de caractères recherchée, "Aucun fichier valide" si expr n’est présente dans aucun des fichiers réguliers du répertoire.

N.B : Vous pouvez utiliser la fonction strstr de la bibliothèque string.h pour trouver si une chaîne de caractères est présente dans une autre.

*/






extern int errno;

#define _POSIX_SOUCE 1
#define TAILLE_PATH 100
#define BUF 1024

char buff_path [TAILLE_PATH];
DIR *pt_Dir;
struct dirent* dirEnt;



int main (int argc, char** argv) {
  int ret=0;
  if (argc ==1 ) {
    /* repertoir courant : obtenir le nom */
    getcwd (buff_path, TAILLE_PATH);
  }
  else
    memcpy (buff_path,argv[1],strlen(argv[1]));
  pt_Dir = opendir (buff_path);
  if (errno ==  ENOENT ) {
    /* repertoire n'existe pas - créer le répertoire */
    mkdir ( buff_path, S_IRUSR|S_IWUSR|S_IXUSR);
    return 0;
  }

	
  /* lire répertoire */
  while ((dirEnt= readdir (pt_Dir)) !=NULL) {
    int fd = open(dirEnt->d_name, O_RDONLY, 0600);
    char c[BUF]={'\0'};
    
    int i=0;
    
    read (fd,c,BUF);

    if (strstr (c,argv[2]) != NULL){
      ret=1;
      printf ("%s\n", dirEnt->d_name);
    }
    
   
  }
  if (!ret)
    printf("Aucun fichier valide\n");
  closedir (pt_Dir);
	
  return 0;
}
