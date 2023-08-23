#include "monty.h"
/**
 * op_div - divides the second top element of the stack by the top element
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void op_div(stack_t **stack, unsigned int line_number)
{
	if (*stack && (*stack)->next)
	{
		if ((*stack)->n == 0)
		{
			fprintf(stderr, "L%d: division by zero\n", line_number);
			exit(EXIT_FAILURE);
		}
		(*stack)->next->n /= (*stack)->n;
		pop(stack, line_number);
	} else
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
}

/**
 * op_mul - multiplies the top two elements of the stack
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void op_mul(stack_t **stack, unsigned int line_number)
{
	if (*stack && (*stack)->next)
	{
		(*stack)->next->n *= (*stack)->n;
		pop(stack, line_number);
	} else
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
}

/**
 * op_mod - computes the modulus of the second top element by the top element
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void op_mod(stack_t **stack, unsigned int line_number)
{
	if (*stack && (*stack)->next)
	{
		if ((*stack)->n == 0)
		{
			fprintf(stderr, "L%d: division by zero\n", line_number);
			exit(EXIT_FAILURE);
		}
		(*stack)->next->n %= (*stack)->n;
		pop(stack, line_number);
	} else
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
}

