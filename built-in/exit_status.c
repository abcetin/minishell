/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:48:07 by acetin            #+#    #+#             */
/*   Updated: 2022/09/09 16:36:43 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_status(int status, int flag, char *message)
{
	static int	ret;
	char		*ret2;

	ret2 = NULL;
	if (flag == 1)
	{
		ret2 = ft_itoa(ret / 256);
		write(STDOUT_FILENO, ret2, ft_strlen(ret2));
		free(ret2);
	}
	if (message)
		printf("%s", message);
	ret = status;
	return (ret);
}
