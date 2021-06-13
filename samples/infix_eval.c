#include <stdio.h>
#include <stdlib.h>

extern char *infix_to_postfix(char *);
extern int postfix_eval(char *);

static int infix_eval(char *infix)
{
	int result = 0;
	char *postfix = infix_to_postfix(infix);
	result = postfix_eval(postfix);
	free(postfix);
	return result;
}

int main(void)
{
	char *infix1 = "1+2";
	int result1 = infix_eval(infix1);
	char *infix2 = "2*(3+1)";
	int result2 = infix_eval(infix2);
	printf("expression %s = %d \n", infix1, result1);
	printf("expression %s = %d \n", infix2, result2);
	return 0;
}
