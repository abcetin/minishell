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
	
	str = malloc(sizeof(char *) * command_count(*cmd) + 1);
	str[0] = (*cmd)->cmd;
	while ((*cmd)->arg != NULL && (*cmd)->arg[i])
	{
		if (char_count((*cmd)->arg[i], 34) || char_count((*cmd)->arg[i], 39))
			(*cmd)->arg[i] = clear_quote((*cmd)->arg[i]);
		str[j++] = ft_strdup((*cmd)->arg[i++]);
	}
	i = 0;
	while ((*cmd)->option != NULL && (*cmd)->option[i])
	{
		if (char_count((*cmd)->arg[i], 34) || char_count((*cmd)->arg[i], 39))
			(*cmd)->option[i] = clear_quote((*cmd)->option[i]);
		str[j++] = ft_strdup((*cmd)->option[i++]);
	}
	str[j] = NULL;
	return (str);
}

int ft_execve(t_cmd **cmd)
{
	int pid;
	char **arg;
	int x;

	x = 0;
	arg = join_cmd(cmd);
	pid = fork();
	if (pid == 0)
	{
		x = execve(arg[0], arg, environ);
		exit(0);
	}
	wait(NULL);
	return (x);
}