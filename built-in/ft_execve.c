#include "../minishell.h"

char *update_cmd(char *cmd)
{
	char *ret;
	char *path;

	if (ft_strchr2(cmd, '/'))
	{
		ret = ft_strdup(cmd);
		return(ret);
	}
	path = where(cmd);
	if (!path)
			return (NULL);
	else
	{
		ret = ft_strjoin2(path, "/");
		ret = ft_strjoin2(ret, cmd);
	}
	return (ret);
}

char **join_cmd(char *cmd, t_list *lst)
{
	char **str;
	int j;

	j = 1;
	str = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 2));
	str[0] = update_cmd(cmd);
	if (!str[0])
		return (NULL);
	while (lst)
	{
		if (ft_strchr2(lst->content, 34) || ft_strchr2(lst->content, 39))
			lst->content = clear_quote(lst->content);
		str[j++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	str[j] = NULL;
	return (str);
}

int ft_execve(t_cmd cmd)
{
	int pid;
	char **arg;

	arg = join_cmd(cmd.cmd, cmd.command);
	if (!arg)
	{
		printf("command not found\n");
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(arg[0], arg, environ) == -1)
			perror("");
		exit(0);
	}
	wait(NULL);
	ft_free_double(arg);
	return (0);
}