#include <stdio.h>

int n; // Number of vertices
int w[11][11], D[11][11],P[11][11]; // Weight, Distance, and Predecessor matrices

void readGraph() {
    FILE* fp;
    fp = fopen("graph.txt", "r");
    if(fp == NULL) return;

    fscanf(fp, "%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) { // Fixed: added * dereference
            fscanf(fp, "%d", &w[i][j]);
        }
    }
    fclose(fp);
}
void floyd() {
    // Initialization
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            D[i][j] = w[i][j];
            if(w[i][j] == 0 || w[i][j] == 999) {
                P[i][j] = -1; // No predecessor
            } else {
                P[i][j] = i;  // Direct link predecessor
            }
        }
    }

    
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {

                if(D[i][k] != 999 &&
                   D[k][j] != 999 &&
                   D[i][k] + D[k][j] < D[i][j]) {

                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(D[i][i] < 0) {
            printf("Negative cycle detected!\n");
            return;
        }
    }
}

void APSP(int i, int j) {
    if (i == j) {
        printf("%d", i);
    } 
    else if (P[i][j] == -1) {
        printf("NO PATH\n");
    } 
    else {
        APSP(i, P[i][j]); // Recursive call to find path up to the predecessor
        printf("--->%d", j);
    }
}

int main() {
    readGraph();
    n=n-1;
    floyd();
    printf("Enter source and destination vertices from 1 to %d:\n", n);
    while(1) {
        int src, dest;
        printf("Enter source and destination (Ctrl + C to exit): ");
        scanf("%d %d", &src, &dest); 
        
        // if (src < 1 || src > n || dest < 1 || dest > n) {
        //     printf("Invalid vertices! Please use 1 to %d.\n", n);
        //     continue;
        // }
        
        printf("Shortest path: ");
        APSP(src, dest);
        printf("\nCost = %d\n",D[src][dest]);
    }
    
    return 0;
}