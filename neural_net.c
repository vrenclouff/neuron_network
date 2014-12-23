#include <stdio.h>
#include <stdlib.h>

#include "neuron.h"
#include "neural_net.h"

float count_activation()
{

  return 5.53;
}

int load_file(char *file, neuron *layers)
{
  FILE *fr;
  unsigned int count_layers;
  neuron *layer_p;

  fr = fopen(file, "r");
  if (fr == NULL)
  {
    printf("Soubor nelze otevrit.\n");
    return 0;         
  }

  fscanf(fr, "Pocet vrstev: %d", &count_layers);
  printf("Vrstev: %d\n", count_layers);

  layer_p = (neuron *) malloc (sizeof((count_layers+1) * sizeof(neuron)));
  if (layer_p == NULL)
  {
    printf("Malo pameti pro alokaci\n");
    return 0;
  }

  layers = layer_p;
  free(layer_p); 
  fclose(fr);
  return layers != NULL ? 1 : 0; 
}

void run(char *neuron_network, char *data)
{

  neuron *layers;

  if (load_file(neuron_network, layers))
  {
    printf("Soubor nenacten\n"); 
  }



/*
  neuron root, val;
  edge val_edge;

  val_edge.index = 1;

  val.index = 5;
  val.edge = &val_edge;
  val.activation = count_activation();

  push_neuron(&root, &val);
*/

}
