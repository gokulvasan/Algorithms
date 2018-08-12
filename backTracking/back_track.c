#include <stdio.h>
#include <string.h>

static void swap (char *a, char *b)
{
	char t = *a;

	*a = *b;
	*b = t;
}

static void print(char *c, int len)
{
	int i = 0;

	while(i < len) {
		printf("%c", c[i]);
		i++;
	}

	printf("\n");
}
/*
 * Fundemental idea:
 *		keep track of the word in the right that we
 *		intend to use at the current position.
 *		Swap the same to the current position.
 *		send the nxt pos recursivly.
 *		Swap back the value.
 *		
 *
 */

void permute (char *c, const int pos, const int len)
{
	int curr_pos = pos;
	int nxt = pos + 1;

	if(len <= pos) {
		print(c, len);
		return;
	}

	while (curr_pos < len) {
		swap (&c[pos], &c[curr_pos]);
		permute (c, nxt, len);
		swap (&c[pos], &c[curr_pos]);
		curr_pos++;
	}

	return;
}

typedef unsigned int u32;

void print_bit_vector (u32 *bit_vector, signed int lsb, char *str)
{
	int i = lsb-1;
	u32 k = 1;

	printf("%d ==>", *bit_vector);
	do {
		k = 1 << i ;
		if( ((*bit_vector) & (1 << i)) > 0 )
			printf("%c", str[i]);
		i--;
	} while(i >= 0);

	printf("\n");
}

#define set_bit(B, p)  ((*B) = ((*B) | (1 << p)))
#define uset_bit(B, p) ((*B) = ((*B) & ~(1 << p)))

void binary (u32 *bit_vector, signed int pos, signed int cnt, char *str)
{
	if(pos < 0) {
		print_bit_vector(bit_vector, cnt, str);
		return;
	}

	/* Represent the possible combinations with current pos 0 */	
	binary (bit_vector, pos-1, cnt, str);

	/* Represent the possible combinations with current pos 1 */	
	set_bit(bit_vector, pos);
	binary (bit_vector, pos-1, cnt, str);
	uset_bit(bit_vector, pos);

	return;	
}

void combinate (char *str, const int len)
{
	u32 bit_vector = 0;

	binary(&bit_vector, len-1, len, str);		
}

int main()
{
	char ex[25] = "abc";
	int len = 0;
	u32 bv = 0;

	len = strlen(ex);

//	printf("%d %s\n", len, ex);
//	permute(ex, 0, len);
//	printf("%d %s\n", len, ex);

//	binary(&bv, 4, 5);
	combinate(ex, len);
	return 0;
}

