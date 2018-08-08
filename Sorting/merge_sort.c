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

void merge(int *A, int alo, int ahi, int blo, int bhi) 
{
	int tmp[15];
	int *t;
	int i = alo;
	int j = blo;
	int k = 0;
	int len;

//	printf("Alen: %d Blen:%d\n", ahi-alo, bhi-blo);
	while(i <= ahi && j <= bhi) {

		if(A[i] < A[j]) {
			tmp[k] = A[i];
			i++;
		}
		else {
			tmp[k] = A[j];
			j++;
		}
		k++;
	}

	while(i <= ahi) {
		tmp[k] = A[i];
		k++;
		i++;
	}

	while(j <= bhi) {
		tmp[k] = A[j];
		j++;
		k++;
	}	

	i = alo;
	j = 0;
	while(j < k) {
		A[i] = tmp[j];
		i++;
		j++;
	}
}

void merge_sort(int *A, int lo, int hi)
{
	int split;

	if(lo >= hi) {
		return;
	}

	split = (lo + hi)/2;
	printf("1st:%d %d 2nd:%d %d\n", lo, split, split+1, hi);
	merge_sort(A, lo, split);
	merge_sort(A, split+1, hi);
	merge(A,lo, split, split+1, hi);
}

int main()
{
	int A[] = {5, 6, 2, 9, 18, 23, 3, 1, 90, 12};
	print(A, ARR_LEN(A));
	merge_sort(A, 0, ARR_LEN(A)-1);
	print(A, ARR_LEN(A));
}
