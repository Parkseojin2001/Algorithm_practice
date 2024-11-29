#include <stdio.h>
#include <time.h>
#include <limits.h>

#define MAX 15 // or 30, 60

// 배열 A, H 선언
int A[MAX];
int H[MAX];


// 함수 선언
void initialize();
int airtelDC(int n, int s, int d);
int airtelDP(int n, int s, int d);
void printCPUTime(int n, int s, int d, int mincost, char *version, clock_t start_time);

int main() {
    int test_case[][2] = {{0, 4}, {2, 5}, {2, 4}}, n = 6, s, d, mincost_dc, mincost_dp;

    // 배열 A, H 초기화
    initialize();
    
    // Header을 출력
    printf("n s d mincost version cputime\n");
    
    // n = 6 인 경우
    
    
    for (int i = 0; i < 3; i++) {
        s = test_case[i][0];
        d = test_case[i][1];
        
        // 분할통치 버전 출력
        clock_t start_time = clock();
        mincost_dc = airtelDC(n, s, d);
        printCPUTime(n, s, d, mincost_dc, "DC", start_time);
        
        // 동적 프로그래밍 버전 출력
        start_time = clock();
        mincost_dp = airtelDP(n, s, d);
        printCPUTime(n, s, d, mincost_dp, "DP", start_time);
    }
    
    // n = Max인 경우
    n = MAX;
    s = 1;
    d = n - 2;
    
    // 분할통치 버전 출력
    clock_t start_time = clock();
    mincost_dc = airtelDC(n, s, d);
    printCPUTime(n, s, d, mincost_dc, "DC", start_time);
    
    // 동적 프로그래밍 버전 출력
    start_time = clock();
    mincost_dp = airtelDP(n, s, d);
    printCPUTime(n, s, d, mincost_dp, "DP", start_time);
    
    return 0;
}

void initialize() {
    // 배열 A 초기화
    A[0] = 0;
    A[1] = 1;
    for (int i = 2; i < MAX; i++) {
        A[i] = A[i-1] + (A[i-1] % 5) + 3;
    }
    
    // 배열 H 초기화
    H[0] = 0;
    H[1] = 5;
    for (int i = 2; i < MAX; i++) {
        H[i] = ((H[i-1] + i) % 9) + 1;
    }
}

// 분할통치 버전 함수
int airtelDC(int n, int s, int d) {
     int minCost = INT_MAX, cost1, cost2, intermediateCost ;

    if (s + 1 == d) {
        return A[1] * H[1];
    }
    
    for (int i = s + 1; i < d; i++) {
        cost1 = airtelDC(n, s, i);
        cost2 = airtelDC(n, i, d);
        
        // 비용 계산
        intermediateCost = A[i-s] * H[i-s] + cost1 + cost2;
        
        if (intermediateCost < minCost) {
            minCost = intermediateCost;
        }
    }
    return minCost;
}

// 동적 프로그래밍 버전 함수
int airtelDP(int n, int s, int d) {
    int dp[MAX][MAX], intermediateCost, tmp;
    
    // DP 테이블 초기화
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INT_MAX;
        }
        dp[i][i] = 0;
    }
    
    // 인접 정점
    for (int i = 0; i < n - 1; i++) {
        dp[i][i+1] = A[1] * H[1];
    }
    
    // DP 테이블 채우기
    for (int i = 3; i <= n; i++) {
        for (int j = 0; j < n - i + 1; j++) {
            tmp = j + i - 1;
            
            for (int k = j + 1; k < tmp; k++) {
                intermediateCost = A[k-j] * H[k-j] + dp[j][k] + dp[k][tmp];
                
                if (intermediateCost < dp[j][tmp]) {
                    dp[j][tmp] = intermediateCost;
                }
            }
        }
    }
    
    return dp[s][d];
}

// CPU 사간 계산 및 출력 함수
void printCPUTime(int n, int s, int d, int mincost, char* version, clock_t start_time) {
    clock_t end_time = clock();
    double cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
    
    printf("%d %d %d %d %s %f\n", n, s, d, mincost, version, cpu_time);
}