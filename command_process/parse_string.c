#include "../minishell.h"

void with_pipe(char *str)
{
	int count;
	char **cmd;
	int i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	cmd = split2(str, '|');
	ft_pipe(cmd, count);
	ft_free_str(cmd);
}

void parse_string(char *str)
{
	char **temp;
	t_cmd cmd;

	cmd.option = NULL;
	cmd.arg = NULL;
	if (!str)
		return;
	temp = split2(str, 32);
	if (word_count(str, '|') > 1)
		with_pipe(str);
	else
	{
		cmd.cmd = ft_strdup(temp[0]);
		option(temp, &cmd);
		arg(temp, &cmd);
		get_func(&cmd);
		free(cmd.cmd);
		ft_free_str(cmd.arg);
		ft_free_str(cmd.option);
	}
	ft_free_str(temp);
}
