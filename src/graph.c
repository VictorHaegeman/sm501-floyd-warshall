#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int **alloc_int_matrix(int n) {
    int **m = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        m[i] = malloc(n * sizeof(int));
    }
    return m;
}

void free_int_matrix(int **m, int n) {
    if (!m) return;
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

Graph *graph_create(int n) {
    Graph *g = malloc(sizeof(Graph));
    g->n = n;
    g->w = alloc_int_matrix(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g->w[i][j] = (i == j ? 0 : INF);

    return g;
}

void graph_free(Graph *g) {
    if (!g) return;
    free_int_matrix(g->w, g->n);
    free(g);
}

int graph_load_from_file(const char *filename, Graph **g_out) {
    FILE *f = fopen(filename, "r");
    if (!f) return 1;

    int n, m;
    if (fscanf(f, "%d", &n) != 1) return 1;
    if (fscanf(f, "%d", &m) != 1) return 1;

    Graph *g = graph_create(n);

    for (int k = 0; k < m; k++) {
        int u, v, w;
        fscanf(f, "%d %d %d", &u, &v, &w);
        g->w[u][v] = w;
    }

    fclose(f);
    *g_out = g;
    return 0;
}
