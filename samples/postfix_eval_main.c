#include <stdio.h>

extern int postfix_eval(char*);

void report(char *expresion, int result)
{
	printf("expression %s = %d \n", expresion, result);
}

int main(void)
{
	char *postfix1 = "23+";
	int result1 = 0;
	char *postfix2 = "32*41-+";
	int result2 = 0;
	result1 = postfix_eval(postfix1);
	result2 = postfix_eval(postfix2);
	report(postfix1, result1);
	report(postfix2, result2);
	return 0;
}
