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

int create();

