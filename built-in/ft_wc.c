#include "../minishell.h"

static int wc_m(char *str)
{
	return (ft_strlen(str));
}

static int wc_l(char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			ret++;
		i++;
	}
	return (ret);
}

void ft_wc(t_cmd **cmd)
{
	int ret;
	char *str;

	ret = 0;
	str = ft_read(STDIN_FILENO);
	if ((*cmd)->option[0] && ft_strnstr((*cmd)->option[0], "-l", ft_strlen((*cmd)->option[0])))
		ret = wc_l(str);
	else if ((*cmd)->option[0] && ft_strnstr((*cmd)->option[0], "-m", ft_strlen((*cmd)->option[0])))
		ret = wc_m(str);
	free(str);
	write(STDOUT_FILENO, ft_itoa(ret), ft_strlen(ft_itoa(ret)));
	write(STDOUT_FILENO, "\n", 1);
}
