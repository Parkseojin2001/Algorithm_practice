# include <stdio.h>
# include<stdlib.h>

int hash(int x, int M);
int hash_prime(int x, int q);
int insertID(int number, int *hashTable, int M, int q);
void searchID(int number, int *hashTable, int M, int q);
void printID(int *hashTable, int M);

int main(){
    int M, *hashTable, id, n, q, address;
    char order;
    scanf("%d %d %d", &M, &n, &q);
    hashTable = (int*)malloc(sizeof(int) * M);
    for(int i = 0; i < M; i++){
        hashTable[i] = 0;
    }

    while (1){
        getchar();
        scanf("%c", &order);
        if(order =='i'){
            scanf("%d", &id);
            address = insertID(id, hashTable, M, q);
            printf("%d\n", address);
        }
        else if(order == 's'){
            scanf("%d", &id);
            searchID(id, hashTable, M, q);
        }
        else if(order =='e'){
            printID(hashTable, M);
            break;
        }
        else if(order == 'p'){
            printID(hashTable, M);
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
int hash_prime(int x, int q){
    return q - (x % q);
}
int insertID(int number, int *hashTable, int M, int q){
    int hash_key, hash_prime_key, bucket; 

    hash_key = hash(number, M);
    hash_prime_key = hash_prime(number, q);

    if(hashTable[hash_key] == 0){
        hashTable[hash_key] = number;
    }
    else{
        while(1){
            if(hashTable[hash_key] == 0){
                hashTable[hash_key] = number;
                break;
            }
            else{
                hash_key = (hash_key + hash_prime_key) % M;
                printf("C");
            }
        } 
    }
    return hash_key;
}
void searchID(int number, int *hashTable, int M, int q){
    int hash_key, hash_prime_key, bucket; 

    hash_key = hash(number, M);
    hash_prime_key = hash_prime(number, q);

    if(hashTable[hash_key] == number){
        printf("%d %d\n", hash_key, number);
    }
    else{
        while(1){
            if(hashTable[hash_key] == number){
                printf("%d %d\n", hash_key, number);
                break;
            }
            else if(hashTable[hash_key] == 0){
                printf("-1\n");
                break;
            }
            else{
                hash_key = (hash_key + hash_prime_key) % M;
            }
        } 
    }
}
void printID(int *hashTable, int M){
    for(int i = 0; i < M; i++){
        printf(" %d", hashTable[i]);
    }
    printf("\n");
}