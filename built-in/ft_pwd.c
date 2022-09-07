/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:53:01 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 10:50:27 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_cmd cmd)
{
	char	*cwd;

	cwd = NULL;
	if (cmd.command)
	{
		exit_status(256, 0, "too many arguments\n");
		return ;
	}
	cwd = getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	free(cwd);
}
