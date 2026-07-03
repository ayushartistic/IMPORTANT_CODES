#include <stdio.h>
#include <stdlib.h>
#define INF 9999
#define MAX 50
int n;
int g[MAX][MAX],dist[MAX],parent[MAX];

void readGraph() {
    FILE* fp;
    fp = fopen("Wgraph.txt", "r");
    if(fp == NULL) return;

    fscanf(fp, "%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) { // Fixed: added * dereference
            fscanf(fp, "%d", &g[i][j]);
        }
    }
    fclose(fp);
}

void printPath(int parent[], int v)
{
    if (v == -1)
    {
        return;
    }

    printPath(parent, parent[v]);

    printf("%c - ", 'A' + v);
}

int bellman(int start) {
    for(int i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;

    // Relax edges V-1 times
    for(int i = 1; i <= n - 1; i++) {
        for(int u = 0; u < n; u++) {
            for(int v = 0; v < n; v++) {
                if(g[u][v] != 0 && dist[u] != INF) {
                    if(dist[u] + g[u][v] < dist[v]) {
                        dist[v] = dist[u] + g[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
    }

    // Check for negative weight cycles
    for(int u = 0; u < n; u++) {
        for(int v = 0; v < n; v++) {
            // Fixed: Added existence and INF validation
            if(g[u][v] != 0 && dist[u] != INF && dist[u] + g[u][v] < dist[v]) {
                return 0; // Negative cycle detected
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("Path to %c: Unreachable\n", i + 'A');
            continue;
        }
        
        printPath(parent, i);
        printf(" | Total Cost: %d\n", dist[i]);
        
    }
    return 1;
}



int main() {
    readGraph();
    
    // Print Input Matrix
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) {
    //         printf("%3d", g[i][j]);
    //     }
    //     printf("\n");
    // }

    if(bellman(0)) {
        printf("No negative weight cycle detected.\n");
    } else {
        printf("Graph contains a negative weight cycle!\n");
    }
    return 0;
}