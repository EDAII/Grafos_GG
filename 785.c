#include <stdbool.h>
#include <stdlib.h>

bool pintar(int u, int cor_atual, int** grafo, int* tam_col, int* cores) {
    cores[u] = cor_atual;

    // Percorre os vizinhos
    for (int i = 0; i < tam_col[u]; i++) {
        int viz = grafo[u][i]; // vizinho

        // Se o vizinho tem a memsa cor, não é bipartido
        if (cores[viz] == cor_atual) {
            return false;
        }

        if (cores[viz] == 0) {
            if (!pintar(viz, -cor_atual, grafo, tam_col, cores)) {
                return false;
            }
        }
    }
    return true;
}

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int* cores = (int*)malloc(graphSize * sizeof(int));

    // 0 
    for(int i = 0; i < graphSize; i++) {
        cores[i] = 0;
    }

    // Passa por todos os nós
    for (int i = 0; i < graphSize; i++) {
        if (cores[i] == 0) {
            // Tenta começar a pintar com a cor 1
            if (!pintar(i, 1, graph, graphColSize, cores)) {
                free(cores);
                return false;
            }
        }
    }

    free(cores);
    return true;
}