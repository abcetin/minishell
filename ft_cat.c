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

static int check_arg_e(t_cmd **cmd)
{
	int i;
	int fd;

	i = 0;

	if (ft_strnstr((*cmd)->option[0], "-e", ft_strlen((*cmd)->option[0])) && (*cmd)->arg[0] != NULL)
	{
		printf("%s\n", (*cmd)->arg[0]);
		while ((*cmd)->arg[i])
		{
			fd = open((*cmd)->arg[i], O_RDONLY);
			if (fd < 0)
				return (0);
			print_e(fd);
			close(fd);
			i++;
		}
		return (1);
	}
	else if (ft_strnstr((*cmd)->option[0], "-e", ft_strlen((*cmd)->option[0])) && (*cmd)->arg[0] == NULL)
	{
		print_e(STDIN_FILENO);
		return (1);
	}
	return (0);
}

void ft_cat(t_cmd **cmd)
{
	char **str;
	int fd;
	int i;
	int	j;

	i = 0;
	if ((*cmd)->option != NULL)
	{
		check_arg_e(cmd);
		return;
	}
	else
	{
		while ((*cmd)->arg[i])
		{
			j = 0;
			fd = open((*cmd)->arg[i], O_RDONLY);
			if (fd < 0)
			{
				perror((*cmd)->arg[i]);
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