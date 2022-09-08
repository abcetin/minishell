/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:08:41 by acetin            #+#    #+#             */
/*   Updated: 2022/09/08 16:51:12 by acetin           ###   ########.fr       */
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
		exit_status(fd, 0, NULL);
		fd = open("./redirect/no_such_file", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		free(temp);
		return (-1);
	}
	free(temp);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (exit_status(fd, 0, NULL));
}

static char	*heredoc_promt(char *eof)
{
	char	*str;
	char	*input;

	str = NULL;
	input = NULL;
	while (1)
	{
		input = readline(">");
		if (ft_strstr(input, eof))
			break ;
		if (ft_strchr2(input, '$'))
			str = ft_strjoin(getenv(&input[1]), "\n");
		else
		{
			input = ft_strjoin2(input, "\n");
			str = ft_strjoin2(str, input);
		}
		free(input);
	}
	free(input);
	return (str);
}

int	double_left_redirect(char *eof)
{
	char	*str;
	int		fd;

	str = NULL;
	if (!eof || !ft_strlen(eof))
		return (exit_status(-1, 0, "asd error\n"));
	eof = ft_strtrim(eof, " ");
	fd = open_file("./redirect/heredoc");
	clear_file("./redirect/heredoc");
	str = heredoc_promt(eof);
	ft_putstr_fd(str, fd);
	close(fd);
	return (exit_status(fd, 0, NULL));
}
