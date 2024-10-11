# include <stdio.h>
# include <stdlib.h>

int search(int *arr, int K, int start, int end);

int main(){
    int n, k, *arr, result;
    scanf("%d %d", &n, &k);
    arr = (int *)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    result = search(arr, k, 0, n - 1);
    printf("%d\n", result);

    free(arr);
    return 0;
}

int search(int *arr, int K, int start, int end){
    int mid = (end - start) / 2 + start;

    if(start > end){
        return end;
    }
    if (arr[mid] == K){
        return mid;
    }
    else if(arr[mid] > K){
        return search(arr, K, start, mid - 1);
    }
    else {
        return search(arr, K, mid + 1, end);
    }
}