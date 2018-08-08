#include <stdio.h>
#include <stdlib.h>

void repeated_element(int A[], int n)
{
	int i = 0;
	int *a = calloc(sizeof(int),  n);
	while(i < n) {
		if(!a[A[i]])
			a[A[i]] = 1;
		else
			printf("%d\n", A[i]); 
		i++;
	}
}

int main() {
	int A[] = {1,2,1,3,3,4};
	int size = sizeof(A)/sizeof(A[0]);

	repeated_element(A, size);
}
