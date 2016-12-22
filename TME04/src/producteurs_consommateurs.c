#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "../include/producteur_consommateur.h"


/*

Reprenez l’exercice précédent en faisant échanger plusieurs producteurs et plusieurs consommateurs de façon concurrente, toujours à travers une seule pile. Votre programme prendra en argument deux nombres : le nombre de producteurs suivi du nombre de consommateurs.
Exemple d'appel :
echo "123456789" | bin/producteurs_consommateurs 5 3

*/


sigset_t sig_proc;
struct sigaction action;

void sig_hand(){
}


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_plein = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_vide = PTHREAD_COND_INITIALIZER;

char pile [100]={'\0'};
int stack_size=0;
int max = 100;

void push (char c){
 pthread_mutex_lock(&mutex);
 while(stack_size == max)
   pthread_cond_wait(&cond_plein,&mutex);
 pile[stack_size++]=c;
 printf ("char push : %c\n",c);
 if (stack_size==1){
   pthread_cond_broadcast(&cond_vide);
 }
 pthread_mutex_unlock(&mutex);
}


char pop (){
 char ret='\0';
 pthread_mutex_lock(&mutex);
 while(stack_size == 0)
   pthread_cond_wait(&cond_vide,&mutex);
 ret = pile[--stack_size];
 printf ("char pop : %c\n",ret);
 pile[stack_size]='\0';
 if (stack_size==max){
   pthread_cond_broadcast(&cond_plein);
 }
 pthread_mutex_unlock(&mutex);
 return ret;
}


void *Producteur(){
 int c;
 while((c = getchar()) != EOF){
   push(c);
 }
 pthread_exit ((void*)NULL);
}

void *Consommateur(){
 while(1) {
   putchar(pop());
   fflush(stdout);
 }
 pthread_exit ((void*)NULL);
}




int main (int argc, char** argv) {

 if(argc != 3){
   perror("arguments\n");
   return EXIT_FAILURE;
 }

 sigfillset(&sig_proc);
 action.sa_mask=sig_proc;
 action.sa_flags=0;
 action.sa_handler = sig_hand;
 sigdelset(&sig_proc,SIGINT);
 sigaction(SIGINT, &action,NULL);
 
 
 int i,nbprod=atoi(argv[1]),nbcons=atoi(argv[2]);
 pthread_t tid [2];
 

 for(i=0;i<nbprod;i++)
   pthread_create (&(tid[0]),NULL,Producteur,NULL);
 for(i=0;i<nbcons;i++)
   pthread_create (&(tid[1]),NULL,Consommateur,NULL);

 printf ("\nPour terminer proprement, utiliser C-c (SIGINT)\n");
 
 sigsuspend(&sig_proc);
 
 pthread_mutex_destroy(&mutex);
 pthread_cond_destroy(&cond_plein);
 pthread_cond_destroy(&cond_vide);
 
 printf ("\nFin programme principal\n");
 
 return EXIT_SUCCESS;
}
