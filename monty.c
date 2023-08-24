#include "monty.h"
#include <stdio.h>

/**
 * exec_in - Executes the appropriate instruction function
 * @opcode: The opcode to execute
 * @argument: The argument for the instruction
 * @stack: Pointer to the stack
 * @line_number: The current line number in the file
 * Return: 1 if successful, 0 if opcode not found
 */
int exec_in(char *opcode, char *argument, stack_t **stack, int line_number)
{
	size_t i;
	instruction_t instructions[] = {
		{"push", push},
		{"pop", pop},
		{"pall", pall},
		{"pint", pint},
		{"swap", swap},
		{"nop", nop},
		{"add", op_add},
		{"sub", op_sub},
		{"div", op_div},
		{"mul", op_mul},
		{"mod", op_mod},
		{NULL, NULL}
	};

	for (i = 0; instructions[i].opcode; i++)
	{
		if (strcmp(instructions[i].opcode, opcode) == 0)
		{
			instructions[i].f(stack, atoi(argument));
			return (1);
		}
	}

	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
	return (0);
}
/**
 * print_usage_and_exit - Prints usage message and exits with failure status
 * @program_name: The name of the program
 */
void print_usage_and_exit(const char *program_name)
{
	fprintf(stderr, "Usage: %s <monty> <file>\n", program_name);
	exit(EXIT_FAILURE);
}

/**
 * open_file - Opens a file and returns the file pointer
 * @filename: The name of the file to open
 * @mode: The mode in which to open the file
 * Return: The file pointer or NULL on failure
 */
FILE *open_file(const char *filename, const char *mode)
{
	FILE *file = fopen(filename, mode);

	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	return (file);
}

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: arguments
 * Return: Success or Fail
 */
int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack;
	char *line;
	int line_number;
	char opcode[32];
	char argument[64];

	if (argc != 3)
		print_usage_and_exit(argv[0]);
	file = open_file(argv[2], "r");
	stack = NULL;
	line = NULL;
	line_number = 0;

	while (getline(&line, NULL, file) != -1)
	{
		line_number++;
		if (sscanf(line, "%31s %63s", opcode, argument) != 2)
			handle_invalid_format(file, line, &stack);
		if (!exec_in(opcode, argument, &stack, line_number))
			handle_execution_error(file, line, &stack); }

	fclose(file);
	free(line);
	while (stack)
	{
		stack_t *temp = stack;

		stack = stack->next;
		free(temp);
	}
	return (EXIT_SUCCESS);
}
