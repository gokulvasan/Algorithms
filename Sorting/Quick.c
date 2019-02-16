#include <stdio.h>
#include <stdlib.h>

#define A_LEN(x) (sizeof(x)/sizeof(x[0]))
typedef unsigned int ui;

static void swap(ui *A, ui l, ui r) 
{
	ui tmp = A[l];
	A[l] = A[r];
	A[r] = tmp;
}

static int parition(ui *A, ui l, ui r)
{
	ui pivot = A[l];
	ui i = l;
	ui j = r;

	printf ("Pivot: %d\n", pivot);
	
	while (i < j){

		while(A[i] <= pivot /*&& i < r*/) {
			i++;
		}
		while(A[j] >= pivot /*&& j > l*/) {
			j--;
		}
		if(i < j) {
			swap (A, i, j);
		}
	}
	A[l] = A[j];
	A[j] = pivot;
	return j;
}

static void quick(ui *A, ui l, ui r)
{
	ui i;

	if(l < r) {
		ui p = parition(A, l, r);
		/* P is in the right place 
		so send (l, p-1) and (p+1, r)
		for further sorting.
		*/
		quick(A,l,p-1);
		quick(A,p+1,r);		
	}
}

int main()
{
	ui A[] = {5,9,1,3,6,12,2,4};
	ui i;

	quick (A, 0, A_LEN(A));
	for(i=0; i<A_LEN(A); i++) {
		printf("%d, ", A[i]);
	}
}

