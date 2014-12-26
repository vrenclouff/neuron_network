#include <stdio.h>
#include <stdlib.h>

#include "neuron.h"
#include "neural_net.h"

float count_activation()
{

  return 5.53;
}

int load_file(char *file, layers *root)
{
  FILE *fr;
  unsigned int count_layers;
  int i;
  layers *tmp;


  fr = fopen(file, "r");
  if (!fr)
  {
    printf("Soubor nelze otevrit.\n");
    return 0;         
  }

  fscanf(fr, "Pocet vrstev: %d", &count_layers);
  printf("Vrstev: %d\n", count_layers);

  count_layers += 1;

  tmp = create_layers(count_layers);
  if (!tmp) return 0;

  neuron ner;
  
  root = tmp;
  free(tmp);
  fclose(fr);
  return root != NULL ? 1 : 0; 
}

void run(char *neuron_network, char *data)
{

  layers *root;

  if (load_file(neuron_network, root))
  {
    printf("Data nebyla nactena\n"); 
  }



}
