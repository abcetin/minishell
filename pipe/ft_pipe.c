/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:07:01 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 17:05:18 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	run(char **cmd, int count)
{
	int	**fd;
	int	*pid;
	int	i;

	pid = malloc(sizeof(int) * count + 1);
	i = -1;
	fd = ft_multiple_fd(count + 1);
	while (++i <= count)
	{
		pid[i] = ft_fork();
		if (pid[i] == 0)
		{
			if (i > 0)
				dup2(fd[i - 1][0], STDIN_FILENO);
			if (i != count)
				dup2(fd[i][1], STDOUT_FILENO);
			ft_multiple_close(fd, count + 1);
			parse_string(cmd[i]);
			exit(0);
		}
	}
	ft_multiple_close(fd, count + 1);
	multiple_waitpid(pid, count + 1);
	ft_free_int(fd, count + 1);
	free(pid);
}

void	ft_pipe(char **cmd, int count)
{
	if (ft_double_strlen(cmd) == 1)
		parse_string(cmd[0]);
	else
		run(cmd, count);
}
