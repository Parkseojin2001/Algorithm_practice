#include <stdio.h>
# include <stdlib.h>

void select_sort(int *arr, int len);

int main(){
    int n, *arr;
    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    select_sort(arr, n);
    for(int i = 0; i < n; i++){
        printf(" %d", arr[i]);
    }
    printf("\n");
    free(arr);

    return 0;
}

void select_sort(int *arr, int len){
    int max_index, tmp;
    for(int i = 0; i < len; i++){
        max_index = 0;
        for(int j = 1; j < len - i; j++){
            if(arr[max_index] < arr[j]){
                max_index = j;
            }
        }
        tmp = arr[max_index];
        arr[max_index] = arr[len - 1 - i];
        arr[len - 1 - i] = tmp;
    }
}