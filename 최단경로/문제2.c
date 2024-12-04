#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int src, dest, weight;
};
struct Edge edges[1001];
int dist[101];

void bellmanFordShortestPath(int n, int m, int s);
void printResult(int n, int s);

int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    bellmanFordShortestPath(n ,m ,s); 
    printResult(n, s);
    return 0;
}

void bellmanFordShortestPath(int n, int m, int s) {
    int u, v, weight;

    for (int i = 1; i <= n; i++) {
        dist[i] = (i == s) ? 0 : 30000;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < m; j++) {
            u = edges[j].src;
            v = edges[j].dest;
            weight = edges[j].weight;

            if (dist[u] != 30000 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
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