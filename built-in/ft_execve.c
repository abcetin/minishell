#include "../minishell.h"

char **join_cmd(char *cmd, t_list *lst)
{
	char **str;
	int j;

	j = 1;
	str = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!ft_strchr(cmd, '/'))
	{
		str[0] = ft_strjoin2(where(cmd), "/");
		str[0] = ft_strjoin2(str[0], cmd);
		if (!str[0])
			return (NULL);
	}
	else
		str[0] = ft_strdup(cmd);
	while (lst)
	{
		str[j++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	str[j] = NULL;
	return (str);
}

int ft_execve(t_cmd *cmd)
{
	int pid;
	char **arg;
	int x;

	x = 0;
	arg = join_cmd(cmd->cmd, cmd->command);
	if (!arg)
	{
		printf("command not found\n");
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		x = execve(arg[0], arg, environ);
		if (x == -1)
			perror("");
		exit(0);
	}
	wait(NULL);
	ft_free_double((void **)arg);
	return (x);
}