#include <stdio.h>
#include <stdlib.h>

#define MAX 50
#define INF 99999

int g[MAX][MAX], n;

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

            g[i][j] = val;
        }
    }

    fclose(fp);
}

int minDistance(int dist[], int visited[])
{
    int min = INF;
    int minIndex = -1;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && dist[i] < min)
        {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

/* ---------------- DIJKSTRA ALGORITHM ---------------- */
void printPath(int parent[], int v)
{
    if (v == -1)
    {
        return;
    }

    printPath(parent, parent[v]);

    printf("%c - ", 'A' + v);
}
void dijkstra(int start)
{
    int dist[MAX], visited[MAX], parent[MAX];

    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < n - 1; count++)
    {
        int u = minDistance(dist, visited);

        if (u == -1)
        {
            break;
        }

        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (g[u][v] > 0 &&
                !visited[v] &&
                dist[u] + g[u][v] < dist[v])
            {
                dist[v] = dist[u] + g[u][v];

                parent[v] = u;
            }
        }
    }

    printf("\nShortest Distances from %c:\n", 'A' + start);

    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INF)
        {
            printf("%c : Not Reachable\n", 'A' + i);
        }
        else
        {  printPath(parent, i);
            printf(" | Total Cost: %d\n", dist[i]);
            
        }
    }
}

int main()
{
    readGraph();  dijkstra(0);

    return 0;
}