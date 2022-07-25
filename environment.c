#include "minishell.h"

static int where(char **s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && ft_strstr(ft_split(s1[i], '=')[0], s2) == 0)
		i++;
	return (i);
}

void env(char **cmd)
{
	int i;

	i = 0;
	if (cmd[1])
	{
		write(STDOUT_FILENO, "too many arguments\n", 19);
		return;
	}
	while (environ[i])
		printf("%s\n", environ[i++]);
	printf("count %d\n", i);
}

int check_env_arg(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(str[i], '0') == 0)
			return (0);
		i++;
	}
	return (i);
}

void export(char **cmd)
{
	int count;
	int arg_index;
	int i;

	if (!check_env_arg(cmd))
	{
		printf("'%s' not a valid identifier\n", cmd[1]);
		return ;
	}
	i = 1;
	count = 0;
	while (environ[count])
		count++;
	while (cmd[i])
	{
		arg_index = where(environ, ft_split(cmd[i], '=')[0]);
		if (arg_index == count)
		{
			environ[count] = malloc(ft_strlen(cmd[i]));
			environ[count] = cmd[i];
			environ[count + 1] = NULL;
		}
		else
			environ[arg_index] = cmd[i];
		i++;
		count++;
	}
}

void unset(char **cmd)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	j = 0;
	while (environ[count])
		count++;
	i = where(environ, cmd[1]);
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