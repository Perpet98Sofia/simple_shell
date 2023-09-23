#include "main.h"

/**
 * built_in_setenv - Function to set an environment variable
 *
 *@command: parameter used
 *Return: (0) otherwise (-1)
 */
int built_in_setenv(data_shell command)
{
	char **end_env = find_end_env(command._environ);
	char *varname = command.av[0], *value = command.av[1];
	char **var = command._environ, *new_var = NULL, *var_cpy = NULL;

	if (varname && value)
	{
		for (; var < end_env; var++)
		{
			var_cpy = extract(*var, 0, (int)strlen(varname) - 1);
			if (strcmp(var_cpy, varname) == 0)
			{
				*var = malloc(strlen(varname) + strlen(value) + 2);
				if (*var == NULL)
					return (-1);
				strcpy(*var, varname);
				strcat(*var, "=");
				strcat(*var, value);
				return (0);
			}
		}
		new_var = malloc(strlen(varname) + strlen(value) + 2);
		if (new_var == NULL)
			return (-1);
		_strcpy(new_var, varname);
		strcat(new_var, "=");
		strcat(new_var, value);
		*end_env = malloc(sizeof(char *) * (size_t)(sizeof(end_env) + 1));
		if (*end_env == NULL)
			return (-1);
		*end_env = strdup(new_var);
		end_env++;
		*end_env = NULL;
		return (0);
	}
	command.status = -1;
	get_error(command.args, command.status, command.counter);
	return (-1);
}

/**
 * _getenv - Function to get the value of an environment variable
 *@args: arguments used
 *@env: char**
 *Return: NULL
 */
char *_getenv(char *args, char *env[])
{
	char **var = env;

	/* Iterate over the environment variables until the end */
	for (; var < find_end_env(env); var++)
	{
		if (_strcmp(*env, args) == 0)
			return (*env + strlen(args) + 1);
	}

	free(var);

	return (NULL);
}

/**
 * find_end_env - Function to find the end of the environment variables
 *@environ: parameter used
 *
 * Return: (env_line)
 */
char **find_end_env(char *environ[])
{
	char **env_line = environ;

	while (*env_line)
		env_line++;

	return (env_line);
}

/**
 * builtin_env - env built-in
 * @command: command
 *
 * Return: Always 0
 */
int builtin_env(data_shell command)
{
	int i;

	for (i = 0; command._environ[i]; i++)
	{
		print_string(command._environ[i]);
		print_string("\n");
	}

	return (0);
}

/**
 * built_in_unsetenv - Function to unset an environment variable
 * @command: command
 * Return: int
 */
int built_in_unsetenv(data_shell command)
{
	char **envp = command._environ, *var, *name, *value;

	while (*envp)
	{
		name = *envp;
		value = name + strlen(name) + 1;
		var = extract(*envp, 0, (int)strlen(command.args[1]) - 1);
		if (_strcmp(var, command.args[1]) == 0)
		{
			*envp = value;
			command.status = 0;
			return (0);
		}
		envp++;
	}
	command.status = -1;

	return (get_error(command.args, command.status, command.counter));
}
