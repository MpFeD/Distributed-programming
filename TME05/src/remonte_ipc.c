#define _SVID_SOURCE 1
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

/*
Ecrire un programme lisant sur la ligne de commande un entier non nul N, s’associant une file de messages System V, puis créant N processus fils. Chaque processus fils génère une valeur aléatoire positive avec l’expression :
(int) (10*(float)rand()/ RAND_MAX);

en initialisant au préalable le générateur via la fonction srand. Chaque valeur aléatoire est insérée dans la file, à destination du processus principal.

De son côté, le processus principal doit attendre la terminaison de tous ses fils, puis extraire toutes les valeurs de la file de messages pour ensuite les additionner et afficher la somme résultante. Pour finir, il libère la file en appelant la fonction msgctl
*/


struct msg_buf{
  long type;
  int data;
}m;


int main(int argc, char** argv){

  m.type = 1;

  struct msqid_ds *buf;
  key_t cle = ftok(argv[0], getpid());
  int msgid = msgget(cle, 0666 | IPC_CREAT);
  int i,somme=0;


  for(i=0;i<atoi(argv[1]);i++){
    if(fork()==0){
      srand(getpid());
      printf("%d\n",m.data=(int) (10*(float)rand()/ RAND_MAX));
      msgsnd(msgid , &m , sizeof(int), 0);
      exit(0);
    }
  }

  for(i=0;i<atoi(argv[1]);i++)
   wait(NULL);
  
  for(i=0;i<atoi(argv[1]);i++){
    msgrcv(msgid , &m , sizeof(int), 0,0);
    somme+=m.data;
  }

  printf ("Somme=%d\n",somme);

  msgctl(msgid, IPC_RMID,buf);

  return EXIT_SUCCESS;
}
