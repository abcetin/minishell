#include "../minishell.h"

void exit_f(t_cmd cmd)
{
	if (cmd.command)
	{
		write(STDOUT_FILENO, "too many arguments\n", 19);
		return;
	}
	exit(EXIT_SUCCESS);
}