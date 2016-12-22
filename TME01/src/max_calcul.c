#include <stdio.h>
#include <stdlib.h>



int main (int argc, char** argv){
  
  
  int i,taille=argc-1,ret;
  
  int tab[taille];

  for(i=0;i<taille;i++){
    tab[i]=atoi (argv[i+1]);
    printf("%d\n",tab[i]);
  }
  ret = max_func(tab,taille);

  printf("Le maxmum est : %d\n",ret);
  
  return EXIT_SUCCESS;
}
