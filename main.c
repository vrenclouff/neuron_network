#include <stdio.h>
#include <stdlib.h>

#include "neural_net.h"


/*
 ---------------------------------------------------------
  Kontrola vstupnich parametru

  @param value - pocet parametru
  @return 0 - parametry jsou v poradku 
 ---------------------------------------------------------
*/
int check_param(int value)
{

  if (value != 3)
  {
    printf("You have entered the wrong parameters. Run the program as:\nneural_net.exe <file with neural network> <file with number>\n");
    return 1;
  }

  return 0;
}

/*
 ---------------------------------------------------------
  Funkce main pro spusteni programu

  @param argc - pocet parametru
  @param argv - nazvy parametru
  @return 0 - program probehl spravne
 ---------------------------------------------------------
*/
int main(int argc, char *argv[])
{

  if (check_param(argc)) exit(1);

  run(argv[1], argv[2]);
  
  return 0;
}
