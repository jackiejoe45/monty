#include "monty.h"
/**
 * handle_execution_error - Handles execution errors
 * @file: File pointer
 * @line: Line content
 * @stack: Stack pointer
 */
void handle_execution_error(FILE *file, char *line, stack_t **stack)
{
	fclose(file);
	free(line);
	while (*stack)
	{
		stack_t *temp = *stack;
		*stack = (*stack)->next;
		free(temp);
	}
	exit(EXIT_FAILURE);
}

/**
 * handle_invalid_format - Handles invalid format errors
 * @file: File pointer
 * @line: Line content
 * @stack: Stack pointer
 */
void handle_invalid_format(FILE *file, char *line, stack_t **stack)
{
	fprintf(stderr, "Invalid format on line: %s", line);
	handle_execution_error(file, line, stack);
}
