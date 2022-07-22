#include "minishell.h"

static int wc_m(char *str)
{
    return(ft_strlen(str));
}

static int wc_l(char *str)
{
    int i;
    int ret;

    i = 0;
    ret = 0;
    while (str[i])
	{
		if (str[i] == '\n')
			ret++;
		i++;
	}
    return (ret);
}

void ft_wc(char **cmd)
{
	int ret;
	char *str;

	ret = 0;
	str = ft_read(STDIN_FILENO);
	if (cmd[1] && ft_strstr(cmd[1], "-l"))
        ret = wc_l(str);
    if (cmd[1] && ft_strstr(cmd[1], "-m"))
        ret = wc_m(str);
    free(str);
    printf("%d\n",ret);
}


