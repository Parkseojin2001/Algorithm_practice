#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node *next;
    int num;
}node;

node* getnode(int num);
node * mergeSort(node *L, int n);
node* merge(node *L1, node *L2);
node* partition(node *L, int k);
void printList(node *L, int n);
void freeList(node *L, int n);

int main(){
    int n, m;
    node *Head, *p, *result;
    Head = (node*)malloc(sizeof(node));
    Head->next = NULL;

    scanf("%d", &n);
    p = Head;
    
    for(int i = 0; i < n; i++){
        scanf("%d", &m);
        p->next = getnode(m);
        p = p->next;
    }

    result = mergeSort(Head->next, n);

    printList(result, n);
    
    freeList(result, n);
    free(result);

    return 0;
}

node* getnode(int num){
    node *newnode;
    newnode = (node*)malloc(sizeof(node));
    newnode->num = num;
    newnode->next = NULL;
    return newnode;
}

node * mergeSort(node *L, int n){
   if(n <= 1){
    return L;
   }

   node *L2 = partition(L, n / 2);
   node *L1 = mergeSort(L, n / 2);
   L2 = mergeSort(L2, n - n/2);

   return merge(L1, L2);
}
node* merge(node *L1, node *L2){
    node *p = NULL;

    if(L1 == NULL){
        return L2;
    }
    else if(L2 == NULL){
        return L1;
    }
    if(L1->num < L2->num){
        p = L1;
        p->next = merge(L1->next, L2);
    }
    else{
        p = L2;
        p->next = merge(L1, L2->next);
    }
    return p;
}

node* partition(node *L, int k){
    node *p = L;
    for(int i = 1; i < k && p != NULL; i++){
        p = p -> next;
    }
    if(p == NULL){
        return NULL;
    }

    node *L2 = p -> next;
    p -> next = NULL;

    return L2;
}
void printList(node *L, int n){
    node *tmp = L;
    for(int i = 0; i < n; i++){
        printf(" %d", tmp->num);
        tmp = tmp->next;
    }
    printf("\n");
}
void freeList(node *L, int n){
    node *tmp = L -> next, *ptmp;
    while(tmp != NULL){
        ptmp = tmp->next;
        free(tmp);
        tmp = ptmp;
    }
}