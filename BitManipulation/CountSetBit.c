/* An algorithm that iterates over a bit array with a complexity of O(N), 
 * where N is the number of bit set */

#include <stdio.h>
#include <stdlib.h>

unsigned int test_a_bit(unsigned int *x)
{
	unsigned int t = *x;
	unsigned int ret = 0;

	if(t) {
		/*
		 * Property: x-1 toggles the last set bit of a number
		 * Example: if x is binary 11, then x-1 is 10.
		 * so, x & ~(x-1) will extract the last set bit.
		 * i.e. if x is binary 1110, then x-1 will be 1101
		 * and ~(x-1) is 0010, so x & ~(x-1) is 0010.
		 */
		unsigned int j = t & ~(t-1); 

		if(j) {
			ret = 1;
		}
		/* Remove the last set bit from the bit array,
		 * To prepare for the next iteration.
		 */
		j = t ^ j;
		*x = j;
		ret = 1;
	}
	return ret;
}

int main()
{
	unsigned int tst = 223;
	unsigned int k = 0;

	while(test_a_bit(&tst)) {
		k++;
	}
	printf("%d\n", k);

	return 0;
}
