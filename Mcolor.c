#include <stdio.h>
#include <stdbool.h>

#define V 4  // Number of vertices in the graph

int solution_count = 0;

// Function to print the color array configuration
void printSolution(int color[]) {
    printf("Solution %d: [", ++solution_count);
    for (int i = 0; i < V; i++) {
        printf("%d", color[i]);
        if (i < V - 1) printf(", ");
    }
    printf("]\n");
}

// Function to check if the current color assignment is safe
bool isSafeColor(int vertex, int graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++) {
        // If there's an edge and the connected neighbor has the same color
        if (graph[vertex][i] == 1 && color[i] == c) {
            return false;
        }
    }
    return true;
}

// Recursive function to generate all coloring options
void graphColoringAll(int graph[V][V], int M, int color[], int vertex) {
    // Base Case: If all vertices are successfully colored
    if (vertex == V) {
        printSolution(color);
        return; // Return to search for alternative color paths
    }

    // Try assigning different colors from 1 to M
    for (int c = 1; c <= M; c++) {
        if (isSafeColor(vertex, graph, color, c)) {
            color[vertex] = c; // Assign color
            
            // Recurse for the next vertex
            graphColoringAll(graph, M, color, vertex + 1);
            
            // Forced Backtrack: Reset the vertex color to 0 
            // before trying the next color choice or returning up the stack
            color[vertex] = 0; 
        }
    }
}

int main() {
    int M = 3; // Maximum number of colors allowed
    
    /* Sample Graph (A square graph with one diagonal connection)
       (0)---(1)
        |  /  |
        | /   |
       (2)---(3)   */
    int graph[V][V] = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };
    
    int color[V];
    // Initialize all vertices as uncolored (0)
    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }
    
    printf("Finding all graph coloring configurations using max %d colors...\n", M);
    graphColoringAll(graph, M, color, 0);
    
    if (solution_count == 0) {
        printf("No valid coloring solution exists for M = %d\n", M);
    } else {
        printf("Total unique coloring patterns found: %d\n", solution_count);
    }
    
    return 0;
}