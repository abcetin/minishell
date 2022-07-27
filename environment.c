#include "minishell.h"

static int where(char **s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && ft_strstr(ft_split(s1[i], '=')[0], s2) == 0)
		i++;
	return (i);
}

void env(t_cmd **cmd)
{
	int i;

	i = 0;
	if ((*cmd)->option != NULL)
	{
		write(STDOUT_FILENO, "with no options\n", 15);
		return;
	}
	while (environ[i])
		printf("%s\n", environ[i++]);
}

int check_env_arg(t_cmd **cmd)
{
	int i;

	i = 0;
	if ((*cmd)->option != NULL)
	{
		write(STDOUT_FILENO, "with no options\n", 15);
		return (0);
	}
	while ((*cmd)->arg[i])
	{
		if (ft_strchr((*cmd)->arg[i], '=') == 0)
		{
			printf("'%s' not a valid identifier\n", (*cmd)->arg[i]);
			return (0);
		}
		i++;
	}
	return (i);
}

void export(t_cmd **cmd)
{
	int count;
	int arg_index;
	int i;

	if (!check_env_arg(cmd))
		return ;
	i = 1;
	count = 0;
	while (environ[count])
		count++;
	while ((*cmd)->arg[i])
	{
		arg_index = where(environ, ft_split((*cmd)->arg[i], '=')[0]);
		if (arg_index == count)
		{
			environ[count] = malloc(ft_strlen((*cmd)->arg[i]));
			environ[count] = (*cmd)->arg[i];
			environ[count + 1] = NULL;
		}
		else
			environ[arg_index] = (*cmd)->arg[i];
		i++;
		count++;
	}
}

void unset(t_cmd **cmd)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	j = 0;
	while (environ[count])
		count++;
	i = where(environ, (*cmd)->arg[0]);
	if (i == count)
		return;
	count = 0;
	while (environ[j])
	{
		if (i != j)
		{
			environ[count] = environ[j];
			count++;
		}
		j++;
	}
	environ[count] = NULL;
}