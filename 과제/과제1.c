// 힙과 정렬 과제
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int findKthSmallest(int *L, int n, int k);
int *buildList(int n, int min, int max);
void writeList(int *L, int n);
void maxHeap(int *L, int n, int index);
void downHeap(int *L, int n, int index);

int main(){
    int *H, karray[4] = {1, 100, 99900, 99999}, output[3], elem;
    double time, start, stop;

    H = buildList(10, 1, 100); // 무순 리스트 생성
    writeList(H, 10);   // 무순 리스트 출력
    for(int k = 1; k < 4; k++){
        output[k - 1] = findKthSmallest(H, 10, k);  // k번째로 작은 수를 ouput 리스트에 저장
    }

    printf("%d %d %d", output[0], output[1], output[2]);  // output 리스트 원소 출력
    printf("\n");

    H = buildList(100000, 1, 1000000);   // 무순 리스트 생성

    for(int k = 0; k < 4; k++){
        start = clock();
        elem = findKthSmallest(H, 100000, karray[k]);   // k번째로 작은 수를 변수에 저장
        stop = clock();
        time = stop - start / CLOCKS_PER_SEC;   // 걸린 시간 측정
        printf("%d %lf\n", elem, time);  // 원소와 걸린 시간 출력
    }
    free(H);  // 동적할당 해제
    return 0;
}

int findKthSmallest(int *L, int n, int k){
    int *heap, result;

    heap = (int*)malloc(sizeof(int) * (k + 1));
    for (int i = 1; i <= k; i++) {
        heap[i] = L[i];
    }

    maxHeap(L, n, k); // 최대힙 생성

    // 나머지 원소들 처리
    for (int i = k + 1; i <= n; i++) {
        if (L[i] < heap[1]) {
            heap[1] = L[i];
            downHeap(heap, k, 1);
        }
    }

    result = heap[1];

    free(heap);
    return result;
}

// 리스트 생성 함수
int *buildList(int n, int min, int max){
    int *heap;
    heap = (int*)malloc(sizeof(int) * (n + 1));
    for(int i = 1; i < n + 1; i++){
        heap[i] = rand() % max + min; // 랜덤하게 숫자를 뽑아 리스트에 저장

    }
    return heap;
}
void writeList(int *L, int n){ // 리스트 원소 출력
    for(int i = 1; i < n + 1; i++){
        printf(" %d", L[i]);
    }
    printf("\n");
}
void maxHeap(int *L, int n, int index){ // 최대힙 생성

    if(index > n / 2){
        return;
    }

    maxHeap(L, n, index * 2); // 왼쪽 자식 최대힙 생성
    maxHeap(L, n, index * 2 + 1);  // 오른쪽 자식 최대힙 생성

    downHeap(L, n, index);  // 힙 재구성

}
void downHeap(int *L, int n, int index){
    int big, tmp;

    if(index > n / 2){ 
        return;
    }
    big = 2 * index;

    if(big < n && L[big] < L[index * 2 + 1]){ // 왼쪽 자식 노드보다 오른쪽 자식 노드가 더 큰 경우
        big = index * 2 + 1;
    }
    if(L[index] < L[big]){   // 부모보다 큰 자식노드 swap
        tmp = L[index];
        L[index] = L[big];
        L[big] = tmp;
    }
    downHeap(L, n, big); 
}
