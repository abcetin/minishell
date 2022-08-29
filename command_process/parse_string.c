#include "../minishell.h"

void with_pipe(char *str)
{
	int count;
	char **cmd;

	count = char_count(str, '|');
	cmd = split2(str, '|');
	ft_pipe(cmd, count);
	ft_free_double((void **)cmd);
	free(cmd);
}

void parse_string(char *str)
{
	char **temp;
	t_cmd *cmd;

	temp = NULL;
	if (!str)
		return;
	if (word_count(str, '|') > 1)
		with_pipe(str);
	else if (redirect(str))
		return;
	else
	{
		cmd = malloc(sizeof(t_cmd));
		cmd->command = (t_list *)malloc(sizeof(t_list));
		cmd->command = NULL;
		temp = split2(str, 32);
		cmd->cmd = ft_strdup(temp[0]);
		add_to_list(temp, &cmd->command);
		//free(temp);
		get_func(cmd);
		if (!cmd->command)
			free(cmd->command);
		ft_free_double((void **)temp);
		//cmd->command = NULL;
		free(cmd->cmd);
	}
}
