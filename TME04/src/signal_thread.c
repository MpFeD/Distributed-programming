#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define N 10

/*
On désire créer une chaîne de N threads (la thread main crée une thread, qui à son tour en crée une autre, et ainsi de suite N fois) qui fonctionne de la manière suivante. Au démarrage du programme, la thread principale masque tous les signaux, puis démarre la chaîne de création. Ensuite la thread main attend que toutes les threads de la chaîne aient été créées avant d’afficher "Tous mes descendants sont créés". Après leur création, toutes les threads (à l’exception de la thread main) se bloquent en attendant que la thread main les libère. Parallèlement, la thread main se bloque en attente d’un signal SIGINT émis au processus par l’utilisateur avec un CTRL+C. A la délivrance du signal SIGINT, la thread main débloque les autres threads de la chaîne puis attend enfin que toutes se soient terminées (pthread_exit) avant d’afficher "Tous mes descendants se sont terminés".

NB : Seule la thread main doit pouvoir être interrompue par un signal.
*/

sigset_t sig_proc;
struct sigaction action;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void sig_hand(){
}


int cpt=0;
pthread_t tid [N];

void *func_thread (void *arg){
 pthread_mutex_lock(&mutex);
 if (cpt !=N)
   pthread_create (&(tid[++cpt]),NULL,func_thread,NULL);
   
 pthread_cond_wait(&cond,&mutex);
 pthread_mutex_unlock(&mutex);
 pthread_exit ((void*)0);
}


int main (int argc, char** argv) {

 int i;

 sigfillset(&sig_proc);
 action.sa_mask=sig_proc;
 action.sa_flags=0;
 action.sa_handler = sig_hand;
 sigaction(SIGINT, &action,NULL);
 sigprocmask(SIG_SETMASK,&sig_proc,NULL);

 pthread_create (&(tid[0]),NULL,func_thread,NULL);

 while (cpt != N)
   usleep(100);
 
 printf("Tous mes descendants sont créés\n");
 
 sigdelset(&sig_proc,SIGINT);
 printf ("Attente de SIGINT...\n");
 sigsuspend(&sig_proc);
 sigaddset(&sig_proc,SIGINT);

 pthread_cond_broadcast(&cond);
 
 for(i=1;i<cpt;i++)
   pthread_join (tid[i],NULL);
 
 printf("Tous mes descendants se sont terminés\n");
 
 pthread_mutex_destroy(&mutex);
 pthread_cond_destroy(&cond);
 
 printf ("\nFin programme principal\n");
 
 return EXIT_SUCCESS;
}
