#include <stdio.h>
#include <stdlib.h>

struct bih_child {
	struct bih *node;
	struct bih_child *nxt;
};

struct bih {
	int key;
	int degree;
	void *payload;
	struct bih *parent;
	struct bih_child *child;
	struct bih *sibling;
};

struct bih_child* bih_child_init(struct bih *node, struct bih_child *nxt) 
{
	struct bih_child *c = (struct bih_child*)malloc(sizeof(struct bih_child));
	if(c) {
		c->node = node;
		c->nxt = nxt;
		return c;
	}
	exit(1);
}

void bih_child_insert(struct bih *parent, struct bih *child)
{
	int degree = parent->degree;
	struct bih_child *c = bih_child_init(child, parent->child);

	parent->child = c;
	child->parent = parent;
	parent->degree++;
}

struct bih* bh_new(int key, void *payload)
{
	struct bih *n = (struct bih*)malloc(sizeof(struct bih));
	if(n) {
		n->key = key;
		n->payload = payload;
		n->degree = 0;
		n->parent =n->sibling = NULL;
		n->child = NULL;
 
		return n;
	}
	exit(1);
}

static struct bih* extract_first(struct bih *b)
{
	struct bih *first;

	if(b) {
		first = b;
		b = first->sibling;
		return first;
	}
	return NULL;
}

static struct bih* __merge(struct bih *hone, struct bih *htwo)
{
	if(hone->key > htwo->key) {
		bih_child_insert(htwo, hone);
		return htwo;
	}
	else {
		bih_child_insert(hone, htwo);
		return hone;
	}
}

static int merge(struct bih *hone, struct bih *htwo)
{
	if(!hone) {
		hone = htwo;
		goto out;
	}
	if(!htwo) {
		goto out;
	}

	if(hone->degree != htwo->degree)
		return 0;

	hone = __merge(hone, htwo);		
out:
	return 1;
}

struct bih* check_extract_same_degree_bt(struct bih *h, int degree)
{
	struct bih *prev = h;
	struct bih *curr = prev->sibling;

	while(curr) {

		if(curr->degree == degree) {
			struct bih *t = curr;
			prev->sibling = curr->sibling;
			return t;
		}
		prev = curr;
		curr = prev->sibling;
	}

}

void bih_insert_right_position(struct bih *h, struct bih *node)
{
	struct bih *curr = h;
	
	if(!curr)
		h = node;

	while(curr) {
		if(curr->sibling->degree > node->degree) {
			node->sibling = curr->sibling;
			curr->sibling = node;
			break;
		}
		curr = curr->sibling;
	}
}

void bih_insert(struct bih *h, struct bih *hd)
{
	struct bih *tmp;

	tmp = check_extract_same_degree_bt(h, hd->degree);
	if(tmp)
		merge(tmp, hd);

	bih_insert_right_position(h, tmp);
}

struct bih* bih_union(struct bih *hone, struct bih *htwo)
{
	struct bih *hdash = NULL;
	struct bih *hone_first;
	struct bih *htwo_first;

	while(hone && htwo) {
		hone_first = extract_first(hone);
		htwo_first = extract_first(htwo);
		if(!merge(hone_first, htwo_first)) {
			bih_insert(hdash, htwo_first);
		}
		bih_insert(hdash, hone_first);
	}
	return hdash;
}

static struct bih* get_min_bt(struct bih *h)
{
	struct bih *curr = h;
	struct bih *min = h;

	while(curr && curr->sibling) {
		if(curr->sibling->key < min->sibling->key) {
			min = curr;
		}
		curr = curr->sibling;
	}
	return min;
}

static int extract_min_node(struct bih *h)
{
	struct bih *t = NULL;
	struct bih_child *c = h->child;
	struct bih *node;
	struct bih_child *tmp;
	int i;

	while(c) {
		node = c->node;
		node->parent = NULL;
		bih_insert(t, node);

		tmp = c;
		c = c->nxt;
		free(tmp);
	}
	i = h->key;
	free(h);

	return i;	
}

int bih_extract_min(struct bih *h)
{
	struct bih *min, *tmp;
	int i = 0;

	if(h) {
		min = get_min_bt(h);
		tmp = min->sibling;
		min->sibling = tmp->sibling;
		i = extract_min_node(tmp);
		h = bih_union(h, tmp);
	}
	return i;
}

int bih_min(struct bih *h)
{
	struct bih *min, *tmp;

	if(h) {
		min = get_min_bt(h);
		tmp = min->sibling;
		return tmp->key;				
	}
}

int main()
{
	return 0;
}


