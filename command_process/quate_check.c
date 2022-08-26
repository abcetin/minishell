#include "../minishell.h"

int	quote_state(char *str, int pos)
{
	int ret;
	int i;

	ret = 0;
	i = 0;
	while (str[i] && i < pos)
	{
		if (first_quote(str) == str[i] && ret == 0)
			ret = 1;
		else if (first_quote(str) == str[i] && ret == 1)
			ret = 0;
		i++;
	}
	return(ret);
}

int first_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39))
			return (str[i]);
		i++;
	}
	return (0);
}

// int first_quote_index(char *str)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != 32 && str[i - 1] == 32)
// 			j = i;
// 		if (str[i] == 34 || str[i] == 39)
// 			return (j);
// 		i++;
// 	}
// 	if (i == (int)ft_strlen(str))
// 		return (0);
// 	return (j);
// }

// int	last_quote_index(char *str)
// {
// 	int i;
// 	int ret;

// 	i = ft_strlen(str) - 1;
// 	ret = i;
// 	while (i >= 0)
// 	{
// 		if (str[i] != 32 && str[i + 1] == 32)
// 			ret = i;
// 		if (str[i] == 34 || str[i] == 39)
// 			return (ret);
// 		i--;
// 	}
// 	return (ret);
// }

int char_count(char *str, char c)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == c)
			ret++;
		i++;
	}
	return (ret);
}

char *clear_quote(char *str)
{
	int i;
	int j;
	char *ret;
	int len;
	int quote_len;

	quote_len = char_count(str, 34) + char_count(str, 39);
	len = ft_strlen(str);
	ret = (char *)ft_calloc(sizeof(char), (len - quote_len) + 1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == first_quote(str) && ft_strchr(&str[i], first_quote(str)))
			continue;
		else
			ret[j++] = str[i];
	}
	return (ret);
}