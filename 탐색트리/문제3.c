#include<stdio.h>
#include<stdlib.h>

typedef struct  node {
	int key;
	int height;
	struct node *lChild;
	struct node *rChild;
	struct node *parent;
}node;



node *root;

int isExternal(node *w);
int isInternal(node *w);
node *sibling(node *w);
node * inOrderSucc(node *w);
void expandExternal(node *w);
node *reduceExternal(node *z);
node *treeSearch(node *w, int k);
int updateHeight(node *w);
int isBalanced(node *w);
node *restructure(node *x, node *y, node *z);
void searchAndFixAfterInsertion(node *w);
void insertItem(node *w, int k);
void searchAndFixAfterRemoval(node *w);
int removeElement(node *w, int k);
void printTree(node *w);
void freeTree(node *w);





int main() {

	char order;
	int key, value;

	root = (node*)malloc(sizeof(node));
	root->parent = NULL;
	root->lChild = NULL;
	root->rChild = NULL;

	while (1) {
		scanf("%c", &order);
		if (order == 'i') {
			scanf("%d", &key);
			insertItem(root, key);
			getchar();
		}
		else if (order == 'd') {
			scanf("%d", &key);
			value = removeElement(root, key);
			if (value == key) {
				printf("%d\n", value);
			}
			else {
				printf("X\n");
			}
			getchar();
		}
		else if (order == 's') {
			scanf("%d", &key);
			if (treeSearch(root, key)->key != key) {
				printf("X\n");
			}
			else {
				printf("%d\n", treeSearch(root, key)->key);
			}
			getchar();
		}
		else if (order == 'p') {
			printTree(root);
			printf("\n");
		}
		else if (order == 'q') {
			break;
		}
	}
	freeTree(root);
    return 0;
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
void expandExternal(node *w) {
	node *leftNode = (node*)malloc(sizeof(node));
	node *rightNode = (node*)malloc(sizeof(node));

	leftNode->lChild = NULL;
	leftNode->rChild = NULL;
	leftNode->height = 0;
	leftNode->parent = w;

	rightNode->lChild = NULL;
	rightNode->rChild = NULL;
	rightNode->height = 0;
	rightNode->parent = w;

	w->lChild = leftNode;
	w->rChild = rightNode;
	w->height = 1;

	return;
}
node *reduceExternal(node *z) {
	node *p, *zs, *x;
	p = z->parent;
	zs = sibling(z);
	if (p->parent == NULL) {
		root = zs;
		zs->parent = NULL;
	}
	else {
		x = p->parent;
		zs->parent = x;
		if (p == x->lChild)
			x->lChild = zs;
		else if (p == x->rChild)
			x->rChild = zs;
	}

	free(z);
	free(p);

	return zs;

}
node* treeSearch(node *w, int k) {

	if (isExternal(w))
		return w;
	if (w->key == k)
		return w;
	else if (w->key > k)
		return treeSearch(w->lChild, k);
	else
		return treeSearch(w->rChild, k);
}

int updateHeight(node *w) {
	int height;
	if (w->lChild->height > w->rChild->height) {
		height = w->lChild->height + 1;
	}
	else {
		height = w->rChild->height + 1;
	}
	if (height != w->height) {
		w->height = height;
		return 1;
	}
	else {
		return 0;
	}
}
int isBalanced(node *w) {
	if ((-1 <= (w->lChild->height - w->rChild->height)) && ((w->lChild->height - w->rChild->height) <= 1)) {
		return 1;
	}
	else {
		return 0;
	}
}
node* restructure(node *x, node *y, node *z) {

	node *a, *b, *c;
	node *p0, *p1, *p2, *p3;
	if ((z->key < y->key) && (y->key < x->key)) {
		a = z;
		b = y;
		c = x;
		p0 = a->lChild;
		p1 = b->lChild;
		p2 = c->lChild;
		p3 = c->rChild;
	}
	else if ((x->key < y->key) && (y->key < z->key)) {
		a = x;
		b = y;
		c = z;
		p0 = a->lChild;
		p1 = a->rChild;
		p2 = b->rChild;
		p3 = c->rChild;
	}
	else if ((z->key < x->key) && (x->key < y->key)) {
		a = z;
		b = x;
		c = y;
		p0 = a->lChild;
		p1 = b->lChild;
		p2 = b->rChild;
		p3 = c->rChild;
	}
	else {
		a = y;
		b = x;
		c = z;
		p0 = a->lChild;
		p1 = b->lChild;
		p2 = b->rChild;
		p3 = c->rChild;
	}

	if (z->parent == NULL) {
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z) {
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else if (z->parent->rChild == z) {
		z->parent->rChild = b;
		b->parent = z->parent;
	}

	a->lChild = p0;
	p0->parent = a;
	a->rChild = p1;
	p1->parent = a;

	updateHeight(a);

	c->lChild = p2;
	p2->parent = c;
	c->rChild = p3;
	p3->parent = c;
	updateHeight(c);
	
    b->lChild = a;
	a->parent = b;
	b->rChild = c;
	c->parent = b;

	updateHeight(b);

	return b;

}
void searchAndFixAfterInsertion(node *w) {

	node *x, *y, *z;
	w->lChild->height = 0;
	w->rChild->height = 0;
	w->height = 1;
	if (w->parent == NULL) {
		return NULL;
	}
	z = w->parent;
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL) {
			return;
		}
		z = z->parent;
	}
	if (isBalanced(z)) {
		return;
	}

	if (z->lChild->height > z->rChild->height) {
		y = z->lChild;
	}
	else {
		y = z->rChild;
	}
	if (y->lChild->height > y->rChild->height) {
		x = y->lChild;
	}
	else {
		x = y->rChild;
	}
	restructure(x, y, z);
	return;
}
void insertItem(node *w, int k) {

	node *p = treeSearch(w, k);
	if (isInternal(p)) {
		return;
	}
	else {
		p->key = k;
		expandExternal(p);
		searchAndFixAfterInsertion(p);
	}
}

void searchAndFixAfterRemoval(node *w) {
	node *x, *y, *z, *T;
	if (w == NULL) {
		return;
	}
	z = w;
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL) {
			return;
		}
		z = z->parent;
	}
	if (isBalanced(z)) {
		return;
	}
	if (z->lChild->height > z->rChild->height) {
		y = z->lChild;
	}
	else {
		y = z->rChild;
	}
	if (y->lChild->height > y->rChild->height) {
		x = y->lChild;
	}

	else if (y->lChild->height < y->rChild->height) {
		x = y->rChild;
	}
	else {
		if (z->lChild == y) {
			x = y->lChild;
		}
		else if (z->rChild == y) {
			x = y->rChild;
		}
	}
	T = restructure(x, y, z);
	searchAndFixAfterRemoval(T->parent);

}
 int removeElement(node *w, int k) {

	node *p = treeSearch(w, k);
	node *x, *zs, *y;
	int e;
	if (isExternal(p)) {
		return -1;
	}
	e = p->key;
	x = p->lChild;
	if (!isExternal(x)) {
		x = p->rChild;
	}
	if (isExternal(x)) {
		zs = reduceExternal(x);
	}
	else {
		y = inOrderSucc(p);
		x = y->lChild;
		p->key = y->key;
		zs = reduceExternal(x);
	}
	searchAndFixAfterRemoval(zs->parent);
	return e;
}

void printTree(node *w) {
	if (isExternal(w)) {
		return;
	}
	else {
		printf(" %d", w->key);
		printTree(w->lChild);
		printTree(w->rChild);
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