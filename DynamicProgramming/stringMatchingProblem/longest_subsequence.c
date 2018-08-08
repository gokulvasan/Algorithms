#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
	idea: on every character in A search B.
		if(A[n] is found in B)
			go to next element in A and B.
		else 
			n+1 and search B.

	Complexity: 	length of A : N.
			length of B : M.
			
			so run time: O( N * M )
			if( M == N ) 2 ^ N. 
*/

int lcs(char *A, char *B)
{
	char *t = B;

	if(*A == '\0')
		return 0;

	while(*t != '\0') {
		if(*A == *t) {
			printf("%c", *A);
			return 1 + lcs(A+1, t+1);
		}
		t++;
	}
	return lcs(A+1, B);
}

/*		
			__
			|  1 + lcs_r(A+1, B+1)	
	lcr_r(A, B) = 	|
			|  MAX[ lcs_r(A+1, B), lcs_r(A, B+1) ]
			--

			[OR]

	lcs_r(A, B) =  __
		       | 	1 + lcs_r(A-1, B-1)
		       |	MAX[ lcs_r(A-1, B), lcs_r(A, B-i) ]
		       ---	
*/
#define MAX(A, B) (((A)>(B)) ? (A) : (B))
int lcs_r(char *A, char *B)
{
	if((*A == '\0') || (*B == '\0'))
		return 0;

	if(*A == *B) {
		printf("%c", *A);
		return 1+lcs_r(A+1, B+1);
	}
	return MAX(lcs_r(A+1, B), lcs_r(A, B+1));
}

/*
	Dynamic programming
					
*/
int arr[50][50];
void print(int alen,int blen)
{
	int i, j;

	for(i=0; i < blen; i++) {
		printf("[");
		for(j=0; j < alen; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("]\n");
	}
}

void lcs_d(char *A, char *B,int alen, int blen)
{
	int i, j;

	for(i=0; i <= blen; i++) {
		for(j=0; j <= alen; j++) {

			if(i==0 || j==0) {
				continue;
			}

			if(A[j-1] == B[i-1]) {
				arr[i][j] = 1 + arr[i-1][j-1];
			}
			else {
				arr[i][j] = MAX(arr[i-1][j], arr[i][j-1]);
			}
		}
	}
}

#define ARR(X) ((sizeof(X))/(sizeof(X[0])))

char A[] = "Hiot";
char B[] = "abHcdeot";
int main()
{
	memset(arr, 0x00, sizeof(arr) );
	lcs_d(A, B, ARR(A), ARR(B));
	print(ARR(A), ARR(B));
	return 0;
}
