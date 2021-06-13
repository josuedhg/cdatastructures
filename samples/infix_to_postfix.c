#include <stdlib.h>
#include <string.h>

#include <array_stack.h>

static int is_operand(char c)
{
	return c >= '0' && c <= '9';
}

static int is_operator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

static int precedence_value(char op)
{
	int value = 0;
	switch(op) {
		case '+':
		case '-':
			value = 1;
			break;
		case '*':
		case '/':
			value = 2;
			break;
	}
	return value;
}

static int precedence(char op1, char op2)
{
	if (op1 == '(' || op2 == '(')
		return 0;
	if (op2 == ')')
		return 1;
	return precedence_value(op2) - precedence_value(op1) < 0;
}

char *infix_to_postfix(char *infix)
{
	struct array_stack *operators = array_stack_init(strlen(infix));
	char *postfix = (char *)calloc(1, strlen(infix));
	char *postfix_pos = postfix;
	while (*infix) {
		char c = *(infix++);
		if (is_operand(c))
			*(postfix_pos++) = c;
		else if (is_operator(c)) {
			while(!array_stack_empty(operators) &&
					precedence((char)array_stack_peek(operators), c)) {
				*(postfix_pos++) = (char)array_stack_pop(operators);
			}
			if (c == ')')
				array_stack_pop(operators);
			else
				array_stack_push(operators, c);
		}
		else
			return NULL;
	}
	while(!array_stack_empty(operators))
		*(postfix_pos++) = (char)array_stack_pop(operators);
	return postfix;
}
