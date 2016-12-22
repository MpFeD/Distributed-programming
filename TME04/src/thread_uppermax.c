#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

/*
On considère maintenant que le nombre de threads créées est inférieur au nombre de fichiers à traiter. Dès qu’une Thread a converti un fichier, elle doit passer à un autre fichier s’il en reste, et sinon se terminer.

Ecrire un nouveau programme C programmant cette stratégie, le premier argument sur la ligne de commande étant le nombre de Thread permis, les suivants étant les fichiers, en nombre supérieur.
Exemple d'appel :
bin/thread_uppermax 2 fichier1 fichier2 fichier3



 */


int NB_FICHIERS;
int NB_THREADS;
int i=2;
char **a;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;


int upper(char *path)
{
   FILE* fp1, *fp2;
   int c = 1;
   
   fp1= fopen (path, "r");
   fp2= fopen (path, "r+");
   if ((fp1== NULL) || (fp2== NULL)) {
       perror ("fopen");
        return errno;
   }
   
   while (c !=EOF) {
       c=fgetc(fp1);
       if (c!=EOF)
       fputc(toupper(c),fp2);
   }

   fclose (fp1);
   fclose (fp2);

   return EXIT_SUCCESS;
}


void *func_thread (void *arg){
 pthread_mutex_lock(&mutex);
 while (i != NB_FICHIERS){
   char *c = a[i+2];
   i++;
   pthread_mutex_unlock(&mutex);
   upper(c);
 }
 pthread_exit ((void*)0);
}



int main (int argc, char** argv) {
 
 if (argc<3){
   perror("Erreur arguments\n");
   return EXIT_FAILURE;
 }
 
 
 NB_THREADS = atoi(argv[1]);

 if (NB_THREADS <= 0){
   perror("Erreur arguments\n");
   return EXIT_FAILURE;
 }
 
 pthread_t tid [NB_THREADS];
 a=argv;
 NB_FICHIERS = argc-2;
 
 for(i=0;i<NB_THREADS;i++)
   pthread_create (&(tid[i]),NULL,func_thread,argv);
 
 for(i=0;i<NB_THREADS;i++)
   pthread_join (tid[i],NULL);


 pthread_mutex_destroy(&mutex);
 pthread_cond_destroy(&c);
 
 printf ("Fin programme principal\n");
 
 return EXIT_SUCCESS;
}
