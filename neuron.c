#include <stdio.h>

#include "neuron.h"

void push_neuron(neuron *root, neuron *val)
{

  printf("Zadany index je: %d\n", val->index);
  printf("Aktivace: %f\n", val->activation);
  printf("Hrana: %d\n", val->edge->index);

}
