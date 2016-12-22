#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

/*
Il y à 5 contenus possibles du fichier :

fghie123
45hie123
453fghi
45123hi
45hi123

Mais il y à 15 possibilités (certaines donnent le même contenu) :

Posons :

write (fd1,"123", strlen ("123") = A
write (fd2,"45", strlen ("45") = B
fd3 = dup(fd1) = C
lseek (fd3,0,SEEK_SET = D
write (fd3,"fg", strlen ("fg") = E
write (fd1,"hi", strlen ("hi") = F

Alors :

ABCDEF = fghie123
ACBDEF = fghie123
ACDBEF = fghie123
ACDEBF = 45hie123
ACDEFB = 45hie123
CABDEF = fghie123
CDABEF = 453fghi
CDEABF = 45123hi
CDEFAB = 45hi123
CADEFB = 45hie123
CADEBF = 45hie123
CADBEF = fghie123
CDAEFB = 453fghi
CDEAFB = 45123hi
CDAEBF = 453fghi


Modifier le programme pour que la taille soit toujours égale à 8

Solution : Il faut mettre A avant C
*/

sigset_t sig;
struct sigaction action;

void sig_hand(int sig){
}


int main (void) {
  int fd1, fd2, fd3;
  if ((fd1 = open ("./fich1", O_RDWR| O_CREAT | O_TRUNC, 0600)) == -1)
    return EXIT_FAILURE;
  if (write (fd1,"abcde", strlen ("abcde")) == -1)
    return EXIT_FAILURE;
  if (fork () == 0) {
    if ((fd2 = open ("./fich1", O_RDWR)) == -1)
      return EXIT_FAILURE;
    if (write (fd1,"123", strlen ("123")) == -1)
      return EXIT_FAILURE;

    kill (getppid(),SIGINT);
    
    if (write (fd2,"45", strlen ("45")) == -1)
      return EXIT_FAILURE;
    close(fd2); 
  } else {
    fd3 = dup(fd1);

    sigdelset(&sig,SIGINT);
   sigsuspend(&sig);
   sigaddset(&sig,SIGINT);
    
    if (lseek (fd3,0,SEEK_SET) == -1)
      return EXIT_FAILURE;
    if (write (fd3,"fg", strlen ("fg")) == -1)
      return EXIT_FAILURE;
    if (write (fd1,"hi", strlen ("hi")) == -1)
      return EXIT_FAILURE;
    wait (NULL);
    close (fd1);
    close(fd3);
    return EXIT_SUCCESS;
  }
}
