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
			break;
		ft_free_str(env);
		i++;
	}
	ft_free_str(temp);
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
static int is_alnum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
int check_env_arg(t_cmd **cmd)
{
	int i;
	char **arg;
	i = 0;
	if ((*cmd)->option != NULL)
	{
		write(STDOUT_FILENO, "with no options\n", 15);
		return (0);
	}
	while ((*cmd)->arg[i])
	{
		arg = split2((*cmd)->arg[i], '=');
		if (!ft_strchr((*cmd)->arg[i], '=') ||
			(*cmd)->arg[i][ft_strlen((*cmd)->arg[i]) - 1] == '='
			|| !is_alnum(arg[0]))
		{
			printf("'%s' not a valid identifier\n", (*cmd)->arg[i]);
			return (0);
		}
		ft_free_str(arg);
		i++;
	}
	return (i);
}

void export(t_cmd **cmd)
{
	int count;
	int arg_index;
	int i;

	if (!(*cmd)->arg)
		env(cmd);
	if (!check_env_arg(cmd))
		return ;
	i = 0;
	count = 0;
	while (environ[count])
		count++;
	while ((*cmd)->arg[i])
	{
		arg_index = where_env((*cmd)->arg[i]);
		if (arg_index == count)
		{
			environ[count] =ft_strdup((*cmd)->arg[i]);
			environ[count + 1] = NULL;
		}
		else
			environ[arg_index] = ft_strdup((*cmd)->arg[i]);
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
	i = where_env((*cmd)->arg[0]);
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