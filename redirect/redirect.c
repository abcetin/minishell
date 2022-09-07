/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:10:33 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 17:11:31 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int create_file(char **files, char **delimeter)
{
	int i;
	int fd;

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

int	choose_redirect(char **command, char **delimeter)
{
	int	i;
	int	j;
	int ret;

	i = -1;
	j = -1;
	while (delimeter[++j])
	{
		if (ft_strstr(delimeter[j], "<<")) // bu patladı bak
			ret = double_left_redirect(command[j]);
	}
	while (delimeter[++i])
	{
		if (j == i && delimeter[i + 1] != NULL)
			continue ;
		if (ft_strstr(delimeter[i], ">"))
			ret = single_right_redirect(command[i]);
		else if (ft_strstr(delimeter[i], ">>"))
			ret = double_right_redirect(command[i]);
		else if (ft_strstr(delimeter[i], "<"))
			ret = singel_left_redirect(command[i]);
	}
	return (ret);
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
		if (create_file(&tmp[1], delimeter) > 0 && choose_redirect(&tmp[1], delimeter) > 0)
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
