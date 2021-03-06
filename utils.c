#include "minishell.h"

char *ft_read(int fd)
{
	char *str;
	char *buff;

	buff = (char *)ft_calloc(1, 2);
	if (!buff)
		return (NULL);
	str = NULL;
	while (read(fd, buff, 1) > 0)
		str = ft_strjoin2(str, buff);
	free(buff);
	return (str);
}

char    *ft_strjoin2(char *s1, char *s2)
{
    char    *str;
    int     i;
    int     j;

    i = -1;
    j = 0;
    if (!s1)
        s1 = (char *)ft_calloc(sizeof(char), 1);
    if (!s2)
        return (NULL);
    str = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!str)
        return (NULL);
    while(s1[++i] != '\0')
        str[i] = s1[i];
    while(s2[j] != '\0')
        str[i++] = s2[j++];
    str[i] = '\0';
    return (str);
}