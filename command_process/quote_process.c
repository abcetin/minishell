/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <mhaksal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:58:53 by acetin            #+#    #+#             */
/*   Updated: 2022/09/10 13:07:58 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dolar_sign(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (str[i + 1] == 32)
		return (-1);
	while (str[++i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			break ;
	}
	if (str[i] == '?')
		return (exit_status(i, 1, NULL) + 1);
	temp = ft_substr(str, 0, i);
	if (getenv(&temp[1]) == NULL)
		return (i);
	write(STDOUT_FILENO, getenv(&temp[1]), ft_strlen(getenv(&temp[1])));
	free(temp);
	return (i);
}

void	print_all(char *str, int quote)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strdup(str);
	temp = clear_char(temp, quote);
	while (temp[i] != '\0')
	{
		if (temp[i + 1] && temp[i] == '$'
			&& quote != 39 && temp[i + 1] != 32)
			i += dolar_sign(&temp[i]);
		else
		{
			write(STDOUT_FILENO, &temp[i], 1);
			i++;
		}
	}
	free(temp);
}
