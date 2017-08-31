#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int num = 5689;

	while(num) {
		num = num/10;
		printf("%d\n", num);
	}
}
