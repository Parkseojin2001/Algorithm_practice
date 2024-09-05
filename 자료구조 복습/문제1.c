# include <stdio.h>
# include <stdlib.h>

typedef struct Node{
    char e;
    struct Node *prev;
    struct Node *next;
}node;

int len(node *list);
void add(node *list, int r, char e);
void delete(node *list, int r);
void get(node *list, int r);
void print(node *list);
void free_node(node *list);

int main(){

    int N, rank;
    node *head, *tail;
    char order, elem, get_elem;

    scanf("%d", &N);

    head = (node*)malloc(sizeof(node));
    tail = (node*)malloc(sizeof(node));

    head->next = tail;
    head->prev = NULL;
    tail->prev = head;
    tail->next = NULL;

    for(int i = 0; i < N; i++){
        getchar();
        scanf("%c", &order);

        if(order == 'A'){
            scanf("%d %c", &rank, &elem);
            add(head, rank, elem);
        }
        else if(order == 'D'){
            scanf("%d", &rank);
            delete(head, rank);
        }
        else if(order == 'G'){
            scanf("%d", &rank);
            get(head, rank);
        }
        else if(order == 'P'){
            print(head);
        }
        else{
            printf("Error\n");
        }
    }
    free_node(head);
    free(head);
    free(tail);

    return 0;
}

int len(node *list){
    node *tmp = list;
    int count = 0;
    while(tmp->next != NULL){
        tmp = tmp->next;
        count++;
    }
    return count - 1;
}
void add(node *list, int r, char e){
    node *tmp = list, *newnode;
    int k = 0, Len;
    Len = len(list);
    if(Len + 1 < r){
        printf("invalid position\n");
        return;
    }
     while(k < r){
        tmp = tmp->next;
        k++;
        }
        newnode = (node*)malloc(sizeof(node));
        newnode->e = e;
        newnode->next = tmp;
        newnode->prev = tmp->prev;
        tmp->prev->next = newnode;
        tmp->prev = newnode;
    
}
void delete(node *list, int r){
    node *tmp = list;
    int k = 0, Len;
    Len = len(list);
    if(Len < r || r < 1){
        printf("invalid position\n");
        return;
    }
    while(k < r){
            tmp = tmp->next;
            k++;
        }
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        free(tmp);
}
void get(node *list, int r){
    char elem;
    node *tmp = list;
    int k = 0, Len;
    Len = len(list);
   if(r < 1 || Len < r){
    printf("invalid position\n");
    return;
   }
    while(k < r){
        tmp = tmp->next;
        k++;
   }
   elem = tmp->e;
   printf("%c\n", elem);
}
void print(node *list){
    node *tmp = list->next;
    while(tmp->next != NULL){
        printf("%c", tmp->e);
        tmp = tmp->next;
    }
    printf("\n");
}
void free_node(node *list){
    node *h = list, *p = list->next, *q;
    while(p->next != NULL){
        q = p;
        p->next->prev = h;
        h->next = p->next;
        p = p->next;
        free(q);
    }
}