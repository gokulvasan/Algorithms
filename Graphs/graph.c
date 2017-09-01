#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum graph_repr {
	adj_matrix = 0,
	adj_list,
	adj_invalid
}graph_repr_t;

typedef enum graph_type {
	dir,
	undir
}graph_type_t;

typedef struct graph {
	graph_repr_t rep;
	graph_type_t type;
	int cnt;
	void *repr;
}graph_t;

/* Adjaceny List representation */
typedef struct edge {
	int vid;
	struct edge *nxt;
}edge_t;

typedef struct vertex_node {
	edge_t *head;
	int vid;
	struct vertex_node *nxt;
}vertex_node_t;

typedef struct adjacency {
	int m;
	int n;
	int *matrix;
}adj_matrix_t; 


///XXX: for now simple adj list will be happy :D
void insert_edge(graph_t *G, int u, int v)
{
	vertex_node_t *h =(vertex_node_t*)G->repr;
	int i=0;
	
	printf("%d %d:\n", u, v);
	while(h) {

		int e = -1;

		printf("%d \n", h->vid);
		if(u == h->vid) {
			e = v;
			i++;
		}
		else if(v == h->vid) {
			e = u;
			i++;
		}

		if(e >= 0) {
			edge_t *edge = malloc(sizeof(*edge));
			edge->vid = e;
			edge->nxt = h->head;
			h->head = edge;
		}

		if(2 == i)
			break;

		h = h->nxt;
	}

}

vertex_node_t* mk_graph(graph_repr_t repr, int vcnt)
{
	int i;
	vertex_node_t *node = NULL;
	vertex_node_t *t;

	for(i=vcnt-1; i >= 0; i--) {
		t = malloc(sizeof(*t));
		t->head = NULL;
		t->vid = i;
		t->nxt = node;
		node = t;
	}
	return node;
}

graph_t* graph_init(graph_repr_t repr,
		 graph_type_t type,
		int vcnt) 
{
	graph_t *g = malloc(sizeof(*g));
	
	g->rep = repr;
	g->type = type;
	g->cnt = vcnt;
	g->repr = mk_graph(repr, vcnt);

	return g;
}

vertex_node_t *queue[256];
int qcnt = -1;

void enqueue(int vid, graph_t *G)
{
	vertex_node_t *v = G->repr;
	
	while(v) {
		if(v->vid == vid) {
			qcnt++;
			queue[qcnt] = v;
		}
		v = v->nxt;
	}
}

vertex_node_t* dequeue()
{
	vertex_node_t *t;
	int i;

	if(qcnt >= 0)
		t = queue[0];
	else
		return NULL;

	for(i=1; i<=qcnt; i++) {
		queue[i-1] = queue[i];
	}

	return t;
}

int bft(graph_t *G)
{
	int i;
	//int u, v;
	vertex_node_t *lst = (vertex_node_t *)G->repr; 
	int *v = malloc(sizeof(int) * G->cnt);

	memset(v, 0x00, sizeof(int) * G->cnt);
	//u=v=0;
	v[lst->vid] = 1;

	for(i=0; i<G->cnt; i++) {

		edge_t *e = lst->head;
		while(e) {
			if(!v[e->vid]) {
				printf("%d ", e->vid);
				v[e->vid] = 1;
				enqueue(e->vid, G);		
			}
			e = e->nxt;
		}
		lst = dequeue();
		if(!lst)
			break;
	}
	printf("\n");
}

static vertex_node_t* edge_to_vertex(graph_t *G, int vid) 
{
	vertex_node_t *t = G->repr;

	while(t) {

		if(t->vid == vid) 
			return t;

		t = t->nxt;
	}
	return NULL;	
}

void dft(graph_t *G, vertex_node_t *lst, int *v)
{
	edge_t *e;
	
	printf("%d ", lst->vid);
	if(!v) {
		v = malloc(sizeof(int) * G->cnt);
		memset(v, 0x00, sizeof(int) * G->cnt);
	}
	if(!lst)
		return;

	e = lst->head;
	while(e) {
		if(!v[e->vid]) {
			vertex_node_t *nxt = edge_to_vertex(G, e->vid);
			v[e->vid] = 1;
			dft(G, nxt, v);
		}
		e = e->nxt;
	}
}

void print_graph(graph_t *G)
{
	int i;
	vertex_node_t *lst = (vertex_node_t *)G->repr; 
	
	for(i=0; i < G->cnt; i++) {
		edge_t *e = lst->head;
		printf("%d:-[ ", lst->vid);
		while(e) {
			printf("%d", e->vid);
			e = e->nxt;
		}
		printf("]\n");
		lst = lst->nxt;
	}

}
int main()
{
	graph_t *G = graph_init(adj_list, undir, 6);

	insert_edge(G, 0, 1);
	insert_edge(G, 0, 2);	
	insert_edge(G, 2, 3);
	insert_edge(G, 2, 4);
	insert_edge(G, 1, 4);
	insert_edge(G, 1, 3);
	insert_edge(G, 3, 5);
	insert_edge(G, 4, 5);

	print_graph(G);

	dft(G, G->repr, NULL);

	return 0;
}
