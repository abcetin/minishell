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
		if (str[i] == first_quote(str))
			i += cut_str(&str[i], &ret[++ret_index], c);
		else if (str[i] != c && str[i] != 34 && str[i] != 39)
			i += cut_str(&str[i], &ret[++ret_index], c);
	}
	ret[++ret_index] = NULL;
	return (ret);
}

void option(char **str, t_cmd *cmd) // echo -a asdasd -a burda ikinci -a option değil ona kurgula
{
	int i;
	int count;

	i = 1;
	count = 0;
	while (str[i])
	{
		if (str[i][0] == '-')
			count++;
		i++;
	}
	if (count > 0)
	{
		cmd->option = (char **)malloc((count + 1) * sizeof(char *));
		i = 1;
		count = 0;
		while (str[i])
		{
			if (str[i][0] == '-')
				cmd->option[count++] = ft_strdup(str[i]);
			i++;
		}
		cmd->option[count] = NULL;
	}
}

void arg(char **str, t_cmd *cmd)
{
	int i;
	int count;

	i = 1;
	count = 0;
	while (str[i])
	{
		if (str[i][0] != '-')
			count++;
		i++;
	}
	if (count > 0)
	{
		cmd->arg = (char **)malloc((count + 1) * sizeof(char *));
		i = 1;
		count = 0;
		while (str[i])
		{
			if (str[i][0] != '-')
			{
				cmd->arg[count] = ft_strdup(str[i]);
				count++;
			}
			i++;
		}
		cmd->arg[count] = NULL;
	}
}