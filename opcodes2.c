#include "monty.h"
/**
 * swap - swaps the top two elements of the stack
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (*stack && (*stack)->next)
	{
		temp = (*stack)->n;
		(*stack)->n = (*stack)->next->n;
		(*stack)->next->n = temp;
	} else
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
}

/**
 * op_add - adds the top two elements of the stack
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void op_add(stack_t **stack, unsigned int line_number)
{
	if (*stack && (*stack)->next)
	{
		(*stack)->next->n += (*stack)->n;
		pop(stack, line_number);
	} else
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
}

/**
 * nop - does nothing
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}


/**
 * op_sub - subtracts the top element from the second top element
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void op_sub(stack_t **stack, unsigned int line_number)
{
	if (*stack && (*stack)->next)
	{
		(*stack)->next->n -= (*stack)->n;
		pop(stack, line_number);
	} else
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
}
