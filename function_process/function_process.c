#include "../minishell.h"

static char *to_lower_str(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (str);
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}


void set_funcs(t_functions *func)
{
	func[0] = (t_functions){{(void *)pwd}, "pwd"};
	func[1] = (t_functions){{(void *)cd}, "cd"};
	func[2] = (t_functions){{(void *)exit_f}, "exit"};
	func[3] = (t_functions){{(void *)env}, "env"};
	func[4] = (t_functions){{(void *)export}, "export"};
	func[5] = (t_functions){{(void *)unset}, "unset"};
	//func[6] = (t_functions){{(void *)ls}, "ls"};
	//func[6] = (t_functions){{(void *)ft_cat}, "cat"};
	//func[8] = (t_functions){{(void *)ft_grep}, "grep"};
	//func[9] = (t_functions){{(void *)ft_wc}, "wc"};
	func[6] = (t_functions){{(void *)ft_echo}, "echo"};
	func[7] = (t_functions){{NULL}, NULL};
}

void get_func(t_cmd *cmd)
{
	int i;
	int ret;
	t_functions function[12];

	i = 0;
	ret = 0;
	set_funcs(function);
	while (function[i].arg != NULL)
	{
		if (ft_strstr(function[i].arg, to_lower_str(cmd->cmd)))
		{
			function[i].func.func_name(&cmd);
			ret = 1;
			return;
		}
		i++;
	}
	if (ret == 0)
	{
		if (ft_execve(&cmd) < 0)
			printf("command '%s' not found\n", cmd->cmd);
	}
}