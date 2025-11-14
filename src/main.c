#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "floyd.h"
#include "io.h"

int main() {
    char fname[256];

    printf("=== Floyd-Warshall – Projet SM501 ===\n\n");

    while (1) {
        printf("Nom du fichier (ou 'q' pour quitter) : ");

        if (!fgets(fname, sizeof(fname), stdin)) break;
        fname[strcspn(fname, "\n")] = 0;

        if (fname[0] == 'q' || fname[0] == 'Q') {
            printf("\nFin du programme.\n");
            break;
        }

        Graph *g = NULL;

        if (graph_load_from_file(fname, &g) != 0) {
            printf("Erreur : impossible de lire le fichier '%s'.\n\n", fname);
            continue;
        }

        printf("\nGraphe chargé depuis '%s'\n", fname);
        print_graph_matrix(g);

        int **L = NULL;
        int **P = NULL;

        floyd_warshall(g, &L, &P);

        /* Vérification du cycle négatif AVANT affichage */
        if (floyd_contains_negative_cycle(L, g->n)) {
            printf("\n==============================================\n");
            printf("⚠️  CIRCUIT ABSORBANT DÉTECTÉ !\n");
            printf("⚠️  Les distances minimales NE SONT PAS VALABLES.\n");
            printf("==============================================\n\n");
        } else {
            print_int_matrix("Distances minimales :", L, g->n);
            interactive_shortest_paths(g, L, P);
        }

        /* Libération mémoire */
        free_int_matrix(L, g->n);
        free_int_matrix(P, g->n);
        graph_free(g);

        printf("\n");
    }

    return 0;
}
