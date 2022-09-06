#include "../minishell.h"

int check_option(t_list **lst)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	if (ft_strstr("-n", (*lst)->content))
	{
		lst_find(lst, "-n");
		return (1);
	}
	else
		return (0);
}

void ft_echo(t_cmd cmd)
{
	int i;
	int new_line;
	int quote;

	i = 0;
	if (cmd.command)
		new_line = check_option(&cmd.command);
	if (!cmd.command)
	{
		exit_status(0, 0, "\n");
		return ;
	}
	while (cmd.command)
	{
		quote = first_quote(cmd.command->content);
		print_all(cmd.command->content, quote);
		if (cmd.command->next != NULL)
			write(STDOUT_FILENO, " ", 1);
		cmd.command = cmd.command->next;
	}
	if (new_line == 0)
		exit_status(0, 0, "\n");
}