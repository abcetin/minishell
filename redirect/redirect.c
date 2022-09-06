#include "../minishell.h"

int choose_redirect(char **command, char **delimeter)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (delimeter[++j])
	{
		if (ft_strstr(delimeter[j], "<<"))
			double_left_redirect(command[j]);
	}
	while (delimeter[++i])
	{
		if (j == i && delimeter[i + 1] != NULL)
			continue;
		if (ft_strstr(delimeter[i], ">"))
			single_right_redirect(command[i]);
		else if (ft_strstr(delimeter[i], ">>"))
			double_right_redirect(command[i]);
		else if (ft_strstr(delimeter[i], "<"))
			singel_left_redirect(command[i]);
	}
	return (0);
}

int redirect(char *cmd)
{
	char **tmp;
	char **delimeter;
	int pid;

	tmp = redirect_split(cmd);
	tmp = join_redirect(tmp);
	delimeter = redirect_delimiter(cmd);
	pid = fork();
	if (pid == 0)
	{
		choose_redirect(&tmp[1], delimeter);
		parse_string(tmp[0]);
		exit(0);
	}
	wait(NULL);
	ft_free_double(tmp);
	ft_free_double(delimeter);
	return (0);
}