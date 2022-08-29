#include "../minishell.h"

int word_count(char *str, char c)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && !quote_state(str, i))
			ret++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (ret);
}

int cut_str(char *dst, char **src, char c)
{
	int i;

	i = 0;
	while (dst[i])
	{
		if (dst[i] == c && !quote_state(dst, i))
			break;
		i++;
	}
	*src = ft_substr(dst, 0, i);
	return (i);
}

char **split2(char *str, char c)
{
	int i;
	int len;
	char **ret;
	int ret_index;

	len = -1;
	ret_index = -1;
	i = 0;
	ret = malloc(sizeof(char *) * (word_count(str, c) + 1));
	while (++len < word_count(str, c))
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] == 34 || str[i] == 39)
			i += cut_str(&str[i], &ret[++ret_index], c);
		else if (str[i] != c)
			i += cut_str(&str[i], &ret[++ret_index], c);
	}
	ret[++ret_index] = NULL;
	return (ret);
}

void	add_to_list(char **temp, t_list **cmd)
{
	int i;

	i = 1;
	while (temp[i])
		ft_lstadd_back(cmd, ft_lstnew(temp[i++]));	
}