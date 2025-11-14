#include <stdio.h>
#include "io.h"
#include "floyd.h"

/* Largeur des colonnes pour avoir matrices lisibles */
#define COLW 10

void print_int_matrix(const char *title, int **mat, int n) {
    if (title) printf("%s\n", title);

    /* En-tête */
    printf("     ");
    for (int j = 0; j < n; j++)
        printf("%*d", COLW, j);
    printf("\n");

    printf("     ");
    for (int j = 0; j < n; j++)
        for (int k = 0; k < COLW; k++)
            printf("-");
    printf("\n");

    /* Lignes */
    for (int i = 0; i < n; i++) {
        printf("%3d |", i);
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == INF)
                printf("%*s", COLW, "INF");
            else
                printf("%*d", COLW, mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_graph_matrix(Graph *g) {
    print_int_matrix("Matrice des poids :", g->w, g->n);
}

void interactive_shortest_paths(Graph *g, int **L, int **P) {
    int n = g->n;

    while (1) {
        char ans[8];
        printf("Afficher un plus court chemin ? (o/n) ");
        if (!fgets(ans, sizeof(ans), stdin)) return;

        if (ans[0] != 'o' && ans[0] != 'O') {
            printf("Fin de la recherche de chemins.\n");
            return;
        }

        int src, dst;
        printf("Sommet de départ : ");
        if (scanf("%d", &src) != 1) {
            printf("Entrée invalide.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Sommet d'arrivée : ");
        if (scanf("%d", &dst) != 1) {
            printf("Entrée invalide.\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n'); /* Nettoyer entrée */

        if (src < 0 || src >= n || dst < 0 || dst >= n) {
            printf("Indices hors limites (0..%d).\n\n", n - 1);
            continue;
        }

        if (L[src][dst] == INF) {
            printf("Aucun chemin de %d à %d.\n\n", src, dst);
        } else {
            printf("\nCoût minimal = %d\n", L[src][dst]);
            printf("Chemin : ");
            floyd_print_path(P, src, dst);
            printf("\n");
        }
    }
}
