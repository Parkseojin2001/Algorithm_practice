#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;

void insertItem(int key);
int removeMax();
void upHeap(int index);
void downHeap(int index);
void printHeap();

int main(){
    char order;
    int num, returnNum;
    while(1){
        scanf("%c", &order);
        if(order == 'i'){
            scanf("%d", &num);
            insertItem(num);
            printf("0\n");
        }
        else if(order == 'p'){
            printHeap();
        }
        else if(order == 'd'){
            returnNum = removeMax();
            printf("%d\n", returnNum);
        }
        else if(order == 'q'){
            break;
        }
        else{
            printf("Wrong order\n");
        }
        getchar();
    }
    return 0;
}

void insertItem(int key){
    n += 1;
    H[n] = key;
    upHeap(n);
}
int removeMax(){
    int key;
    key = H[1];
    H[1] = H[n];
    n -= 1;
    downHeap(1);
    return key;
}
void upHeap(int index){
    int parentIndex, tmp;
    if(index % 2 == 0){
        parentIndex = index / 2;
    }
    else{
        parentIndex = (index - 1) / 2;
    }
    if (parentIndex == 0){
        return;
    }
    if(H[parentIndex] < H[index]){
        tmp = H[index];
        H[index] = H[parentIndex];
        H[parentIndex] = tmp;
        upHeap(parentIndex);
    }
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
    for(int i = 1;i <= n; i++){
        printf(" %d", H[i]);
    }
    printf("\n");
}