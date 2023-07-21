#include "main.h"

/**
 * prompt - Display the shell prompt to the user.
 *
 * This function prints the shell prompt "#alxdohardthings$ " and flushes
 * the output to make sure the prompt is displayed to the user.
 */
void prompt(void)
{
	printf("#alxdohardthings$ ");
	fflush(stdout);
}

/**
 * execute - Execute a command with arguments using execvp.
 * @command: The command line entered by the user.
 *
 * This function takes a command line as input and splits it into tokens
 * using space as the delimiter. The tokens are stored in an array `args`.
 * The command and its arguments are then passed to execvp to execute the
 * specified command with the provided arguments. If execvp fails, it
 * prints an error message using perror().
 *
 * Return: This function does not return anything. The child process
 * will be replaced with the new program if execvp is successful.
 */
void execute(char *command)
{
	char *args[MAX_COMMAND_LENGTH];
	char *token;
	int i = 0;

	/* Split the command into tokens using space as delimiter */
	token = strtok(command, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}

	args[i] = NULL; /* The last element of args should be NULL */

	if (execvp(args[0], args) == -1)
	{
		perror("./shell");
	}
}

/**
 * main - Entry point of the simple shell.
 *
 * This function implements a simple UNIX command line interpreter. It displays
 * a prompt to the user and waits for a command to be entered.
 * The command is then executed using the execute() function.
 * The command lines can include arguments separated by spaces.
 * The shell handles errors and the "end of file"
 * condition (Ctrl+D). To exit the shell, the user can use the "exit" command.
 *
 * Return: Always returns 0 to indicate successful completion.
 */
int main(void)
{
	size_t len;
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		prompt();

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			/* Handle Ctrl+D (EOF) */
			printf("\nExiting the shell...\n");
			break;
		}

		len = strlen(command);
		if (len > 0 && command[len - 1] == '\n')
		{
			/* Remove the newline character from the input */
			command[len - 1] = '\0';
		}

		execute(command);
	}

	return (0);
}
