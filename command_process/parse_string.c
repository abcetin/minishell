#include "../minishell.h"

void with_pipe(char *str)
{
	int count;
	char **cmd;

	count = char_count(str, '|');
	cmd = split2(str, '|');
	ft_pipe(cmd, count);
	ft_free_str(cmd);
}

void parse_string(char *str)
{
	char **temp;
	t_cmd cmd;

	temp = NULL;
	if (!str)
		return;
	if (word_count(str, '|') > 1)
		with_pipe(str);
	else if (redirect(str))
		return;
	else
	{
		temp = split2(str, 32);
		cmd.option = NULL;
		cmd.arg = NULL;
		cmd.cmd = ft_strdup(temp[0]);
		option(temp, &cmd);
		arg(temp, &cmd);
		get_func(&cmd);
		ft_free_str(cmd.arg);
		ft_free_str(cmd.option);
		ft_free_str(temp);
	}
}
