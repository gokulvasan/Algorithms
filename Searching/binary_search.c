#include <stdio.h>
#include <stdlib.h>


/*
 *	Given: A n element array.
 *	Challenge:  rotate i elements on right
 *		ab is a string, rotate it to ba		
 *
 */




typedef struct _stack {

	#define MAX_DEPTH 255
	char a[MAX_DEPTH];
	int pointer;
	void (*push) (struct _stack *diese, char element);
	char (*pop) (struct _stack *diese);

} stack;

static void push (struct _stack *diese, char element)
{
	if(diese->pointer >= MAX_DEPTH)
		return;

	diese->a[diese->pointer] = element;
	diese->pointer++;
}

static char pop (struct _stack *diese)
{
	if (!diese->pointer)
		return 0xff;

	diese->pointer--;
	
	return (diese->a[diese->pointer]);

}

static stack s = {
	.push = push,
	.pop = pop,	
	.pointer = 0,	
};

void reverse(char *arr, int start, int e)
{
	return;		
}


int main() {

	return 0;
}
