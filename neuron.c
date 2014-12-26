#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "neuron.h"


layers *create_layers(unsigned int size)
{
  layers *root;
  int i;

  if (!size) return NULL;

  root = (layers *) malloc (sizeof(layers));

  if (!root) return NULL;

  root -> items = malloc (size * sizeof(dynNeuron));
  if (!root -> items) return NULL;
  
  root -> size = size;
  root -> item_size = sizeof(dynNeuron);

  for ( i = 0; i < size; i++)
  {
    root -> items[i] -> size = 0;
  }

  return root;

}


int push_neuron(layers *root, unsigned int nm, unsigned int index, float cons)
{
  neuron *tmp;
  
  if (!root || !nm || !index || !cons) return 0;
  if (root -> size <= nm) return 0;

  tmp = (neuron *) malloc (sizeof(neuron));
  if (!tmp) return 0;

  tmp -> edges = (dynEdge *) malloc (sizeof(dynEdge));
  if (!tmp -> edges)
  {
    free (tmp);
    return 0;
  }

  tmp -> next = NULL;
  tmp -> activation = 0;
  tmp -> cons = cons;
  tmp -> index = index;

  tmp -> edges -> size = 0;

  if (root -> items[nm] -> size != 0)
  {
    root -> items[nm] -> last -> next = tmp;
  }else
  {
    root -> items[nm] -> first = tmp;
    root -> items[nm] -> actual = tmp;
  }

  root -> items[nm] -> last = tmp;
  root -> items[nm] -> size++;
  
  return 1;
}

int push_edge(layers *root, unsigned int nm, unsigned int index_from, unsigned int index_to, float weight)
{
  int i;
  neuron *from;
  neuron *to;
  edge *tmp_edge;

  nm -= 1;
  from = find_neuron(root, nm, index_from);
  if (!from) return 0;

  nm += 1;
  if (root -> items[nm] -> size <= index_to)
  {
    to = find_neuron(root, nm, index_to);
    if (!to) return 0;

  }else
  {
    if (push_neuron( root, nm, index_to, 0.0)) return 0;
    to = root -> items[nm] -> last;
  }

  tmp_edge = (edge *) malloc (sizeof(edge));
  if (!tmp_edge) return 0;

  tmp_edge -> weight = weight;
  tmp_edge -> next = NULL;
  tmp_edge -> from = from;

  if (to -> edges -> size != 0)
  {
    to -> edges -> last -> next = tmp_edge;
  
  }else
  {
    to -> edges -> first = tmp_edge;
  }
  
  to -> edges -> last = tmp_edge;
  to -> edges -> size++;
  return 1;
}

neuron *find_neuron(layers *root, unsigned int nm, unsigned int index)
{
  int i;

  for(i = root -> items[nm] -> actual -> index; i <= root -> items[nm] -> size; i++)
  {
    if (root -> items[nm] -> actual -> index == index)
    {
      return root -> items[nm] -> actual;
    }
    root -> items[nm] -> actual = root -> items[nm] -> actual -> next;
  }
  return NULL;
}

int reset_actual(layers *root, unsigned int nm)
{
  root -> items[nm] -> actual = root -> items[nm] -> first;
  return 1;
}

int get_max_activation_class(layers *root)
{
  int ind, i, class;
  float max;
  neuron *tmp;

  max = FLT_MIN;
  ind = root -> size -1;
  tmp = root -> items[ind] -> first;

  for (i = 0; i < root -> items[ind] -> size; i++)
  {
    if (max < tmp -> activation)
    {
      class = tmp -> index;
      tmp = tmp -> next;
    }
  }

  return class;
}
