#include "../minishell.h"

int is_exist_file(char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	return (1);
}

int create_file(char *path)
{
	int fd;

	if (!is_exist_file(path))
		fd = open(path, O_RDWR | O_CREAT);
	else
		fd = open(path, O_APPEND | O_DSYNC | O_RDWR);
	if (fd == -1)
	{
		perror("");
		return (0);
	}
	return (fd);
}

void clear_file(char *path)
{
	int fd;
	fd = open(path, O_TRUNC);
	if (fd < 0)
		perror("");
	close(fd);
}

static char **parsing_redirect(char **cmd)
{
	int i;
	int j;
	char **temp;

	i = 1;
	while (cmd[i])
	{
		j = 1;
		temp = split2(cmd[i], 32);
		while (temp[j])
		{
			cmd[0] = ft_strjoin2(cmd[0], " ");
			cmd[0] = ft_strjoin2(cmd[0], temp[j]);
			free(cmd[i]);
			cmd[i] = ft_strdup(temp[0]);
			if (temp[j + 1])
				cmd[0] = ft_strjoin2(cmd[0], " ");
			j++;
		}
		ft_free_double((void **)temp);
		i++;
	}
	return (cmd);
}

void right_redirect(char *cmd, char *file)
{
	int fd;
	int pid;

	fd = create_file(file);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		parse_string(cmd);
		exit(0);
	}
	wait(NULL);
	close(fd);
}

void single_right_redirect(char **cmd)
{
	int i;

	i = 1;
	printf("single\n");
	while (cmd[i])
	{
		if (is_exist_file(cmd[i]))
			clear_file(cmd[i]);
		right_redirect(cmd[0], cmd[i]);
		i++;
	}
}

void double_right_redirect(char **cmd)
{
	int i;

	i = 1;
	printf("double\n");
	while (cmd[i])
	{
		right_redirect(cmd[0], cmd[i]);
		i++;
	}
}

//void singel_left_redirect(char *cmd)

int redirect(char *cmd)
{
	char **temp;
	if (ft_strchr(cmd, '>'))
	{
		temp = split2(cmd, '>');
		temp = parsing_redirect(temp); 
		if (ft_strnstr(cmd, ">>", ft_strlen(cmd)))
			double_right_redirect(temp);
		else if (ft_strnstr(cmd, ">", ft_strlen(cmd)))
			single_right_redirect(temp);
		ft_free_double((void **)temp);
		return (1);
	}
	return (0);
}

// int main()
// {
// 	char *i;
// 	i = readline("asdas : ");
// 	redirect(i);
// 	char **red;
// 	// red = split2(i, '>');

// 	// red = right_redirect(red);
// 	// int j = 0;
// 	// while (red[j])
// 	// 	printf("%s\n", red[j++]);
// }