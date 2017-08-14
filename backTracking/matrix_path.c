#include <stdio.h>
#include <stdlib.h>

/*
The problem is to print all the possible paths from top left to bottom right of a mXn matrix 
with the constraints that from each cell you can either move only to right or down.
*/

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

static void print_paths_util(int A[][4], int i, int j, int M, int N)
{
	if(i < M-1) {
		push(A[i][j]);
		print_paths_util(A, i+1, j, M, N);
		pop();
	}
	if(j < N-1) {
		push(A[i][j]);
		print_paths_util(A, i, j+1, M, N);
		pop();
	}

	if((i >= M-1) && (j >= N-1)) {
		push(A[M-1][N-1]);
		print_stack();
		pop();
	}

}

static void print_all_paths(int A[][4], int M, int N)
{

	print_paths_util(A, 0, 0, M, N);

}

int main()
{
	int A[4][4] = {{2, 3, 4, 5}, {4, 5, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	stack_init();
	print_all_paths(A, 4, 4);
	return 0;
}
