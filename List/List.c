#include <stdio.h>
#include <stdlib.h>

typedef void* univpoint_t;
typedef unsigned int uint_t;

typedef struct _NodeList {
	univpoint_t data;
	struct _NodeList* next;
} NodeList, *PNodeList;

typedef struct _List {
	uint_t length;
	PNodeList head;
	PNodeList tail;
} List, *PList;

typedef int (*prict_t)(PNodeList);

PList createList() {
	PList lst = malloc(sizeof(List));
	lst->head = NULL;
	lst->tail = NULL;
	lst->length = 0;
	return lst;
}

PNodeList getNodeByIndexFromBegin(PList lst, uint_t i) {
	if (lst->head == NULL || i > lst->length) {
		exit(-1);
	}
	int j;
	PNodeList node = lst->head;
	for (j = 0; j < i; ++j) {
		node = node->next;
	}
	return node;
}

PNodeList getNodeByIndexFromBeginR(PList lst, PNodeList node, uint_t i) {
	if (lst->head == NULL || i > lst->length) {
		exit(-1);
	}
	else if (i == 0) {
		return node;
	}
	else {
		return getNodeByIndexFromBeginR(lst, node->next, i - 1);
	}
}

PNodeList getNodeByIndexFromEnd(PList lst, uint_t i) {
	if (lst->head == NULL || i > lst->length) {
		exit(-1);
	}
	return getNodeByIndexFromBegin(lst, lst->length - i);
}

uint_t getLength(PList lst) {
	return lst->length;
}

void addNodeListFirst(PList lst, univpoint_t data) {
	PNodeList node = malloc(sizeof(NodeList));
	node->data = data;
	if (lst->head == NULL) {
		lst->head = node;
		lst->tail = node;
		return;
	}
	node->next = lst->head;
	lst->head = node;
	lst->length++;
}

void addNodeListLast(PList lst, univpoint_t data) {
	PNodeList node = malloc(sizeof(NodeList));
	node->data = data;
	if (lst->head == NULL) {
		lst->head = node;
		lst->tail = node;
		return;
	}
	lst->tail->next = node;
	lst->tail = node;
	lst->length++;
}

void addNodeListByIndex(PList lst, univpoint_t data, uint_t i) {
	if (lst->head == NULL) {
		return;
	}
	else if (i == 0) {
		addNodeListFirst(lst, data);
	}
	else if (i > lst->length) {
		addNodeListLast(lst, data);
	}
	else {
		PNodeList node = malloc(sizeof(NodeList));
		node->data = data;
		PNodeList innode = getNodeByIndexFromBegin(lst, i - 1);
		node->next = innode->next;
		innode->next = node;
		lst->length++;
	}
}

void removeNodeListFirst(PList lst) {
	if (lst->head == NULL) {
		return;
	}
	PNodeList node = lst->head;
	lst->head = lst->head->next;
	free(node);
	lst->length--;
}

void removeNodeListLast(PList lst) {
	if (lst->head == NULL) {
		return;
	}
	PNodeList node = getNodeByIndexFromEnd(lst, 1);
	lst->tail = node;
	lst->tail->next = NULL;
	node = node->next;
	free(node);
	lst->length--;
}

void removeNodeListByIndex(PList lst, uint_t i) {
	if (lst->head == NULL) {
		return;
	}
	if (i == 0) {
		removeNodeListFirst(lst);
	}
	else if (i > lst->length) {
		removeNodeListLast(lst);
	}
	else {
		PNodeList node = getNodeByIndexFromBegin(lst, i - 1);
		PNodeList nodetmp = node->next;
		node->next = node->next->next;
		free(nodetmp);
		lst->length--;
	}
}

void removeNodeListByIndexR(PList lst, uint_t i) {
	if (lst->head == NULL) {
		return;
	}
	if (i == 0) {
		removeNodeListFirst(lst);
	}
	else if (i > lst->length) {
		removeNodeListLast(lst);
	}
	else {
		PNodeList node = getNodeByIndexFromBeginR(lst, lst->head, i - 1);
		PNodeList nodetmp = node->next;
		node->next = node->next->next;
		free(nodetmp);
		lst->length--;
	}
}

void removeAllNodes(PList lst) {
	if (lst->head == NULL) {
		return;
	}
	PNodeList node = lst->head;
	PNodeList nodetmp;
	while(node) {
		nodetmp = node;
		node = node->next;
		free(nodetmp);
	}
	lst->head = NULL;
	lst->tail = NULL;
	lst->length = 0;
}

PList formNewListByPredicate(PList lst, prict_t f) {
	if (lst->head == NULL) {
		exit(-1);
	}
	PList newlst = createList();
	PNodeList node = lst->head;
	while (node) {
		if (f(node)) {
			addNodeListLast(newlst, node->data);
		}
		node = node->next;
	}
	return newlst;
}

int predicate1(PNodeList a) {
	if (a->data < (univpoint_t)10) {
		return 1;
	}
	else {
		return 0;
	}
}

int predicate2(PNodeList a) {
	if ((int)a->data % 2 != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void show(PList lst, char type) {
	if (lst->head == NULL) {
		return;
	}
	PNodeList node = lst->head;
	while(node) {
		if (type == 's') {
			printf("%s\t", node->data);
		}
		else if (type == 'd') {
			printf("%d\t", node->data);
		}
		else if (type == 'f') {
			printf("%f\t", node->data);
		}
		else if (type == 'c') {
			printf("%c\t", node->data);
		}
		node = node->next;
	}
	printf("\n");
}

int main() {
    PList lst_s = createList();
    PList lst_d = createList();
    PList lst_c = createList();
    PList lst_new_by_pred;
    addNodeListFirst(lst_s, (univpoint_t)"21323");
    addNodeListFirst(lst_s, (univpoint_t)"asdasd");
    addNodeListLast(lst_s, (univpoint_t)"sadasba");
    addNodeListFirst(lst_s, (univpoint_t)"xvxcv");
    addNodeListByIndex(lst_s, (univpoint_t)"wqeqwe", 2);
    removeNodeListFirst(lst_s);
    show(lst_s, 's');
    printf("%s\n\n", (char*)getNodeByIndexFromBeginR(lst_s, lst_s->head, 2)->data);
    
    addNodeListFirst(lst_c, (univpoint_t)'f');
    addNodeListFirst(lst_c, (univpoint_t)'q');
    addNodeListLast(lst_c, (univpoint_t)'c');
    addNodeListByIndex(lst_c, (univpoint_t)'1', 1);
    addNodeListByIndex(lst_c, (univpoint_t)'2', 1);
    removeNodeListByIndex(lst_c, 3);
    show(lst_c, 'c');
    printf("%c\n\n", (char*)getNodeByIndexFromEnd(lst_c, 3)->data);
    
    addNodeListFirst(lst_d, (univpoint_t)12);
    addNodeListFirst(lst_d, (univpoint_t)11);
    addNodeListFirst(lst_d, (univpoint_t)15);
    addNodeListByIndex(lst_d, (univpoint_t)2, 0);
    addNodeListLast(lst_d, (univpoint_t)8);
    addNodeListLast(lst_d, (univpoint_t)3);
    addNodeListFirst(lst_d, (univpoint_t)6);
    addNodeListFirst(lst_d, (univpoint_t)33);
    removeNodeListLast(lst_d);
    show(lst_d, 'd');
    printf("%d\n\n", (int*)getNodeByIndexFromBegin(lst_d, 0)->data);
    
    lst_new_by_pred = formNewListByPredicate(lst_d, predicate1);
    show(lst_new_by_pred, 'd');
    removeAllNodes(lst_new_by_pred);
    lst_new_by_pred = formNewListByPredicate(lst_d, predicate2);
    show(lst_new_by_pred, 'd');
	getchar();
	return 0;
}