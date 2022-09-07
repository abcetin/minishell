/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:10:33 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 14:35:32 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	choose_redirect(char **command, char **delimeter)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (delimeter[++j])
	{
		if (ft_strstr(delimeter[j], "<<"))
			double_left_redirect(command[j]);
	}
	while (delimeter[++i])
	{
		if (j == i && delimeter[i + 1] != NULL)
			continue ;
		if (ft_strstr(delimeter[i], ">"))
			single_right_redirect(command[i]);
		else if (ft_strstr(delimeter[i], ">>"))
			double_right_redirect(command[i]);
		else if (ft_strstr(delimeter[i], "<"))
			singel_left_redirect(command[i]);
	}
	return (0);
}



int	redirect(char *cmd)
{
	char	**tmp;
	char	**tmp2;
	char	**delimeter;
	int		pid;

	tmp2 = split2(cmd, '|');
	tmp = redirect_split(tmp2[0]);
	tmp = join_redirect(tmp);
	delimeter = redirect_delimiter(cmd);
	pid = fork();
	if (pid == 0)
	{
		choose_redirect(&tmp[1], delimeter);
		parse_string(tmp[0]);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	if (char_count(cmd, '|'))
		ft_pipe(&tmp2[1], ft_double_strlen(&tmp2[1]));
	ft_free_double(tmp);
	ft_free_double(tmp2);
	ft_free_double(delimeter);
	return (0);
}
