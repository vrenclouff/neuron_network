#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "neuron.h"
#include "neural_net.h"

/* Ukazatel na celou neuronovou sit */
layers *root;

/*
 ---------------------------------------------------------
  Spocita aktivaci pro neuron

  @param ner - neuron
  @return activation - spocitana aktivace
 ---------------------------------------------------------
*/
float count_activation(neuron *ner)
{
  int i;
  float activation;
  edge *edge_tmp;

  activation = ner -> activation;
  if (ner -> edges -> size != 0)
  {
    /* Projde vsechny hrany do daneho neuronu  */
    edge_tmp = ner -> edges -> first;
    for (i = 0; i < ner -> edges -> size; i++)
    {
      activation += (edge_tmp -> from -> activation * edge_tmp -> weight);
      edge_tmp = edge_tmp -> next;
    }
    activation = tanh(activation);
  }

  return activation;
}

/*
 ---------------------------------------------------------
  Spocita aktivace pro vsechny neurony ve vrstvach

  @return 1 - ve funkci nenastala chyba
 ---------------------------------------------------------
*/
int calculate_activations()
{
  int i, j, k;
  neuron *neuron_tmp;
  float activation;

  /* Neurony v danych vrstvach  */
  for (i = 1; i < root -> size; i++)
  {
    /* Neurony ve vrstve  */
    neuron_tmp = root -> items[i].first;
    for (j = 0; j < root -> items[i].size; j++)
    {
      activation = count_activation(neuron_tmp);
      neuron_tmp -> activation = activation;
      neuron_tmp = neuron_tmp -> next;
    }
  }
  return 1;
}

/*
 ---------------------------------------------------------
  Nacte oba vstupni soubory a vytvori strukturu

  @param neuron_network - nazev souboru s neuronovou siti
  @param data - nazev souboru s daty k rozpoznavani
  @return 1 - nacteni souboru bylo uspesne
 ---------------------------------------------------------
*/
int load_file(char *neuron_network, char *data)
{
  FILE *fr;
  unsigned int count_layers;
  int layer, index_from, index_to, index_pom, i;
  float weight;

  if (!neuron_network || !data) return 0;

  fr = fopen(neuron_network, "r");
  if (!fr) return 0;         

  fscanf(fr, "Pocet vrstev: %d\n", &count_layers);
  count_layers += 1;

  root = create_layers(count_layers);
  if (!root) return 0;

  if (!load_input_data(data)) return 0;

  for (i = 1; i < count_layers; i++)
  {
    read_edges(fr);
    read_cons(fr);
    
    reset_actual(root, i);
  }

  fclose(fr);
  return (!root) ? 1 : 0; 
}

/*
 ---------------------------------------------------------
  Nacte aktivace neuronu ze souboru

  @param frr - otevreny soubor s neuronovou siti
  @return 1 - nacteni bylo uspesne
 ---------------------------------------------------------
*/
int read_cons(FILE *frr)
{
  int layer, index;
  float cons;

  if (!frr) return 0;

  fscanf(frr,"b hodnoty vrstvy %d:\n", &layer);
  
  do{
    index = -1;
    fscanf(frr, "%d %f\n", &index, &cons);
    add_neuron_cons(root, layer, index, cons);
        
  }while(index != -1);

  return 1;
}

/*
 ---------------------------------------------------------
  Nacte hrany ze souboru

  @param frr - otevreny soubor s neuronovou siti
  @return 1 - nacteni bylo uspesne
 ---------------------------------------------------------
*/
int read_edges(FILE *frr)
{
  int layer, index_from, index_to, index_pom;
  float weight;

  if (!frr) return 0;

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

/*
 ---------------------------------------------------------
  Nacte data pro rozpoznavani

  @param file - nazev souboru s daty pro rozpoznani
  @return 1 - nacteni bylo uspesne
 ---------------------------------------------------------
*/
int load_input_data(char *file)
{
  FILE *fb;
  int i, length;
  float nm;

  if (!file) return 0;

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

/*
 ---------------------------------------------------------
  Ridi prubeh aplikace

  @param neuron_network - nazev souboru s neuronovou siti
  @param data - nazev souboru s daty pro rozpoznani
 ---------------------------------------------------------
*/
void run(char *neuron_network, char *data)
{ 
  int class;

  if (!neuron_network || !data) exit(1);

  if (load_file(neuron_network, data)) exit(2);

  calculate_activations();

  
  class = get_max_activation_class(root);
  printf("%d\n", class);

  free_all(&root);

}
