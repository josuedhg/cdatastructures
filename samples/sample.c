#include <stdio.h>
#include <array_stack.h>

char get_open_bracket(char c)
{
	if (c == ')') return '(';
	if (c == ']') return '[';
	if (c == '}') return '{';
	return '\0';
}

char get_close_bracket(char c)
{
	if (c == '(') return ')';
	if (c == '[') return ']';
	if (c == '{') return '}';
	return '\0';
}

int is_open_bracket(char c)
{
	return c == '(' || c == '[' || c == '{';
}

int is_close_bracket(char c)
{
	return c == ')' || c == ']' || c == '}';
}

char bracket_evaluate(char *text)
{
	struct array_stack *stack = array_stack_init(10);
	char missing = '\0';
	while(*text) {
		char c = *(text++);
		if (is_open_bracket(c))
			array_stack_push(stack, (void *)c);
		else if (is_close_bracket(c)) {
			if (array_stack_empty(stack)) {
				missing = get_open_bracket(c);
				break;
			}
			if (c != get_close_bracket((char)array_stack_peek(stack))) {
				missing = get_close_bracket((char)array_stack_peek(stack));
				break;
			}
			array_stack_pop(stack);
		}
	}
	if (missing == '\0' && !array_stack_empty(stack))
		missing = get_close_bracket((char)array_stack_peek(stack));

	array_stack_free(&stack);
	return missing;
}

void print_report(char *expresion, char missing)
{
	if (missing != '\0')
		printf("%s has missing bracket %c\n", expresion, missing);
	else
		printf("%s has well formed\n", expresion);
}

int main(void)
{
	char *expresion1 = "{([])}";
	char missing1;
	char *expresion2 = "{([)]}";
	char missing2;
	char *expresion3 = "{([])";
	char missing3;
	missing1 = bracket_evaluate(expresion1);
	missing2 = bracket_evaluate(expresion2);
	missing3 = bracket_evaluate(expresion3);
	print_report(expresion1, missing1);
	print_report(expresion2, missing2);
	print_report(expresion3, missing3);

	return 0;
}
