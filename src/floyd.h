#ifndef FLOYD_H
#define FLOYD_H

#include "graph.h"

void floyd_warshall(Graph *g, int ***L_out, int ***P_out);
int floyd_contains_negative_cycle(int **L, int n);
void floyd_print_path(int **P, int src, int dst);

#endif
