#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Approach:
		a will be the scratch
		two buffers tbuf and tbuf
*/
int* msd_radix_sort(int *a, int cnt, int digit, int range)
{
	int *k = malloc(sizeof(int) * range+1);
	int *tbuf[2];
	int i, j;
	int loop = 0;
	int base = 1;

	for(i=0; i<2; i++) {
		tbuf[i] = malloc(sizeof(int) * cnt);
		memset(tbuf[i], 0x00, sizeof(int) * cnt);
	}
	for(i=digit-1; i>=0; i--) {

		memset(k, 0x00, sizeof(int)*range+1);	

		/// Accumulate count.
		for(j=0; j<cnt; j++) {
			int tmp = (a[j]/base) % 10;
			k[tmp+1]++;
		}

		/// cumulate count
		for(j=0; j<range; j++) {
			k[j+1] += k[j];
		}

		/// make tmp buf ready
		/*
		 * Be careful: Stability needs to be preserved.
		*/
		for(j=0; j<cnt; j++) {

			int tmp = k[(a[j]/base) % 10];
			tbuf[loop][tmp] = a[j];
			k[(a[j]/base) % 10]++;
		}

		for(j=0; j<cnt; j++){
			a[j] = tbuf[loop][j];
		}
	
		memset(tbuf[loop], 0x00, sizeof(int) * cnt);
		base = base * 10;
	}
	return a;
}

/*
	Approach:
		1. make k buffer cnt equals range
		2. use index of k to represent range
		3. increment k on looking at that value in a.
		4. now cumulate the value.
		5. use the index
*/
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
	int a[] = {111, 100, 123, 511, 523, 533, 403, 422, 412, 142, 324, 313, 235};
	int *g;
	int i;

	for(i=0; i < (sizeof(a)/sizeof(a[0])); i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n");

	g = msd_radix_sort(a, sizeof(a)/sizeof(a[0]), 3, 6);

	printf("After Sort:\n");
	for(i=0; i < (sizeof(a)/sizeof(a[0])); i++) {
		printf("%d ", g[i]);
	}
	printf("\n");
}
