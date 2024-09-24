#include <stdio.h>
#include <stdlib.h>

int H[100];
int s;
int n;

void inPlaceHeapSort();
void printArray();
void downHeap(int index);
void rBuildHeap(int index);

int main(){
    int count;
    scanf("%d", &n);
    s = n;
    for(int i = 1; i < n + 1; i++){
        scanf("%d", &H[i]);
    }
    rBuildHeap(1);
    inPlaceHeapSort();
    printArray();
    return 0;
}
void inPlaceHeapSort(){
    int tmp;
    for(int i = n; i > 1; i--){
        tmp = H[1];
        H[1] = H[i];
        H[i] = tmp;
        n --;
        downHeap(1);

    }
}
void printArray(){
    for(int i = 1; i < s + 1; i++){
        printf(" %d", H[i]);
    }
    printf("\n");
}
void downHeap(int index){
    int tmp, big;
    if(n < 2 * index && n < 2 * index + 1){
        return;
    }

    big = 2 * index;
    if(n >= 2 * index + 1){
        if(H[big] < H[2 * index + 1]){
            big = 2 * index + 1;
        }
    }
    if(H[big] <= H[index]){
        return;
    }
    tmp = H[index];
    H[index] = H[big];
    H[big] = tmp;
    downHeap(big);
}
void rBuildHeap(int index){
    if(index > n){
        return;
    }
    rBuildHeap(2 * index);
    rBuildHeap(2 * index + 1);
    downHeap(index);

    return;
}