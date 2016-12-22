#define _SVID_SOURCE 1
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>

/*
On souhaite à présent que chaque processus soit associé à une file de messages MQi, où i est le numéro d’ordre de création du processus fils : 0 < i < N-1. Le programme principal est associé à la file MQN. Il y a donc en tout N+1 files de messages, donc chacune avec un identifiant spécifique fourni par ftok.

Cette fois-ci la valeur aléatoire générée par chaque processus fils, notée max_msg_i (1 <= max_msg_i <= N), représente le nombre de messages que le processus fils veut recevoir de son père. Une fois générée, chaque fils envoie cette valeur à son père par le biais de la file de messages associée au processus principal. Chaque processus fils attend ensuite sur sa propre file de messages que son père lui renvoie max_msg_i messages.

Dans ces messages, le processus père insère à chaque fois une valeur tirée aléatoirement entre 0 et 100. Lorsque tous les messages ont été extraits de sa file, chaque processus fils fait la somme des valeurs reçues et affiche le résultat.
*/


struct msg_buf{
  long type;
  int data;
}m;


int main(int argc, char** argv){

  m.type = 1;
  int i,j,max_msg_i,envoi,somme=0,N=atoi(argv[1]);
  
  struct msqid_ds *buf;
  key_t cle[N+1];
  int msgid[N+1];
  char *keystr;
  keystr = malloc (strlen(argv[0]) * sizeof(char));
  
  
  for(i=0;i<=N;i++){
    sprintf(keystr,"%s",argv[0]);
    cle[i] = ftok(argv[0], getpid()+i);
    msgid[i] = msgget(cle[i], 0666 | IPC_CREAT);
  }
  
  for(i=0;i<N;i++){
    if(fork()==0){
      srand(getpid());
      max_msg_i = (int) (N*(float)rand()/ RAND_MAX)+1;
      printf("Fils %d envoie %d a envoyer\n",i,max_msg_i);
      m.data=max_msg_i;
      m.type=(N*i)+1;
      msgsnd(msgid[N] , &m , sizeof(int), 0);
      for(j=0;j<max_msg_i;j++){
	msgrcv(msgid[i], &m , sizeof(int), (N*i)+1,0);
	printf("Fils %d recoi %d pour la somme\n",i,m.data);
	somme+=m.data;
      }
      printf("Somme=%d\n",somme);
      exit(0);
    }
  }

  
  for(i=0;i<N;i++){
    msgrcv(msgid[N], &m , sizeof(int), (N*i)+1,0);
    printf("Pere %d recoi %d a envoyer\n",i,m.data);
    max_msg_i=m.data;
    m.type=N*i+1;
    for(j=0;j<max_msg_i;j++){
      m.data= (int) (100*(float)rand()/ RAND_MAX);
      printf("Pere %d envoi %d pour la somme\n",i,m.data);
      msgsnd(msgid[i], &m , sizeof(int), 0);
    }
    }

  free(keystr);
   
  for(i=0;i<N;i++)
   wait(NULL);


  for(i=0;i<N;i++)
    msgctl(msgid[i], IPC_RMID,buf);
    

  return EXIT_SUCCESS;
}
