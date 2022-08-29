#include "../minishell.h"

static char *to_lower_str(char *str)
{
	int i;
	char *ret;

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


void set_funcs(t_functions *func)
{
	func[0] = (t_functions){{(void *)pwd}, "pwd"};
	func[1] = (t_functions){{(void *)cd}, "cd"};
	func[2] = (t_functions){{(void *)exit_f}, "exit"};
	func[3] = (t_functions){{(void *)env}, "env"};
	func[4] = (t_functions){{(void *)export}, "export"};
	//func[5] = (t_functions){{(void *)unset}, "unset"};
	func[5] = (t_functions){{(void *)ft_echo}, "echo"};
	func[6] = (t_functions){{NULL}, NULL};
}

void get_func(t_cmd *cmd)
{
	int i;
	int ret;
	t_functions function[7];

	i = 0;
	ret = 0;
	set_funcs(function);
	cmd->cmd = to_lower_str(cmd->cmd);
	while (function[i].arg != NULL)
	{
		if (ft_strstr(function[i].arg, cmd->cmd))
		{
			function[i].func.func_name(cmd);
			ret = 1;
			return;
		}
		i++;
	}
	if (ret == 0)
	{
		if (ft_execve(cmd) < 0)
			printf("command '%s' not found\n", cmd->command->content);
	}
}