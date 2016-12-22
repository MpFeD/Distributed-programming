#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5


/*

Modifier le programme de l’exercice précédent pour que chaque thread affiche non plus son numéro de création mais une valeur aléatoire entre 0 et 10. Pour cela, utilisez la fonction rand de la façon suivante :

(int) (10*((double)rand())/ RAND_MAX)

De plus, cette valeur aléatoire sera ajoutée à une variable globale. On veillera évidemment à éviter les accès concurrents à cette variable, initialisée à zéro par le programme principal. Celui-ci, après avoir attendu la terminaison de toutes les threads, affichera la valeur finale de cette variable.


*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int val;

void *func_thread (void *arg){
  srand(pthread_self());
  int b = (int) (10*((double)rand())/ RAND_MAX);
  printf ("Mon numéro est %d, mon id est %d\n", b, (int)pthread_self());
  pthread_mutex_lock(&mutex);
  val+=b;
  pthread_mutex_unlock(&mutex);
  pthread_exit( (void*) NULL);
  return NULL;
}

int main (int argc, char** argv) {
  int i;
  pthread_t tid [NUM_THREADS];
  
  val=0;
  
  for(i=0;i<NUM_THREADS;i++){
    pthread_create (&(tid[i]),NULL,func_thread,NULL);
  }
 
  for(i=0;i<NUM_THREADS;i++){
    pthread_join (tid[i], NULL);
  }

  printf("valeur finale %d\n",val);

  pthread_mutex_destroy(&mutex);
  
  return EXIT_SUCCESS;
}
