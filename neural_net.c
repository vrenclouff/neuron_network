#include <stdio.h>
#include <stdlib.h>

#include "neuron.h"
#include "neural_net.h"

float count_activation(){

  return 5.53;
}

void run(){
 
  printf("Loanding and crating neuron network...\n");

  neuron root, val;
  edge val_edge;

  val_edge.index = 1;

  val.index = 5;
  val.edge = &val_edge;
  val.activation = count_activation();

  push_neuron(&root, &val);


}
