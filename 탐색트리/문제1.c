#include<stdio.h>
#include<stdlib.h>

typedef struct node{

	int key;
	struct node *parent;
	struct node *lChild;
	struct node *rChild;
}node;                   

void insertItem(node *W, int k);
int isExternal(node *w);
int isInternal(node *w);
node *sibling(node *w);
node *inOrderSucc(node *w);
void reduceExternal(node *R, node *z);
node *treeSearch(node *w, int k);
int removeElement(node *w, int k);
void printNode(node *w);
void freeTree(node *w);

int main() {

	char order;
	int key, value;

	node *w = (node*)malloc(sizeof(node));

	w->parent = NULL;

	w->lChild = NULL;

	w->rChild = NULL;

	while (1) {

		scanf("%c", &order);

		if (order == 'i') {

			scanf("%d", &key);

			insertItem(w, key);

			getchar();

		}

		else if (order == 'd') {

			scanf("%d", &key);

			value = removeElement(w, key);

			if (value == -1) {

				printf("X\n");

			}

			else {

				printf("%d\n", value);

			}

			getchar();

		}

		else if (order == 's') {

			scanf("%d", &key);

			if (treeSearch(w, key)->key != key) {

				printf("X\n");

			}

			else {

				printf("%d\n", treeSearch(w, key)->key);

			}

			getchar();

		}

		else if (order == 'p') {

			printNode(w);

			printf("\n");

		}

		else if (order == 'q') {

			break;

		}

	}

	freeTree(w);
}

void insertItem(node *w, int k) {

    node *p = treeSearch(w, k);
	node *lChild_node = (node*)malloc(sizeof(node));
	node *rightChild_node = (node*)malloc(sizeof(node));

	p->key = k;
	p->lChild = lChild_node;
	p->rChild = rightChild_node;
	lChild_node->parent = p;
	rightChild_node->parent = p;
	lChild_node->lChild = NULL;
	lChild_node->rChild = NULL;
	rightChild_node->lChild = NULL;
	rightChild_node->rChild = NULL;
}

int isExternal(node *w) {
	if ((w->lChild == NULL) && (w->rChild == NULL)) {
		return 1;
	}

	else {
		return 0;
	}
}

int isInternal(node *w) {
	if ((w->lChild != NULL) && (w->rChild != NULL)) {
		return 1;
	}
	else {
		return 0;
	}
}

node* sibling(node *w) {

	if (w->parent == NULL) {
		return;
	}
	if (w->parent->lChild == w) {
		return w->parent->rChild;
	}
	else {
		return w->parent->lChild;
	}
}

node* inOrderSucc(node *w) {

	w = w->rChild;
	if (isExternal(w)) {
		return;
	}
	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	return w;
}

void reduceExternal(node *R, node *z) {
	node *w, *zs, *g;
	w = z->parent;
	zs = sibling(z);
	if (w->parent == NULL) {
		R->lChild->parent = zs;
		R->rChild->parent = zs;
        R->lChild = zs->lChild;
		R->rChild = zs->rChild;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lChild) {
			g->lChild = zs;
		}
		else if (w == g->rChild) {
			g->rChild = zs;
		}
	}
	free(z);
	free(w);
	return zs;
}
node* treeSearch(node *w, int k) {
	if (isExternal(w)) {
		return w;
	}
	if (w->key == k) {
		return w;
	}
	else if (w->key > k) {
		return treeSearch(w->lChild, k);
	}
	else {
		return treeSearch(w->rChild, k);
	}
}
int removeElement(node *w, int k) {

	int elem;
    node *x, *y;
	node *p = treeSearch(w, k);
	
	if (isExternal(p))
		return -1;

	elem = p->key;
	x = p->lChild;

	if (!isExternal(x))
		x = p->rChild;
	if (isExternal(x))
		reduceExternal(p, x);
	else {
		y = inOrderSucc(p);
		x = y->lChild;
		p->key = y->key;
		reduceExternal(p,x);
	}
	return elem;
}

void printNode(node *w) {

	if (isExternal(w)) {
		return;
	}

	else {
		printf(" %d", w->key);
		printNode(w->lChild);
		printNode(w->rChild);
	}
}
void freeTree(node *w) {

	if (isExternal(w)) {
		return;
	}
	else {
		freeTree(w->lChild);
		freeTree(w->rChild);
		free(w);
	}
}