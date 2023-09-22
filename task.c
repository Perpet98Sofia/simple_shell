#include "main.h"

/**
 * main - Entry point
 * @ac: Args count
 * @av: Args
 * @env: Environment
 *
 * Return: 0 on success, -1 on failure
 */
int main(int ac, char **av, char *env[])
{
	int is_interact = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)), status;
	size_t buf_size = 0;
	pid_t pid;
	char *args[] = {"", NULL}, *command, *buffer = NULL;

	UNUSED(av);
	UNUSED(ac);
	while (1)
	{
		if (is_interact)
			printf("$ "), fflush(stdout);
		if (getline(&buffer, &buf_size, stdin) == -1)
			break;
		if (buffer[0] != '\n')
		{
			if (buffer[strlen(buffer) - 1] == '\n')
				buffer[strlen(buffer) - 1] = '\0';
			command = removeSpaces(buffer);
			if (strlen(command) > 0)
			{
				pid = fork();
				if (pid == 0)
				{
					args[0] = command;
					if (execve(command, args, env) == -1)
					{
                        free(command);
						perror("./shell");
						exit(1);
					}
				}
				else if (pid > 0)
					waitpid(pid, &status, 0);
				else
					perror("Fork failed");
				free(command);
			}
			free(command);
		}
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
