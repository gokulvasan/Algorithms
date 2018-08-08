#include <stdio.h>
#include <string.h>

void swap (char *a, char *b)
{
	char t = *a;

	*a = *b;
	*b = t;
}

void permute (char *c, const int pos, const int len)
{
	int curr_pos = pos;
	int nxt = pos + 1;

	if(len <= pos) {
		printf("%s\n", c);
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

int main()
{
	char ex[25] = "pal";
	int len = 0;

	len = strlen(ex);

	printf("%d %s\n", len, ex);
	permute(ex, 0, len);
	printf("%d %s\n", len, ex);
	
	return 0;
}
