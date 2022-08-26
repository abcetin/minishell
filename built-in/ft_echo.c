#include "../minishell.h"

int check_option(char **str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_strnstr(str[i], "-n", ft_strlen(str[i])))
			ret++;
		i++;
	}
	return (ret);
}

void ft_echo(t_cmd **cmd)
{
	int		i;
	int		new_line;

	i = 0;
	new_line = check_option((*cmd)->option);
	if (!(*cmd)->arg)
	{
		write(STDOUT_FILENO, "\n", 1);
		return;
	}
	while ((*cmd)->arg[i])
	{
		print_all((*cmd)->arg[i]);
		if ((*cmd)->arg[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line == 0)
		write(STDOUT_FILENO, "\n", 1);
}