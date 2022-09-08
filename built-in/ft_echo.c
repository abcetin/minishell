/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:49:06 by acetin            #+#    #+#             */
/*   Updated: 2022/09/08 17:52:07 by mhaksal          ###   ########.fr       */
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
