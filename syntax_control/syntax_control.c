/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:11:29 by mhaksal           #+#    #+#             */
/*   Updated: 2022/09/10 13:45:30 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Checks right of the array to determine '<' or '>' is wrong or not
@param position of < or >
@param string needed to be checked
@return 0 on err and 1 on no err
*/
int	check_right(int pos, char *str)
{
	int	len;

	len = ft_strlen(str);
	pos++;
	while (pos < len && (str[pos] <= 32 || str[pos] == '|'))
		pos++;
	if (pos < len)
		return (1);
	return (0);
}

/*
Checks right of the array to determine '<<'
@param position of <
@param string needed to be checked
@return 0 on err 1 on no err
*/
int	check_right_r(int pos, char *str)
{
	int	len;

	len = ft_strlen(str);
	pos++;
	while (pos < len && str[pos] <= 32)
		pos++;
	if (pos < len)
		return (1);
	return (0);
}

int	check_for_gr_le_signs(char *str, int len, int i)
{
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (i < len && str[i + 1] == '>')
			{
				i++;
				if (!check_right_r(i, str))
					return (exit_status(258 * 256, 0,
							"syntax error near unexpected token 'newline'\n"));
			}
			else if (i < len && str[i + 1] == '<')
			{
				if (str[i++] == '>')
					return (exit_status(258 * 256, 0,
							"syntax error near unexpected token '<'\n"));
				if (!check_right_r(i, str))
					return (exit_status(258 * 256, 0,
							"syntax error near unexpected token 'newline'\n"));
			}
			else if (determine_syntax(str, i))
				return (258 * 256);
		}
	}
	return (0);
}

int	check_for_pipe_syntax(char *str, int i)
{
	char	**cmd;
	int		count;
	char	*temp;

	count = char_count(str, '|');
	cmd = split2(str, '|');
	while (++i < count + 1)
	{
		temp = ft_strtrim(cmd[i], " ");
		if (!temp || !ft_strlen(temp))
		{
			exit_status(258 * 256, 0,
				"syntax error near unexpected token '|'\n");
			ft_free_double(cmd);
			return (1);
		}
		free(temp);
	}
	ft_free_double(cmd);
	return (0);
}

int	check_syntax(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(str);
	if (check_for_gr_le_signs(str, len, i))
		return (1);
	else if (char_count(str, '|') && check_for_pipe_syntax(str, i))
		return (1);
	return (0);
}
