#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stddef.h>
/* 
 Merge Sort: Given an input array 
	1. Divide
	2. on merge compare and place in the right place.
*/

typedef unsigned int ui;

static void copy_to_orig(ui *A, ui start, ui end, ui *arr)
{
	ui i=0;
	ui k = start;

	for (i=0; k < end; i++,k++) {
		A[k] = arr[i]; 
	}
}

static ui merge (ui *A, ui astart, ui aend, ui bstart, ui bend)
{
	ui a = astart;
	ui b = bstart;
	ui c = 0; 
	ui *merge;

	merge  = malloc(sizeof(*merge) * (bend - astart));
	if(!merge)
		return 0;
	
	while((a < aend) && (b < bend)) {
		if(A[a] <= A[b]){
			merge[c] = A[a];
			a++;
		}
		else {
			merge[c] = A[b];
			b++;
		}
		c++;
	}
	while(a < aend) {
		merge[c] = A[a];
		a++;
		c++;
	}
	while(b < bend) {
		merge[c] = A[b];
		b++;
		c++;
	}

	copy_to_orig (A, astart, bend, merge);
	free(merge);

	return (bend-astart);
}

static void merge_sort(ui *A, ui start, ui end) 
{
	ui split;
	if(end - start <= 1)
		return;
	split = (start + end)/2;
	printf("Start: %d split:%d End: %d\n", start, split, end);
	merge_sort(A, start, split);
	merge_sort(A, split, end);

	merge(A, start, split, split, end);
}

static ui sort(ui *arr, ui len)
{
	merge_sort(arr, 0, len);

}

#define ARR_LEN(x) (sizeof(x)/sizeof(x[0]))
int main()
{
	ui a[] = {15,2,5,7,25,22,8,0};
	ui i = 0;

	sort(a, ARR_LEN(a));
	
	for (i=0; i<ARR_LEN(a); i++)
	{
		printf("%d, ", a[i]);
	}
	printf("\n");
	return 0;
}

