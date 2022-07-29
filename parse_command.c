#include "minishell.h"

static int count(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == 34 || str[i] == 39 || str[i] == 32)
			i++;
		if (str[i])
			j++;
		while (str[i] && str[i] != 34 &&
			str[i] != 39 && str[i] != 32)
			i++;
	}
	return (j);
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
	int j;
	int ret_index;

	i = 0;
	j = -1;
	ret_index = 0;
	ret = (char **)malloc((count(str) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (++j < count(str))
	{
		while(str[i] == 32)
			i++;
		if (i == first_index(str) && first_index(str) != 0)
		{	
			ret[ret_index] = ft_substr(str, first_index(str),
				(last_index(str) - first_index(str) + 1));
			i = last_index(str) + 1;
			ret_index++;
		}
		if (str[i] && str[i] != 32)
		{
			ret[ret_index] = ft_substr(str, i, find_char(&str[i], 32));
			i += find_char(&str[i], 32);
			ret_index++;
		}
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