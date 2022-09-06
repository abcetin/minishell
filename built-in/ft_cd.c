#include "../minishell.h"
#include <string.h>
char *sequence(char *str)
{
	char **temp;
	char *ret;
	int i;

	ret = NULL;
	temp = split2(str, '/');
	i = -1;
	while (temp[++i])
	{
		if (temp[i][0] == '$')
		{
			ret = ft_strjoin2(ret, getenv(&temp[i][1])) ;
			if (!ret)
			{
				perror("");
				ft_free_double(temp);
				return (NULL);
			}
		}
		if (temp[i + 1])
			ret = ft_strjoin(ret, "/");
	}
	ft_free_double(temp);
	return (ret);
}

void cd(t_cmd cmd)
{
	char *temp;

	temp = NULL;
	if (cmd.command != NULL && ft_strchr2(cmd.command->content, '$'))
	{
		temp = ft_strdup(cmd.command->content);
		free(cmd.command->content);
		cmd.command->content = sequence(temp);
		free(temp);
	} //******************buna bak
	if (cmd.command == NULL)
		chdir(getenv("HOME"));
	else
	{
		cmd.command->content = clear_quote(cmd.command->content);
		if (chdir(cmd.command->content) < 0)
		{
			exit_status(1, 0, NULL);
			perror("");
			return ;
		}
	}
	exit_status(0, 0, NULL);
}