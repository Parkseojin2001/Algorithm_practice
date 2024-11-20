#include <stdio.h>
#include <stdlib.h>


typedef struct INCIDENT {
	int edgeIdx; 
	struct INCIDENT* next; 
} Incident;


typedef struct EDGE {
	int src; 
	int dest; 
} Edge;

typedef struct VERTEX {
	char name; 
	Incident* inEdges; 
	Incident* outEdges; 
	int inDegree; 
} Vertex;

typedef struct GRAPH {
	Vertex* vertex; 
	Edge* edge; 
} Graph;

Graph graph;
int gN, gM; 
int g_topOrder[100];
int queue[100], gFront = 0, gRear = 0;

void initializeGraph();
void buildGraph();
void insertVertex(char vName, int idx);
void insertDirectedEdge(char src, char des, int idx);
int findVertexIdx(char vName);
void addFirst(Incident* head, int idx);
void topLogicalSort(); 
void initQueue();
int isQueueEmpty();
void enqueue(int v);
int dequeue();

int main() {
	buildGraph();

	topLogicalSort();
	if (g_topOrder[0] == 0) { 
		printf("0"); 
	}
	else { 
		for (int i = 1; i <= gN; i++) {
			printf("%c ", graph.vertex[g_topOrder[i]].name); 
		}
	}

	return 0;
}

void initializeGraph() {
	graph.vertex = (Vertex*)malloc(100 * sizeof(Vertex)); 
	graph.edge = (Edge*)malloc(1000 * sizeof(Edge)); 
}

void buildGraph() {
	int i;
	char vName, src, des;

	initializeGraph();

	scanf("%d", &gN);
	for (i = 0; i < gN; i++) {
		scanf(" %c", &vName);
		insertVertex(vName, i);
	}

	scanf("%d", &gM);
	for (i = 0; i < gM; i++) {
		scanf(" %c %c", &src, &des);
		insertDirectedEdge(src, des, i); 
	}
}

void insertVertex(char vName, int idx) {
	graph.vertex[idx].name = vName; 

	graph.vertex[idx].outEdges = (Incident*)malloc(1 * sizeof(Incident)); 
	graph.vertex[idx].inEdges = (Incident*)malloc(1 * sizeof(Incident)); 
	graph.vertex[idx].outEdges->next = NULL;
	graph.vertex[idx].inEdges->next = NULL;

	graph.vertex[idx].inDegree = 0;
}

void insertDirectedEdge(char src, char des, int idx) {
	int curVertexIdx = findVertexIdx(src); 
	int adjVertexIdx = findVertexIdx(des); 
	graph.edge[idx].src = curVertexIdx;
	graph.edge[idx].dest = adjVertexIdx;

	addFirst(graph.vertex[curVertexIdx].outEdges, idx); 
	addFirst(graph.vertex[adjVertexIdx].inEdges, idx);

	graph.vertex[adjVertexIdx].inDegree++; 
}

int findVertexIdx(char vName) {
	for (int i = 0; i < gN; i++) {
		if (graph.vertex[i].name == vName) 
			return i; 
	}
}

void addFirst(Incident* head, int idx) {
	Incident* node = (Incident*)malloc(1 * sizeof(Incident)); 
	node->edgeIdx = idx;
	node->next = head->next; 
	head->next = node;
}

void initQueue() {
	for (int i = 0; i < 100; i++) {
		queue[i] = 0;
	}
}

int isQueueEmpty() {
	return gFront == gRear;
}

void enqueue(int v) {
	queue[gRear] = v;
	gRear = (gRear + 1) % 100;
}

int dequeue() {
	int v = queue[gFront];
	gFront = (gFront + 1) % 100;
	return v;
}

void topLogicalSort() {
	int inDegreeArr[100];
	int sortIdx, curVertexIdx, adjVertexIdx;
	Incident* e;

	initQueue();
	for (int i = 0; i < gN; i++) {
		inDegreeArr[i] = graph.vertex[i].inDegree; 
		if (inDegreeArr[i] == 0) { 
			enqueue(i);
		}
	}

	sortIdx = 1;
	while (!isQueueEmpty()) {
		curVertexIdx = dequeue(); 
		g_topOrder[sortIdx] = curVertexIdx; 
		sortIdx++;

		e = graph.vertex[curVertexIdx].outEdges;
		e = e->next;
		while (e != NULL) {
			adjVertexIdx = graph.edge[e->edgeIdx].dest; 
			inDegreeArr[adjVertexIdx]--; 
			if (inDegreeArr[adjVertexIdx] == 0) { 
				enqueue(adjVertexIdx); 
			}
			e = e->next; 
		}
	}

	if (sortIdx <= gN) { 
		g_topOrder[0] = 0;
	}
	else {
		g_topOrder[0] = 1; 
	}
}