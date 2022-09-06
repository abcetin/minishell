#include "../minishell.h"

int exit_status(int status, int flag, char *message)
{
	static int exit_status;

	if (flag == 1)
		printf("%d", exit_status);
	if (message)
		printf("%s", message);
	exit_status = status;
	return (exit_status);
}