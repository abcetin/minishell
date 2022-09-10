/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <mhaksal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:10:13 by mhaksal           #+#    #+#             */
/*   Updated: 2022/09/10 13:10:15 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(char *arg)
{
	char	**temp;
	char	*temp2;

	temp2 = NULL;
	temp = environ;
	if (where_env(arg) < 0)
		return ;
	while (*environ != NULL)
	{
		if (!where_env(arg))
			break ;
		environ++;
	}
	while (*environ != NULL)
	{
		if (*environ)
			*environ = *(environ + 1);
		environ++;
	}
	environ = temp;
}
