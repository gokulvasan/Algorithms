#include "btree.h"

extern node *btree;

/*
 * An Algorithm that will check if the tree is height balanced.
 *
 * Define Height Balance: if( (left-subtree-height - right-subtree-height) == 0)
 * 					Balanced;
 * 			  else
 * 			  		not-balanced;
 *
 * Variant: K Balanced.
 */

s32 check_height(node *root, u32 k)
{
	s32 ret = 0;
	s32 l = 0;
	s32 r = 0;

	if(!root) {
		goto RET;
	}

	if(root->l) {
		l++;
		l += check_height(root->l, k);
	}
	if(root->r) {
		r++;
		r += check_height(root->r, k);
	}

	ret = l - r;

RET:
	return ret;
}

#define POSITIVE(n) ((n) < 0 ? 0 - (n) : (n))

int main()
{
	u32 k =0;
	s32 h =0;

	create();

	h = check_height(btree, k);
	h = POSITIVE(h);

	if( h > k) {
		printf("Not Balanced\n");
	}
	else {
		printf("Balanced\n");
	}
}
