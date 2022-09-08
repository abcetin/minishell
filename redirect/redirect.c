/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:10:33 by acetin            #+#    #+#             */
/*   Updated: 2022/09/08 10:52:08 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_file(char **files, char **delimeter)
{
	int	i;
	int	fd;

	i = 0;
	while (files[i])
	{
		files[i] = ft_strtrim(files[i], " ");
		if (!is_exist_file(files[i]) && !ft_strchr(delimeter[i], '<'))
		{
			fd = open(files[i], O_CREAT, 0666);
			if (fd < 0)
			{
				perror("");
				return (fd);
			}
			close(fd);
		}
		i++;
	}
	return (1);
}

void	run_heredoc(char **command, char **delimeter)
{
	int	j;
	int	ret;
	int	pid;

	j = -1;
	ret = 1;
	while (delimeter[++j])
	{
		if (ft_strstr(delimeter[j], "<<"))
		{
			pid = fork();
			if (pid == 0)
			{
				if (double_left_redirect(command[j]) < 0)
					exit(1);
				exit(0);
			}
			waitpid(pid, &ret, 0);
		}
	}
	exit_status(ret, 0, NULL);
}

int	choose_redirect(char **files, char **delimeter)
{
	int	i;
	int	ret;

	i = -1;
	while (delimeter[++i])
	{
		if (ft_strstr(delimeter[i], ">"))
			ret = single_right_redirect(files[i]);
		else if (ft_strstr(delimeter[i], ">>"))
			ret = double_right_redirect(files[i]);
		else if (ft_strstr(delimeter[i], "<"))
			ret = singel_left_redirect(files[i]);
		else if (ft_strstr(delimeter[i], "<<"))
			singel_left_redirect("./redirect/heredoc");
	}
	return (ret);
}

int	redirect(char *cmd)
{
	char	**tmp;
	char	**delimeter;
	int		pid;

	tmp = redirect_split(cmd);
	tmp = join_redirect(tmp);
	delimeter = redirect_delimiter(cmd);
	pid = fork();
	if (pid == 0)
	{
		run_heredoc(&tmp[1], delimeter);
		if (create_file(&tmp[1], delimeter) > 0)
		{
			choose_redirect(&tmp[1], delimeter);
			parse_string(tmp[0]);
		}
		exit(0);
	}
	waitpid(pid, NULL, 0);
	ft_free_double(tmp);
	ft_free_double(delimeter);
	return (0);
}
