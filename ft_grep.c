#include "minishell.h"

void ft_grep(char **cmd)
{
	char **str;
	int i;

	str = ft_split(ft_read(STDIN_FILENO), '\n');
	i = 0;
	while (str[i])
	{
		if (ft_strnstr(str[i], cmd[1], ft_strlen(str[i])) != 0)
		{
			write(STDOUT_FILENO, str[i], ft_strlen(str[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}