#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fibonacci(int n, int *arr)
{
	int val;
	
	printf("%d\n", n);

	if(!arr) {
		arr = malloc(sizeof(int) * n);
		memset(arr, 0x00, sizeof(int)*n);
	}

	if(n <= 0)
		return 0;
	if(n == 1)
		return 1;

	if(arr[n])
		return arr[n];

	arr[n] = fibonacci(n-1, arr) + fibonacci(n-2, arr);

	return arr[n];
}

int main()
{
	int *arr = NULL;

	printf("fib: 7 is %d", fibonacci(7, arr));
}
