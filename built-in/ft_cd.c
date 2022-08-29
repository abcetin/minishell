#include "../minishell.h"

void cd(t_cmd *cmd)
{
	// if ((*cmd)->arg != NULL && ft_strchr((*cmd)->arg[0], '$'))
	// 	(*cmd)->arg[0] = sequence((*cmd)->arg[0]); //******************buna bak
	if (cmd->command == NULL)
		chdir(getenv("HOME"));
	else if (chdir(clear_quote(cmd->command->content)))
		perror("");
}