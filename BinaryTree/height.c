#include "btree.h"

extern node *btree;

#define max(a,b) (((a)>(b))? (a) : (b))
u32 get_height( const node const *root)
{
	u32 l=0;
	u32 r=0;

	if(!root) {
		return 0;
	}

	if(root->l) {
		l = get_height(root->l);
		l++;
	}
	if(root->r) {
		r = get_height(root->r);
		r++;
	}
	return max(l,r);
}

int main()
{
	u32 h = 0;

	create();
	h = get_height(btree);
	printf("height %d\n", h);
}
