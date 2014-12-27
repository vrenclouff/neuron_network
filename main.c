#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "neural_net.h"

int check_param(int value)
{

  if (value != 3)
  {
    printf("You have entered the wrong parameters. Run the program as:\nneural_net.exe <file with neural network> <file with number>\n");
    return 1;
  }

  return 0;
}

int main(int argc, char *argv[])
{

  if (check_param(argc)) exit(1);

  clock_t t1, t2;
  t1 = clock();

  run(argv[1], argv[2]);
  
  t2 = clock();
  printf("Proces bezel %f sekund\n", ((double) (t2-t1))/CLOCKS_PER_SEC); 

  return 0;
}
