#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    struct node *next;
    int key;
}node;

void printKey(node *ar[], int M);
void insertKey(node *ar[], int key, int num);
int searchKey(node *ar[], int key, int num);
int deleteKey(node *ar[], int key, int num);
int hash(int key, int m);

int main(){
    int M, key, num, rank;
    node **ar;
    char order;

    scanf("%d", &M);
    ar = (node**)malloc(sizeof(node*) * M);
    for (int i = 0; i < M; i++) {
        ar[i] = (node *)malloc(sizeof(node));
        ar[i]->next = NULL;
    }
    while (1){
        getchar();
        scanf("%c", &order);
        if (order == 'i'){
            scanf("%d", &key);
            num = hash(key, M);
            insertKey(ar, key, num);
        }
        else if (order == 's'){
            scanf("%d", &key);
            num = hash(key, M);
            rank = searchKey(ar, key, num);
            printf("%d\n", rank);
        }
        else if (order == 'd'){
            scanf("%d", &key);
            num = hash(key, M);
            rank = deleteKey(ar, key, num);
            printf("%d\n", rank);
        }
        else if (order == 'p'){
            printKey(ar, M);
            printf("\n");
        }
        else{
            break;
        }
    }

    for (int i = 0; i < M; i++) {
        node *tmp = ar[i];
        while (tmp != NULL) {
            node *next = tmp->next;
            free(tmp);
            tmp = next;
        }
    }
    free(ar);

    return 0;
}

int hash(int key, int m){
    return key % m;
}
void insertKey(node *ar[], int key, int num){
    node *newnode, *tmp;
    newnode = (node *)malloc(sizeof(node));
    newnode->key = key;
    newnode->next =NULL;
    if (ar[num]->next == NULL){
        ar[num]->next = newnode;
    }
    else{
        newnode->next = ar[num]->next;
        ar[num]->next = newnode;
    }
}
int searchKey(node *ar[], int key, int num){
    node *tmp = ar[num];
    int count = 0, flag = 0;
    while (tmp->next != NULL){
        count ++;
        tmp = tmp->next;
        if(tmp->key == key){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        return count;
    }
    else{
        return 0;
    }
}
int deleteKey(node *ar[], int key, int num){
    node *tmp = ar[num]->next, *pt = ar[num];
    int count = 0, flag = 0;
    while(tmp!= NULL){
        count++;
        if(tmp->key == key){
            flag = 1;
            if(tmp->next == NULL){
                pt->next = NULL;
            }
            else{
                pt->next = tmp->next;
            }
            free(tmp);
            break;
        }
        tmp = tmp->next;
        pt = pt->next;
    }
    if(flag == 1){
        return count;
    }
    else{
        return 0;
    }
}
void printKey(node *ar[], int M){
    node *tmp;
    int flag = 0;
    for(int i = 0; i < M; i++){
        if(ar[i]->next!=NULL){
            flag = 1;
            tmp = ar[i]->next;
            while (tmp!= NULL){
                printf(" %d", tmp->key);
                tmp = tmp->next;
            }
        }
    }
    if(flag == 0){
        printf("0");
    }
}