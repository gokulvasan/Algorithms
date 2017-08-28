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
			printf("%d ", n->vertice);
			n = n->nxt;
		}
		printf("]\n");
		v = v->nxt;
	}
}

int main()
{
	graph_t *g = graph_init();

	add_vertice(g, 1);
	add_vertice(g, 2);
	add_vertice(g, 3);
	add_vertice(g, 4);

	add_edge(g, 1, 2, 12);
	add_edge(g, 1, 3, 9);
	add_edge(g, 1, 4, 12);
	add_edge(g, 2, 4, 4);

	print_adj(g);

	return 0;
}
