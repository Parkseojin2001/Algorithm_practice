# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

// 전역 변수 선언
int n = 100000;
int Limits[4] = {1, 100, 500, 1000};

// 함수 선언
int *createArray();
void quickSort(int *A, int n, int limit, char *mode);
void insertionSort(int *A, int n);
void rQuickSort(int *A, int l, int r, int limit, char *mode);
void inPlacePartition(int *A, int l, int r, int pivot_index, int *a, int *b);
int findPivot(int *A, int l, int r, char *mode);
int findIndexOfMedianOfThree(int *A, int a, int b, int c);
void printCPUTime(clock_t start, clock_t end);

int main(){
    int Limit, *A, *A_copy;
    char *Mode, *mode[4] = {"deterministic1", "deterministic3", "randomized1", "randomized3"};
    clock_t start, end;
    
    A = createArray(); // 무작위 배열 생성 함수 

    for(int i = 0; i < 4; i++){
        Limit = Limits[i];  // quick-sort limit size 설정
        printf("%d", Limit);
        for(int j = 0; j < 4; j++){
            Mode = mode[j]; // pivot 결정 방식 설정
            A_copy = (int *)malloc(sizeof(int) * n);
            for(int k = 0; k < n; k++){  
                A_copy[k] = A[k];
            }
            start = clock();     // 실행시간 측정
            quickSort(A_copy, n, Limit, Mode);
            end = clock();
            printCPUTime(start, end);
            free(A_copy);
        }
        printf("\n");
    }
    free(A);

    return 0;
}

int *createArray(){
    int *A;
    A = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        A[i] = rand () % n + 1;     // 1과 n 사이의 무작위 정수를 배열에 저장
    }
    return A;
}

void quickSort(int *A, int n, int limit, char *mode){
    rQuickSort(A, 0, n - 1, limit, mode);
    if(limit > 1){
        insertionSort(A, n);
    }
}

// 삽입 정렬
void insertionSort(int *A, int n){
    int key, j;
    for(int i = 1; i < n; i++){
        key = A[i];
        j = i - 1;
        while(j >= 0 && A[j] > key){
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}
// 재귀적 퀵정렬
void rQuickSort(int *A, int l, int r, int limit, char *mode){
    int pivot, a, b;
    if(r - l >= limit){
        pivot = findPivot(A, l, r, mode); // pivot 설졍
        inPlacePartition(A, l, r, pivot, &a, &b); // partition 나누기
        rQuickSort(A, l, a - 1, limit, mode);
        rQuickSort(A, b + 1, r, limit, mode);
    }
}
void inPlacePartition(int *A, int l, int r, int pivot_index, int *a, int *b){
    int i = l, j = l, k = r, pivot = A[pivot_index], tmp;
    while(j <= k){
        if(A[j] < pivot){
            tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
            i++;
            j++;
        }
        else if(A[j] > pivot){
            tmp = A[j];
            A[j] = A[k];
            A[k] = tmp;
            k--;
        }
        else{
            j++;
        }
    }
    *a = i; // LT index
    *b = k; // GT index
}

// Pivot 찾는 함수
int findPivot(int *A, int l, int r, char *mode){
    int a, b, c, result;

    if(strcmp(mode, "deterministic1") == 0){
        return r;
    }
    else if(strcmp(mode, "randomized1") == 0){
        return l + rand() % (r - l + 1);
    }
    else if(r - l == 1){
        return l;
    }
    else{
        if(strcmp(mode, "deterministic3") == 0){
            a = l;
            b = (l + r) / 2;
            c = r;

        }
        else{
            a = l + rand() % (r - l + 1);
            b = l + rand() % (r - l + 1);
            c = l + rand() % (r - l + 1);
        }
        result = findIndexOfMedianOfThree(A, a, b, c); // 중간값 반환
        return result;
    }
}


int findIndexOfMedianOfThree(int *A, int a, int b, int c){
    if ((A[a] < A[b] && A[b] < A[c]) || (A[c] < A[b] && A[b] < A[a])){
        return b;
    }
    else if ((A[b] < A[a] && A[a] < A[c]) || (A[c] < A[a] && A[a] < A[b])){
        return a;
    }
    else{
        return c;
    }
}

// 실행시간 출력함수
void printCPUTime(clock_t start, clock_t end){
    double cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    printf(" %.8f", cpu_time);
}