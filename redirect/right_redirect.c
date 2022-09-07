/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:11:06 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 10:11:28 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	right_redirect(char *file)
{
	int	fd;

	fd = open_file(file);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	single_right_redirect(char *file)
{
	char	*temp;

	temp = ft_strtrim(file, " ");
	if (is_exist_file(temp))
		clear_file(temp);
	right_redirect(temp);
	free(temp);
}

void	double_right_redirect(char *file)
{
	char	*temp;

	temp = ft_strtrim(file, " ");
	right_redirect(temp);
}
