#include <stdio.h>
#include<stdlib.h>
#define MAX 10
typedef struct Stack{
    int a[MAX];
    int top;
}Stack;
typedef struct {
    int a[MAX];
    int front,rear;
}Queue;
Stack* createStack(){
    Stack* s1 = malloc(sizeof *s1);
    s1->top=-1;
    return s1;
}
int isEmpty(Stack* s){
    return s->top==-1;
}
void push(Stack* s,int k){
    if(s->top!=MAX-1) {
        (s->top)++;
        s->a[s->top]=k;
    }
    return;
}
int pop(Stack* s){
    if(s->top==-1) return 999;
    return s->a[(s->top)--];
}
Queue* createQueue(){
    Queue* q = malloc(sizeof *q);
    q->front = q->rear = -1;
}
void enqueue(Queue* q, int k){
    if(q->rear==MAX-1) return;
    (q->rear)++;
    q->a[q->rear] = k;

}
int dequeue(Queue* q){
    if(q->front==q->rear) return 999;
    return q->a[++(q->front)];
}
int isEmptyQ(Queue* q){
    return q->front==q->rear;
}
void display(Stack* s){
    if(s->top==-1) return;
    for(int i=0;i<=s->top;i++) printf("%d ",s->a[i]);
}
int w[MAX][MAX];
int n;
void readGraph(){
    FILE* fp = fopen("testgraph.txt","r");
    if(!fp) return;
    fscanf(fp,"%d",&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fscanf(fp,"%d",&w[i][j]);
        }
    }
    fclose(fp);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",w[i][j]);
        }
        printf("\n");
    }
}

int main(){
    

    Stack* s1 = createStack();
    readGraph();
    printf("\n");
    printf("DFS - \n");
    int visited[n];
    for(int i=0;i<n;i++) visited[i]=0;
    push(s1,0);
    visited[0]=1;
    while(!isEmpty(s1)){
        int x = pop(s1);
        printf("%d ",x);
        for(int j=0;j<n;j++){
            if(w[x][j]){
                if(!visited[j]) {
                    visited[j]=1;
                    push(s1,j);
                }
            }
        }

    }
    printf("\n");
    printf("BFS - \n");
    Queue* q1 = createQueue();
    for(int i=0;i<n;i++) visited[i]=0;
    enqueue(q1,0);
    visited[0]=1;
    while(!isEmptyQ(q1)){
        int x = dequeue(q1);
        printf("%d ",x);
        for(int j=0;j<n;j++){
            if(w[x][j]){
                if(!visited[j]) {
                    visited[j]=1;
                    enqueue(q1,j);
                }
            }
        }

    }

}
