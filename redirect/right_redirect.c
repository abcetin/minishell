/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:11:06 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 16:36:27 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	right_redirect(char *file)
{
	int	fd;

	fd = open_file(file);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return(fd);
}

int	single_right_redirect(char *file)
{
	char	*temp;
	int		ret;

	temp = ft_strtrim(file, " ");
	//clear_file(temp);
	ret = right_redirect(temp);
	free(temp);
	return (ret);
}

int	double_right_redirect(char *file)
{
	char	*temp;
	int		ret;
	
	temp = ft_strtrim(file, " ");
	ret = right_redirect(temp);
	free(temp);
	return(ret);
}
