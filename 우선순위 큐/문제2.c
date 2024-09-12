#include <stdio.h>
# include <stdlib.h>

void insert_sort(int *arr, int len);

int main(){
    int n, *arr;
    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    insert_sort(arr, n);
    for(int i = 0; i < n; i++){
        printf(" %d", arr[i]);
    }
    printf("\n");
    free(arr);

    return 0;
}

void insert_sort(int *arr, int len){
    int index, tmp;
    for(int i = 1; i < len; i++){
        index = i;
        tmp = arr[i];
        for(int j = 0; j < i; j++){
            if(arr[j] > arr[i]){
                index = j;
                break;
            }
        }
        for(int j = i; j > index; j--){
            arr[j] = arr[j - 1];
        }
        arr[index] = tmp;
    }
}