/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:56:52 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 14:17:09 by acetin           ###   ########.fr       */
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

int deneme(char *cmd)
{
	int j;
	char	**tmp;
	char	**delimeter;

	tmp = redirect_split(cmd);
	tmp = join_redirect(tmp);
	delimeter = redirect_delimiter(cmd);
	j = -1;
	while (delimeter[++j])
	{
		if (ft_strstr(delimeter[j], "<<"))
			double_left_redirect(tmp[j + 1]);
	}
	return(j);
}

void	parse_string(char *str)
{
	char	**temp;
	t_cmd	cmd;

	temp = NULL;
	if (!ft_strlen(str))
		return ;
	// if (ft_strncmp(str, "<<", 2))
	// 	deneme(str);
	if (char_count(str, '>') || char_count(str, '<'))
		redirect(str);
	else if (char_count(str, '|'))
		with_pipe(str);
	else
	{
		temp = split2(str, 32);
		cmd.command = NULL;
		cmd.cmd = ft_strdup(temp[0]);
		add_to_list(temp, &cmd.command);
		ft_free_double(temp);
		get_func(cmd);
		lstclear(&cmd.command);
		free(cmd.cmd);
	}
}
