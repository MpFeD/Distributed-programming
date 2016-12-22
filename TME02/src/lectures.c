#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>




  /*
Écrire deux fonctions C qui lisent caractère par caractère un fichier passé en argument, et qui affichent chaque caractère dès qu’il est lu. Ces fonctions utiliseront 3 processus partageant le même descripteur et agissant à l’identique (l’identité de chaque processus est affichée avec le caractère lu). La première utilisera les standard POSIX open et read, la seconde fopen et fgetc.

Question : quelle différence observez-vous ? Expliquez cette différence, et testez votre explication à l’aide de la fonction setvbuf.



Solution => 


On remarque que les fonctions posix read et open sont plus souples sur la commutation de processus, en effet on remarque que les fonctions fopen et fread n'utilisent qu'un seul processus sur les 3.

Cette difference s'explique avec la fonction setvbuf, gràce à cette dernière on peut forcer l'information à aller à destination directement après l'écriture. On arrive donc à avoir un comportement similaire entre les 2 types de fonctions avec setvbuf.

On en conclue donc que les fonctions utilisant fread et fopoen ne commute pas tout de suite sans doute pour des raisons d'optimisation.

   */

void f1(char* fic){
 int fd = open (fic,O_RDWR, 0600),i;
 char c;
 pid_t principal = getpid();
 
 for(i=0;i<2;i++)
   if (fork()==0)
     break;
 
 while(read(fd,&c,1))
   printf("charactère lu = %c, pid =%d\n",c,getpid());

 if (principal != getpid())
   exit(0);

 wait(NULL);
 wait(NULL);
 return;
}



void f2(char* fic){
 FILE *f = fopen (fic,"r");
 char c;
 int i;

 for(i=0;i<2;i++)
   if (fork()==0)
     break;
 
 while((c = fgetc(f))!=EOF){
   setvbuf(f, &c, _IONBF, 1);
   printf("charactère lu = %c, pid =%d\n",c,getpid());
 }
 wait(NULL);
 wait(NULL);
 return;
}


int main (int argc, char** argv) {
 printf("Premiere fonction\n");
 f1("test");
 printf("Deuxieme fonction\n");
 f2("test");
 return EXIT_SUCCESS;
}
