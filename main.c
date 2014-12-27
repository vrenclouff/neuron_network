#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "neural_net.h"

int check_param(int value)
{

  if (value != 3)
  {
    printf("Chyba...\n");
    return 1;
  }
  
  printf("Overuji vstupni soubory...\n");

  return 0;
}

int main(int argc, char *argv[])
{

//  if (check_param(argc)) exit(0);


  printf("Spustim program...\n");

//  run(argv[1], argv[2]);
  clock_t t1, t2;
  t1 = clock();
  run("neuronova_sit.txt","vstupy/0.dat");
  t2 = clock();
  printf("Proces bezel %f sekund\n", ((double) (t2-t1))/CLOCKS_PER_SEC); 

  return 0;
}
