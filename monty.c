#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <monty> <file>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	FILE *file = fopen(argv[2], "r");

	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[2]);
		return (EXIT_FAILURE);
	}

	stack_t *stack = NULL;


	instruction_t instructions[] = {
		{"push", push},
		{"pop", pop},
		{"pall", pall},
		{"pint", pint},
		{"swap", swap},
		{"nop", op_nop},
		{"add", op_add},
		{"sub", op_sub},
		{"div", op_div},
		{"mul", op_mul},
		{"mod", op_mod},
		{NULL, NULL}
	};

	char *line = NULL;
	size_t line_size = 0;
	ssize_t read;

	while ((read = getline(&line, &line_size, file)) != -1)
	{
		char *opcode = strtok(line, " \t\n");

		if (opcode == NULL || opcode[0] == '#')
		{
			continue;
		}

		int found = 0;

		for (size_t i = 0; instructions[i].opcode[0]; ++i)
		{
			if (strcmp(instructions[i].opcode, opcode) == 0)
			{
				char *arg = strtok(NULL, " \t\n");

				instructions[i].f(&stack, arg ? atoi(arg) : 0);
				found = 1;
				break;
			}
		}

		if (!found)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			fclose(file);
			return (EXIT_FAILURE);
		}
	}

	fclose(file);
	free(line);

	return (EXIT_SUCCESS);
}

