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

  val.index = 5;
  val.activation = count_activation();

  push_neuron(&root, &val);


}
