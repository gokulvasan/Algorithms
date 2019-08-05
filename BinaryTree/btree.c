#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;
typedef signed int s32;

typedef struct _node {
	u32 key;
	struct _node *l;
	struct _node *r;
}node;

typedef enum _traversal_order {
	preorder = 0,
	inorder,
	postorder
} trav_order;

/* Global variable holding the btree*/
node *btree = NULL;

node* node_init(int key)
{
	node *t;

	t = malloc(sizeof(*t));
	if(!t)
		return NULL;

	t->l = NULL;
	t->r = NULL;
	t->key = key;

	return t;	
}

s32 btree_insert_i(const u32 key, node **root)
{
	node *t = *root;
	node *n = NULL;
	s32 ret = -1;

	while(t) {

		if(key >= t->key) {
			n = t->r;
		}
		else if(key < t->key) {
			n = t->l;
		}

		if(n) {
			t = n;
			n = NULL;
		}
		else
			break;
	}
	if (!(n = node_init(key)))
		goto FAIL;

	if (t && key >= t->key) {
		printf("r %d\n", key);
		t->r = n;
	}
	else if (t && key < t->key) {
		printf("l %d\n", key);
		t->l = n;
	}
	else {
		printf("root %d\n", key);
		*root = n;
	}
	ret = 0;

FAIL:
	return ret;
}

s32 btree_insert_r(const u32 key, node *root)
{
	s32 ret = -1;
	node *t = root;

	if(!t) {
		ret = 1;
		goto RET;
	}

	if(key >= t->key) {
		ret = btree_insert_r(key, t->r);
		if(ret > 0) {
			if(!(t->r = node_init(key))) {
				goto RET;
			}
		}
	}
	else if(key < t->key) {
		ret = btree_insert_r(key, t->l);
		if(ret > 0) {
			if(!(t->l = node_init(key))) {
				goto RET;
			}
			printf ("%d\n", t->l->key);
		}
	}
	ret = 0;

RET:
	return ret;
}

s32 btree_traverse_inorder (const node *root)
{
	s32 ret = -1;

	if(!root) {
		ret = 0;
		goto RET;		
	}

	btree_traverse_inorder(root->l);
	btree_traverse_inorder(root->r);

	printf("%d, ", root->key);
	ret = 1;

RET:
	return ret;
}

int main()
{
	btree_insert_i(25, &btree);	
	btree_insert_i(15, &btree);	
	btree_insert_i(50, &btree);	
	btree_insert_i(10, &btree);	
	btree_insert_i(22, &btree);	
	btree_insert_i(30, &btree);	
	btree_insert_i(70, &btree);	
	btree_insert_i(4, &btree);	
	btree_insert_i(12, &btree);	
	btree_insert_i(18, &btree);	
	btree_insert_i(24, &btree);	
	btree_insert_i(29, &btree);	
	btree_insert_i(44, &btree);	
	btree_insert_i(66, &btree);	
	btree_insert_i(90, &btree);

	btree_traverse_inorder(btree);
	printf("\n");	
}
