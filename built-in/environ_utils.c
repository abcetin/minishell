/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:46:04 by acetin            #+#    #+#             */
/*   Updated: 2022/09/10 13:30:26 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	where_env(char *s2)
{
	int		i;
	char	**temp;
	char	**env;

	i = 0;
	if (ft_strchr2(s2, '+'))
		temp = split2(s2, '+');
	else
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
	return (-1);
}

int	check_env_arg(t_cmd cmd)
{
	char	**arg;

	arg = split2(cmd.command->content, '=');
	if (!arg[0])
	{
		free((void *)arg);
		return (exit_status(256, 0, "not a valid identifier\n"));
	}
	else if ((!is_alnum(arg[0]) || ft_isdigit(arg[0][0])))
	{
		ft_free_double(arg);
		return (exit_status(256, 0, "not a valid identifier\n"));
	}
	ft_free_double(arg);
	return (exit_status(0, 0, NULL));
}

static void	norm1(char **a)
{
	char	*temp;

	temp = NULL;
	temp = clear_char(*a, '+');
	*a = ft_strdup(temp);
	free(temp);
}

static void	norm2(char *env, int env_index)
{
	char	**temp2;

	temp2 = ft_split(env, '=');
	environ[env_index] = ft_strjoin2(environ[env_index], temp2[1]);
	ft_free_double(temp2);
}

void	add_env(char *env, int env_index)
{
	int		count;

	count = ft_double_strlen(environ);
	if (env_index < 0)
	{
		if (ft_strchr2(env, '='))
			norm1(&env);
		environ = ft_realloc(environ, sizeof(char *) * (count + 2));
		environ[count] = ft_strdup(env);
		environ[count + 1] = NULL;
	}
	else
	{
		if (ft_strchr2(env, '+'))
			norm2(env, env_index);
		else
		{
			free(environ[env_index]);
			environ[env_index] = ft_strdup(env);
		}
	}
}
