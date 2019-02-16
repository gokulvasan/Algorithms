#include <stdio.h>
#include <stdlib.h>

typedef unsigned int ui;
#define ARR_LEN(x) (sizeof(x)/sizeof(x[0]))

static void swap(ui *A, ui i, ui j)
{
	ui tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

static void selection(ui *A, ui len)
{
	ui i;

	for(i=1; i < len; i++) {

		ui tmp = A[i];
		int j;

		for(j=i-1; j >= 0; j--) {

			if(A[j] < tmp) {
				break;
			}
			A[j+1] = A[j];
			A[j] = tmp;
		}
	}
}

int main(){
	ui A[] = {3,5,7,1,4,0,12,24,20};
	ui i;

	selection(A, ARR_LEN(A));
	
	for(i=0; i<ARR_LEN(A); i++) {
		printf("%d, ", A[i]);
	}
	printf("\n");
}
