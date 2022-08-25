#include "../minishell.h"

void pwd(t_cmd **cmd)
{
	char cwd[256];

	if ((*cmd)->option != NULL && (*cmd)->arg != NULL)
	{
		printf("with no options \n");
		return;
	}
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}