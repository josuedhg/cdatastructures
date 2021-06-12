#include <math.h>
#include <string.h>

#include <array_stack.h>


static int is_operator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

static int is_operand(char c)
{
	return c <= '9' && c >= '0';
}

static int operate(int operand_l, int operand_r, char operator)
{
	int result = 0;
	switch(operator) {
		case '+':
			result = operand_l + operand_r;
			break;
		case '-':
			result = operand_l - operand_r;
			break;
		case '*':
			result = operand_l * operand_r;
			break;
		case '/':
			result = operand_l / operand_r;
			break;
	}
	return result;
}

int postfix_eval(char *postfix)
{
	struct array_stack *operands = array_stack_init(strlen(postfix));
	int final_result = 0;
	while(*postfix) {
		char c = *(postfix++);
		if (is_operand(c)) {
			int val = c - '0';
			array_stack_push(operands, (void *)val);
		}
		else if (is_operator(c)) {
			int operand2 = array_stack_pop(operands);
			int operand1 = array_stack_pop(operands);
			int result = operate(operand1, operand2, c);
			array_stack_push(operands, result);
		}
	}
	final_result = (int) array_stack_pop(operands);
	array_stack_free(&operands);
	return final_result;
}
