#include <stdio.h>
#include "io.h"
#include "floyd.h"

void print_int_matrix(const char *title, int **mat, int n) {
    if (title) printf("%s\n", title);

    printf("     ");
    for (int j = 0; j < n; j++) printf("%5d", j);
    printf("\n");

    printf("     ");
    for (int j = 0; j < n; j++) printf("-----");
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%3d |", i);
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == INF) printf("%5s", "INF");
            else printf("%5d", mat[i][j]);
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
        printf("Afficher un chemin ? (o/n) ");
        fgets(ans, sizeof(ans), stdin);

        if (ans[0] != 'o' && ans[0] != 'O') {
            printf("Fin.\n\n");
            return;
        }

        int src, dst;
        printf("Départ : ");
        scanf("%d", &src);
        printf("Arrivée : ");
        scanf("%d", &dst);

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}

        if (L[src][dst] == INF) {
            printf("Pas de chemin.\n\n");
        } else {
            printf("Coût : %d\n", L[src][dst]);
            printf("Chemin : ");
            floyd_print_path(P, src, dst);
            printf("\n");
        }
    }
}
