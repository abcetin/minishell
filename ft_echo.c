#include "minishell.h"

int check_option(char **str)
{
	int i;
	int ret;

	i = 1;
	ret = 1;
	while (str[i])
	{
		if (ft_strstr(str[i], "-n"))
			ret++;
		i++;
	}
	return (ret);
}

void ft_echo(char **cmd)
{
	int		i;
	int		new_line;
	char	*str;

	i = check_option(cmd);
	new_line = i;
	while (cmd[i])
	{
		if (cmd[i][0] == '$')
		{
			str = getenv(&cmd[i][1]);
			if (!str)
			{
				perror("");
				return ;
			}
			else
				write(STDOUT_FILENO, getenv(&cmd[i][1]), ft_strlen(getenv(&cmd[i][1])));
		}
		else
			write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line == 1)
		write(STDOUT_FILENO, "\n", 1);
}