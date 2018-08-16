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
typedef void (*what_to_do) (u32 *bit_vector, signed int lsb, void *data);

void print_bit_vector (u32 *bit_vector, signed int lsb, void *str1)
{
	int i = lsb-1;
	u32 k = 1;
	char *str = (char*)str1;

	printf("%d ==>", *bit_vector);
	do {
		k = 1 << i ;
		if( ((*bit_vector) & (1 << i)) > 0 )
			printf("%c", str[i]);
		i--;
	} while(i >= 0);

	printf("\n");
}

typedef struct subsetSum {
	u32 *arr;
	u32 sum;
	u32 len;
}ss;

void check_subset_sum (u32 *bit_vector, signed int lsb, void *subset1)
{
	ss *s = (ss*)subset1;
	int i = lsb-1;
	u32 k = 1;
	u32 sum = 0;
 
	do {
		k = 1 << i ;
		if( ((*bit_vector) & (1 << i)) > 0 )
			sum += s->arr[i];			
		i--;
	} while(i >= 0);

	if(sum == s->sum) {
		k = 1;
		i = 0;
		
		printf("{");
		do {
			k = 1 << i ;
			if( ((*bit_vector) & (1 << i)) > 0 )
				printf("%u, ", s->arr[i]);
			i++;
		} while(i <= lsb-1);
		printf("}");
	}
	printf("\n");

}
#define set_bit(B, p)  ((*B) = ((*B) | (1 << p)))
#define uset_bit(B, p) ((*B) = ((*B) & ~(1 << p)))


void binary (u32 *bit_vector, signed int pos, signed int cnt, what_to_do w,void *ip)
{
	if(pos < 0) {
		w(bit_vector, cnt, ip);
		return;
	}

	/* Represent the possible combinations with current pos 0 */	
	binary (bit_vector, pos-1, cnt, w, ip);

	/* Represent the possible combinations with current pos 1 */	
	set_bit(bit_vector, pos);
	binary (bit_vector, pos-1, cnt, w, ip);
	uset_bit(bit_vector, pos);

	return;	
}

void subset_sum(u32 *arr, u32 len, u32 sum)
{
	ss s = {arr, sum, len};
	u32 bit_vector = 0;

	
	binary(&bit_vector, len-1, len, check_subset_sum, &s);
	return;	
}
void combinate (char *str, const int len)
{
	u32 bit_vector = 0;

	binary(&bit_vector, len-1, len, print_bit_vector, str);
}


#define A(x) ((sizeof(x))/(sizeof(x[0])))

int main()
{
	char ex[25] = "abc";
	int len = 0;
	u32 bv = 0;
	u32 arr[]={1,2,3,1,1,0};
	int arr_len = A(arr);
	
	len = strlen(ex);

//	printf("%d %s\n", len, ex);
//	permute(ex, 0, len);
//	printf("%d %s\n", len, ex);

//	binary(&bv, 4, 5);
//	combinate(ex, len);
	
	subset_sum(arr, arr_len, 3);	
	return 0;
}

