/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:52:49 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 10:50:10 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_f(t_cmd cmd)
{
	if (cmd.command)
	{
		exit_status(256, 0, "too many arguments\n");
		return ;
	}
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
