#include "../minishell.h"

char *sequence(char *str) // bunu kontrol et
{
	char **temp;
	char *ret;
	int i;

	i = 0;
	ret = NULL;
	temp = ft_split(str, '/');
	while (temp[i])
	{
		if (temp[i][0] == '$')
		{
			temp[i] = getenv(&temp[i][1]);
			if (!temp[i])
			{
				perror("");
				return (NULL);
			}
		}
		ret = ft_strjoin2(ret, temp[i]);
		if (temp[i + 1])
			ret = ft_strjoin2(ret, "/");
		i++;
	}
	return (ret);
}

int ft_isspace(char str)
{
	if (str == 32)
		return (1);
	else if (str == '\t')
		return (1);
	return (0);
}

// int ft_doublestrchr(char **str, char c)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (ft_strchr(str[i], c) && ft_strlen(str[i]) == 1)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void ft_free_str(char **str)
{
	int i;

	i = 0;
	if (!str)
		return;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void ft_free_cmd(t_cmd *cmd)
{
	ft_free_str(cmd->arg);
	ft_free_str(cmd->option);
	free(cmd->cmd);
}

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

char *ft_strjoin2(char *s1, char *s2)
{
	char *str;
	int i;
	int j;

	i = -1;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		s1 = (char *)ft_calloc(sizeof(char), 1);
	str = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}