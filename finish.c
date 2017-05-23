#include "monty.h"

/**
 * free_stack - frees all malloc'd in stack
 *
 * Return: void
 */
void free_stack(void)
{
	stack_t *temp;
	stack_t *head;

	if (inventory->stack)
	{
		head = inventory->stack;

		while (head)
		{
			temp = head->next;
			free(head);
			head = temp;
		}
	}
}

/**
 * free_all - frees all malloc'd memory
 *
 * Return: void
 */
void free_all(void)
{
	if (inventory != NULL)
	{
		if (inventory->line != NULL)
			free(inventory->line);
		if (inventory->input != NULL)
			free(inventory->input);
		free_stack();
		free(inventory);
	}
}

/**
 * find_error - finds error message
 * @error: the error message
 *
 * Return: int of error message
 */
int find_error(char *error)
{
	char *flags[] = {
		"malloc fail", "usage file",
		"can't open file", "unknown instruction",
		"push integer", "can't pint", "can't pop", "can't swap",
		"can't add", "can't sub", "can't div", "div by 0", "can't mul",
		NULL
	};
	int e = 0;

	while (flags[e] != NULL)
		if (strcmp(error, flags[e]) != 0)
			e++;
		else
			break;
	return (e);
}

/**
 * handle_errors - function to handle all errors
 *
 * Return: void
 */
void handle_errors(char *error)
{
	int e;
	unsigned int n;
	char *errors[] = {
		"Error: malloc failed\n", "USAGE: monty file\n",
		NULL, NULL,
		"usage: push integer\n", "can't pint, stack empty\n",
		"can't pop an empty stack\n", "can't swap, stack too short\n",
		"can't add, stack too short\n", "can't sub, stack too short\n",
		"can't div, stack too short\n", "division by zero\n",
		"can't mul, stack too short\n"
	};

	e = find_error(error);
	if (inventory)
		n = inventory->linenum;

	if (e <= 1)
		dprintf(STDERR_FILENO, "%s", errors[e]);
	else if (e == 2)
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n",
				inventory->filename);
	else if (e == 3)
		dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n", n,
				inventory->input[0]);
	else if (e >= 4)
		dprintf(STDERR_FILENO, "L%u: %s", n, errors[e]);

	free_all();
	exit(EXIT_FAILURE);
}
