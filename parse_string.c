#include "minishell.h"

void set_funcs(t_functions *func)
{
	func[0] = (t_functions){{(void *)pwd}, "pwd"};
	func[1] = (t_functions){{(void *)cd}, "cd"};
	func[2] = (t_functions){{(void *)exit_f}, "exit"};
	func[3] = (t_functions){{(void *)env}, "env"};
	func[4] = (t_functions){{(void *)export}, "export"};
	func[5] = (t_functions){{(void *)unset}, "unset"};
	func[6] = (t_functions){{(void *)ls}, "ls"};
	func[7] = (t_functions){{(void *)ft_cat}, "cat"};
	func[8] = (t_functions){{(void *)ft_grep}, "grep"};
	func[9] = (t_functions){{(void *)ft_wc}, "wc"};
	func[10] = (t_functions){{(void *)ft_echo}, "echo"};
	func[11] = (t_functions){{NULL}, NULL};
}


static char *to_lower_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void	get_func(t_functions *function, t_cmd *cmd)
{
	int i;

	i = 0;
	while (function[i].arg != NULL)
	{
		if (ft_strstr(function[i].arg, to_lower_str(cmd->cmd)))
		{
			function[i].func.func_name(&cmd);
			return ;
		}
		i++;
	}
	printf("command '%s' not found\n", cmd->cmd);
}

void with_pipe(char *str)
{
	int count;
	char **cmd;
	int i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	cmd = ft_split(str, '|');
	ft_pipe(cmd, count);
	ft_free_str(cmd);
}

void semicolon(char *str)
{
	char **cmd;
	int i;

	cmd = ft_split(str, ';');
	i = 0;
	while (cmd[i])
	{
		parse_string(cmd[i]);
		i++;
	}
	ft_free_str(cmd);
}

void parse_string(char *str)
{
	char		**temp;
	t_cmd		cmd;
	t_functions	function[12];

	cmd.option = NULL;
	cmd.arg = NULL;
	if (!str)
	    return;
	set_funcs(function);
	if (ft_strchr(str, ';'))
		semicolon(str);
	else if (ft_strchr(str, '|'))
		with_pipe(str);
	else
	{
		temp = split2(str);
		cmd.cmd = temp[0];
		option(temp, &cmd);
		arg(temp, &cmd);
		get_func(function, &cmd);
		ft_free_str(cmd.arg);
		ft_free_str(cmd.option);
	}
}
