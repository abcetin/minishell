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
			ft_free_double((void **)env);
			break;
		}
		ft_free_double((void **)env);
		i++;
	}
	ft_free_double((void **)temp);
	return (i);
}

void env(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->command)
	{
		write(STDOUT_FILENO, "with no options\n", 16);
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
int check_env_arg(t_cmd *cmd)
{
	char **arg;
	// if ((*cmd)->option != NULL)
	// {
	// 	write(STDOUT_FILENO, "with no options\n", 15);
	// 	return (0);
	// }
	arg = split2(cmd->command->content, '=');
	if (!ft_strchr(cmd->command->content, '=') || !arg[1] || !is_alnum(arg[0]))
	{
		printf("'%s' not a valid identifier\n", cmd->command->content);
		return (0);
	}
	ft_free_double((void **)arg);
	return (1);
}

void export(t_cmd *cmd)
{
	int count;
	int arg_index;

	if (!cmd->command)
	{
		env(cmd);
		return ;
	}
	if (!check_env_arg(cmd))
		return;
	count = 0;
	while (environ[count])
		count++;
	while (cmd->command)
	{
		arg_index = where_env(cmd->command->content);
		if (arg_index == count)
		{
			environ[count++] = ft_strdup(cmd->command->content);
			environ[count] = NULL;
		}
		else
			environ[arg_index] = ft_strdup(cmd->command->content);
		cmd->command = cmd->command->next;
	}
}

// void unset(t_cmd **cmd) listeeye göre optimize et
// {
// 	int i;
// 	int j;
// 	int count;

// 	i = 0;
// 	count = 0;
// 	j = 0;
// 	while (environ[count])
// 		count++;
// 	i = where_env();
// 	if (i == count)
// 		return;
// 	count = 0;
// 	while (environ[j])
// 	{
// 		if (i != j)
// 		{
// 			environ[count] = environ[j];
// 			count++;
// 		}
// 		j++;
// 	}
// 	environ[count] = NULL;
// }