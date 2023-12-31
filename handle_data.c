#include "main.h"

/**
 * free_data - frees data structure
 *
 * @datash: data structure
 * Return: no return
 */
void free_data(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->av[i]; i++)
		free(datash->av[i]);
	for (i = 0; datash->args[i]; i++)
		free(datash->args[i]);
	free(datash->input);
}

/**
 * set_data - Initialize data structure
 *
 * @datash: data structure
 * @environ: Environment
 *
 * Return: no return
 */
void set_data(data_shell *datash, char **environ)
{
	unsigned int i = 0;

	while (i < MAX_ARGS)
	{
		datash->args[i] = NULL;
		i++;
	}
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		datash->_environ[i] = _strdup(environ[i]);
	for (; i < 100; i++)
		datash->_environ[i] = NULL;

	datash->pid = getpid();
}
