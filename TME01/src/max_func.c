#include "../include/max_func.h"

int max_func (int tab[], int taille){
  int ret=-1,i;
  for (i=0;i<taille;i++)
    if (tab[i]>ret)
      ret=tab[i];
  return ret;
}
