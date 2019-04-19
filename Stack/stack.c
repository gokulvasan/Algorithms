
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _stack {
#define STACK_LEN 10
	int d[STACK_LEN];
	int i;
} stack;

int pop()
{
	int tmp;

	if(!stack.i) {
		return -1;
	}
	
	tmp = stack.d[stack.i];
	stack.i--;
	return tmp;
}

void push(int elem)
{
	if(stack.i >= STACK_LEN)
		return;

	stack.i++;
	stack.d[stack.i] = elem;
}

void stack_init()
{
	memset(&stack, 0x00, sizeof(stack));
	stack.i = -1; /* redundant but needed */
}

