#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#define INF 1000000000

typedef struct {
    int n;
    int **w;
} Graph;

int **alloc_int_matrix(int n);
void  free_int_matrix(int **m, int n);

Graph *graph_create(int n);
void   graph_free(Graph *g);

int graph_load_from_file(const char *filename, Graph **g_out);

#endif
