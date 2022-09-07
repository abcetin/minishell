/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:57:34 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 09:58:50 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_state(char *str, int pos)
{
	int	ret;
	int	i;
	int	quote;

	ret = 0;
	i = 0;
	quote = 0;
	while (str[i] && i < pos)
	{
		if (str[i] == 34 || str[i] == 39)
			quote = str[i];
		if (quote == str[i] && ret == 0)
			ret = 1;
		else if (quote == str[i] && ret == 1)
			ret = 0;
		i++;
	}
	return (ret);
}

int	first_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39))
			return (str[i]);
		i++;
	}
	return (0);
}

int	char_count(char *str, char c)
{
	int	i;
	int	ret;

	if (!str)
		return (0);
	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == c)
			ret++;
		i++;
	}
	return (ret);
}

char	*clear_quote(char *str)
{
	int		i;
	int		j;
	char	*ret;
	int		len;
	int		quote_len;

	quote_len = char_count(str, 34) + char_count(str, 39);
	len = ft_strlen(str);
	ret = (char *)ft_calloc(sizeof(char), (len - quote_len) + 1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == first_quote(str))
			continue ;
		else
			ret[j++] = str[i];
	}
	free(str);
	return (ret);
}