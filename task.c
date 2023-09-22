#include "main.h"

/**
 * main - Entry point
 * @ac: args count
 * @av: args
 * @env: environment
 *
 * Return: 0 on success, -1 on failure
 */
int main(int ac, char **av, char *env[])
{
	int is_interact = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)),
		status, len;
	size_t buf_size = 0;
	pid_t pid;
	char *args[] = { "", NULL}, *command, *buffer = NULL;

	UNUSED(av);
	UNUSED(ac);
	while (1)
	{
		command = malloc(BUFFER_SIZE);
		if (command == NULL)
			return (-1);
		if (is_interact)
			printf("$ "); /* Display the prompt */
		fflush(stdout);
		if (getline(&buffer, &buf_size, stdin) == -1)
		{
			free(command);
			break; /* Handle Ctrl+D (End of file) */
		}
		len = _strlen(buffer);
		if (buffer[len - 1] == '\n')
			buffer[len - 1] = '\0';
		command = removeSpaces(buffer);
		pid = fork();  /* Fork a new process */
		if (pid == 0)
		{
			args[0] = command;
			if (execve(command, args, env) == -1)
			{
				perror("./shell");
				exit(1);
			}
		}
		else if (pid > 0)
			waitpid(pid, &status, 0); /* Wait for the child process to complete */
		else
		{
			perror("Fork failed");
			free(command);
		}
		free(command);
	}
	return (0);
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
