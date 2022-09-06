#include "../minishell.h"

void right_redirect(char *file)
{
	int fd;

	fd = open_file(file);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void single_right_redirect(char *file)
{
	char *temp;

	temp = ft_strtrim(file, " ");
	if (is_exist_file(temp))
		clear_file(temp);
	right_redirect(temp);
	free(temp);
}

void double_right_redirect(char *file)
{
	char *temp;

	temp = ft_strtrim(file, " ");
	right_redirect(temp);
}