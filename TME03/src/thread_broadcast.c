#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NB_THREADS 5


/*
Une barrière est un mécanisme de synchronisation. Elle permet à N threads de prendre rendez-vous en un point donné de leur exécution. Dès que l’une d’entre elles atteint la barrière, elle reste bloquée jusqu’à ce que toutes les autres y arrivent. Lorsque toutes sont arrivées, chacune peut alors reprendre son exécution.

Ecrire une fonction, qu’on nommera wait_barrier prenant en argument un entier N, permettant à N threads de se synchroniser sur une barrière. Testez votre programme avec la thread suivante :
void* thread_func (void *arg) {
   printf ("avant barriere\n");
   wait_barrier (NB_THREADS);
   printf ("après barriere\n");
   pthread_exit ( (void*)0);
}

En exécutant votre programme avec 2 threads, il devra afficher :

avant barrière
avant barrière
après barrière
après barrière

En d’autres termes, on veut que tous les messages « avant barrière » soient affichés avant les messages « après barrière ».

*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
int val;
int t;

void wait_barrier(int n){
  int k=0;
  pthread_mutex_lock(&mutex);
  t++;
  while(t!=n){
    pthread_cond_wait(&c,&mutex);
    pthread_mutex_unlock(&mutex);
    return;
  }
  pthread_cond_broadcast(&c);
  pthread_mutex_unlock(&mutex);
}

void* thread_func (void *arg) {
   printf ("avant barriere\n");
   wait_barrier (NB_THREADS);
   printf ("après barriere\n");
   pthread_exit ( (void*)0);
}



int main (int argc, char** argv) {
  int i;
  pthread_t tid [NB_THREADS];
  
  val=0;
  t=0;
  
  for(i=0;i<NB_THREADS;i++)
    pthread_create (&(tid[i]),NULL,thread_func,NULL);
  
  
  for(i=0;i<NB_THREADS;i++)
    pthread_join(tid[i],NULL);

  
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&c);


  return EXIT_SUCCESS;
}
