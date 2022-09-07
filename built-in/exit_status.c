/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:48:07 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 09:48:07 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_status(int status, int flag, char *message)
{
	static int	exit_status;

	if (flag == 1)
		printf("%d", exit_status);
	if (message)
		printf("%s", message);
	exit_status = status;
	return (exit_status);
}
