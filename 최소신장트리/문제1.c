#include <stdio.h>
#include <stdlib.h>

typedef struct Edge{
    int s;
    int e;
    int weight;
    struct Edge *next;
}edge;


edge *graph;
int visited[1001];

int path[101] = {0,};
int idx = 0;
edge *pq;

//method
edge *popqueue();
void enqueue(edge *e);
int isEmpty();
int prim(int s);
void handle_error(char *str);
void initGraph(int N);
void makeEdge(int a, int b, int weight);
void buildGraph(int M);
void print_path();


int main(){
    int n, N, M;
    scanf("%d %d", &N, &M);
    graph = (edge *)malloc(sizeof(edge)*(N+1));
    initGraph(N);
    buildGraph(M);
    n = prim(1);
    print_path();
    printf("%d\n", n);
}

void handle_error(char *str){
    printf("%s", str );
    exit(1);
}

void initGraph(int N){
    for(int i=1;i<=N;i++){
        graph[i].next = NULL;
        visited[i] = 0;
    }
    pq = (edge *)malloc(sizeof(edge));
    pq->next = NULL;
}

void makeEdge(int a, int b, int weight){
    edge *p, *newEdge;
    p = &graph[a];
    while(p->next != NULL && p->next->e < b)
        p = p->next;
    newEdge = (edge*)malloc(sizeof(edge));
    newEdge->weight = weight;
    newEdge->next = p->next;
    newEdge->s = a;
    newEdge->e = b;
    p->next = newEdge;
}

void buildGraph(int M){
    int u,v,w;
    for(int i=1;i<=M;i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        makeEdge(u,v,w);
        makeEdge(v,u,w);
    }
}

void print_path(){
    for(int i =0;i<idx;i++)
        printf("%d ", path[i]);
    printf("\n");
}
edge *popqueue(){
    edge *pop;
    if (pq->next == NULL)
        handle_error("ERROR!\n");
    pop = pq->next;
    pq->next= pop->next;
    return (pop);
}

void enqueue(edge *e){
    edge *p, *newedge;
    newedge = (edge*)malloc(sizeof(edge));
    newedge->weight = e->weight;
    newedge->e = e->e;
    newedge->s = e->s;

    p = pq;
    while(p->next != NULL && p->next->weight < e->weight)
        p = p->next;
    newedge->next = p->next;
    p->next = newedge;
}

int isEmpty(){
    if(pq->next == NULL)
        return 1;
    return 0;
}

int prim(int s){
    int f_cost = 0, current;
    edge *p, *pop;

    p = graph[s].next;
    while(p != NULL)
    {
        enqueue(p);
        p=p->next;
    }
    visited[s] = 1;
    path[idx++] = s;

    while(!isEmpty()){
        pop = popqueue();
        current = pop->e;
        if(visited[current] == 1){
            free(pop);
            continue;
        }
        path[idx++] = current;
        visited[current] = 1;
        f_cost += pop->weight;
        p = graph[current].next;
        while(p != NULL){
            if (visited[p->e] == 0) {
                enqueue(p);
            }
            p = p->next;
        }

    }
    return f_cost;
}