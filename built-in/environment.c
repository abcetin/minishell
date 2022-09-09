/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:47:23 by acetin            #+#    #+#             */
/*   Updated: 2022/09/09 17:19:15 by acetin           ###   ########.fr       */
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


//@bakıcam.......
// void	free_env(char *arg, char **temp)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;


// 	j = 0;
// 	i = 0;
// 	if (where_env(arg) == -1)
// 		return ;
// 	while (temp[i])
// 	{
// 		if (i == where_env(arg))
// 		{
// 			tmp = ft_strdup(temp[i + 1]);
// 			free(temp[i]);
// 			temp[i] = ft_strdup(tmp);
// 			//free(tmp);
// 		}
// 		i++;
// 	}
// 	temp[i] = NULL;
// 	//free(tmp);
// 	ft_free_double(temp);
// }

// void	unset(t_cmd cmd)
// {
// 	char	**temp;

// 	temp = (char **)malloc(sizeof(char *) * (ft_double_strlen(environ) - ft_lstsize(cmd.command) + 1));
// 	ft_memcpy(temp, environ, ft_double_strlen(environ));
// 	while (cmd.command)
// 	{
// 		free_env(cmd.command->content, temp);
// 		cmd.command = cmd.command->next;
// 	}
// 	//ft_free_double(environ);
// 	environ = malloc(sizeof(char *) * (ft_double_strlen(temp) + 1));
// 	ft_memmove(environ, temp, ft_double_strlen(temp));
// 	//ft_free_double(temp);
// 	exit_status(0, 0, NULL);
// }
