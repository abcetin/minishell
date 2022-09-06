#include "../minishell.h"

void exit_f(t_cmd cmd)
{
	if (cmd.command)
	{
		exit_status(1, 0, "too many arguments\n");
		return ;
	}
	printf("exit\n");
	exit(EXIT_SUCCESS);
}