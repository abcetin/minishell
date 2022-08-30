#include "../minishell.h"

void with_pipe(char *str)
{
	int count;
	char **cmd;

	count = char_count(str, '|');
	cmd = split2(str, '|');
	ft_pipe(cmd, count);
	ft_free_double(cmd);
}

void parse_string(char *str)
{
	char **temp;
	t_cmd cmd;

	temp = NULL;
	if (!str)
		return;
	if (char_count(str, '|'))
		with_pipe(str);
	else if (ft_strchr(str, '>') || ft_strchr(str, '<'))
		redirect(str);
	else
	{
		temp = split2(str, 32);
		cmd.command = (t_list *)malloc(sizeof(t_list));
		cmd.command = NULL;
		cmd.cmd = ft_strdup(temp[0]);
		add_to_list(temp, &cmd.command);
		ft_free_double(temp);
		get_func(cmd);
		free(cmd.cmd);
		ft_lstclear(&cmd.command, free);
	}
}
