/********************************************************************************
				B-TREES
			------------------------
	PROPERTIES:

		Branching factor: P
			Determines number of branch a node can
			make.
		Key: Each node will have atleast CEIL[P/2] keys
			and atmost P-1 keys.

			if(<CEIL[P/2])
				declare UNDERFLOW
			if(>P-1)
				declare OVERFLOW.

		Children: Each node can have atmost P children.
		
		Example: p = 3, so key 1-2
		----------------
		||  a  ||  b  ||
		----------------
		|	|     |
		|	|     |
		|	|     | 
	________    _____    _____
	|  c	|  |  D  |  |  E  |		
	--------   -------  -------
	  	1. a < b
		2. c < a
		3. a <= D < b
		4. E >= b

	In general, Formally:
		Btree can be viewed as a tuple:
			# < C1<K1, D1>, C2<K2, D2>, ...,Cq<Kq, Dq> Cq+1 >.
			# q < P-1.
			# Cq is less than or equal to <Kq, Dq> and
				 greater than <K[q-1], D[q-1]>.

	PRIMARY OPERATIONS:
		PROMOTE: if(OVERFLOW)
				promote p/2 key.
		DEMOTE: if(UNDERFLOW)
				# combine higly poulated sibling, common parent key
				  and underflow node.
				# Combined node OVERFLOWS:
					PROMOTE.


P.S. Always add a key to the corresponding leaf of a node. 
*************************************************************************************/

#define OVERFLOW(key_count, branching_factor) (((key_count) > (branching_factor-1))?1:0)
#define UNDERFLOW(key_count, branching_factor) (((key_count) < (branching_factor-1))?1:0)
#define IS_LEAF(n) (n->leaf_node)

typedef struct key {
	int key;
	void *data;
}key_t;

typedef struct bnode {
	int count;
	int leaf_node;
	key_t *key;
	struct bnode *children;
	struct bnode *parent;		
}bnode_t;

typedef struct btree {
	int branching_factor;
	bnode_t *head;
}btree_t;

btree_t* btree_init(int bf) 
{
	btree_t *t = NULL;		

	if(!bf) {
		printf("Error: in branching factor :%d\n", bf);
		goto out;
	}

	t = malloc(sizeof(*t));
	if(t) {
		t->branching_factor = bf;
		t->head = NULL;
		return t;
	}
out:
	return NULL;
}

bnode_t* bnode_init(btree_t *tree)
{
	bnode_t *node = malloc(sizeof(bnode_t));
	
	if(node) {
		node->count = 0;
		node->leaf_node = 1;
		node->key = calloc(sizeof(node->key) * (tree->branching_factor));
		if(!node->key) {
			free(node);
			goto out;
		}
		node->children = calloc(sizeof(node->children) * (tree->branching_factor + 1));
		if(!node->children) {
			free(node);
			goto out;
		}
		return node;
	}
out:
	return NULL;
}

static inline key_t* key_init(int key, void *data)
{
	key_t *key= malloc(sizeof(key_t));
	
	if(!key) {
		printf("Error: Malloc fail in key_t\n");
		goto out;
	}
 	key->key = key;
	key->data = data;

	return key;
out:
	return NULL;
}

static int insert_right_pos(bnode_t *node, key_t *key)
{
	key_t *klist = node->key;
	int c = node->count-1;

	klist[node->count] = key;

	while(c) {
		if(klist[c]->key > klist[c+1]->key) {
			key_t *tmp = klist[c];
			klist[c] = klist[c+1];
			klist[c+1] = tmp;
		}
		else {
			break;
		}
		c--;
	}
	node->count++;

	return c;
}

static int insert_key(bnode_t *node, int key, void *data)
{
	key_t *key = key_init(key, data);

	if(!key)
		exit(1);

	return (insert_right_pos(node, key));
}

static void add_children( btree_t *tree,
			bnode_t *node,
			int idx,
		 	bnode_t *left,
		 	bnode_t *right)
{
	int i;
	bnode_t *tmp, tmp1;

	for(i = tree->branching_factor; i<= idx+1; i--) {
		
		if(!node->children[i])
			continue;

		node->children[i+1] = node->children[i];
	}
	node->children[idx] = left;
	node->children[idx+1] = right;

}

static bnode_t* promote(btree_t *tree, bnode_t *node)
{
	/* 
		1. split
		2. make each to a node.
	*/
	bnode_t *left, *right;
	key_t *pkey;
	int split_point = tree->branching_factor/2;
	int i;

	/* SPLIT OPERATION */
	right = bnode_init(tree);
	for(j=0,i=split_point+1; i<node->count; j++, i++) {
		right->key[j] = node->key[i];
		node->key[i] = NULL;
		if(j+1 <= tree->branching_factor){
			right->children[j+1] = node->children[j+1];
			node->children[j+1] = NULL;	
		}
	}
	pkey = node->key[split_point];
	node->key[split_point] = NULL;
	left = node;

	/* PROMOTION OPERATION */
	if(node->parent) {
		i = insert_right_pos(node->parent, key);
		add_children(node->parent, i, left, right);
		if(OVERLOAD(node->parent->count, tree->branching_factor))
			goto prom;
		else
			goto out;
	}
	else {
		bnode_t *tmp = bnode_init(tree->branching_factor);

		tmp->leaf_node = 0;
		tree->head = tmp;
		left->parent = tmp;
		right->parent = tmp;
		i = insert_right_pos(tmp, pkey);
		add_children(tmp, i, left, right);
		goto out;				
	}
prom:
	return node->parent;
out:
	return NULL;

}

static int find_right_idx(key_t *key, int key)
{
	int i = 0;

	/*TODO: MAKE BINARY SEARCH*/
	while(key[i]) {
		if(key[i]->key >= key)
			break;
		i++;
	}

	if(i-1)
		return i-1;

	return 0;
}

static bnode_t* find_right_node(btree_t *tree, int key)
{
	bnode_t *node = tree->head;

	if(!node) {
		tree->head = bnode_init(tree->branching_factor);
		return tree->head;
	}

	while(!IS_LEAF(node)) {
		int i = find_right_idx(node->key, key);
		if(!node->children[i])
			break;
		node = node->children[i];		
	}
	return node;
}

void btree_insert(btree_t *btree, int key, void *data)
{
	bnode_t *node;

	node = find_right_node(btree, key)
	insert_key(node, key, data);

	if(OVERFLOW(node->count, btree->branching_factor)) {
		while(node = promote(btree, node)) ;		
	}
}

