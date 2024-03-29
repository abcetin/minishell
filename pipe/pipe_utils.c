/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <mhaksal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:06:21 by mhaksal           #+#    #+#             */
/*   Updated: 2022/09/10 13:06:31 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_multiple_close(int **fd, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (j == 2)
		{
			j = 0;
			i++;
			if (i == len)
				break ;
		}
		if (close(fd[i][j]) < 0)
			perror("close ");
		j++;
	}
}

int	**ft_multiple_fd(int count)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * count + 1);
	while (i <= count)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			printf("error memory allocation\n");
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (i <= count)
	{
		if (pipe(fd[i]) < 0)
			perror("pipe ");
		i++;
	}
	return (fd);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("pid ");
		return (-1);
	}
	return (pid);
}

void	multiple_waitpid(int *pid, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}
