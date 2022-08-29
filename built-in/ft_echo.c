#include "../minishell.h"

int check_option(t_list **lst)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	if (!(*lst))
		return (0);
	else if (ft_strstr("-n", (*lst)->content))
	{
		lst_find(lst, "-n");
		return(1);
	}
	else
		return(0);
}

void ft_echo(t_cmd *cmd)
{
	int		i;
	int		new_line;

	i = 0;
	new_line = check_option(&cmd->command);
	if (!cmd->command->content)
	{
		write(STDOUT_FILENO, "\n", 1);
		return;
	}
	while (cmd->command)
	{
		print_all(cmd->command->content);
		if (cmd->command->next != NULL)
			write(STDOUT_FILENO, " ", 1);
		cmd->command = cmd->command->next;
	}
	if (new_line == 0)
		write(STDOUT_FILENO, "\n", 1);
}