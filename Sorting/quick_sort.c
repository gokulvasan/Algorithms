#include <stdio.h>
#include <stdlib.h>
#define ARR_LEN(x) ((sizeof(x))/(sizeof(x[0])))

void print(int *A, int len)
{
	int i = 0;
	while(i < len) {
		printf("%d, ", A[i]);
		i++;
	}
	printf("\n");
}


void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t; 
}

int split(int *A, int lo, int hi)
{
	int i = lo-1;
	int j = lo;

	swap(&A[lo], &A[hi]);

	while(j < hi) {
		if(A[j] < A[hi]) {
			i++;
			swap(&A[j], &A[i]);
		}
		j++;
	}
	i++;
	if(i < hi)
		swap(&A[i], &A[hi]);

	return i;
}

void quick_sort(int *A, int lo, int hi) 
{
	int sp;

	if(lo >= hi)
		return;

	sp = split(A, lo, hi);
	quick_sort(A, lo, sp);
	quick_sort(A, sp+1, hi); 	
}

int main()
{
	int A[] = {5, 6, 2, 9, 18, 23, 3, 1, 90, 12};
	print(A, ARR_LEN(A));
	quick_sort(A, 0, ARR_LEN(A)-1);
	print(A, ARR_LEN(A));
}
