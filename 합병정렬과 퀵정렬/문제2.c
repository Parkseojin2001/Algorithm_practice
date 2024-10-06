#include <stdio.h>
#include <stdlib.h>

void printArr(int *ar, int n);
void inPlaceQuickSort(int *ar, int l, int r);
int findPivot(int l, int r);
void inPlacePartition(int *ar, int l, int r, int p, int *a, int *b);

int main(){
    int n, *arr;

    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    inPlaceQuickSort(arr, 0, n - 1);

    printArr(arr, n);
    free(arr);
    return 0;

}

void inPlaceQuickSort(int *ar, int l, int r){
    int pivot, a, b;
    if(l >= r){
        return;
    }
    pivot = findPivot(l, r);

    inPlacePartition(ar, l, r, pivot, &a, &b);

    inPlaceQuickSort(ar, l, a-1);
    inPlaceQuickSort(ar, b+ 1, r);

}

int findPivot(int l, int r){
    return l + rand() % (r - l + 1);
}

void inPlacePartition(int *ar, int l, int r, int p, int *a, int *b){
    int pivot, tmp, i, j, k;

    pivot = ar[p];
    tmp = ar[p];
    ar[p] = ar[r];
    ar[r] = tmp;
    i = l;
    j = l;
    k = r - 1;

    while(j <= k){
        if(ar[j] < pivot){
            tmp = ar[i];
            ar[i] = ar[j];
            ar[j] = tmp;
            i++;
            j++;
        }
        else if(ar[j] > pivot){
            tmp = ar[j];
            ar[j] = ar[k];
            ar[k] = tmp;
            k--;
        }
        else{
            j++;
        }
    }

    *a = i;
    *b = k;

}
void printArr(int *ar, int n){
    for(int i = 0; i < n; i++){
        printf(" %d", ar[i]);
    }
    printf("\n");
}