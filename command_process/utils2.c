/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:04:13 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 16:38:14 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strchr2(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((char)c == s[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_exist_file(char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	return (1);
}

int	open_file(char *path)
{
	int	fd = 0;

	if (!path)
		return (-1);
	if (!is_exist_file(path))
		fd = open(path, O_RDWR | O_CREAT);
	else
		fd = open(path, O_WRONLY | O_APPEND);
	if (fd < 0)
	{
		perror("");
		return (fd);
	}
	return (fd);
}

void	clear_file(char *path)
{
	int	fd;

	fd = open(path, O_TRUNC);
	if (fd < 0)
		perror("");
	close(fd);
}
