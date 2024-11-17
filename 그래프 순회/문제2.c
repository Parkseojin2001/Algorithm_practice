#include<stdio.h>
#include<string.h>
#define MAX 1001
 
int graph[MAX][MAX];
int visited[MAX];
int queue[MAX];
 
void BFS(int N, int S);
 
int main() {
	int n, m, s, x, y;
	scanf("%d %d %d", &n, &m, &s);
 
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		graph[x][y] = 1;
		graph[y][x] = 1;
	}

	for (int i = 0; i <= n; i++) {
        visited[i] = 0; 
    }
	BFS(n, s);
	return 0;
}
 
void BFS(int N, int S) {
	int front = -1, rear = -1, pop;
	printf("%d\n", S);
	visited[S] = 1;
	queue[++rear] = S;
 
	while (front < rear) {
		pop = queue[++front];
		for (int i = 1; i <= N; i++) {
			if (visited[i] == 0 && graph[pop][i]) {
				printf("%d\n", i);
				visited[i] = 1;
				queue[++rear] = i;
			}
		}
	}
	return;
}