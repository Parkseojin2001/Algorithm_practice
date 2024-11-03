# include <stdio.h>
# include<stdlib.h>

int hash(int x, int M);
int insertID(int number, int *hashTable, int M);
void searchID(int number, int *hashTable, int M);

int main(){
    int M, n, id, address, *hashTable;;
    char order;

    scanf("%d %d", &M, &n);
    hashTable = (int *)malloc(sizeof(int) * M);
    for(int i = 0; i < M; i++){
        hashTable[i] = 0;
    }

    while (1){
        getchar();
        scanf("%c", &order);
        if(order =='i'){
            scanf("%d", &id);
            address = insertID(id, hashTable, M);
            printf("%d\n", address);
        }
        else if(order == 's'){
            scanf("%d", &id);
            searchID(id, hashTable, M);
        }
        else if(order =='e'){
            break;
        }
        else{
            printf("Invalid Order\n");
        }
    }

    free(hashTable);
    return 0;

}

int hash(int x, int M){
    return x % M;
}
int insertID(int number, int *hashTable, int M){
    int hash_key, result = -1; 
    hash_key = hash(number, M);
    for(int i = hash_key; i < hash_key + M ; i++){
        if(hashTable[i % M] == 0){
            hashTable[i % M] = number;
            result = i % M;
            break;
        }
        else{
            printf("C");
        }
    }
    return result;
}
void searchID(int number, int *hashTable, int M){
    int hash_key, result = -1; 
    hash_key = hash(number, M);
    for(int i = hash_key; i < hash_key + M; i++){
        if(number == hashTable[i % M]){
            result = i % M;
        }
    }
    if(result != -1){
        printf("%d %d\n", result, number);
    }
    else{
        printf("%d\n", result);
    }
}  