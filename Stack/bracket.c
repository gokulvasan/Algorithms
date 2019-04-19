#include "stack.h"
#include <stdio.h>

#define O_SQ_BRAC '['
#define O_CUR_BRAC '{'
#define O_BRAC	'('


#define C_SQ_BRAC ']'
#define C_CUR_BRAC '}'
#define C_BRAC	')'

/* 
 * return 0 if balanced, return -1 if error
 *
 */
int bracket_balanced (char *str)
{
	char t;
	int ret = 1;

	while(*str) {

		if ((O_SQ_BRAC == *str) ||
		(O_CUR_BRAC == *str) ||
		(O_BRAC == *str)) {
			
			push(*str);
		}
		else if ((C_SQ_BRAC == *str) ||
			(C_CUR_BRAC == *str) ||
			(C_BRAC == *str)) {
			
			t = pop();
			if (C_SQ_BRAC == *str) {
				if(O_SQ_BRAC != t) {
					break;
				}
			}
			else if(C_CUR_BRAC == *str) {
				if(O_CUR_BRAC != t) {
					break;
				}
			}
			else if(C_BRAC == *str) {
				if(O_BRAC != t) {
					break;
				}
			}
		}
		*str++;
	}
	if(!(*str) && (pop() < 0))
		ret = 0;

	return ret;
}

int main(int argc, char *argv[]) 
{
	if(argc < 2) {
		printf("Provide bracketed input\n");
		return -1;
	}

	if(bracket_balanced(argv[1])) {
		printf("Bracket is not balanced\n");
	}
	else {
		printf("All is OK\n");
	}

	return 0;
}
