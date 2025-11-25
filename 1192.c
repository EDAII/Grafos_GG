#include <stdlib.h>

int timer;
int* desc;
int* temp;
int** grafo;
int* gno;

int** resp;
int conta;

// Pegar o valor mínimo
int minimo(int a, int b) {
    if (a < b) return a;
    return b;
}

void dfs(int u, int pai) {
    timer++;
    desc[u] = timer;
    temp[u] = timer;

    for (int i = 0; i < gno[u]; i++) {
        int v = grafo[u][i];

        if (v == pai) continue;

        if (desc[v] != -1) {
            // se v ja foi visitado, atualiza o temp atual
            temp[u] = minimo(temp[u], desc[v]);
        } else {
            dfs(v, u);
            
            // na volta da recursão, atualiza com o valor do filho
            temp[u] = minimo(temp[u], temp[v]);

            if (temp[v] > desc[u]) {
                resp[conta] = (int*)malloc(2 * sizeof(int));
                resp[conta][0] = u;
                resp[conta][1] = v;
                conta++;
            }
        }
    }
}

int** criticalConnections(int n, int** connections, int connectionsSize, int* connectionsColSize, int* returnSize, int** returnColumnSizes) {
    desc = (int*)malloc(n * sizeof(int));
    temp = (int*)malloc(n * sizeof(int));
    gno = (int*)malloc(n * sizeof(int));
    timer = 0;

    for(int i = 0; i < n; i++) {
        desc[i] = -1;
        temp[i] = -1;
        gno[i] = 0;
    }

    // Conta o grau de cada nó
    for (int i = 0; i < connectionsSize; i++) {
        gno[connections[i][0]]++;
        gno[connections[i][1]]++;
    }

    grafo = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        grafo[i] = (int*)malloc(gno[i] * sizeof(int));
        gno[i] = 0;
    }

    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        
        grafo[u][gno[u]] = v;
        gno[u]++;
        
        grafo[v][gno[v]] = u;
        gno[v]++;
    }

    resp = (int**)malloc(connectionsSize * sizeof(int*));
    conta = 0;

    dfs(0, -1);

    *returnSize = conta;
    *returnColumnSizes = (int*)malloc(conta * sizeof(int));
    for(int i = 0; i < conta; i++) {
        (*returnColumnSizes)[i] = 2;
    }

    free(desc); free(temp); free(gno);
    for(int i=0; i<n; i++) free(grafo[i]);
    free(grafo);

    return resp;
}