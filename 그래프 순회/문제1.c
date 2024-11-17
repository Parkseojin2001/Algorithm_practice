/*#include<stdio.h>
#include<string.h>
#define MAX 1001
 
int graph[MAX][MAX];
int visited[MAX];
int queue[MAX];
 
void DFS(int N, int S);
 
int main() {
	int n, m, s, x, y;
	scanf("%d %d %d", &n, &m, &s);
 
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		graph[x][y] = 1;
		graph[y][x] = 1;
	}
 
	DFS(n, s);
	printf("\n");
	memset(visited, 0, sizeof(int) * (n + 1));
	return 0;
}
 
void DFS(int N, int S) {
	visited[S] = 1;
	printf("%d\n", S);
	for (int i = 1; i <= N; i++) {
		if (visited[i] == 0 && graph[S][i]) {
			DFS(N, i);
		}
	}
	return;
}
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1001

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adj[MAX];
    int visited[MAX];
} Graph;

Node* createNode(int v);
void addEdgeSorted(Graph* graph, int src, int des);
void addEdge(Graph* graph, int src, int des);
void DFS(Graph* graph, int vertex);
Graph* createGraph();
void freeGraph(Graph* graph);

int main() {
    int n, m, s, x, y;

    Graph* graph = createGraph();

    scanf("%d %d %d", &n, &m, &s);
    
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        addEdge(graph, x, y);
    }
    
    DFS(graph, s);
    
    freeGraph(graph);
    
    return 0;
}


Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdgeSorted(Graph* graph, int src, int des) {
    Node* newNode = createNode(des);
    
    if (graph->adj[src] == NULL || graph->adj[src]->vertex > des) {
        newNode->next = graph->adj[src];
        graph->adj[src] = newNode;
    } else {
        Node* current = graph->adj[src];
        while (current->next != NULL && current->next->vertex < des) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void addEdge(Graph* graph, int src, int des) {
    addEdgeSorted(graph, src, des);  
    addEdgeSorted(graph, des, src);  
}

void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d\n", vertex);
    
    Node* tmp = graph->adj[vertex];
    while (tmp != NULL) {
        int connectedV = tmp->vertex;
        if (graph->visited[connectedV] == 0) {
            DFS(graph, connectedV);
        }
        tmp = tmp->next;
    }
}

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < MAX; i++) {
        graph->adj[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < MAX; i++) {
        Node* current = graph->adj[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph);
}