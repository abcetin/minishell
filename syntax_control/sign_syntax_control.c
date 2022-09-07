#include "../minishell.h"

/*
Checks right of the array to determine '<' or '>' is wrong or not
@param position of < or >
@param string needed to be checked
@return 0 on err and 1 on no err
*/
int check_right(int pos, char *str)
{
    int len;

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
int check_right_r(int pos, char *str)
{
    int len;

    len = ft_strlen(str);
    pos++;
    while (pos < len && str[pos] <= 32)
        pos++;
    if (pos < len)
        return (1);
    return (0);
}

int check_syntax(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(str);
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
            if (i < len && str[i + 1] == '>')
            {
                i++;
                if (!check_right(i, str))
                    return (exit_status(258 * 256, 0, "syntax error near unexpected token 'newline'\n"));
            }
            else if (i < len && str[i + 1] == '<')
            {
                if (str[i] == '>')
                    return (exit_status(258 * 256, 0, "syntax error near unexpected token '<'\n"));
                i++;
                if (!check_right(i, str))
                    return (exit_status(258 * 256, 0, "syntax error near unexpected token 'newline'\n"));
            }
            else if (!check_right(i, str))
            {
                if (!check_right_r(i, str))
                    return (exit_status(258 * 256, 0, "syntax error near unexpected token 'newline'\n"));
            }
		}
	}
    return (0);
}
