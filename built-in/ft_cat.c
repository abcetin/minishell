#include "../minishell.h"

void ft_write(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(STDOUT_FILENO, str[i], ft_strlen(str[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

static void print_e(int fd)
{
	int j;
	char **str;

	j = -1;
	str = ft_split(ft_read(fd), '\n');
	while (str[++j])
		str[j] = ft_strjoin(str[j], "$");
	ft_write(str);
	ft_free_str(str);
}

static int check_arg_e(t_cmd **cmd)
{
	int i;
	int fd;

	i = 0;
	
	if (ft_strnstr((*cmd)->option[0], "-e", ft_strlen((*cmd)->option[0])) && (*cmd)->arg[0] != NULL)
	{
		//printf("%s\n", (*cmd)->arg[0]);
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
	int fd;
	int i;

	i = 0;
	if ((*cmd)->option != NULL)
		check_arg_e(cmd);
	// else if ((*cmd)->arg[0] == NULL)
	// 	ft_write(ft_split(ft_read(STDIN_FILENO), '\n')); argüman verilmezse stdin den oku ama çalışmıyor
	else
	{
		while ((*cmd)->arg[i])
		{
			fd = open((*cmd)->arg[i], O_RDONLY);
			if (fd < 0)
			{
				perror((*cmd)->arg[i]);
				return ;
			}
			ft_write(ft_split(ft_read(fd), '\n'));
			close(fd);
			i++;
		}
	}
}