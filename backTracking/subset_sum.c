#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_LEN(x) ((sizeof(x))/(sizeof(x[0])))

static inline void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

static inline void print(int *A, int len)
{
	int i = 0;

	printf("[ ");
	while(i < len) {
		printf("%d, ", A[i]);
		i++;
	}
	printf("]\n");
}


void simple_insertion_sort(int *A, int len)
{
	int i, j, key;
	printf("%d\n", len);
	for(i = 1; i < len; i++) {
		key = A[i];
		for(j = i-1; j >= 0 && A[j] < key; j--) {
				A[j+1] = A[j];
		}
		A[j+1] = key;
	}

}

void selection_sort(int *A, int len)
{
	int i, j, max;
	for (i = 0; i < len; i++) {
		max = i; /// initial hypothesis
		for(j = i+1; j < len; j++) {
			if(A[j] > A[max]) /// correct the hypothesis
				max = j;
		}
		if(i != max)
			swap(&A[i], &A[max]);

	}

}

/*
 *	uses 2 basic optimization technique.
 *		1. Len factor optimisation,
 *			i.e. bubble sort guarantees that
 *			after one complete internal iteration
 *			bottom most is sorted.
 *		2. swap count based halting.
 */
void bubble_sort(int *A, int len)
{
	int i, j, bubble_cnt;
	for(i=0; i<len; i++) {
		bubble_cnt = 0;
		for(j=0; j<len-i && j+1 < len-i; j++) {
			if(A[j] < A[j+1]) {
				swap(&A[j], &A[j+1]);
				bubble_cnt++;
			}
		}
		if(!bubble_cnt)
			break;
	}
}

/*
 * A stupid stack to keep the elements in track.
 */
static int stack[256];
static int top = 0;

void stack_init() {
	memset(stack, 0x00, sizeof(stack));
}

static void push(int element)
{
	top++;
	stack[top] = element;
}

static void  pop()
{
	if(top > 0) {
		stack[top] = -1;
		top--;
	}
}

int is_empty()
{
	return (top < 0);
}

void print_stack()
{
	int i = 1;

	printf("[");
	while(i <= top) {
		printf("%d, ", stack[i]);
		i++;
	}
	printf("]\n");
}


/* This subrouting assumes that A is sorted
 	in descending order */
void subset_sum(int *A, int len, int sum)
{
	int i, dv;

	printf("len: %d\n", len);
	if(len <= 0)
		return;	

	for(i = 0; i< len; i++) {

	 	dv = sum - A[i];
		if(dv < 0) {
			continue;
		}
		else if(dv > 0) {
			push(A[i]);
			/* Send next index*/
			subset_sum(&A[i+1], len-(i+1), dv);
			pop();
		}
		else if(dv == 0) {
			push(A[i]);
			print_stack();
			pop(A[i]);
		}
	}

}

int main()
{
	int a[] = {12, 7, 6, 5, 3, 2, 1, 8, 0};
	printf("Before Sort:");
	print(a, ARR_LEN(a));
	bubble_sort(a, ARR_LEN(a));
	print(a, ARR_LEN(a));
	subset_sum(a, ARR_LEN(a), 8);

	return 0;
}
