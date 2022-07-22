#include "minishell.h"

int ft_strstr(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] == s2[i])
        i++;
    if ((i - 1) == (int)ft_strlen(s1))
        return (1);
    return (0);
}