#include <stdio.h>
#include <stdlib.h>

/* ---------- Graph Node ---------- */
typedef struct Node {
    int v;
    struct Node* next;
} Node;

/* ---------- Add Edge ---------- */
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(1);
    newNode->v = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Node** adjList, int u, int v) {
    Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

/* ---------- Read Graph (Undirected) ---------- */
Node** readGraph(int* n) {
    FILE* fp = fopen("graph.txt", "r");
    if (!fp) {
        printf("Error opening file\n");
        exit(1);
    }

    if (fscanf(fp, "%d", n) != 1 || *n <= 0) {
        printf("Invalid number of vertices\n");
        exit(1);
    }

    Node** adjList = (Node**)calloc(*n, sizeof(Node*));
    if (!adjList) exit(1);

    int val;

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(fp, "%d", &val) != 1) {
                printf("Invalid matrix input\n");
                exit(1);
            }

            // Build undirected graph (avoid duplicates)
            if (val == 1 && j > i) {
                addEdge(adjList, i, j);
                addEdge(adjList, j, i);
            }
        }
    }

    fclose(fp);
    return adjList;
}

/* ---------- Queue (Array-based) ---------- */
typedef struct {
    int* data;
    int front, rear;
} Queue;

Queue createQueue(int n) {
    Queue q;
    q.data = (int*)malloc(n * sizeof(int));
    q.front = q.rear = -1;
    return q;
}

int isQueueEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int x) {
    if (q->rear == -1) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->data[q->rear] = x;
}

int dequeue(Queue* q) {
    int x = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return x;
}

/* ---------- Stack (Array-based) ---------- */
typedef struct {
    int* data;
    int top;
} Stack;

Stack createStack(int n) {
    Stack s;
    s.data = (int*)malloc(n * sizeof(int));
    s.top = -1;
    return s;
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int x) {
    s->data[++(s->top)] = x;
}

int pop(Stack* s) {
    return s->data[(s->top)--];
}

/* ---------- BFS ---------- */
void BFS(Node** adjList, int n, int start) {
    int* visited = (int*)calloc(n, sizeof(int));
    Queue q = createQueue(n);

    enqueue(&q, start);
    visited[start] = 1;

    printf("BFS Order: ");
    while (!isQueueEmpty(&q)) {
        int u = dequeue(&q);
        printf("%c ", u + 'A'); // Print as character

        Node* temp = adjList[u];
        while (temp) {
            if (!visited[temp->v]) {
                visited[temp->v] = 1;
                enqueue(&q, temp->v);
            }
            temp = temp->next;
        }
    }
    printf("\n");

    free(visited);
    free(q.data);
}

/* ---------- DFS (Iterative) ---------- */
void DFS(Node** adjList, int n, int start) {
    int* visited = (int*)calloc(n, sizeof(int));
    Stack s = createStack(n);

    push(&s, start);
    visited[start] = 1;

    printf("DFS Order: ");
    while (!isStackEmpty(&s)) {
        int u = pop(&s);
        printf("%c ", u + 'A'); // Print as character

        Node* temp = adjList[u];
        while (temp) {
            if (!visited[temp->v]) {
                visited[temp->v] = 1;
                push(&s, temp->v);
            }
            temp = temp->next;
        }
    }
    printf("\n");

    free(visited);
    free(s.data);
}

/* ---------- Main ---------- */
int main() {
    int n;
    Node** adjList = readGraph(&n);

    BFS(adjList, n, 0);
    DFS(adjList, n, 0);

    // Free adjacency list
    for (int i = 0; i < n; i++) {
        Node* temp = adjList[i];
        while (temp) {
            Node* next = temp;
            temp = temp->next;
            free(next);
        }
    }
    free(adjList);
    return 0;
}