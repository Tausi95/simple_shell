#include "main.h"

/**
 * prompt - Display the shell prompt to the user.
 *
 * This function prints the shell prompt ":) " and flushes
 * the output to make sure the prompt is displayed to the user.
 */
void prompt(void)
{
	printf(":) ");
	fflush(stdout);
}

/**
 * execute - Execute a command with arguments using execve.
 * @command: The command line entered by the user.
 *
 * This function takes a command line as input and splits it into tokens
 * using space as the delimiter. The tokens are stored in an array `args`.
 * The command is then executed using execve. If the command doesn't exist
 * in the current directory, the function will try to find the command in
 * the directories listed in the PATH environment variable. If execve fails,
 * it prints an error message using perror().
 *
 * Return: This function does not return anything. The child process
 * will be replaced with the new program if execve is successful.
 */
void execute(char *command)
{
	char *args[MAX_COMMAND_LENGTH];
	char *token;
	char *path;
	char *dirs[MAX_COMMAND_LENGTH];
	int i = 0, num_dirs = 0;

	token = strtok(command, " "); /* Split the command into tokens using space as delimiter */

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}

	args[i] = NULL; /* The last element of args should be NULL */

	if (access(args[0], X_OK) == 0)
	{
        /* Command is available in the current directory or with an absolute path */
		if (execve(args[0], args, environ) == -1)
		{
			perror(":)");
		}
	}
	else
	{
	/* Command not found in the current directory, try to find it in PATH */
		path = getenv("PATH");

		token = strtok(path, ":");
		while (token != NULL)
		{
			dirs[num_dirs++] = token;
			token = strtok(NULL, ":");
		}
		for (i = 0; 1 < num_dirs; i++)
		{
			cmd_path[MAX_COMMAND_LENGTH];
			snprintf(cmd_path, sizeof(cmd_path), "%s/%s", dirs[i], args[0]);
	

			if (access(cmd_path, X_OK) == 0)
			{
			/* Found the command in one of the directories in PATH */
				if (execve(cmd_path, args, environ) == -1)
				{
					perror(":)");
				}
				break;
			}
		}

	        /* Command not found in PATH */
		printf(":) %s: command not found\n", args[0]);
	}

}

/**
 * main - Entry point of the simple shell.
 *
 * This function implements a simple UNIX command line interpreter. It displays
 * a prompt to the user and waits for a command to be entered. The command is
 * then executed using the execute() function. The command lines can include
 * arguments separated by spaces. The shell handles errors and the "end of file"
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

		if (strcmp(command, "exit") == 0)
		{
		/* Handle exit command to exit the shell */
			printf("Exiting the shell...\n");
			break;
		}

		execute(command);
	}
	return (0);
}
