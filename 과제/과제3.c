# include <stdio.h>
# include <stdlib.h>

int max = 23;
int q = 11;

int hash(int x);
int hash_prime(int x);
void insertItem(int number, int *hashTable);
void findElement(int number, int *hashTable);
void removeElement(int number, int *hashTable);
void showHashTable(int *hashTable);

int main(){
    int *hashTable, id, n, q, address;
    char order;
    hashTable = (int*)malloc(sizeof(int) * max);
    for(int i = 0; i < max; i++){
        hashTable[i] = -1;
    }

    while (1){
        scanf("%c", &order);
        if(order == 'f'){
            scanf("%d", &id);
            getchar();
            findElement(id, hashTable);
        }
        else if(order =='i'){
            scanf("%d", &id);
            getchar();
            insertItem(id, hashTable);
            showHashTable(hashTable);
        }
        else if(order == 'r'){
            scanf("%d", &id);
            getchar();
            removeElement(id, hashTable);
            showHashTable(hashTable);
        }
        else if(order =='q'){
            break;
        }
        else{
            printf("Invalid Order\n");
        }
    }

    free(hashTable);
    return 0;
}

int hash(int x){
    return x % max;
}
int hash_prime(int x){
    return q - (x % q);
}

void insertItem(int number, int *hashTable){
    int hash_key, hash_prime_key, bucket; 

    hash_key = hash(number);
    bucket = hash_key;
    hash_prime_key = hash_prime(number);

    if(hashTable[hash_key] == -1){
        hashTable[hash_key] = number;
    }
    else{
        while(1){
            if(hashTable[hash_key] == -1){
                hashTable[hash_key] = number;
                break;
            }
            else if(hash_key == bucket){
                printf("Full hashTable");
                break;
            }
            else{
                hash_key = (hash_key + hash_prime_key) % max;
            }
        } 
    }
}

void findElement(int number, int *hashTable){
    int hash_key, hash_prime_key, bucket; 

    hash_key = hash(number);
    hash_prime_key = hash_prime(number);

    if(hashTable[hash_key] == number){
        printf("%d %d\n", hash_key, number);
    }
    else{
        while(1){
            if(hashTable[hash_key] == number){
                printf("%d %d\n", hash_key, number);
                break;
            }
            else if(hashTable[hash_key] == -1){
                printf("NoSuchKey\n");
                break;
            }
            else{
                hash_key = (hash_key + hash_prime_key) % max;
            }
        } 
    }
}
void removeElement(int number, int *hashTable){
    int hash_key, hash_prime_key, bucket; 

    hash_key = hash(number);
    hash_prime_key = hash_prime(number);

    if(hashTable[hash_key] == number){
        hashTable[hash_key] = -1;
    }
    else{
        while(1){
            if(hashTable[hash_key] == number){
                printf("%d %d\n", hash_key, number);
                break;
            }
            else if(hashTable[hash_key] == -1){
                printf("NoSuchKey\n");
                break;
            }
            else{
                hash_key = (hash_key + hash_prime_key) % max;
            }
        } 
    }
}

void showHashTable(int *hashTable){
    for(int i = 0; i < max; i++){
        printf("%d ", i);
    }
    printf("\n");
    for(int i = 0; i < max; i++){
        if (hashTable[i] == -1){
            printf(". ");
        }
        else{
            printf("%d ", hashTable[i]);
        }
    }
    printf("\n");
}