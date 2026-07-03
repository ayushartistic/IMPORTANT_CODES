#include <stdio.h>
#include <stdlib.h>

#define MAX 50
#define INF 99999

int g[MAX][MAX], n;

typedef struct Edge
{
    int u, v, weight;
} Edge;

Edge edges[MAX * MAX];
Edge solution[MAX * MAX];

int edgeCount = 0;
int parent[MAX];

/* ---------------- GRAPH INPUT ---------------- */

void readGraph()
{
    FILE *fp = fopen("Wgraph.txt", "r");

    if (!fp)
    {
        printf("Error opening file\n");
        exit(1);
    }

    if (fscanf(fp, "%d", &n) != 1 || n <= 0 || n > MAX)
    {
        printf("Invalid number of vertices\n");
        exit(1);
    }

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            g[i][j] = 0;
        }
    }

    int val;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(fp, "%d", &val) != 1)
            {
                printf("Invalid matrix input\n");
                exit(1);
            }

            if (val > 0 && j > i)
            {
                g[i][j] = g[j][i] = val;
            }
        }
    }

    fclose(fp);
}

/* ---------------- COMMON FUNCTIONS ---------------- */

// void displayMatrix()
// {
//     printf("\nAdjacency Matrix:\n");

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             printf("%4d", g[i][j]);
//         }
//         printf("\n");
//     }
// }

void makeEdges()
{
    edgeCount = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (g[i][j] > 0)
            {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = g[i][j];

                edgeCount++;
            }
        }
    }
}

void displayEdges()
{
    printf("\nEdges (u, v, weight):\n");

    for (int i = 0; i < edgeCount; i++)
    {
        printf("%c - %c : %d\n",
               'A' + edges[i].u,
               'A' + edges[i].v,
               edges[i].weight);
    }
}

/* ---------------- KRUSKAL FUNCTIONS ---------------- */

void initParent()
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = -1;
    }
}

int find(int x)
{
    if (parent[x] < 0)
    {
        return x;
    }

    return parent[x] = find(parent[x]);
}

void unionSet(int a, int b)
{
    int rootA = find(a);
    int rootB = find(b);

    if (rootA == rootB)
    {
        return;
    }

    if (parent[rootA] < parent[rootB])
    {
        parent[rootA] += parent[rootB];
        parent[rootB] = rootA;
    }
    else
    {
        parent[rootB] += parent[rootA];
        parent[rootA] = rootB;
    }
}

void sortEdges()
{
    for (int i = 0; i < edgeCount - 1; i++)
    {
        int swapped = 0;

        for (int j = 0; j < edgeCount - i - 1; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;

                swapped = 1;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}

void kruskalMST()
{
    printf("\nKRUSKAL MST\n");

    initParent();

    sortEdges();

    int solCount = 0;
    int totalCost = 0;

    for (int i = 0; i < edgeCount && solCount < n - 1; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        if (find(u) != find(v))
        {
            solution[solCount++] = edges[i];

            totalCost += edges[i].weight;

            unionSet(u, v);
        }
    }

    if (solCount != n - 1)
    {
        printf("\nGraph is disconnected.\n");
        return;
    }

    printf("\nMST Edges:\n");

    for (int i = 0; i < solCount; i++)
    {
        printf("%c - %c : %d\n",
               'A' + solution[i].u,
               'A' + solution[i].v,
               solution[i].weight);
    }

    printf("\nTotal MST Cost = %d\n", totalCost);
}

/* ---------------- PRIM FUNCTIONS ---------------- */

int minKey(int key[], int visited[])
{
    int min = INF;
    int minIndex = -1;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && key[i] < min)
        {
            min = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void primMST()
{
    printf("\nPRIM MST\n");

    int prt[MAX];
    int key[MAX];
    int visited[MAX];

    for (int i = 0; i < n; i++)
    {
        key[i] = INF;
        visited[i] = 0;
        prt[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < n - 1; count++)
    {
        int u = minKey(key, visited);

        if (u == -1)
        {
            break;
        }

        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (g[u][v] > 0 &&
                !visited[v] &&
                g[u][v] < key[v])
            {
                key[v] = g[u][v];
                prt[v] = u;
            }
        }
    }

    int totalCost = 0;

    printf("\nMST Edges:\n");

    for (int i = 1; i < n; i++)
    {
        if (prt[i] == -1)
        {
            printf("\nGraph is disconnected.\n");
            return;
        }

        printf("%c - %c : %d\n",
               'A' + prt[i],
               'A' + i,
               g[i][prt[i]]);

        totalCost += g[i][prt[i]];
    }

    printf("\nTotal MST Cost = %d\n", totalCost);
}

/* ---------------- MAIN ---------------- */

int main()
{
    readGraph();

    // displayMatrix();

    makeEdges();

    printf("\nOriginal Edge List:\n");
    displayEdges();

    kruskalMST();

    primMST();

    return 0;
}