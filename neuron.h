#ifndef _NEURON_H
#define _NEURON_H


typedef struct edge{
  float weight;
  unsigned index;
  struct edge *next;
}edge;

typedef struct neuron{
 unsigned index;
 float activation;
 float cons;
 edge *edge;
 struct neuron *next; 
}neuron;


void push_neuron(neuron *root, neuron *val);
void free_neuron(neuron *root);

void push_edge(edge *root, edge *val);
void free_edge(edge *root);

#endif
