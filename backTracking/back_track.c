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

void combinate(char *c, const int len)
{
	int curr_len = 1;

	while(curr_len <= len) {
		;
	}
}

int main()
{
	char ex[25] = "world";
	int len = 0;

	len = strlen(ex);

	printf("%d %s\n", len, ex);
	permute(ex, 0, len);
	printf("%d %s\n", len, ex);
	
	return 0;
}
