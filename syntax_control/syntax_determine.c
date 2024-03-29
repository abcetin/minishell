/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_determine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <mhaksal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:11:27 by mhaksal           #+#    #+#             */
/*   Updated: 2022/09/10 13:13:15 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	determine_syntax(char *str, int i)
{
	if (str[i] == '<')
	{
		if (!check_right_r(i, str))
			return (exit_status(258 * 256, 0,
					"syntax error near unexpected token '<'\n"));
	}
	else if (str[i] == '>')
	{
		if (!check_right(i, str))
			return (exit_status(258 * 256, 0,
					"syntax error near unexpected token '>'\n"));
	}
	return (0);
}
