/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:11:33 by acetin            #+#    #+#             */
/*   Updated: 2022/09/09 17:16:40 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rl_gets(char *str, const char *prompt)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	str = readline(prompt);
	if (str && *str)
		add_history(str);
	return (str);
}



void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
}

void	heredoc(char *cmd)
{
	char	**tmp;
	char	**delimeter;

	if (!ft_strchr2(cmd, '<') && !ft_strchr2(cmd, '>'))
		return ;
	tmp = redirect_split(cmd);
	tmp = join_redirect(tmp);
	delimeter = redirect_delimiter(cmd);
	run_heredoc(&tmp[1], delimeter);
	ft_free_double(tmp);
	ft_free_double(delimeter);
}


void	loop(void)
{
	char	*input;
	char	*user;

	signal(SIGINT, &handler);
	input = NULL;
	user = ft_strjoin("\033[0;36m", getenv("LOGNAME"));
	user = ft_strjoin2(user, " %\e[0m ");
	while (1)
	{
		input = rl_gets(input, user);
		if (!input)
		{
			write(2, "exit\n", 6);
			exit(0);
		}
		else if (check_syntax(input))
			continue ;
		heredoc(input);
		parse_string(input);
	}
}

int	main(void)
{
	//loop();
	parse_string("unset asd");
}
