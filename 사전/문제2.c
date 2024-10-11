# include <stdio.h>
# include <stdlib.h>

int binary_search(int *arr, int K, int N);

int main(){
    int n, k, *arr, result;
    scanf("%d %d", &n, &k);
    arr = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    result = binary_search(arr, k, n);
    printf("%d\n", result);
    free(arr);
    return 0;
}

int binary_search(int *arr, int K, int N){
    int start, end, mid, result;
    start = 0;
    end = N - 1;
    while(1){
        if(start > N){
            result = N;
            break;
        }
        if(end < start){
            result = end + 1;
            break;
        }
        mid = (end - start) / 2 + start;
        if(arr[mid] == K){
            result = mid;
            break;
        }
        else if(arr[mid] > K){
            end = mid - 1;
        }
        else if(arr[mid] < K){
            start = mid + 1;
        }
    }
    return result;
}