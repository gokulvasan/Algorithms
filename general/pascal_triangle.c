#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(int *a, int i) 
{
	int c;
	printf("[");
	for(c=0; c <= i; c++) {
		printf("%d, ", a[c]);
	}
	printf("]\n");
}

void pascal_triangle(int n)
{
	int **a;
	int i, j;

	a = (int **)malloc(sizeof(a) * (n + 1));
	for(i = 0; i<=n; i++) {
		a[i] = (int *)malloc(sizeof(int) * (n+1));
	}

	for(i=0; i<=n; i++) {

		a[i][0] = 1;
		a[i][i] = 1;

		for(j = 1; j < i; j++) {
			a[i][j] = a[i-1][j-1] + a[i-1][j];	
		}

		print(a[i], j);
	}
}

int main()
{
	pascal_triangle(6);

}
