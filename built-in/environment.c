/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:47:23 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 12:14:37 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_cmd cmd)
{
	int	i;

	i = 0;
	if (cmd.command)
	{
		exit_status(256, 0, "with no options\n");
		return ;
	}
	while (environ[i])
		printf("%s\n", environ[i++]);
	exit_status(0, 0, NULL);
}

void	free_env(char *arg)
{
	int	i;
	int	j;

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
		cmd.command->content = clear_char(cmd.command->content,
				first_quote(cmd.command->content));
		if (ft_strchr2(cmd.command->content, '='))
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
