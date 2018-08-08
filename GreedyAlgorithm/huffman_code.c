#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char a[] = "abbaaaacdddeeefffffffffggggg";
int range = 7;

typedef struct character {
	char a;
	char cnt;
} char_t;

typedef struct char_lst {
	int cnt;
	char_t *lst;
}char_lst_t;

typedef struct huffman {
	int freq;
	char_t *data;
	struct huffman *left;
	struct huffman *right;
	
} huffman_t;

char_t* search_element(char_t *lst, int cnt, char c)
{
	int i = 0;

	while(i<cnt) {
		if(lst[i].a == c)
			return &lst[i];
		i++;
	}
	return NULL;
}


/* Assumes a[] is null terminated */
char_lst_t* huffman_count_freq(char *a, int range)
{
	char_t *c = malloc(sizeof(char_t) * range);
	char_lst_t *lst = malloc(sizeof(*lst));
	char_t *t;
	int i = 0;

	memset(c, 0x00, (sizeof(char_t) * range));
	while(*a) {

		if((i) && (t = search_element(c, i, *a))) {
			t->cnt++;
		}
		else {
			c[i].a = *a;
			c[i].cnt++;
			i++;
		} 
		a++;
	}
	lst->cnt = i;
	lst->lst = c;

	return lst;
}

static void swap(char_t *A, char_t *B)
{
	char_t c;
	
	c.a = A->a;
	c.cnt = A->cnt;

	A->a = B->a;
	A->cnt = B->cnt;

	B->a = c.a;
	B->cnt = c.cnt;
}

#define lchild(i) ((2*(i))+1)
#define rchild(i) ((2*(i))+2)

void min_heapify(char_lst_t *a, int i)
{
	int smallest;
	char_t *lst = a->lst;

	if((a->cnt <= i) || 
	((lchild(i) >= a->cnt) && 
	(rchild(i) >= a->cnt)) )
		return;
	
	if(lchild(i) >= a->cnt)
		smallest = rchild(i);
	else if(rchild(i) >= a->cnt)
		smallest = lchild(i);
	else {
		smallest = lchild(i);
		if(lst[lchild(i)].cnt  > lst[rchild(i)].cnt)
			smallest = rchild(i);
	}

	if(lst[i].cnt > lst[smallest].cnt) {
		swap(&lst[i], &lst[smallest]);
		min_heapify(a, smallest);
	}
}

void build_heap(char_lst_t *a)
{
	int i;

	for(i=(a->cnt+1)/2; i>=0; i--)
		min_heapify(a, i);
}


char_t* extract_min(char_lst_t *a)
{
	a->cnt--;
	swap(&a->lst[0], &a->lst[a->cnt]);
	min_heapify(a, 0);

	return &a->lst[a->cnt];
}

huffman_t* node_init(char_lst_t *lst)
{
	huffman_t *node = malloc(sizeof(*node));
	node->data = extract_min(lst);
	node->freq = node->data->cnt;
	node->left = NULL;
	node->right = NULL;

	return node;
}

static huffman_t*  node_insert(huffman_t *root, huffman_t *node)
{
	if(!root) {
		root = malloc(sizeof(*root));
		root->left = node;
		root->freq += node->freq;
		root->right = NULL;
		root->data = NULL;
		return root;
	}
	
	if(root->left) {
		if(!root->right) {
			huffman_t *new_root = malloc(sizeof(*new_root));
			
			/// maintain order
			if(root->left->freq > node->freq) {
				huffman_t *t = root->left;
				root->left = node;
				root->right = t;
			}
			else {
				root->right = node;
			}
			root->freq += node->freq;
			
			/// populate new root.
			/// Here is the problem:
			/// this unnecessarily increases height of a tree.
			new_root->left = root;
			new_root->freq = root->freq;
			new_root->right = NULL;
			new_root->data = NULL;
			root = new_root;
		}
	}
	return root;
}

huffman_t* build_huffman(char_lst_t *l)
{
	huffman_t *root= NULL;
	huffman_t *node;

	while(l->cnt) {
		node = node_init(l);
		root = node_insert(root, node);
		printf("%d\n", root->freq);
	}
	return root;
}

int stack[256];
int cnt = 0;

void push(int i) 
{
	stack[cnt] = i;
	cnt++;
}

int pop()
{
	cnt--;
	return stack[cnt];
}

void stack_print()
{
	int i;
	printf("[ ");
	for(i = 0; i<cnt; i++) {
		printf("%d ", stack[i]);
	}
	printf("]\n");
}
void print_huffman(huffman_t *root)
{
	if(!root)
		return;

	if(root->data) {
		printf("%c ==>", root->data->a);
		stack_print();
	}

	push(1);
	print_huffman(root->left);
	pop();
	push(0);
	print_huffman(root->right);
	pop();
}
void huffman_code(char *a, int range)
{
	char_lst_t *c;
	int i;
	huffman_t *root;

	c = huffman_count_freq(a, range);
	for(i=0; i<c->cnt; i++) {
		printf("%c: c[%d]: %d\n", c->lst[i].a, i, c->lst[i].cnt);
	}
	printf("\n");
	build_heap(c);

	for(i=0; i<c->cnt; i++) {
		printf("%c: c[%d]: %d\n", c->lst[i].a, i, c->lst[i].cnt);
	}		

	root = build_huffman(c);
	print_huffman(root);
}

int main()
{
	huffman_code(a, range);

}
