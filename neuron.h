#ifndef _NEURON_H
#define _NEURON_H


typedef struct neuron{
 unsigned int index;
 float activation;
 struct dynEdge *edges;
 struct neuron *next; 
}neuron;

typedef struct edge{
  float weight;
  neuron *from;
  struct edge *next;
}edge;

typedef struct dynEdge{
  edge *first;
  edge *last;
  unsigned int size;
}dynEdge;

typedef struct dynNeuron{
  neuron *first;
  neuron *last;
  neuron *actual;
  unsigned int size;
}dynNeuron;

typedef struct layers{
  dynNeuron *items;
  unsigned int size;
}layers;

layers *create_layers(unsigned int size);
int push_edge(layers *root, unsigned int nm, unsigned int index_from, unsigned int index_to, float weight);
int push_neuron(layers *root, unsigned int nm, unsigned int index, float cons);
neuron *find_neuron(layers *root, unsigned int nm, unsigned int index);
void reset_actual(layers *root, unsigned int nm);
int get_max_activation_class(layers *root);
void free_all(layers **root);
int add_neuron_cons(layers *root, unsigned int nm, unsigned int index, float cons);

#endif
