#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
 
struct sigaction action;

/*
On souhaite écrire un variante de la fonction précédente, de sorte que toutes les Threads d’un niveau L soient créées avant de commencer à créer celles du niveau L+1. Pour cela, écrire une fonction main qui

    prend sur sa ligne de commande la profondeur de Thread désirée ;
    lance une première Thread qui se bloque en attendant que toutes celles du niveau courant soient créées (utiliser la formule demandée à la question précédente) ;
    lance la variante de la fonction thread_func désirée ;
    affiche pour finir le nombre total de Threads créées (à partir d’une variable incrémentée à chaque création) ;

Indication : utliser un signal SIGINT de sorte que son n-ième apparition déclenche la création des Threads de niveau n.
Exemple d'appel :
bin/thread_arborescent_sync 4
*/

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int max=5; //profondeur maximale
int nbthreads=0; //compteur du nombre de threads
int seuilmax; //nbthread à attendre (formule)
int seuilatteint=0; //savoir si le nb de thread atteint est bon 
int a; //argument (argv[1])


int fact(int n){ //Fonction factorielle
  int res =1,i;
  for (i=1;i<=n;i++)
    res *= i;
  return res;
}

int nbthread(int n){ //Fonction qui calcule la somme des factorielles (formule)
  int i=1, res=0;
  while(i<=n){
    res += fact(i);
    i++;
  }
  return res;
}


sigset_t sig_set;
int monsignal;


void* thread_func(void* arg) {

  int i, nb;
  int *param;
  int *lvl = (int*)arg;
  pthread_t *tid;
     
  nb = (*lvl)+1;
  
  pthread_mutex_lock(&mutex);
  nbthreads++;

  if(nbthreads == nbthread(*lvl)){
    /*Si la fonction appliqué au paramètre du thread vaut le nb de threads (formule) alors il faut débloquer les autre threads (comme dit dans l'énoncé : la n-ième thread débloque les thread de niveau n)*/
    pthread_mutex_lock(&mutex2);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex2);
  }
 
  
  
  if (nbthreads == seuilmax){
    printf("*****************************************\n*****************************************\n*****************************************\nTOUS LES THREADS DE NIVEAU %d SOONT CRÉÉES\n LES THREADS DE NIVEAUX SUPÉRIEURES VONT \n     MAINTENANT POUVOIR ÊTRE CRÉÉES  \n*****************************************\n*****************************************\n*****************************************\n",a);
    seuilatteint=1;  //une seulle thread accède à cette variable globale, inutile de la protégée
  }
  if(nbthreads <= seuilmax){ //Les threads de niveau inférieur doivent être bloqué (sigwait)
    pthread_mutex_unlock(&mutex);
    if(nbthreads == 1){ //La première thread applique le masque de signaux
      sigemptyset (&sig_set);
      sigaddset (&sig_set,SIGINT);
      pthread_sigmask (SIG_SETMASK, &sig_set,NULL);
    }else
      sigwait (&sig_set,&monsignal);
  }else
    pthread_mutex_unlock(&mutex);
  
  

  
  
  if (*lvl < max) {
    param = (int*)malloc(sizeof(int));
    *param = nb;
     tid = calloc(nb, sizeof(pthread_t));
    
    pthread_t tid [nb];  
    
    printf("%d cree %d fils\n", (int)pthread_self(), nb);
    for (i = 0; i < nb; i++) {
      pthread_create((tid+i), 0, thread_func, param);
    }

    if(seuilatteint==0){//Les thread de niveau inférieure doivent attendre
      pthread_mutex_lock(&mutex2);
      pthread_cond_wait(&cond,&mutex2);
      pthread_mutex_unlock(&mutex2);
    }
 
    for (i = 0; i < nb; i++)
      pthread_kill((tid[i]),SIGINT);
    
    for (i = 0; i < nb; i++)
      pthread_join(tid[i], NULL);
    
  }
  if (*lvl > 1)
    pthread_exit ( (void*)0);
	
  return (void*)0;
  
}

int main (int argc, char** argv) {
  
  if (argc != 2){
    perror("arguments");
    return EXIT_FAILURE;
  }

  a=atoi(argv[1]);
  seuilmax = nbthread(a);
  
  int b[1]={1};
  pthread_t tid[1];
  
  pthread_create (&(tid[0]),NULL,thread_func,b);
  pthread_join (tid[0],NULL);
  
  pthread_mutex_destroy(&mutex);
  pthread_mutex_destroy(&mutex2);
  pthread_cond_destroy(&cond);

  printf ("\nNombre de threads : %d\n",nbthreads);
  printf ("\nFin programme principal\n");
  
  return EXIT_SUCCESS;
}

