#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>


/*
Ecrire un programme C prenant plusieurs noms de fichiers en argument et leur appliquant upper. Le programme doit créer autant de Threads que de fichiers, et les exécuter en parallèle.


*/


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


int main (int argc, char** argv) {
 
 if (argc==1){
   perror("Au moins un nom de fichier est requis\n");
   return EXIT_FAILURE;
 }
 
 int NB_THREADS = argc-1;
 
 int i;
 pthread_t tid [NB_THREADS];
 
 for(i=0;i<NB_THREADS;i++)
   pthread_create (&(tid[i]),NULL,upper,argv[i+1]);
 
 for(i=0;i<NB_THREADS;i++)
   pthread_join (tid[i],NULL);

 printf ("Fin programme principal\n");
 
 return EXIT_SUCCESS;
}
