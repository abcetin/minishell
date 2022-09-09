#include "../minishell.h"

int	determine_syntax(char *str, int i)
{
	if (str[i] == '<')
	{
		if (!check_right_r(i, str))
			return (exit_status(258 * 256, 0, "syntax error near unexpected token '<'\n"));
	}
	else if (str[i] == '>')
	{
		if (!check_right(i, str))
			return (exit_status(258 * 256, 0, "syntax error near unexpected token '>'\n"));
	}
	return (0);
}
