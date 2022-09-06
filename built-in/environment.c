#include "../minishell.h"

static int where_env(char *s2)
{
	int i;
	char **temp;
	char **env;

	i = 0;
	temp = split2(s2, '=');
	while (environ[i])
	{
		env = split2(environ[i], '=');
		if (ft_strstr(env[0], temp[0]))
		{
			ft_free_double(env);
			ft_free_double(temp);
			return (i);
		}
		ft_free_double(env);
		i++;
	}
	ft_free_double(temp);
	return (0);
}

void env(t_cmd cmd)
{
	int i;

	i = 0;
	if (cmd.command)
	{
		exit_status(1, 0, "with no options\n");
		return;
	}
	while (environ[i])
		printf("%s\n", environ[i++]);
	exit_status(0, 0, NULL);
}

int check_env_arg(t_cmd cmd)
{
	char **arg;
	t_list *lst;

	lst = cmd.command;
	if (lst_find(&lst, "-"))
		return (exit_status(1, 0, "with no options\n"));
	arg = split2(cmd.command->content, '=');
	if (!ft_strchr2(cmd.command->content, '=') || !arg[1] || !is_alnum(arg[0]) || ft_isdigit(arg[0][0]))
	{
		ft_free_double(arg);
		return (exit_status(1, 0, "not a valid identifier\n"));
	}
	ft_free_double(arg);
	return (exit_status(0, 0, NULL));
}

void export(t_cmd cmd)
{
	int count;
	int arg_index;

	if (!cmd.command)
	{
		env(cmd);
		return;
	}
	if (check_env_arg(cmd))
		return;
	count = ft_double_strlen(environ);
	while (cmd.command)
	{
		arg_index = where_env(cmd.command->content);
		if (!arg_index)
		{
			environ = ft_realloc(environ, sizeof(char *) * (count + 2));
			environ[count] = ft_strdup(cmd.command->content);
			environ[++count] = NULL;
		}
		else
			environ[arg_index] = ft_strdup(cmd.command->content);
		cmd.command = cmd.command->next;
	}
	exit_status(0, 0, NULL);
}

void free_env(char *arg)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	if (!where_env(arg))
		return ;
	while (environ[j])
	{
		if (i == where_env(arg))
		{
			free(environ[j]);
			j++;
		}
		environ[i] = environ[j];
		i++;
		j++;
	}
	environ[i] = NULL;
}

void unset(t_cmd cmd)
{
	char *temp;

	temp = NULL;
	while (cmd.command)
	{
		free_env(cmd.command->content);
		cmd.command = cmd.command->next;
	}
	exit_status(0, 0, NULL);
}