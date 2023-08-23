#include "monty.h"
/**
*
  *
  */
int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack;
	char *line;
	size_t i;
	int found;
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
	int line_number = 0; 
	/* size_t line_size = 0; */ 
	char opcode[32];
        char argument[64];

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <monty> <file>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	file = fopen(argv[2], "r");

	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[2]);
		return (EXIT_FAILURE);
	}

	stack = NULL;
	line = NULL;

	while (fgets(line, sizeof(line), file))
	{
		line_number++;

		sscanf(line, "%31s %63s", opcode, argument);

		found = 0;
		for (i = 0; instructions[i].opcode; i++)
		{
			if (strcmp(instructions[i].opcode, opcode) == 0)
			{
				instructions[i].f(&stack, atoi(argument)); 
				found = 1;
				break;
			}
		}

		if (!found)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			fclose(file);
			free(line);
			return (EXIT_FAILURE);
		}

		if (stack == NULL) 
		{ 
			fprintf(stderr, "Error: malloc failed\n");
			fclose(file); 
			free(line);
			return (EXIT_FAILURE);
		}
	}

	fclose(file);
	free(line);

	while (stack != NULL)
	{
		stack_t *temp = stack;
		stack = stack->next;
		free(temp);
	}
	return (EXIT_SUCCESS);
}

