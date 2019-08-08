#include "btree.h"

extern node *btree;

/*
 * An Algorithm that will check if the tree is height balanced.
 */

s32 check_height(node *root)
{
	s32 ret = 0;
	s32 l = 0;
	s32 r = 0;

	if(!root) {
		goto RET;
	}

	if(root->l) {
		l++;
		l += check_height(root->l);
	}
	if(root->r) {
		r++;
		r += check_height(root->r);
	}

	ret = l - r;
	
RET:
	return ret;
}

int main()
{
	create();
	if(check_height(btree)) {
		printf("Not Balanced\n");
	}
	else {
		printf("Balanced\n");
	}
}
