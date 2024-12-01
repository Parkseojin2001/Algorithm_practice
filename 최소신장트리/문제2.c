#include <stdio.h>
#include <stdlib.h>

typedef struct INCIDENT {
	int edgeIdx;
	struct INCIDENT* next;
}incident;

typedef struct VERTEX {
	int num;
} vertex;

typedef struct EDGE {
	int u, v;
	int w;
} edge;

typedef struct GRAPH {
	int n, m;
	vertex* vertex;
	edge* edge;
} graph;

typedef struct DISJOINTSET {
	int setSize;
	incident* head; 
} disjoinset;

typedef struct HEAP {
	int edgeIdx; 
	int w; 
} heap;

graph Graph;

void initGraph(int n, int m);
void insertIncidentEdge(int u, int v, int w, int idx);
void addIncidentNode(incident** head, int idx);
int removeIncidentNode(incident** head);
void freeGraph();

void KruskalMST();
disjoinset* buildDisjointSet();
heap* buildMinHeap();
void downHeap(heap* Heap, int idx, int heapSize);
int extractMin(heap* Heap, int heapSize);
int findSet(disjoinset* set, int v);
void unionSet(disjoinset* set, int u, int v);
void swapElem(heap* x, heap* y);
void freeSet(disjoinset* set);

int main(void) {
	int N, M;
	int u, v, w;

	scanf("%d %d", &N, &M);
	initGraph(N, M);
	for (int i = 0; i < Graph.m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		insertIncidentEdge(u, v, w, i);
	}
	KruskalMST();

	freeGraph();
	return 0;
}

void initGraph(int n, int m) {
    Graph.n = n;
	Graph.m = m;
    Graph.edge = (edge*)malloc(m * sizeof(edge));
	Graph.vertex = (vertex*)malloc((n + 1) * sizeof(vertex)); 
	for (int i = 1; i <= n; i++) {
		Graph.vertex[i].num = i;
	}
}

void insertIncidentEdge(int u, int v, int w, int idx) {
	Graph.edge[idx].u = u;
	Graph.edge[idx].v = v;
	Graph.edge[idx].w = w;
}

void addIncidentNode(incident** head, int idx) {
	incident* node = (incident*)malloc(1 * sizeof(incident));
	node->edgeIdx = idx; 
	node->next = *head; 
	*head = node; 
}

int removeIncidentNode(incident** head) {
	if (*head == NULL) {
        return -1;
    }

	int idx_to_remove = (*head)->edgeIdx;
	*head = (*head)->next; 
	return idx_to_remove;
}

void freeGraph() {
	free(Graph.vertex);
	free(Graph.edge);
}

void KruskalMST() {
	disjoinset* set = buildDisjointSet();
	heap* heap = buildMinHeap();
	int heap_size = Graph.m;
	int distance_sum = 0; 
	int min_edge_idx, u, v;
	while (heap_size > 0) {
		min_edge_idx = extractMin(heap, heap_size); 
		u = findSet(set, Graph.edge[min_edge_idx - 1].u); 
		v = findSet(set, Graph.edge[min_edge_idx - 1].v); 
		if (u != v) { 
			printf(" %d", Graph.edge[min_edge_idx - 1].w);
			distance_sum += Graph.edge[min_edge_idx - 1].w;
			unionSet(set, u, v); 
		}
		heap_size--;
	}
    printf("\n");
	printf("%d", distance_sum);

	freeSet(set);
	free(heap);
}

disjoinset* buildDisjointSet() {
	disjoinset* set = (disjoinset*)malloc(Graph.n * sizeof(disjoinset));
	for (int i = 0; i < Graph.n; i++) {
        set[i].head = (incident*)malloc(1 * sizeof(incident));
        set[i].head->edgeIdx = Graph.vertex[i + 1].num;
		set[i].head->next = NULL;
		set[i].setSize = 0;
	}
	return set;
}

heap* buildMinHeap() {
	heap* Heap = (heap*)malloc((Graph.m + 1) * sizeof(heap));
	for (int i = 1; i <= Graph.m; i++) { 
		Heap[i].w = Graph.edge[i - 1].w;
		Heap[i].edgeIdx = i;
	}
	for (int i = Graph.m / 2; i >= 1; i--) { 
		downHeap(Heap, i, Graph.m);
	}
	return Heap;
}

void downHeap(heap* Heap, int idx, int heapSize) {
	int left_child_idx = 2 * idx;
	int right_child_idx = 2 * idx + 1;
	int smaller;
	if (left_child_idx > heapSize) {
        return;
    }

	smaller = left_child_idx;
	if (right_child_idx <= heapSize) {
		if (Heap[right_child_idx].w < Heap[left_child_idx].w) {
			smaller = right_child_idx;
		}
	}
	if (Heap[idx].w <= Heap[smaller].w) {
        return;
    }

	swapElem(Heap + idx, Heap + smaller); 
	downHeap(Heap, smaller, heapSize); 
}

int extractMin(heap* Heap, int heapSize) {
	if (heapSize == 0) {
        return -1;
    }
	
	heap idx_to_remove = Heap[1]; 
	swapElem(Heap + 1, Heap + heapSize); 
	downHeap(Heap, 1, heapSize - 1);
	return idx_to_remove.edgeIdx;
}

int findSet(disjoinset* set, int v) {
	incident* tmp;
	for (int i = 0; i < Graph.n; i++) {
		tmp = set[i].head; 
		while (tmp != NULL) { 
			if (Graph.vertex[tmp->edgeIdx].num == v) {
                return i;
            }
			tmp = tmp->next;
		}
	}
	return -1;
}

void unionSet(disjoinset* set, int u, int v) {
	int tmp, i;
	if (set[u].setSize < set[v].setSize) { 
		tmp = u;
		u = v;
		v = tmp;
	}

	while (1) { 
		i = removeIncidentNode(&(set[v].head));
		if (i == -1) {
            break;
        }

		addIncidentNode(&(set[u].head), i); 
	}

	set[v].head = NULL; 
	set[v].setSize = 0; 
}

void swapElem(heap* x, heap* y) {
	heap tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void freeSet(disjoinset* set) {
	incident* current;

	for (int i = 0; i < Graph.n; i++) {
		current = set[i].head; 
		while (current != NULL) {
			incident* temp = current;
			free(temp);
			current = current->next;
		}
	}
	free(set);
}
