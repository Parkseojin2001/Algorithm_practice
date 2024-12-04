#include <stdio.h>
#include <stdlib.h>

int dist[101];

void dijkstraShortestPath(int n, int m, int s);
void printResult(int n, int s);


int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    dijkstraShortestPath(n, m , s); 
    printResult(n ,s);
    return 0;
}

void dijkstraShortestPath(int n, int m, int s) {

    int graph[101][101] = {0}, visited[101] = {0};
    int u, v, w, minDist;
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w; 
    }
    for (int i = 1; i <= n; i++) {
        dist[i] = (i == s) ? 0 : 30000;
    }

    for (int count = 0; count < n - 1; count++) {
        minDist = 30000;
        u = -1;

        for (int v = 1; v <= n; v++) {
            if (visited[v] == 0 && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (visited[v] == 0 && graph[u][v] > 0) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }
}
void printResult(int n, int s){
    for (int v = 1; v <= n; v++) {
        if (dist[v] != 30000 && v != s) {
            printf("%d %d\n", v, dist[v]);
        }
    }
}