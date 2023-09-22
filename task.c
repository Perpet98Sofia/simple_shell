#include "main.h"

int main(void)
{
	int is_interact = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
	int status;
    size_t buf_size = 0, command_length;
	pid_t pid = fork();  /* Fork a new process */
	char *args[] = { "", NULL}, *command = NULL;

    while (1)
    {
        if (is_interact)
            printf("$ "); /* Display the prompt */
        fflush(stdout);

        if (getline(&command, &buf_size, stdin) == -1)
            break; /* Handle Ctrl+D (End of file) */
		command_length = strlen(command);
        if (command[command_length - 1] == '\n')
            command[command_length - 1] = '\0';
		command = removeSpaces(command);

        if (pid == 0)
        {
            args[0] = command;
            execve(command, args, NULL);
            perror("./shell");
            exit(1);
        }
        else if (pid > 0)
            waitpid(pid, &status, 0); /* Wait for the child process to complete */
        else
            perror("Fork failed");
    }

    return 0;
}

/**
 * execute - executes command
 * @command: command to execute
 *
 * Return: 0 for success, -1 for failure
 */
int execute(data_shell command)
{
	int status, found = 0;
	char *exec;

	if (access(command.args[0], X_OK) == 0)
		found = 1;
	else
	{
		exec = find_executable(command.args[0], command._environ);
		if (exec)
		{
			found = 1;
			command.args[0] = _strdup(exec);
		}
	}
	if (found == 1)
	{
		command.pid = fork(); /* Fork a new process */
		if (command.pid == 0)
		{
			command.status = 0;
			return (execve(command.args[0], command.args, command._environ));
		}
		else if (command.pid > 0) /* Wait for the child process to complete */
		{
			waitpid(command.pid, &status, 0);
			command.status = WEXITSTATUS(status);
		}
		else
			perror("./hsh: 0");
	}
	else
	{
		command.status = 127;
		get_error(command.args, command.status, command.counter);
	}
	return (0);
}

/**
 * trim - Trim a string
 * @str: the string
 *
 * Return: void
 */
char *trim(char *str)
{
    int start = 0, end = _strlen(str) - 1, i, j = 0;
    char *trimmed;

    trimmed = malloc(_strlen(str) + 1);
    if (trimmed == NULL)
        return (NULL);
    while (str[start] == ' ')
        start++;
    while (end >= start && (str[end] == ' ' || str[end] == '\n'))
        end--;

    for (i = start; i <= end; i++)
        trimmed[j++] = str[i];
    trimmed[j] = '\0';

    return (trimmed);
}
