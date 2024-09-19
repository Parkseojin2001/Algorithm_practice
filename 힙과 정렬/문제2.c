#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;

void rBuildHeap(int index);
void downHeap(int index);
void printHeap();

int main(){
    int keyNum, key;
    scanf("%d", &keyNum);
    for(n = 1;n <= keyNum; n++){
        scanf("%d", &key);
        H[n] = key;
    }
    rBuildHeap(1);
    printHeap();
    return 0;
}


void rBuildHeap(int index){
    if(index > n){
        return;
    }
    rBuildHeap(2 * index);
    rBuildHeap(2 * index + 1);
    downHeap(index);
}
void downHeap(int index){
    int leftChild, rightChild, childIdx, tmp;
    leftChild = index * 2;
    rightChild = index * 2 + 1;
    if(H[leftChild] > H[rightChild]){
        childIdx = leftChild;
    }
    else{
        childIdx = rightChild;
    }
    if(childIdx > n){
        return;
    }
    if(H[index] < H[childIdx]){
        tmp = H[index];
        H[index] = H[childIdx];
        H[childIdx] = tmp;
        downHeap(childIdx);
    }
}
void printHeap(){
    for(int i = 1;i < n; i++){
        printf(" %d", H[i]);
    }
    printf("\n");
}