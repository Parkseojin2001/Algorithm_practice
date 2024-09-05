#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    struct Node *left;
    struct Node *right;
    int data; 
}node;

void create_tree(node *ROOT, int parent, int left, int right);
void get_leftNode(node *ROOT, int num);
void get_rightNode(node *ROOT, int num);
void print_node(node *ROOT, char *order);
void free_tree(node *ROOT);

int main(){
    int n, s, right_num, left_num, parent_num;
    char str[101];

    node *root;
    root = (node *)malloc(sizeof(node));
    root->right = NULL;
    root->left = NULL;

    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d %d", &parent_num, &left_num, &right_num);
        if(i == 0){
            root->data = parent_num;
        }
        create_tree(root, parent_num, left_num, right_num);
    }
    scanf("%d", &s);
    for(int i = 0; i < s; i++){
        getchar();
        scanf("%s", str);
        print_node(root, str);
    }
    free_tree(root);

    return 0;
}

void create_tree(node *ROOT, int parent, int left, int right){
    node *tmp = ROOT;
    if(ROOT == NULL){
        return;
    }
    else if(ROOT->data == parent){
        get_leftNode(ROOT, left);
        get_rightNode(ROOT, right);
    }
    else{
        create_tree(ROOT->left, parent, left, right);
        create_tree(ROOT->right, parent, left, right);
    }
}

void get_leftNode(node *ROOT, int num){
    node *newnode;
    if(num == 0){
        return;
    }
    newnode = (node*)malloc(sizeof(node));
    newnode->data = num;
    newnode->left = NULL;
    newnode->right = NULL;
    ROOT->left = newnode;
}
void get_rightNode(node *ROOT, int num){
    node *newnode;
    if(num == 0){
        return;
    }
    newnode = (node*)malloc(sizeof(node));
    newnode->data = num;
    newnode->left = NULL;
    newnode->right = NULL;
    ROOT->right = newnode;
}

void print_node(node *ROOT, char *order){
    int len = strlen(order);
    node *tmp = ROOT;
    printf(" %d", tmp->data);
    for(int i = 0; i < len; i++){
        if(order[i] == 'R'){
            tmp = tmp->right;
        }
        else{
            tmp = tmp->left;
        }
        printf(" %d", tmp->data);
    }
    printf("\n");
}

void free_tree(node *ROOT){
    if(ROOT == NULL){
        return;
    }
    else{
        free_tree(ROOT->left);
        free_tree(ROOT->right);
        free(ROOT);
    }     
}