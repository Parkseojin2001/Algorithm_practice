#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

enum VisitMode { Visited, NotVisited };

typedef int ElementType;

typedef struct tagGraph {
	int **matrix; 
	int vertexCount; 
}Graph;

Graph* CreateGraph(int max_vertex);
void add_edge(Graph *graph, int start, int target, int weight); 
void delete_edge(Graph *graph, int start, int target);
int isEdge(Graph *graph, int start, int target); 
void modify_edge(Graph *graph, int vertex_num1, int vertex_num2, int weight); 
void Print_edge(Graph *g, int num); 

int main() {
	Graph *graph = CreateGraph(6);

	int num;
	char order;
	int vertex1, vertex2, weight;

	add_edge(graph, 1, 2, 1);
	add_edge(graph, 1, 3, 1);
	add_edge(graph, 1, 4, 1);
	add_edge(graph, 1, 6, 2);

	add_edge(graph, 2, 3, 1);

	add_edge(graph, 3, 5, 4);

	add_edge(graph, 5, 5, 4);

	add_edge(graph, 5, 6, 3);

	while (1) {
		scanf("%c", &order);

		if (order == 'a') { 
			scanf("%d", &num);
			Print_edge(graph, num);
		}
		else if (order == 'm') {
			scanf("%d %d %d", &vertex1, &vertex2, &weight);
			modify_edge(graph, vertex1, vertex2, weight);
		}
		else if (order == 'q') {
			return 0;
		}
		getchar();
	}

	return 0;
}

Graph* CreateGraph(int max_vertex) { 
	int i = 0;
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->vertexCount = max_vertex; 
	graph->matrix = (int **)malloc(sizeof(int *)*(max_vertex+1));

	for (i = 0; i <= max_vertex; i++) {
		graph->matrix[i] = (int *)malloc(sizeof(int)*(max_vertex+1));
		memset(graph->matrix[i], 0, sizeof(int)*(max_vertex+1)); 
	}
	return graph;
}

void add_edge(Graph *graph, int start, int target,int weight) { 
	graph->matrix[start][target] = weight; 
	graph->matrix[target][start] = weight; 
}


void delete_edge(Graph *graph, int start, int target) { 
	graph->matrix[start][target] = 0; 
	graph->matrix[target][start] = 0;
}

int isEdge(Graph *graph, int start,int target) {
	if (graph->matrix[start][target]) {
		return 1;
	}
	else { 
		return 0;
	}
}
void modify_edge(Graph *graph, int vertex_num1, int vertex_num2, int weight) { 

	if (vertex_num1 > graph->vertexCount|| vertex_num2 > graph->vertexCount
		|| vertex_num1<1||vertex_num2<1) { 
		printf("-1\n");
		return;
	}


	if (weight == 0) { 
		delete_edge(graph, vertex_num1, vertex_num2);
	}
	else {
		if (isEdge(graph,vertex_num1,vertex_num2)) { 
			graph->matrix[vertex_num1][vertex_num2] = weight; 
			graph->matrix[vertex_num2][vertex_num1] = weight; 
		}
		else {
			add_edge(graph,vertex_num1,vertex_num2,weight);
		}
	}


}

void Print_edge(Graph *g,int num) 
{
	int i;

	if (g->vertexCount < num || num < 1) {
		printf("-1\n");
		return;
	}

	for (i = 1; i <= g->vertexCount; i++)

	{

		if (g->matrix[num][i])
		{
			printf(" %d %d", i, g->matrix[num][i]);
		}

	}
	printf("\n");
}