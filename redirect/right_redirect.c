/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:11:06 by acetin            #+#    #+#             */
/*   Updated: 2022/09/09 15:27:49 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	right_redirect(char *file)
{
	int	fd;

	fd = open_file(file);
	if (fd > 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (exit_status(fd, 0, NULL));
}

int	single_right_redirect(char *file)
{
	int		ret;
	char	*temp;

	temp = ft_strdup(file);
	temp = clear_char(temp, 32);
	clear_file(temp);
	ret = right_redirect(temp);
	free(temp);
	return (exit_status(ret, 0, NULL));
}

int	double_right_redirect(char *file)
{
	int		ret;
	char	*temp;

	temp = ft_strdup(file);
	temp = clear_char(temp, 32);
	ret = right_redirect(temp);
	free(temp);
	return (exit_status(ret, 0, NULL));
}
