#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "../include/producteur_consommateur.h"

/*
Nous voulons faire communiquer une thread Producteur et une thread Consommateur en utilisant une pile de taille fixe (un tableau de 100 caractères). Les valeurs empilées sont des caractères. La thread Producteur utilise la fonction Push() pour empiler un caractère au sommet de la pile et la thread Consommateur utilise la fonction Pop() pour désempiler une valeur du sommet de la pile. Une variable globale stack_size contrôle le sommet de la pile.

Programmez les fonctions Push() et Pop() décrites ci-dessus pour faire communiquer les threads Producteur et Consommateur, le corps de ces deux fonctions reposant respectivement sur les deux séquences de code définies par les deux macros suivantes, fournies dans le fichier .h en annexe :

#define PRODUCTEUR int c;  while((c = getchar()) != EOF){ push(c); }

#define CONSOMMATEUR while(1) { putchar(pop()); fflush(stdout); }

Ecrire ensuite le programme main utilisant ces deux fonctions.
Exemple d'appel :
echo "123456789" | bin/producteur_consommateur

 */



sigset_t sig_proc;
struct sigaction action;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

char pile [100]={'\0'};
int stack_size=0;
int max = 100;

void sig_hand(){
}

void push (char c){
 pthread_mutex_lock(&mutex);
 while(stack_size == max)
   pthread_cond_wait(&cond,&mutex);
 pile[stack_size++]=c;
 if (stack_size==1){
   pthread_cond_signal(&cond);
 }
 pthread_mutex_unlock(&mutex);
}


char pop (){
 char ret='\0';
 pthread_mutex_lock(&mutex);
 while(stack_size == 0)
   pthread_cond_wait(&cond,&mutex);
 ret = pile[--stack_size];
 pile[stack_size]='\0';
 if (stack_size==max){
   pthread_cond_signal(&cond);
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
 
 sigfillset(&sig_proc);
 action.sa_mask=sig_proc;
 action.sa_flags=0;
 action.sa_handler = sig_hand;
 sigdelset(&sig_proc,SIGINT);
 sigaction(SIGINT, &action,NULL);
 
 int i;
 pthread_t tid [2];

 
 pthread_create (&(tid[0]),NULL,Producteur,NULL);
 pthread_create (&(tid[1]),NULL,Consommateur,NULL);

 printf ("\nPour terminer proprement, utiliser C-c (SIGINT)\n");
 
 sigsuspend(&sig_proc);
 
 pthread_mutex_destroy(&mutex);
 pthread_cond_destroy(&cond);
 
 printf ("\nFin programme principal\n");
 
 return EXIT_SUCCESS;
}
