#include "minishell.h"

static void	print_grep(int fd, char *grep)
{
	char	**str;
	int		i;

	str = ft_split(ft_read(fd), '\n');
	i = 0;
	while (str[i])
	{
		if (ft_strnstr(str[i], grep, ft_strlen(str[i])) != 0)
		{
			write(STDOUT_FILENO, str[i], ft_strlen(str[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	i = 0;
	ft_free_str(str);
}


static void	with_file(char **cmd)
{
	int	i;
	int	fd;

	i = 2;
	while (cmd[i])
	{
		fd = open(cmd[i], O_RDONLY);
		if (fd < 0)
		{
			perror("");
			return ;
		}
		print_grep(fd, cmd[1]);
		close(fd);
		i++;		
	}
}

void ft_grep(char **cmd)
{
	if (cmd[2] != NULL)
		with_file(cmd);
	else
		print_grep(STDIN_FILENO, cmd[1]);
}