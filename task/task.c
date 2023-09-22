#include "main.h"

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @sig: Signal handler
 *
 * Return: void
 */
void get_sigint(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n\\_(^-^)_/\n", 12);
}

/**
 * main - Entry point
 * @ac: Arguments count
 * @av: Arguments
 * @env: Environment
 *
 * Return: Always 0
 */
int main(int ac, char **av, char *env[])
{
	size_t buf_size = 0;
	char *command = NULL;
	data_shell data;
	int is_interact = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)), k = 0;

	UNUSED(ac);
	set_data(&data, env);
	signal(SIGINT, get_sigint);
	while (1)
	{
		fflush(stdout);
		if (is_interact)
			print_string("$ "); /* Display the prompt */
		if (getline(&command, &buf_size, stdin) == -1)
		{
			if (feof(stdin))
				free(command);
			break; /* Handle Ctrl+D (End of file) */
		}
		if (_strlen(command) == 1)
			continue;
		data.input = _strdup(command);
		for (; k < MAX_ARGS; k++)
			data.av[k] = NULL;
		split_commands(&data, data.input);
		data.counter++;
	}
	free_data(&data);
	if (data.status < 0)
		return (255);
	return (data.status);
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
