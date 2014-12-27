#include <stdio.h>
#include <stdlib.h>

#include "neuron.h"
#include "neural_net.h"

layers *root;

float count_activation()
{

  return 5.53;
}

int load_file(char *neuron_network, char *data)
{
  FILE *fr;
  unsigned int count_layers;
  int layer, index_from, index_to, index_pom;
  float weight;

  fr = fopen(neuron_network, "r");
  if (!fr) return 0;         

  fscanf(fr, "Pocet vrstev: %d\n", &count_layers);
  count_layers += 1;

  root = create_layers(count_layers);
  if (!root) return 0;

  if (load_input_data(data)) return 0;

  fscanf(fr, "W hodnoty vrstvy %d:\n", &layer);
  
  index_pom = 0;
  do{
    index_from = -1;
    fscanf(fr, "%d %d %f\n", &index_from, &index_to, &weight);

    if (index_from != index_pom)
    {
      index_pom = index_from;
      reset_actual(root, layer);
    }
    
    push_edge(root, layer, index_from, index_to, weight);
     
  }while(index_from != -1);

  printf("%d\n", root -> items[layer].size);

  fclose(fr);
  return (!root) ? 1 : 0; 
}

int load_input_data(char *file)
{
  FILE *fb;
  int i, length;
  float nm;

  fb = fopen(file, "rb");
  if (!fb) return 0;

  fseek(fb, 0, SEEK_END);
  length = ftell(fb);
  rewind (fb);
  
  i = 0;
  while(fread(&nm, sizeof(float), 1, fb) != 0) push_neuron(root, 0, i++, nm);
  
  fclose(fb);
  return 0;
}

void run(char *neuron_network, char *data)
{ 
  int class;

  if (load_file(neuron_network, data))
  {
    printf("Data nebyla nactena\n"); 
    exit(0);
  }
/*  
  class = get_max_activation_class(root);
  printf("%d\n", class);

  free_all(&root);
*/
}
