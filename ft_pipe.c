#include "minishell.h"

// int ft_write(int fd, void *ptr, unsigned int size)
// {
// 	if (write(fd, ptr, size) < 0)
// 	{
// 		perror("write : ");
// 		return 0;
// 	}
// 	return (1);
// }
void ft_multiple_close(int **fd, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < len)
	{

		if (j == 2)
		{
			j = 0;
			i++;
			if (i == len)
				break;
		}
		if (close(fd[i][j]) < 0)
			perror("close ");
		j++;
	}
}
int **ft_multiple_fd(int count)
{
	int i;
	int **fd;

	i = 0;
	fd = malloc(sizeof(int *) * count);
	while (i < count)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			printf("error memory allocation\n");
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (i < count)
	{
		if (pipe(fd[i]) < 0)
			perror("pipe ");
		i++;
	}
	return (fd);
}

int	ft_fork(void)
{
	int pid;

	pid = fork();
	if (pid < 0)
	{
		perror("pid ");
		return (-1);
	}
	return(pid);
}
void	multiple_waitpid(int *pid, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}
void ft_pipe(char **cmd, int count)
{
	int	**fd;
	int	*pid;
	int i;

	pid = malloc(sizeof(int) * count);
	fd = ft_multiple_fd(count);
	i = -1;
	while (++i <= count)
	{
		pid[i] = ft_fork();
		if (pid[i] == 0)
		{
			if  (i > 0)
				dup2(fd[i - 1][0], STDIN_FILENO);
			if (i != count)
				dup2(fd[i][1], STDOUT_FILENO);
			ft_multiple_close(fd, count);
			parse_string(cmd[i]);
			exit(0);
		}
	}
	ft_multiple_close(fd, count);
	multiple_waitpid(pid, count + 1);
}
// int main()
// {
// 	char *cmd = "cat asd.txt | grep 1 | grep 2 | grep 3 | wc";
// 	char **cmd2 = ft_split(cmd, 124);
// 	//ft_pipe(cmd2, 4);
// 	parse_string(cmd);
// }