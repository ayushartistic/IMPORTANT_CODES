#include <stdio.h>
#include <stdbool.h>

#define V 5 // Number of vertices

int solution_count = 0;

// Function to print a valid cycle path
void printSolution(int path[]) {
    printf("Solution %d: ", ++solution_count);
    for (int i = 0; i < V; i++) {
        printf("%d -> ", path[i]);
    }
    printf("%d\n", path[0]); // Complete the loop back to the start
}

// Check if vertex v can be added at index 'pos' in the path
bool isSafeHam(int v, int graph[V][V], int path[], int pos) {
    // Check if this vertex is connected to the previously added vertex
    if (graph[path[pos - 1]][v] == 0) {
        return false;
    }

    // Check if this vertex has already been visited in the current path
    for (int i = 0; i < pos; i++) {
        if (path[i] == v) {
            return false;
        }
    }

    return true;
}

// Recursive utility to find all Hamiltonian Cycles
void hamCycleUtil(int graph[V][V], int path[], int pos) {
    // Base Case: If all vertices are included in the path
    if (pos == V) {
        // Double check if there is an edge from the last vertex back to the first vertex
        if (graph[path[pos - 1]][path[0]] == 1) {
            printSolution(path);
        }
        return; // Return to look for alternative paths
    }

    // Try different vertices as the next candidate in the path
    for (int v = 1; v < V; v++) {
        if (isSafeHam(v, graph, path, pos)) {
            path[pos] = v; // Place vertex in path

            // Recurse to find the next vertex
            hamCycleUtil(graph, path, pos + 1);

            // Forced Backtrack: Reset choice
            path[pos] = -1;
        }
    }
}

int main() {
    /* Sample Graph:
       (0)---(1)---(2)
        |   /   \   |
        |  /     \  |
        | /       \ |
       (3)---------(4)   */
    int graph[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    int path[V];
    for (int i = 0; i < V; i++) {
        path[i] = -1;
    }

    // Fix the first vertex as 0
    path[0] = 0; 
    
    printf("Finding all Hamiltonian Cycles starting from Vertex 0...\n");
    hamCycleUtil(graph, path, 1);

    if (solution_count == 0) {
        printf("No Hamiltonian Cycle exists in this graph.\n");
    } else {
        printf("Total unique Hamiltonian cycles found: %d\n", solution_count);
    }

    return 0;
}