#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertice {
	int vertice;
	int weight;
	struct vertice *nxt;			
}vertice_node_t;

typedef struct vertice_lst {
	int vertice;
	vertice_node_t *node;
	struct vertice_lst *nxt;
} vertice_lst_t;

typedef struct graph {
	int cnt;
	vertice_lst_t *head;
}graph_t;

graph_t* graph_init(void) 
{
	graph_t *t = malloc(sizeof(*t));
	if(t) {
		t->cnt = 0;
		t->head = NULL;
		return t;
	}
	exit(1);
}

void add_vertice(graph_t *G, int v)
{
	vertice_lst_t *vt = malloc(sizeof(*vt));

	if(vt) {
		vt->vertice = v;
		vt->node = NULL;
		vt->nxt  = NULL;
	}
	G->cnt++;
	vt->nxt = G->head;
	G->head = vt;
}

void add_edge(graph_t *G, int u, int v, int weight)
{
	vertice_node_t *node;
	vertice_lst_t *iter = G->head;

	node = malloc(sizeof(*node));
	node->vertice = v;
	node->weight = weight;

	while(iter) {
		if(iter->vertice == u) {
			node->nxt  = iter->node;
			iter->node = node;
			break;
		}
		iter = iter->nxt;
	}
}

void print_adj(graph_t *G)
{
	vertice_lst_t *v = G->head;
	vertice_node_t *n;

	while(v) {
		n = v->node;
		printf("%d: [", v->vertice);
		while(n) {
			printf("%d:%d ", n->vertice, n->weight);
			n = n->nxt;
		}
		printf("]\n");
		v = v->nxt;
	}
}


/*
	T[i] = Min[ cost(i, j) + T[j] ]
	index = i-1.
	j = i to nxt. 
*/
#define IMAX (0xFFFF)

void min_cost(graph_t *G)
{
	int *a = malloc(sizeof(int)*G->cnt);
	vertice_lst_t *l = G->head;
	vertice_node_t *e;
	int index, i;

	while(l) {
		a[l->vertice -1] = IMAX;
		e = l->node;
		if(!e)
			a[l->vertice-1] = 0; 
		while(e) {
			int c = e->weight + a[e->vertice-1];
			if(c < a[l->vertice-1])
				a[l->vertice-1] = c;
			e = e->nxt;
		}
		l = l->nxt;
	}

	printf("MIN PATH:\n");
	printf("%d ", a[0]);
	printf("\n");
}

int main()
{
	graph_t *g = graph_init();

	add_vertice(g, 1);
	add_vertice(g, 2);
	add_vertice(g, 3);
	add_vertice(g, 4);
	add_vertice(g, 5);
	add_vertice(g, 6);
	add_vertice(g, 7);
	add_vertice(g, 8);

	add_edge(g, 1, 2, 1);
	add_edge(g, 1, 3, 3);
	add_edge(g, 1, 4, 5);
	add_edge(g, 2, 5, 4);
	add_edge(g, 2, 6, 11);
	add_edge(g, 3, 5, 9);
	add_edge(g, 3, 6, 5);
	add_edge(g, 3, 7, 16);
	add_edge(g, 4, 7, 2);
	add_edge(g, 5, 8, 18);
	add_edge(g, 6, 8, 13);
	add_edge(g, 7, 8, 12);

	print_adj(g);
	
	min_cost(g);
	return 0;
}
