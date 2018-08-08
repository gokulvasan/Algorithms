#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


int rat_in_maze(int A[][3], int i, int j, int M, int N)
{
	if(i == M-1 && j == N-1) {
		printf("reached\n");
		print_stack();
		return 1;
	}
	push(A[i][j]);

	if((i+1 <= M-1) && (A[i+1][j])) {
		printf("down\n");
		if(rat_in_maze(A, i+1, j, M, N))
			return 1;
	}

	if((j+1 <= N-1) && (A[i][j+1])) {
		printf("right\n");
		if( rat_in_maze(A, i, j+1, M, N))
			return 1;
	}

	if((j-1 >= 0) && (A[i][j-1])) {
		printf("left\n");
		if(rat_in_maze(A, i, j-1, M, N))
			return 1;
	}
	pop();

	return 0;
}

int main()
{
	int A[3][3] = { {1,1,0},
			{1,1,0},
			{0,1,1}
			};
	rat_in_maze(A, 0, 0, 3, 3);
}
