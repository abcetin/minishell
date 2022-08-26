#include "../minishell.h"

void cd(t_cmd **cmd)
{
	if ((*cmd)->arg != NULL && ft_strchr((*cmd)->arg[0], '$'))
		(*cmd)->arg[0] = sequence((*cmd)->arg[0]);
	if ((*cmd)->arg == NULL)
		chdir(getenv("HOME"));
	else if (chdir((*cmd)->arg[0]))
		perror("");
}