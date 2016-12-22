#include <stdio.h>
#include <stdlib.h>


int nfork(int n){
  if(n<=0)
    return -1;
  int i;
  for(i=0;i<n;i++){
    if(fork()==0){
      return 0;
    }
  }
    
  return n;
  
}

int main (int argc, char** argv){

  nfork(3);

  return EXIT_SUCCESS;
}
