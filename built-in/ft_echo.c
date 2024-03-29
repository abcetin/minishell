/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:49:06 by acetin            #+#    #+#             */
/*   Updated: 2022/09/09 16:35:59 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(t_list **lst)
{
	if (ft_strstr("-n", (*lst)->content))
	{
		lst_find(lst, "-n");
		return (1);
	}
	else
		return (0);
}

void	ft_echo(t_cmd cmd)
{
	int	new_line;
	int	quote;

	if (cmd.command)
		new_line = check_option(&cmd.command);
	if (!cmd.command)
	{
		exit_status(0, 0, "\n");
		return ;
	}
	while (cmd.command)
	{
		quote = first_quote(cmd.command->content);
		print_all(cmd.command->content, quote);
		if (cmd.command->next != NULL)
			write(STDOUT_FILENO, " ", 1);
		cmd.command = cmd.command->next;
	}
	if (new_line == 0)
		exit_status(0, 0, "\n");
}
