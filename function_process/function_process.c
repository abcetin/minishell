/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:04:53 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 12:13:17 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*to_lower_str(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	if (!str)
		return (str);
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	ret = ft_strdup(str);
	free(str);
	return (ret);
}

void	set_funcs(t_functions *func)
{
	func[0] = (t_functions){{(void *)pwd}, "pwd"};
	func[1] = (t_functions){{(void *)cd}, "cd"};
	func[2] = (t_functions){{(void *)exit_f}, "exit"};
	func[3] = (t_functions){{(void *)env}, "env"};
	func[4] = (t_functions){{(void *)export}, "export"};
	func[5] = (t_functions){{(void *)unset}, "unset"};
	func[6] = (t_functions){{(void *)ft_echo}, "echo"};
	func[7] = (t_functions){{NULL}, NULL};
}

void	get_func(t_cmd cmd)
{
	int			i;
	int			ret;
	char		*command;
	t_functions	function[8];

	i = 0;
	ret = 0;
	set_funcs(function);
	command = clear_char(to_lower_str(ft_strtrim(cmd.cmd, " ")),
			first_quote(cmd.cmd));
	while (function[i].arg != NULL)
	{
		if (ft_strstr(function[i].arg, command))
		{
			function[i].func.func_name(cmd);
			ret = 1;
			break ;
		}
		i++;
	}
	free(command);
	if (ret == 0)
		ft_execve(cmd);
}
