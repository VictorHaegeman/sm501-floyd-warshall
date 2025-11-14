#include <stdio.h>
#include <stdlib.h>
#include "floyd.h"

/*
   Conformément au cours :
   L[i][j] = coût(i,j)
   P[i][j] = i si arc existant, sinon -1
*/

void floyd_warshall(Graph *g, int ***L_out, int ***P_out) {
    int n = g->n;

    int **L = alloc_int_matrix(n);
    int **P = alloc_int_matrix(n);

    // --- INITIALISATION ---
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            L[i][j] = g->w[i][j];

            if (i == j || g->w[i][j] == INF)
                P[i][j] = -1;
            else
                P[i][j] = i;
        }
    }

    // --- ALGORITHME DE FLOYD-WARSHALL ---
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (L[i][k] == INF) continue;

            for (int j = 0; j < n; j++) {
                if (L[k][j] == INF) continue;

                int new_cost = L[i][k] + L[k][j];

                if (new_cost < L[i][j]) {
                    L[i][j] = new_cost;
                    P[i][j] = P[k][j];   // EXACTEMENT COMME DANS LE COURS
                }
            }
        }
    }

    *L_out = L;
    *P_out = P;
}

int floyd_contains_negative_cycle(int **L, int n) {
    for (int i = 0; i < n; i++)
        if (L[i][i] < 0) return 1;
    return 0;
}

// -------- Reconstruction des chemins (cours) ---------

static void print_path_rec(int **P, int i, int j) {
    if (i == j) {
        printf("%d", i);
    } else if (P[i][j] == -1) {
        printf(" ? ");
    } else {
        print_path_rec(P, i, P[i][j]);
        printf(" -> %d", j);
    }
}

void floyd_print_path(int **P, int src, int dst) {
    print_path_rec(P, src, dst);
    printf("\n");
}
