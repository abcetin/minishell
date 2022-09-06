#include "../minishell.h"

void singel_left_redirect(char *file)
{
	int fd;
	char *temp;

	temp = ft_strtrim(file, " ");
	fd = open(temp, O_RDONLY);
	if (fd < 0)
		perror(file);
	free(temp);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void double_left_redirect(char *eof)
{
	char *str;
	char *input;
	int fd;

	input = NULL;
	str = NULL;
	eof = ft_strtrim(eof, " ");
	fd = open_file("./redirect/heredoc");
	clear_file("./redirect/heredoc");
	while (1)
	{
		input = readline(">");
		if (ft_strstr(input, eof))
			break;
		input = ft_strjoin2(input, "\n");
		str = ft_strjoin2(str, input);
		free(input);
	}
	ft_putstr_fd(str, fd);
	close(fd);
	singel_left_redirect("./redirect/heredoc");
}