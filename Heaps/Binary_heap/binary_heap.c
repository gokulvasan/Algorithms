#include <stdio.h>
#include <stdlib.h>

typedef unsigned int ui;

#define MAX 50
ui arr[MAX];
int curr_index = 0;

#define PARENT(i) ((i-1)/2)
#define LEFT_CHILD(i) ((i*2) +1)
#define RIGHT_CHILD(i) ((i*2) +2)

static void swap (ui *A, int a, int b)
{
	ui t = A[a];
	A[a] = A[b];
	A[b] = t;
}

static void min_heapify(int index )
{
	int parent = PARENT(index);

	if(index < 0)
		return;

	if(arr[parent] > arr[index]) {
		swap(arr, parent, index);
		min_heapify(parent);
	}
}

static void insert(ui val)
{
	if(curr_index >= MAX)
		return;

	arr[curr_index]=val;
	min_heapify(curr_index);
	curr_index++;
}

int main()
{
	int i = 0;

	insert(2);
	insert(1);
	insert(5);
	insert(17);
	insert(15);
	insert(4);
	insert(10);
	insert(3);
	insert(2);

	for( i=0; i<=8; i++)
	{
		printf("%d, ", arr[i]);
	}
	printf("\n");

	return 0;

}
