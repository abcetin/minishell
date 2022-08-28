#include "../minishell.h"

int command_count(t_cmd *cmd)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	while (cmd->arg != NULL && cmd->arg[i])
		i++;
	ret += i;
	i = 0;
	while (cmd->option != NULL && cmd->option[i])
		i++;
	ret += i;
	return (ret + 1);
}

char **join_cmd(t_cmd **cmd)
{
	int i, j;
	char **str;

	i = 0;
	j = 1;
	
	str = malloc(sizeof(char *) * (command_count(*cmd) + 1));
	if (!ft_strchr((*cmd)->cmd, '/'))
	{
		str[0] = ft_strjoin(where((*cmd)->cmd), "/");
		str[0] = ft_strjoin(str[0], (*cmd)->cmd);
		if (!str[0])
			return (NULL);
	}
	else
		str[0] = ft_strdup((*cmd)->cmd);
	while ((*cmd)->option != NULL && (*cmd)->option[i])
		str[j++] = ft_strdup((*cmd)->option[i++]);
	i = 0;
	while ((*cmd)->arg != NULL && (*cmd)->arg[i])
		str[j++] = ft_strdup((*cmd)->arg[i++]);
	str[j] = NULL;
	ft_free_cmd(*cmd);
	//free(cmd);
	return (str);
}

int ft_execve(t_cmd **cmd)
{
	int pid;
	char **arg;
	int x;

	x = 0;
	arg = join_cmd(cmd);
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
	ft_free_str(arg);
	return (x);
}