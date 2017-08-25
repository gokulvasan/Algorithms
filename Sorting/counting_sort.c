#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* counting_sort(int *a, int cnt, int range)
{
	int *k = malloc(sizeof(int) * range+1);
	int *t = malloc(sizeof(int) * cnt);
	int i;
	
	memset(k, 0x00, sizeof(int)*range+1);

	for(i=0; i<cnt; i++) {
		k[a[i]]++;
	}

	for(i=1; i<range+1; i++) {
		k[i] += k[i-1];
	}

	for(i=cnt-1; i >= 0; i--) {

		t[ k[a[i]]-1 ] = a[i];
		k[a[i]]--;
	}

	return t;
}

int main()
{
	int a[] = {1, 2, 1, 1, 3, 3, 3, 2, 2, 2, 4, 3, 5};
	int *g;
	int i;

	g = counting_sort(a, sizeof(a)/sizeof(a[0]), 5);

	for(i=0; i < (sizeof(a)/sizeof(a[0])); i++) {
		printf("%d ", g[i]);
	}

	printf("\n");
}
