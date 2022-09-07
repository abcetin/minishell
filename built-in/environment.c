/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:47:23 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 10:00:26 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_cmd cmd)
{
	int	i;

	i = 0;
	if (cmd.command)
	{
		exit_status(1, 0, "with no options\n");
		return ;
	}
	while (environ[i])
		printf("%s\n", environ[i++]);
	exit_status(0, 0, NULL);
}

void	add_env(char *env, int env_index)
{
	int		count;
	char	**temp2;

	count = ft_double_strlen(environ);
	if (!env_index)
	{
		environ = ft_realloc(environ, sizeof(char *) * (count + 2));
		environ[count] = ft_strdup(env);
		environ[count + 1] = NULL;
	}
	else
	{
		if (ft_strchr2(env, '+'))
		{
			temp2 = ft_split(env, '=');
			environ[env_index] = ft_strjoin2(environ[env_index], temp2[1]);
			ft_free_double(temp2);
		}
		else
		{
			free(environ[env_index]);
			environ[env_index] = ft_strdup(env);
		}
	}
}

void	export(t_cmd cmd)
{
	int	arg_index;

	if (!cmd.command)
	{
		env(cmd);
		return ;
	}
	if (check_env_arg(cmd))
		return ;
	while (cmd.command)
	{
		arg_index = where_env(cmd.command->content);
		add_env(cmd.command->content, arg_index);
		cmd.command = cmd.command->next;
	}
	exit_status(0, 0, NULL);
}

void	unset(t_cmd cmd)
{
	while (cmd.command)
	{
		free_env(cmd.command->content);
		cmd.command = cmd.command->next;
	}
	exit_status(0, 0, NULL);
}
