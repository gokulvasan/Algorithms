#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>

#define LEFT_CHILD(i) (2 * i)
#define RIGHT_CHILD(i) ((2*i) + 1)
#define PARENT(i) ( (i%2) ? (i/2) : ((i/2) - 1) )

#define SWAP(a, b) do {		\
		int c = a;	\
		a = b;		\
		b = c;		\
	 }while(0);

struct bheap {
	int *key;
	int count;
};

void bheap_init(struct bheap *b, int count)
{
	b->key = (int*)malloc(sizeof(*b->key)*count);
	if(!b->key)
		exit(1);
	b->count = count;
}

/*
	MAXIFY HEAP
	r: recursive
	i: iterative
*/
static void bheap_heapify_r(struct bheap *b, int element)
{
	if((element < b->count) && 
		(LEFT_CHILD(element) < b->count) && 
		(RIGHT_CHILD(element) < b->count)) {

		int largest = element;
		/* Get the maximum index of these 3*/
		if( b->key[LEFT_CHILD(element)] >= b->key[RIGHT_CHILD(element)])
			largest = LEFT_CHILD(element);
		if(b->key[largest] > b->key[element]) {
			SWAP(b->key[largest], b->key[element]);
			bheap_heapify_r(b, largest);
		}
	}
}

static void bheap_heapify_i(struct bheap *b, int element)
{
	while((element < b->count) && 
		(LEFT_CHILD(element) < b->count) && 
		(RIGHT_CHILD(element) < b->count)) {

		int largest = element;
		/* Get the maximum index of these 3*/
		if( b->key[LEFT_CHILD(element)] >= b->key[RIGHT_CHILD(element)])
			largest = LEFT_CHILD(element);
		if(b->key[largest] > b->key[element]) {
			SWAP(b->key[largest], b->key[element]);
			element = largest;
			continue;
		}
		break;
	}	
}

int bheap_delete_max(struct bheap *b)
{
	int max;
	
	if(b->count) {
	 	max = b->key[0];
		b->key[0] = b->key[b->count - 1];
		b->count--;
		bheap_heapify_r(b, 0);
	}
}

int bheap_get_max(struct bheap *b)
{
	if(b->count) 
		return b->key[0];
}

void bheap_extend(struct bheap *b)
{
	int *i = b->key;
	int c = 0;

	b->key = malloc(sizeof(*b->key) * (b->count + 1));
	if(!b->key)
		exit(1);
	
	while(c < b->count) {
		b->key[c] = i[c];
		c++;
	}
	b->count++;
}

int bheap_insert(struct bheap *b, int key)
{
	int i;
	bheap_extend(b);
	b->key[b->count-1] = key;
	
	i = b->count-1;
	while(i) {
		if(b->key[PARENT(i)] < b->key[i]) {
			SWAP(b->key[PARENT(i)], b->key[i]);
			i = PARENT(i);
		}
		else {
			break;
		}
	}
}

void bheap_build(struct bheap *b)
{
	for(i=(b->count-1)/2; i < 0; i--) {
		bheap_heapify_r(b, i);
	}
}

void bheap_sort(struct bheap *b)
{
	while(b->count) {
		SWAP(b->key[0], b->key[b->count - 1]);
		b->count--;
		bheap_heapify_r(b, 0);
	}
} 

int main() {
	return 0;
}
