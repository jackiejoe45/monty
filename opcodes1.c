#include "monty.h"

/**
 * push - pushes an element onto the stack
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void push(stack_t **stack, unsigned int line_number)
{
	if (line_number == 0)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	stack_t *new_node = malloc(sizeof(stack_t));

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = atoi(line_number);
	new_node->prev = NULL;
	new_node->next = *stack;
	if (*stack)
		(*stack)->prev = new_node;
	*stack = new_node;
}


/**
 * pall - prints all elements in the stack
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void pall(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
	stack_t *current = *stack;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * pint - prints the value at the top of the stack
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack)
	{
		printf("%d\n", (*stack)->n);
	} else
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
}


/**
 * pop - removes the top element of the stack
 * @stack: pointer to the stack
 * @line_number: line number where the opcode appears
 */
void pop(stack_t **stack, unsigned int line_number)
{
	if (*stack)
	{
		stack_t *temp = *stack;
		*stack = (*stack)->next;
		if (*stack)
			(*stack)->prev = NULL;
		free(temp);
	} else
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
}
