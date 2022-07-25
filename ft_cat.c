#include "minishell.h"

void ft_write(char *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, "\n", 1);
}

static void print_e(int fd)
{
	int j;
	char **str;

	j = 0;
	str = ft_split(ft_read(fd), '\n');
	while (str[j])
	{
		ft_write(ft_strjoin(str[j], "$"));
		j++;
	}
	ft_free_str(str);
}

static int check_arg_e(char **cmd)
{
	int i;
	int fd;

	i = 1;
	if (ft_strstr(cmd[1], "-e") && cmd[2] != NULL)
	{
		while (cmd[i + 1])
		{
			fd = open(cmd[i + 1], O_RDONLY);
			print_e(fd);
			close(fd);
			i++;
		}
		return (1);
	}
	else if (ft_strstr(cmd[1], "-e") && cmd[2] == NULL)
	{
		print_e(STDIN_FILENO);
		return (1);
	}
	return (0);
}

void ft_cat(char **cmd)
{
	char **str;
	int fd;
	int i;
	int	j;

	i = 1;
	if (check_arg_e(cmd))
		return;
	else
	{
		while (cmd[i])
		{
			j = 0;
			fd = open(cmd[i], O_RDONLY);
			if (fd < 0)
			{
				perror(cmd[i]);
				return ;
			}
			str = ft_split(ft_read(fd), '\n');
			while (str[j])
			{
				ft_write(str[j]);
				j++;
			}
			close(fd);
			ft_free_str(str);
			i++;
		}
	}
}
