#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Pascal Triangle:
 *			  1
 *		        1   1
 *		      1   2   1
 *		    1   3   3   1
 *                1   4   6   4   1
 *              1   5   10  10  5   1
 *
 *
 *			[OR]
 *
 *       		     n!
 *  			------------
 *  			(n-r)! . r!
 *
 *
 */

int c(int n, int r, int **t)
{
	if(n==r)
		return 1;
	if(0==r)
		return 1;

	if(t[n][r])
		return t[n][r];

	t[n][r] = c(n-1, r-1, t) + c(n-1, r, t);
	return t[n][r];
}

int C(int n, int r)
{
	int **t;
	int i;

	t = (int **)malloc(sizeof(t) * (n+1));
	for(i=0; i<=n; i++) {
		t[i] = (int *)malloc(sizeof(int) * (n+1));
		memset(t[i], 0x00, sizeof(int) * (n+1));
	}

	return c(n, r, t);
}

int main()
{

	printf("C(7,5): %d\n", C(7,5));
}
