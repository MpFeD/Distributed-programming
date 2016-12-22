#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int max=3;
int nbthreads=0;

void* thread_func(void* arg) {
  
  pthread_mutex_lock(&mutex);
  nbthreads++;
  printf ("Nombre de threads : %d\n",nbthreads);
  pthread_mutex_unlock(&mutex);
	
  int i, nb;
  int *param;
  int *lvl = (int*)arg;
  pthread_t *tid;
	
  nb = (*lvl)+1;

  
  if (*lvl < max) {
    param = (int*)malloc(sizeof(int));
    *param = nb;
    tid = calloc(nb, sizeof(pthread_t));
    printf("%d cree %d fils\n", (int)pthread_self(), nb);
    for (i = 0; i < nb; i++) {
      pthread_create((tid+i), 0, thread_func, param);
    }
    for (i = 0; i < nb; i++)
      pthread_join(tid[i], NULL);
  }

  if (*lvl > 1)
    pthread_exit ( (void*)0);
	
  return (void*)0;
}

int main (int argc, char** argv) {

  int i;
  //int *a=1;
  int b[1];
  b[0]=1;
  //int *c = (int *) 1;
  pthread_t tid [1];
  
  //pthread_create (&(tid[0]),NULL,thread_func,c);
  pthread_create (&(tid[0]),NULL,thread_func,b);
  //pthread_create (&(tid[0]),NULL,thread_func,1);

  
  pthread_join (tid[0],NULL);
  
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  
  printf ("\nFin programme principal\n");
  
  return EXIT_SUCCESS;
}

