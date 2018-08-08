#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char A[] = "Hello";
char B[] = "Hello";


bool subseq_test(char *a, char *b)
{
	while(*a != '\0' && *b != '\0') {
		if(*a == *b)
			a++;
		b++; 
	}
	if(*a != '\0')
		return false;

	return true;
}

int main() {

	printf("%d\n", subseq_test(A, B));
}
