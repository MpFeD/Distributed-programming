#define _SVID_SOURCE 1
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>

/*
Reprenez le programme de l’exercice précédent de sorte que tous les messages envoyés passent par une seule file, celle du processus principal.
*/

struct msg_buf{
  long type;
  int data;
}m;


int main(int argc, char** argv){

  m.type = 1;
  int i,j,max_msg_i,envoi,somme=0,N=atoi(argv[1]),k=999; /*Constante de différenciation */
  
  struct msqid_ds *buf;
  key_t cle=ftok(argv[0], getpid());
  int msgid=msgget(cle, 0666 | IPC_CREAT);

  for(i=0;i<N;i++){
    if(fork()==0){
      srand(getpid());
      max_msg_i = (int) (N*(float)rand()/ RAND_MAX)+1;
      m.data=max_msg_i;
      m.type=N*i+2;
      printf("Fils %d envoie %d a envoyer type : %d\n",i,max_msg_i,m.type);
      msgsnd(msgid, &m , sizeof(int), 0);
      for(j=0;j<max_msg_i;j++){
	printf("Fils %d type recu %d\n",i, N*i+k+2);
	msgrcv(msgid, &m , sizeof(int), N*i+k+2,0);
	printf("Fils %d recoi %d pour la somme\n",i,m.data);
	somme+=m.data;
      }
      printf("Somme=%d\n",somme);
      exit(0);
    }
  }
  
  for(i=0;i<N;i++){
    printf("Pere %d type recu %d\n",i, N*i+2);
    msgrcv(msgid, &m , sizeof(int), N*i+2,0);
    max_msg_i=m.data;
    m.type=N*i+2+k;
    printf("Pere %d recoi %d a envoyer type : %d\n",i,m.data,m.type);
    for(j=0;j<max_msg_i;j++){
      m.data= (int) (100*(float)rand()/ RAND_MAX);
      printf("Pere %d envoi %d pour la somme\n",i,m.data);
      msgsnd(msgid, &m , sizeof(int), 0);
    }
  }

  for(i=0;i<N;i++)
   wait(NULL);

  msgctl(msgid, IPC_RMID,buf);

  return EXIT_SUCCESS;
}
