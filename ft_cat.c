# include "minishell.h"

void	ft_cat(char **cmd)
{
	char	*str;
	int		fd;
	int		input;

	fd = open(cmd[1], O_RDONLY);
	if (fd < 0)
	{
		perror("");
		return ;
	}
	input = STDIN_FILENO;
	input = dup(fd);
	str = ft_read(input);
	write(STDOUT_FILENO, str, ft_strlen(str));
	close(fd);
	close(input);
	free(str);
}

// int main()
// {
// 	char *cmd[2] = {"cmd", "asd.txt"};
// 	ft_cat(cmd);
// }