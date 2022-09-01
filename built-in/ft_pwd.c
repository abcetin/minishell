#include "../minishell.h"

void pwd(t_cmd cmd)
{
	char *cwd;

	cwd = NULL;
	if (cmd.command)
	{
		printf("with no options \n");
		return;
	}
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}