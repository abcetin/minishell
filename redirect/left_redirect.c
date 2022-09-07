/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:08:41 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 16:27:04 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	singel_left_redirect(char *file)
{
	int		fd;
	char	*temp;
	
	temp = ft_strtrim(file, " ");
	fd = open(temp, O_RDWR);
	if (fd < 0)
	{
		perror(file);
		return (fd);
	}
	free(temp);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}

int	double_left_redirect(char *eof)
{
	char	*str;
	char	*input;
	int		fd;

	input = NULL;
	str = NULL;
	eof = ft_strtrim(eof, " ");
	fd = open_file("./redirect/heredoc");
	if (fd < 0)
		return (fd);
	clear_file("./redirect/heredoc");
	while (1)
	{
		input = readline(">");
		if (ft_strstr(input, eof))
			break ;
		input = ft_strjoin2(input, "\n");
		str = ft_strjoin2(str, input);
		free(input);
	}
	ft_putstr_fd(str, fd);
	close(fd);
	singel_left_redirect("./redirect/heredoc");
	return (fd);
}
