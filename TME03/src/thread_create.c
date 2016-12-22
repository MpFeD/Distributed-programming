#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5


/*
Ecrire un programme créeant N threads et passant en paramètre à chacune son numéro de création compris entre 0 et N. Chacune affichera son numéro de création et son identité (utiliser la fonction pthread_self). Ensuite elle se termine en retournant son numéro de création multiplié par 2. De son côté, le programme principal doit attendre la terminaison de toutes les threads en affichant la valeur renvoyée par chacune lors de sa terminaison.

*/

void *func_thread (void *arg){
  int b = 2 * (*((int*)arg));
  printf ("Mon numéro de création est %d, mon id est %d\n", b, (int)pthread_self());
  pthread_exit( (void*) b);
  return NULL;
}

int main (int argc, char** argv) {
  int i;
  int* ret;
  pthread_t tid [NUM_THREADS];
  int a[NUM_THREADS];

  for(i=0;i<NUM_THREADS;i++){
    a[i]=i;
    pthread_create (&(tid[i]),NULL,func_thread,&a[i]);
  }
 
  for(i=0;i<NUM_THREADS;i++){
    pthread_join (tid[i], (void**) &ret);
    printf("pthread %d terminée sa valeur de retour est %d\n",i,ret);
  }

  return EXIT_SUCCESS;
}
