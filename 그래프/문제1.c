#include<stdio.h>
#include<stdlib.h>


typedef int ElementType;
typedef enum { NotVisited, Visited } VisitStatus;

typedef struct tagVertex {
	ElementType data; 
	struct tagVertex *next;
	struct tagEdge *ad_List; 
    VisitStatus visited;        
    int index; 
}Vertex;

typedef struct tagEdge {
	int weight; 
	struct tagEdge *next; 
	Vertex *start;
	Vertex *end; 
}Edge;

typedef struct tagGraph {
	Vertex *vertices; 
	int vertexCount; 
}Graph;

Graph* create_graph();
void destroy_graph(Graph* g); 
Vertex* create_vertex(ElementType data); 
void destroy_edgeOfVertex(Vertex* vertex, Edge* edge); 
Edge* create_edge(Vertex* start, Vertex* end, int weight); 
void destroy_edge(Edge* e);
void add_edge(Vertex* v, Edge* e); 
void add_vertex(Graph* g, Vertex* v);
void print_graph(Graph* g, int num); 
void modify_graph(Graph *graph, int vertexNum, int vertexNum2, int weight); 

int main() {
	Graph *Graph = create_graph();

	Vertex* v1 = create_vertex(1);
	Vertex* v2 = create_vertex(2);
	Vertex* v3 = create_vertex(3);
	Vertex* v4 = create_vertex(4);
	Vertex* v5 = create_vertex(5);
	Vertex* v6 = create_vertex(6);

	add_vertex(Graph, v1);
	add_vertex(Graph, v2);
	add_vertex(Graph, v3);
	add_vertex(Graph, v4);
	add_vertex(Graph, v5);
	add_vertex(Graph, v6);

	add_edge(v1, create_edge(v1, v2, 1));
	add_edge(v1, create_edge(v1, v3, 1));
	add_edge(v1, create_edge(v1, v4, 1));
	add_edge(v1, create_edge(v1, v6, 2));
	add_edge(v2, create_edge(v2, v1, 1));
	add_edge(v2, create_edge(v2, v3, 1));
	add_edge(v3, create_edge(v3, v1, 1));
	add_edge(v3, create_edge(v3, v2, 1));
	add_edge(v3, create_edge(v3, v5, 4));
	add_edge(v4, create_edge(v4, v1, 1));
	add_edge(v5, create_edge(v5, v3, 4));
	add_edge(v5, create_edge(v5, v5, 4));
	add_edge(v5, create_edge(v5, v6, 3));
	add_edge(v6, create_edge(v6, v1, 2));
	add_edge(v6, create_edge(v6, v5, 3));


	int number;
	char order;
	int vertex1, vertex2, weight;

	while (1) {
		scanf("%c", &order);

		if (order == 'a') { 
			scanf("%d", &number);
			print_graph(Graph, number);
		}
		else if (order == 'm') {
			scanf("%d %d %d", &vertex1, &vertex2, &weight);
			modify_graph(Graph, vertex1, vertex2, weight);
		}
		else if (order == 'q') {
			break;
		}
		getchar();
	}
	return 0;
}

Graph* create_graph() { 
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->vertices = NULL;
	graph->vertexCount = 0;
	return graph;
}

Vertex* create_vertex(ElementType data) {
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));

	v->data = data;
	v->next = NULL;
	v->ad_List = NULL;
	v->visited = NotVisited;
	v->index = -1;

	return v;
}

void destroy_edgeOfVertex(Vertex* vertex, Edge* edge) {
	Edge* pEdge = vertex->ad_List->next;
	Edge* preEdge = vertex->ad_List;

	while (preEdge != NULL) {
		if (vertex->ad_List->end->data == edge->end->data) { 
			destroy_edge(vertex->ad_List); 
			vertex->ad_List = pEdge;
			return;
		}
		else if (pEdge->end->data == edge->end->data) {
			preEdge->next = pEdge->next;
			destroy_edge(pEdge);
			return;
		}
		preEdge = preEdge->next;
		pEdge = pEdge->next;
	}
}

Edge* create_edge(Vertex* start, Vertex* end, int weight) { 
	Edge *edge = (Edge*)malloc(sizeof(Edge));
	edge->start = start;
	edge->end = end;
	edge->next = NULL;
	edge->weight = weight;

	return edge;
}

void destroy_edge(Edge* e) {
	free(e);
}

void add_vertex(Graph* g, Vertex* v) {
	Vertex* vertexList = g->vertices;

	if (vertexList == NULL) {
		g->vertices = v;
	}
	else {
		while (vertexList->next != NULL) {
			vertexList = vertexList->next;
		}
		vertexList->next = v;
	}
	v->index = g->vertexCount++;

}

void add_edge(Vertex* vertex, Edge* edge) {

	if (vertex->ad_List == NULL) {
		vertex->ad_List = edge;
	}
	else
	{
		Edge *adjacencyList = vertex->ad_List;

		while (adjacencyList->next != NULL) {

			if (adjacencyList->end->data > edge->end->data) {
				edge->next = adjacencyList;
				vertex->ad_List = edge;
				return;
			}
			else if (adjacencyList->next->end->data > edge->end->data) { 
				edge->next = adjacencyList->next;
				adjacencyList->next = edge;
				return;
			}
			adjacencyList = adjacencyList->next;
		}

		if (adjacencyList->end->data > edge->end->data) { 
			edge->next = adjacencyList;
			vertex->ad_List = edge;
			return;
		}

		adjacencyList->next = edge; 
	}
}


void print_graph(Graph* g, int num) { 
	Vertex *vertex = g->vertices;
	Edge *edge = NULL;

	while (1) {

		if (vertex == NULL) {
			printf("-1\n");
			return;
		}

		edge = vertex->ad_List;

		if (vertex->data == num) {
			while (edge != NULL) {
				printf(" %d %d", edge->end->data, edge->weight);
				edge = edge->next;
			}
			printf("\n");
			return;
		}

		vertex = vertex->next;
	}
	printf("\n");

}

void modify_graph(Graph *graph, int vertex_num, int vertex_num2, int weight) { 

	Vertex *vertex = graph->vertices;
	Edge *edge = NULL;
	int cnt = 0;
	Vertex *vertex_1, *vertex_2;
	while (1) {
		if (vertex == NULL) 
		{
			printf("-1\n");
			return;
		}
		else if (vertex->data == vertex_num && vertex->data == vertex_num2) {
			vertex_1 = vertex;
			vertex_2 = vertex;
			break; 
		}
		else if (vertex->data == vertex_num) {
			vertex_1 = vertex;
			cnt++;
		}
		else if (vertex->data == vertex_num2) {
			vertex_2 = vertex;
			cnt++;
		}

		if (cnt == 2)
			break;

		vertex = vertex->next;

	}
	cnt = 0;
	vertex = graph->vertices;
	while (1) {
		if (vertex->data == vertex_1->data) {
			edge = vertex->ad_List;
			while (1) {
				if (edge == NULL) { 
					if (weight == 0)
						return;

					if (vertex->data == vertex_1->data && vertex->data == vertex_2->data) {
						add_edge(vertex, create_edge(vertex, vertex_1, weight));
						return;
					}
					else if (vertex->data == vertex_num) {
						add_edge(vertex, create_edge(vertex, vertex_2, weight));
						cnt++;
						break;
					}
					else if (vertex->data == vertex_num2) {
						add_edge(vertex, create_edge(vertex, vertex_1, weight));
						cnt++;
						break;
					}

				}
				else if (edge->end->data == vertex_2->data && edge->end->data == vertex_1->data) {
					if (weight == 0) { 
						destroy_edgeOfVertex(vertex, edge);
						return;
					}
					edge->weight = weight; 
					return;
				}
				else if (edge->end->data == vertex_2->data) {
					if (weight == 0) { 
						destroy_edgeOfVertex(vertex, edge);
					}
					else {
						edge->weight = weight;
					}
					cnt++;
					break;
				}
				edge = edge->next;

			} 
			if (cnt == 2)
				return;
		} 
		else if (vertex->data == vertex_2->data) {
			edge = vertex->ad_List;
			while (1) {
				if (edge == NULL) { 
					if (weight == 0)
						return;

					if (vertex->data == vertex_1->data && vertex->data == vertex_2->data) {
						add_edge(vertex, create_edge(vertex, vertex_1, weight));
						return;
					}
					else if (vertex->data == vertex_num) {
						add_edge(vertex, create_edge(vertex, vertex_2, weight));
						cnt++;
						break;
					}
					else if (vertex->data == vertex_num2) {
						add_edge(vertex, create_edge(vertex, vertex_1, weight));
						cnt++;
						break;
					}

				}
				else if (edge->end->data == vertex_2->data && edge->end->data == vertex_1->data) {
					if (weight == 0) { 
						destroy_edgeOfVertex(vertex, edge);
						return;
					}
					edge->weight = weight; 
					return;
				}
				else if (edge->end->data == vertex_1->data) {
					if (weight == 0) { 
						destroy_edgeOfVertex(vertex, edge);
					}
					else {
						edge->weight = weight;
					}
					cnt++;
					break;
				}
				edge = edge->next;

			} 
			if (cnt == 2)
				return;
		}
		vertex = vertex->next;
	}
}