#include "main.h"

/**
 * cd_shell - cd built-in
 * @command: Command
 *
 * Return: status
 */
int cd_shell(data_shell command)
{
	if (command.args[1] == NULL)
		command.args[1] = _strdup("..");

	cd_to(&command);

	return (command.status);
}

/**
 * cd_to - changes to a directory given
 * by the user
 * @command: Command
 *
 * Return: no return
 */
void cd_to(data_shell *command)
{
	char *pwd = NULL, *dir = NULL;

	getcwd(pwd, sizeof(pwd));

	if (chdir(command->args[1]) == -1)
	{
		command->status = 2;
		get_error(command->args, command->status, command->counter);
		return;
	}
	getcwd(dir, BUFFER_SIZE);

	update_value(*command, "PWD", dir);
	update_value(*command, "OLDPWD", pwd);
}
