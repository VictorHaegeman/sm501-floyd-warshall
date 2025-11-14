#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "floyd.h"
#include "io.h"

int main() {
    char fname[256];

    printf("=== Floyd-Warshall ===\n\n");

    while (1) {
        printf("Nom du fichier (ou q): ");
        if (!fgets(fname, sizeof(fname), stdin)) break;
        fname[strcspn(fname, "\n")] = 0;

        if (fname[0] == 'q') break;

        Graph *g = NULL;
        if (graph_load_from_file(fname, &g) != 0) {
            printf("Erreur fichier.\n\n");
            continue;
        }

        print_graph_matrix(g);

        int **L, **P;
        floyd_warshall(g, &L, &P);

        print_int_matrix("Distances minimales :", L, g->n);

        if (floyd_contains_negative_cycle(L, g->n)) {
            printf("CIRCUIT ABSORBANT détecté !\n\n");
        } else {
            interactive_shortest_paths(g, L, P);
        }

        free_int_matrix(L, g->n);
        free_int_matrix(P, g->n);
        graph_free(g);
    }

    return 0;
}
