#include <stdio.h>

#include "neural_net.h"

int parse_param(int value){

  if (value)
  { 
    return 0;
  }
  
  printf("Overuji vstupni soubory...\n");

  return 1;
}

int main(void){

  if (parse_param(1))
  {
    printf("Chyba...\n");
    return 1;
  }

  printf("Spustim program...\n");

  run();

  return 0;
}
