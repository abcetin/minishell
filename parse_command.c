#include "minishell.h"

static int count(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
				i++;
			j++;
		}
		if (str[i] && str[i] == 32 && str[i + 1] != 32)
			j++;
		if (str[i])
			i++;
	}
	return (j + 1);
}

int find_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char **split2(char *str)
{
	char **ret;
	int i;
	int start;
	int ret_index;

	start = 0;
	i = 0;
	ret_index = 0;
	ret = (char **)malloc((count(str)) * sizeof(char *) + 1);
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] && str[i] != 32)
		{
			i = find_char(&str[i], 32) + i;
			ret[ret_index] = ft_substr(str, start, i - start);
			ret_index++;
			start = ++i;
		}
		if (str[i] == 34)
			i = find_char(&str[i + 1], 34) + i + 1;
		if (str[i] == 32)
			start = ++i;
	}
	ret[ret_index] = NULL;
	return (ret);
}

void option(char **str, t_cmd *cmd)
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
		cmd->option = (char **)malloc((count * sizeof(char *)) + 1);
		i = 1;
		count = 0;
		while (str[i])
		{
			if (str[i][0] == '-')
			{
				cmd->option[count] = ft_strdup(str[i]);
				count++;
			}
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
	cmd->arg = (char **)malloc((count * sizeof(char *)) + 1);
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