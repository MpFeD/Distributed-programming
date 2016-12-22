#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5


/*

Modifier le programme précédent pour que la valeur finale soit affichée non plus par le programme principal mais par une nouvelle thread créée par lui. Celle-ci, après sa création, doit se bloquer en attendant que la somme de toutes les valeurs aléatoires soit complétée. La dernière thread à ajouter sa valeur aléatoire à la variable globale réveille alors celle-ci pour qu’elle puisse afficher la valeur finale.

Cette fois cia vec des thread détachée

*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexcondition = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
int val;
int t;

void *func_thread (void *arg){
  pthread_detach(pthread_self());
  srand(pthread_self());
  int b = (int) (10*((double)rand())/ RAND_MAX);
  printf ("Mon numéro est %d, mon id est %d\n", b, (int)pthread_self());
  pthread_mutex_lock(&mutex);
  val+=b;
  t++;
  if(t==NUM_THREADS){
    pthread_mutex_lock(&mutexcondition);
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&mutexcondition);
  }
  pthread_mutex_unlock(&mutex);
  pthread_exit( (void*) NULL);
  return NULL;
}

void *func_thread2 (void *arg){
  while(t!=NUM_THREADS)
    pthread_cond_wait(&c,&mutexcondition);
  
  printf("valeur finale %d\n",val);
  pthread_exit( (void*) NULL);
  return NULL;
}


int main (int argc, char** argv) {
  int i;
  pthread_t tid [NUM_THREADS+1];
  val=0;
  t=0;
  
  for(i=0;i<NUM_THREADS;i++){
    pthread_create (&(tid[i]),NULL,func_thread,NULL);
  }
  pthread_create (&(tid[NUM_THREADS]),NULL,func_thread2,NULL);


  pthread_join(tid[NUM_THREADS],NULL);


  pthread_mutex_destroy(&mutex);
  pthread_mutex_destroy(&mutexcondition);
  pthread_cond_destroy(&c);


  return EXIT_SUCCESS;
}
