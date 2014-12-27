#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
  int layer, index_from, index_to, index_pom, i;
  float weight;

  fr = fopen(neuron_network, "r");
  if (!fr) return 0;         

  fscanf(fr, "Pocet vrstev: %d\n", &count_layers);
  count_layers += 1;

  root = create_layers(count_layers);
  if (!root) return 0;

  if (!load_input_data(data)) return 0;

  reset_actual(root, 0);
  for (i = 1; i < count_layers; i++)
  {
    read_edges(fr);
    read_cons(fr);
    
    reset_actual(root, i);
/*    
    printf("Posledni index %d a hrana %d - %f\n",root -> items[i].last -> index, root -> items[i].last -> edges -> last -> from -> index, root -> items[i].last -> edges -> last -> weight);
    printf("Posledni aktivace %2.10f\n", root -> items[i].last -> activation);
 */
  }

  fclose(fr);
  return (!root) ? 1 : 0; 
}

int read_cons(FILE *frr)
{
  int layer, index;
  float cons;

  fscanf(frr,"b hodnoty vrstvy %d:\n", &layer);
  
  do{
    index = -1;
    fscanf(frr, "%d %f\n", &index, &cons);
    add_neuron_cons(root, layer, index, cons);
        
  }while(index != -1);

  return 1;
}

int read_edges(FILE *frr)
{
  int layer, index_from, index_to, index_pom;
  float weight;

  fscanf(frr, "W hodnoty vrstvy %d:\n", &layer);
  
  index_pom = 0;
  do{
    index_from = -1;
    fscanf(frr, "%d %d %f\n", &index_from, &index_to, &weight);

    if (index_from != index_pom)
    {
      index_pom = index_from;
      reset_actual(root, layer);
    }
    
    push_edge(root, layer, index_from, index_to, weight);
     
  }while(index_from != -1);

  return 1;
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
  return 1;
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
