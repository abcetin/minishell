/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:56:52 by acetin            #+#    #+#             */
/*   Updated: 2022/09/10 13:45:07 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	with_pipe(char *str)
{
	int		count;
	char	**cmd;

	count = char_count(str, '|');
	cmd = split2(str, '|');
	ft_pipe(cmd, count);
	ft_free_double(cmd);
}

void	parse_string(char *str)
{
	char	**temp;
	t_cmd	cmd;

	temp = NULL;
	if (!ft_strlen(str))
		return ;
	if (char_count(str, '|'))
		with_pipe(str);
	else if (char_count(str, '>') || char_count(str, '<'))
		redirect(str);
	else
	{
		temp = split2(str, 32);
		if (!temp[0])
			return ;
		cmd.command = NULL;
		cmd.cmd = ft_strdup(temp[0]);
		add_to_list(temp, &cmd.command);
		ft_free_double(temp);
		get_func(cmd);
		lstclear(&cmd.command);
		free(cmd.cmd);
	}
}
