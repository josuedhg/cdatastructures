#include <stdlib.h>

extern char *infix_to_postfix(char *);

int main(void)
{
	char *infix1 = "2+3";
	char *infix2 = "3*(1+2)-5";
	char *postfix1 = infix_to_postfix(infix1);
	char *postfix2 = infix_to_postfix(infix2);

	printf("infix %s = postfix %s \n", infix1, postfix1);
	printf("infix %s = postfix %s \n", infix2, postfix2);
	free(postfix1);
	free(postfix2);
	return 0;
}
