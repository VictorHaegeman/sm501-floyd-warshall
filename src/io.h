#ifndef IO_H
#define IO_H

#include "graph.h"

void print_graph_matrix(Graph *g);
void print_int_matrix(const char *title, int **mat, int n);
void interactive_shortest_paths(Graph *g, int **L, int **P);

#endif
