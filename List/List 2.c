#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint_t;
typedef void* univpoint_t;

typedef struct _Node {
	univpoint_t data;
	struct _Node* next;
} Node, *PNode;

typedef struct _List {
	PNode head;
} List, *PList;

typedef int (*prict_t)(PNode);

typedef enum _From {
	BEGIN,
	END
} From;

PList createlst();
void add(uint_t, From, PList, univpoint_t);
PNode get(uint_t, From, PList);
void del(uint_t, From, PList);
void clear(PList);
uint_t getlen(PList);
PList newlstbypred(PList, prict_t);
PList mergesort(PList, PList);
PList merge(PList, PList);
void show(PList, char);

PList createlst() {
	PList lst = malloc(sizeof(List));
	lst->head = NULL;
	return lst;
}

void add(uint_t i, From af, PList lst, univpoint_t data) {
	PNode node = malloc(sizeof(Node));
	node->data = data;
	PNode innode;
	if (lst->head == NULL) {
		lst->head = node;
		return;
	}
	else if (i == 0 && af == BEGIN) {
	    node->next = lst->head;
        lst->head = node;
        return;
	}
	if (af == BEGIN) {
	    innode = get(i - 1, af, lst);
	}
	else if (af == END) {
	    innode = get(i, af, lst);
	}
    node->next = innode->next;
    innode->next = node;
}

PNode get(uint_t i, From gf, PList lst) {
	if (lst->head == NULL) {
		return NULL;
	}
	int j;
	PNode node = lst->head;
	if (gf == BEGIN) {
		for (j = 0; j < i && node->next; ++j) {
			node = node->next;
		}
	}
	else if (gf == END) {
		PNode node2 = lst->head;
		for (j = 0; j < i && node2->next; ++j) {
			node2 = node2->next;
		}
		while(node2->next) {
			node2 = node2->next;
			node = node->next;
		}
	}
	return node;
}

void del(uint_t i, From rf, PList lst) {
    if (lst->head == NULL) {
        return;
    }
    PNode node;
    if (i == 0 && rf == BEGIN || get(i, rf, lst) == lst->head) {
	    PNode node = lst->head;
	    lst->head = lst->head->next;
	    free(node);
	    return;
	}
	else if (rf == BEGIN) {
        node = get(i - 1, rf, lst);
	}
	else if (rf == END) {
	    node = get(i + 1, rf, lst);
	}
	PNode nodetmp = node->next;
    node->next = node->next->next;
    free(nodetmp);
}

void clear(PList lst) {
	if (lst->head == NULL) {
		return;
	}
	PNode node = lst->head;
	PNode nodetmp;
	while(node) {
		nodetmp = node;
		node = node->next;
		free(nodetmp);
	}
	lst->head = NULL;
}

uint_t getlen(PList lst) {
	uint_t length = 0;
	PNode node = lst->head;
	while(node) {
		node = node->next;
		++length;
	}
	return length;
}

PList newlstbypred(PList lst, prict_t f) {
	if (lst->head == NULL) {
		exit(-1);
	}
	PList newlst = createlst();
	PNode node = lst->head;
	while (node) {
		if (f(node)) {
			add(0, BEGIN, newlst, node->data);
		}
		node = node->next;
	}
	return newlst;
}

PList mergesort(PList lst1, PList lst2) {
    PList newlst = createlst();
    PNode node1 = lst1->head;
    PNode node2 = lst2->head;
    while (node1 && node2) {
        if (node1->data < node2->data) {
            add(0, END, newlst, node1->data);
            node1 = node1->next;
        }
        else {
            add(0, END, newlst, node2->data);
            node2 = node2->next;
        }
    }
    if (node2 == NULL) {
        while (node1) {
            add(0, END, newlst, node1->data);
            node1 = node1->next;
        }
    }
    else {
        while (node2) {
            add(0, END, newlst, node2->data);
            node2 = node2->next;
        }
    }
    return newlst;
}

PList merge(PList lst1, PList lst2) {
    PList newlst = createlst();
    PNode node1 = lst1->head;
    PNode node2 = lst2->head;
    while(node1) {
        add(0, END, newlst, node1->data);
        node1 = node1->next;
    }
    while(node2) {
        add(0, END, newlst, node2->data);
        node2 = node2->next;
    }
    return newlst;
}

int predicate1(PNode a) {
	if (a->data < (univpoint_t)10) {
		return 1;
	}
	else {
		return 0;
	}
}

int predicate2(PNode a) {
	if ((int)a->data & 1) {
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
	PNode node = lst->head;
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
	PList lst1 = createlst();
	PList lst2 = createlst();
	add(0, END, lst1, (univpoint_t)10);
	add(0, END, lst1, (univpoint_t)12);
	add(0, END, lst1, (univpoint_t)23);
	add(0, END, lst1, (univpoint_t)51);
	add(0, END, lst1, (univpoint_t)69);
	add(0, END, lst1, (univpoint_t)72);
	show(lst1, 'd');
	
	add(0, END, lst2, (univpoint_t)7);
	add(0, END, lst2, (univpoint_t)15);
	add(0, END, lst2, (univpoint_t)27);
	add(0, END, lst2, (univpoint_t)52);
	add(0, END, lst2, (univpoint_t)70);
	add(0, END, lst2, (univpoint_t)100);
	show(lst2, 'd');
	
	PList lst3 = mergesort(lst1, lst2);
	show(lst3, 'd');
	getchar();
	return 0;
}